/*
 *  Written By: Grant Hutchinson
 *  License: GPLv3.
 *  h.g.utchinson@gmail.com
 *  Copyright (C) 2016 by Grant Hutchinson
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fileobj.h"


/*
 * Constructor
 */
fileObj::fileObj()
{
    school = "";
    provTotal = 0;
    objSize = 0;
    InitSize = INITSIZE;
    initFile(INITSIZE);
}

/*
 *  Copy Constructor
 */
fileObj::fileObj(const fileObj &src){

    if(src.objSize > 0){
        initFile(src.objSize);
        for(int i=0; i< src.objSize; i++){
            set(i,src.institution[i].c_str(), src.amt[i].c_str(), src.reason[i].c_str());
        }
        objSize = src.objSize;
        InitSize = src.InitSize;
    }
}

/*
 *  Initialize Object
 */
void fileObj::initFile(int initSZ){
    if(objSize > 0){
        delete [] institution;
        delete [] amt;
        delete [] reason;
    }

    objSize = 0;
    InitSize = 0;
    institution = new string[initSZ];
    amt = new string[initSZ];
    reason = new string[initSZ];
    for(int i=0; i< initSZ; i++){
        setInit(i, "-", "-", "-");
    }
}

/*
 *  Reinitialize Object
 */
void fileObj::REinitFile(int oldsize, int newsize){
    //set the new initialize size
    InitSize = oldsize+newsize;
    int tempObjSize = 0;
    string *instCopy, *amtCopy, *reasonCopy;

    instCopy = new string[objSize+1];
    amtCopy = new string[objSize+1];
    reasonCopy = new string[objSize+1];

    for(int i=0; i< objSize; i++){
        instCopy[i] = "-";
        amtCopy[i] = "-";
        reasonCopy[i] = "-";
    }

    for(int i=0; i< objSize; i++){
        instCopy[i] = institution[i];
        amtCopy[i] = amt[i];
        reasonCopy[i] = reason[i];
    }
    tempObjSize = objSize;
    initFile(InitSize);
    /// refill array fileName fileID filePar array

    for(int i=0; i< tempObjSize; i++){
        set(i,instCopy[i].c_str(), amtCopy[i].c_str(), reasonCopy[i].c_str());
    }
    delete [] amtCopy;
    delete [] reasonCopy;
    delete [] instCopy;
}

/*
 *  Destructor
 */
fileObj::~fileObj(){
    delete [] amt;
    delete [] institution;
    delete [] reason;
}

/*
 *  Display all var
 */
void fileObj::display(){
    cout << "obj size is " << objSize << endl;
    for(int i=0; i< objSize; i++){
        cout << " Num: " << i
             << " Institution: " << getInst(i)
             <<  " Amount: " << getAmt(i)
            <<  " Reason: " << getReason(i) << endl;
    }
}

/*
 * Display JSON
 */
QString fileObj::covertToJSON(int runCount){
    QString qSchool = "", qTotal = "", totalForm = "", amtWcomma = "", qOpen="";
    string jAmt = "", jInstitution = "", jReason = "";
    std::stringstream stream;

    // format total
    qTotal= QString::number(provTotal);
    totalForm = qTotal.insert(qTotal.length()-3, ",");
    totalForm = totalForm.insert(qTotal.length()-7, ",");
    if(qTotal.length() > 10){
        totalForm = totalForm.insert(qTotal.length()-10, ",");
    }
    qTotal = "\"provTotal\":\""+ totalForm+"\", ";

    // format school
    qSchool = "\"title\":\""+QString(school.c_str())+"\", ";
    if(runCount == 0){
        qOpen = "{";
    }else{
        qOpen = ",{";
    }
    stream << qOpen.toStdString().c_str() << qSchool.toStdString().c_str() <<  qTotal.toStdString().c_str()<< endl;

    stream <<  "\"funding\":["<< endl;
    // format funding data
    for(int i=0; i< objSize; i++){

        jInstitution = "{\"ministry\":\""+QString(getInst(i)).toStdString()+"\", ";
        jReason = "\"reason\":\""+QString(getReason(i)).toStdString()+"\", ";

        // remove $, leave commas
        amtWcomma = QString(getAmt(i)).replace(QString("$"), QString(""));

        if(i == objSize-1){
            jAmt = "\"amt\":"+amtWcomma.toStdString()+"}";
        }else{
            jAmt = "\"amt\":"+amtWcomma.toStdString()+"},";
        }
        stream << jInstitution.c_str() << jReason.c_str() << jAmt.c_str()<< endl;
    }
    stream << "]}" << endl;
    return QString(stream.str().c_str());
}


/*
 *  Object copy operator
 */
fileObj& fileObj::operator=(const fileObj& src){

    if(this != &src){
        if(src.objSize > 0){
            initFile(src.objSize);

            for(int i=0; i< src.objSize; i++){
                set(i,src.institution[i].c_str(), src.amt[i].c_str(), src.reason[i].c_str());
            }
            objSize = src.objSize;
            InitSize = src.InitSize;
        }
    }
    return *this;
}

