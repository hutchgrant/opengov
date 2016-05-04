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
    countColumn = 0;
    countColumnPos = 0;
    total = 0;
    qTotal = "";
    dataURL = "";
    dataName = "";
    listName = "";
    objSize = 0;
    colSize = 0;
    initColNamePos(INITCOLSIZE);
    initFile(INITSIZE, INITCOLSIZE);
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
        for(int i=0; i< src.colSize; i++){
            setColName(i, src.colName[i]);
            setColPos(i, src.colPos[i]);
        }
        InitSize = src.InitSize;
        colInitSize = src.colInitSize;
        countColumn = src.countColumn;
        countColumnPos = src.countColumnPos;
        dataURL = src.dataURL;
        dataName = src.dataName;
        listName = src.listName;
        total = src.total;
        qTotal = src.qTotal;
    }
}

/*
 *  Initialize Object
 */
void fileObj::initFile(int initLineSz, int initColSz){
    if(objSize > 0){
        for(int i=0; i<objSize; i++){
            delete [] columns[i];
        }
        delete [] columns;
    }
    objSize = 0;
    colSize = 0;
    InitSize = 0;
    colInitSize = 0;
    setInit(initLineSz, initColSz);
}

/*
 *  Reinitialize Object
 */
void fileObj::REinitFile(int newsize){
    int oldInitSize = InitSize;
    int oldColInitSize = colInitSize;

    string **colCopy;
    colCopy = new string*[InitSize+newsize];
    for(int i=0; i<InitSize+newsize; i++){
        colCopy[i] = new string[colInitSize];
        for(int x=0; x<colInitSize; x++){
            colCopy[i][x] = "-";
        }
    }
    for(int i=0; i<objSize; i++){
        for(int x=0; x<colSize; x++){
            colCopy[i][x] = columns[i][x];
        }
    }

    for(int i=0; i<objSize; i++){
        delete [] columns[i];
    }
    delete [] columns;

    InitSize = 0;
    colInitSize = 0;
    setInit(oldInitSize+newsize, oldColInitSize);

    for(int i =0; i<oldInitSize; i++){
        for(int x=0; x<colInitSize; x++){
            columns[i][x] = colCopy[i][x];
        }
    }

    for(int i=0; i<oldInitSize; i++){
        delete [] colCopy[i];
    }
    delete [] colCopy;
}

/*
 *  Destructor
 */
fileObj::~fileObj(){
    for(int i=0; i<objSize; i++){
        delete [] columns[i];
    }
    delete [] columns;
    delete [] colName;
    delete [] colPos;
}

/*
 *  Display all var
 */
void fileObj::display(){
    cout << "dataName: "<<dataName.toStdString() << endl;
    cout << "listName: "<< listName.toStdString() <<endl;
    cout << "colSize: " << colSize << endl;
    cout << "objSize: " << objSize << endl;
    cout << "column names: "<<endl;
    for(int i=0; i<colSize; i++){
        cout << i << " colPos " << colPos[i] << " colName: " <<colName[i] << endl;
    }
    for(int i=0; i< objSize; i++){
        cout << " line: " << i;
        for(int x=0; x<colSize; x++){
            cout << " column: " << colName[x] << " ";
            cout << columns[i][x];
        }
        cout << endl;
    }
}

/*
 * Covert to JSON
 */
QString fileObj::covertToJSON(int runCount){
    QString jTotal = "", qTitle = "", qOpen="";
    stringstream stream;

    // format total
    qTotal= QString::number(total);
    qTotal = qTotal.insert(qTotal.length()-3, ",");
    qTotal = qTotal.insert(qTotal.length()-7, ",");
    if(qTotal.length() > 11){
        qTotal = qTotal.insert(qTotal.length()-11, ",");
    }
    jTotal = "\""+ QString(colName[countColumnPos].c_str()) + "\":\"" + qTotal + "\", ";
    qTotal.startsWith("$");

    qTitle = "\"query\":\""+title+"\", ";
    if(runCount == 0){
        qOpen = "{";
    }else{
        qOpen = ",{";
    }
    stream << qOpen.toStdString().c_str() << qTitle.toStdString().c_str() <<  jTotal.toStdString().c_str()<< endl;
    stream <<  "\""+listName.toStdString()+"\":["<< endl;

    // format list data
    for(int i=0; i< objSize; i++){
        stream << "{";
        for(int x=0; x< colSize; x++){
            if(x == colSize-1){
                stream << "\""+colName[x]+"\"" +":\""+columns[i][x]+"\"";
            }else{
                stream << "\""+colName[x]+"\"" +":\""+columns[i][x]+"\", ";
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
            for(int i=0; i< src.colSize; i++){
                setColName(i, src.colName[i]);
                setColPos(i, src.colPos[i]);
            }
            InitSize = src.InitSize;
            colInitSize = src.colInitSize;
            countColumn = src.countColumn;
            countColumnPos = src.countColumnPos;
            dataURL = src.dataURL;
            dataName = src.dataName;
            listName = src.listName;
            total = src.total;
            qTotal = src.qTotal;
        }
    }
    return *this;
}

