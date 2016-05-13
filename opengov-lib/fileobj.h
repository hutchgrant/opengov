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

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <QObject>
#include <QDebug>
#include <cfgobj.h>

using namespace std;
class fileObj : public QObject
{
    Q_OBJECT
public:
    string **columns;       // all lines + columns
    int objSize;            // Actual number of Items/lines
    int InitSize;           // Amt of lines before reallocate
    int colSize;            // Actual number of columns per line
    int colInitSize;        // Amt of columns per line before allocate
    long total;             // Total from column with $Count param
    QString title;          // Title(from search input)
    QString qTotal;         // String with commas of total from column with $Count param

    explicit fileObj();
    fileObj(const fileObj& src);
    fileObj& operator=(const fileObj& src);
    fileObj* operator=(const fileObj* src);

    void initFile(int initLineSz, int initColSz);
    void REinitFile(int newsize);
    void display();
    QString convertToJSON(int runCount, bool append, cfgObj *cObj);

    virtual ~fileObj();

public slots:

    void reInitCols(int row, int col){
        objSize = 0;
        InitSize = 0;
        colInitSize = 0;
        qTotal = "";
        colSize = col;
        delete columns;
        setInit(row,col);
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

    void setCol(int line, int col, string someStr){
        if(col >= 0 && col <= colInitSize && line >=0 && line <=objSize){
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
    int getColSize(){
        return colSize;
    }
    int getObjSize(){
        return objSize;
    }
    string getColumn(int line, int colPos){
        if(line <= objSize && colPos <= colSize){
            return columns[line][colPos];
        }
        return "";
    }
    string *getLine(int line){
        return columns[line];
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
