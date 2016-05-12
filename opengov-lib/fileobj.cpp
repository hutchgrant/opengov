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

    total = 0;
    objSize = 0;
    colSize = 0;
    initFile(3, 10);
}

/*
 *  Copy Constructor
 */
fileObj::fileObj(const fileObj &src){

    if(src.objSize > 0){
        initFile(src.InitSize, src.colInitSize);
        for(int i=0; i< src.objSize; i++){
            setLine(i,src.colSize,src.columns[i]);
        }
        InitSize = src.InitSize;
        colInitSize = src.colInitSize;
        total = src.total;
        qTotal = src.qTotal;
    }
}

/*
 *  Initialize Object
 */
void fileObj::initFile(int initLineSz, int initColSz){
    if(objSize > 0){
        delete columns;
    }
    objSize = 0;
    colSize = 0;
    InitSize = 0;
    colInitSize = 0;
    qTotal = "";
    setInit(initLineSz, initColSz);
}

/*
 *  Reinitialize Object
 */
void fileObj::REinitFile(int newsize){
    int oldInitSize = InitSize;
    int oldColInitSize = colInitSize;

    string **colCopy;
    colCopy = new string*[objSize];
    for(int i=0; i<objSize; i++){
        colCopy[i] = new string[colSize];
        for(int x=0; x<colSize; x++){
            colCopy[i][x] = "-";
        }
    }
    for(int i=0; i<objSize; i++){
        for(int x=0; x<colSize; x++){
            colCopy[i][x] = columns[i][x];
        }
    }

    delete columns;
    InitSize = 0;
    colInitSize = 0;
    setInit(oldInitSize+newsize, oldColInitSize);

    for(int i =0; i<objSize; i++){
        for(int x=0; x<colSize; x++){
            columns[i][x] = colCopy[i][x];
        }
    }

    delete colCopy;
}

/*
 *  Destructor
 */
fileObj::~fileObj(){
    delete columns;
}

/*
 *  Display all var
 */
void fileObj::display(){
    cout << "colSize: " << colSize << endl;
    cout << "objSize: " << objSize << endl;
    for(int i=0; i< objSize; i++){
        cout << " line: " << i;
        for(int x=0; x<colSize; x++){
            cout << columns[i][x];
        }
        cout << endl;
    }
}

/*
 * Covert to JSON
 */
QString fileObj::convertToJSON(int runCount, bool append, cfgObj *cObj){
    QString jTotal = "", qTitle = "", qOpen="";
    stringstream stream;
    if(!title.isEmpty()){
        qTitle = "\"query\":\""+title+"\", ";
    }else{
        qTitle = "";
    }

    if(!append || runCount == 0){
        qOpen = "{";
    }else{
        qOpen = ",{";
    }

    if(cObj->getCountColumnFlag()){
        // format total
        qTotal= QString::number(total);
        qTotal = qTotal.insert(qTotal.length()-3, ",");
        if(qTotal.length() > 7){
            qTotal = qTotal.insert(qTotal.length()-7, ",");
        }
        if(qTotal.length() > 11){
            qTotal = qTotal.insert(qTotal.length()-11, ",");
        }
        jTotal = "\""+ QString(cObj->getColName(cObj->getCountColumnPos()).c_str()) + "\":\"" + qTotal + "\", ";
        qTotal.startsWith("$");
    }else{
        jTotal = "";
    }
    stream << qOpen.toStdString().c_str() << qTitle.toStdString().c_str() <<  jTotal.toStdString().c_str()<< endl;
    stream <<  "\""+cObj->getListName().toStdString()+"\":["<< endl;
    // format list data
    for(int i=0; i< objSize; i++){
        stream << "{";
        for(int x=0; x< colSize; x++){
            stream << "\""+cObj->getColName(x)+"\"" +":\""+columns[i][x]+"\"";
            if(x < colSize-1){
                stream << ", ";
            }
        }
        if(i == objSize-1){
            stream << "}" << endl;
        }else{
            stream << "}," << endl;
        }
    }
    stream << "]}";
    return QString(stream.str().c_str());
}


/*
 *  Object copy operator
 */
fileObj& fileObj::operator=(const fileObj& src){

    if(this != &src){
        if(src.objSize > 0){
            initFile(src.InitSize, src.colInitSize);
            for(int i=0; i< src.objSize; i++){
                setLine(i,src.colSize,src.columns[i]);
            }
            InitSize = src.InitSize;
            colInitSize = src.colInitSize;
            total = src.total;
            qTotal = src.qTotal;
        }
    }
    return *this;
}

