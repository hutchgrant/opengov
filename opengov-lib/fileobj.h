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

#ifndef FILEOBJ_H
#define FILEOBJ_H

#define INITSIZE 3
#define INITCOLSIZE 10
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <QObject>
#include <QDebug>

using namespace std;
class fileObj : public QObject
{
    Q_OBJECT
public:
    QString dataName, listName;  // titles of the overall data, list of data
    QString dataURL;        // URL for downloading data set
    string **columns;       // all lines + columns
    string *colName;        // all column names
    int objSize;            // Actual number of Items/lines
    int InitSize;           // Amt of lines before reallocate
    int colSize;            // Actual number of columns per line
    int colInitSize;        // Amt of columns per line before allocate
    int *colPos;            // Position of the preferred column in data
    int countColumn;        // Column position used to calculate total
    int countColumnPos;     // index position in colName array used to calculate total
    bool countColumnFlag;   // Flag that indicates whether a $COUNT is found in config
    int ignoreColumn;       // Column position used to ignore text
    bool ignoreRow;         // Flag that indicates whether a $IGNORE is found in config
    string ignoreText;      // Text found in column, to be used for ignoring a column
    long total;             // Total from column with $Count param
    QString title;          // Title(from search input)
    QString qTotal;         // String with commas of total from column with $Count param

    explicit fileObj();
    fileObj(const fileObj& src);
    fileObj& operator=(const fileObj& src);
    fileObj* operator=(const fileObj* src);

    void initFile(int initLineSz, int initColSz);
    void REinitFile(int newsize);

    virtual ~fileObj();
public slots:
    void display();
    QString convertToJSON(int runCount, bool append);
    void removeColumnsArr(int size){
        for(int i=0; i<size; i++){
            delete [] columns[i];
        }
        delete [] columns;
    }
    void removeColNamePos(){
        delete [] colName;
        delete [] colPos;
    }

    // re-initialize when array empty, without losing cfg changes
    void reInitNearEmpty(int row, int col){
        InitSize = 0;
        colInitSize = 0;
        removeColumnsArr(row);
        setInit(row,col);
        removeColNamePos();
        initColNamePos(col);
    }

    void setInit(int lines, int cols){
        columns = new string*[lines];
        for(int i = 0; i < lines; i++){
            columns[i] = new string[cols];
            for(int x=0; x<cols; x++){
                if(i == 0){
                    colInitSize++;
                }
                columns[i][x] = "-";
            }
            InitSize++;
        }
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
    }

    void setCol(int line, int col, string someStr){
        if(col >= 0 && col <= colSize && line >=0 && line <=objSize){
            columns[line][col] = someStr;
        }
    }
    void setLine(int line, int colCount, string *someStr){
        if(objSize >= InitSize-1){
            REinitFile(100);
        }
        for(int i=0; i< colCount; i++){
            setCol(line, i, someStr[i]);
        }
        objSize++;
    }
    void setLine(int line, int colCount, QString *someStr){
        if(objSize >= InitSize-1){
            REinitFile(100);
        }
        for(int i=0; i< colCount; i++){
            setCol(line, i, someStr[i].toStdString());
        }
        objSize++;
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
    int getObjSize(){
        return objSize;
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

    string getColumn(int line, int colPos){
        if(line <= objSize && colPos <= colSize){
            return columns[line][colPos];
        }
        return "";
    }
    string *getLine(int line){
        if(line <= objSize){
            return columns[line];
        }
    }
    void setTotal(long calc){
        total = calc;
    }

    void setTitle(QString name){
        title = name;
    }

    QString getQTotal(){
        return qTotal;
    }

};
#endif // FILEOBJ_H
