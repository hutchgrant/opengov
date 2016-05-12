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

#include "cfgobj.h"


/*
 * Constructor
 */
cfgObj::cfgObj()
{
    initFile(10);
}

/*
 *  Copy Constructor
 */
cfgObj::cfgObj(const cfgObj &src){

    if(src.colSize > 0){
        initColNamePos(src.colSize);
        for(int i=0; i< src.colSize; i++){
            setColNamePos(i, src.colName[i], src.colPos[i]);
        }
        colInitSize = src.colInitSize;
        countColumn = src.countColumn;
        countColumnPos = src.countColumnPos;
        countColumnFlag = src.countColumnFlag;
        ignoreColumn = src.ignoreColumn;
        ignoreText = src.ignoreText;
        ignoreRow = src.ignoreRow;
        dataURL = src.dataURL;
        dataName = src.dataName;
        listName = src.listName;
    }
}

/*
 *  Initialize Object
 */
void cfgObj::initFile(int initLineSz){
    colSize = 0;
    colInitSize = 0;
    countColumn = 0;
    countColumnPos = 0;
    countColumnFlag = false;
    ignoreColumn = 0;
    ignoreText = "";
    ignoreRow = false;
    dataURL = "";
    dataName = "";
    listName = "";
    initColNamePos(initLineSz);
}

/*
 *  Reinitialize Object
 */
void cfgObj::REinitFile(int newsize){

    string *colCopy;
    int *colPosCopy;
    colCopy = new string[colSize];
    colPosCopy = new int[colSize];
    for(int i=0; i<colSize; i++){
        colCopy[i] = "-";
        colPosCopy[i] = 0;
    }
    for(int i=0; i<colSize; i++){
        colCopy[i] = colName[i];
        colPosCopy[i] = colPos[i];
    }

    initColNamePos(colSize + newsize);

    for(int i =0; i<colSize; i++){
        colName[i] = colCopy[i];
        colPos[i] = colPosCopy[i];
    }
}

/*
 *  Display all var
 */
void cfgObj::display(){
    cout << "dataName: "<<dataName.toStdString() << endl;
    cout << "listName: "<< listName.toStdString() <<endl;
    cout << "colSize: " << colSize << endl;
    cout << "column names: "<<endl;
    for(int i=0; i<colSize; i++){
        cout << i << " colPos " << colPos[i] << " colName: " <<colName[i] << endl;
    }
}

/*
 *  Object copy operator
 */
cfgObj& cfgObj::operator=(const cfgObj& src){

    if(this != &src){
        if(src.colSize > 0){
            initColNamePos(src.colSize);
            for(int i=0; i< src.colSize; i++){
                setColNamePos(i, src.colName[i], src.colPos[i]);
            }
            countColumn = src.countColumn;
            countColumnPos = src.countColumnPos;
            countColumnFlag = src.countColumnFlag;
            ignoreColumn = src.ignoreColumn;
            ignoreText = src.ignoreText;
            ignoreRow = src.ignoreRow;
            dataURL = src.dataURL;
            dataName = src.dataName;
            listName = src.listName;
        }
    }
    return *this;
}

/*
 *  Destructor
 */
cfgObj::~cfgObj(){
}
