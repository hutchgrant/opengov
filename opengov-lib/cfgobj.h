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

#ifndef cfgObj_H
#define cfgObj_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <QObject>
#include <QDebug>

using namespace std;
class cfgObj : public QObject
{
    Q_OBJECT
public:
    QString dataName, listName;  // titles of the overall data, list of data
    QString dataURL;        // URL for downloading data set
    string *colName;        // all column names
    int *colPos;            // Position of the preferred column in data
    int colSize;            // Actual number of columns per line
    int colInitSize;        // Amt of columns per line before allocate
    int countColumn;        // Column position used to calculate total
    int countColumnPos;     // index position in colName array used to calculate total
    bool countColumnFlag;   // Flag that indicates whether a $COUNT is found in config
    int ignoreColumn;       // Column position used to ignore text
    bool ignoreRow;         // Flag that indicates whether a $IGNORE is found in config
    string ignoreText;      // Text found in column, to be used for ignoring a column

    explicit cfgObj();
    cfgObj(const cfgObj& src);
    cfgObj& operator=(const cfgObj& src);
    cfgObj* operator=(const cfgObj* src);

    void initFile(int initLineSz);
    void REinitFile(int newsize);
    void display();
    virtual ~cfgObj();

public slots:
    void removeColNamePos(){
        delete colName;
        delete colPos;
    }

    void initColNamePos(int colSz){
        colName = new string[colSz];
        colPos = new int[colSz];
        for(int i=0; i<colSz; i++){
            colName[i] = "-";
        }
        for(int i=0; i<colSz; i++){
            colPos[i] = 0;
        }
        colInitSize = colSz;
    }

    void setColName(int col, string name){
        colName[col] = name;
    }
    string getColName(int col){
        return colName[col];
    }
    void setColPos(int col, int pos){
        colPos[col] = pos;
        colSize++;
    }
    void setColNamePos(int index, string name, int pos){
        if(colSize < colInitSize){
            setColName(index,  name);
            setColPos(index, pos);
        }else{
            REinitFile(colInitSize+10);
        }
    }

    int getColPos(int col){
        return colPos[col];
    }
    void setName(QString name){
        dataName = name;
    }
    QString getName(){
        return dataName;
    }
    void setURL(QString url){
        dataURL = url;
    }
    QString getURL(){
        return dataURL;
    }
    void setListName(QString name){
        listName = name;
    }
    QString getListName(){
        return listName;
    }
    int getColSize(){
        return colSize;
    }
    void setCountingColumn(int pos, int countCol){
        countColumn = countCol;
        countColumnPos = pos;
        countColumnFlag = true;
    }
    int getCountingColumn(){
        return countColumn;
    }
    int getCountColumnPos(){
        return countColumnPos;
    }
    bool getCountColumnFlag(){
        return countColumnFlag;
    }
    void setIgnoreRow(int countCol, string name){
        ignoreColumn = countCol;
        ignoreText = name;
        ignoreRow = true;
    }
    int getIgnoreColumn(){
        return ignoreColumn;
    }
    string getIgnoreText(){
        return ignoreText;
    }
    bool getIgnoreRow(){
        return ignoreRow;
    }
    void setIgnoreFlag(bool ignore){
        ignoreRow = ignore;
    }

};
#endif // cfgObj_H
