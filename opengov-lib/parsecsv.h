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
#ifndef PARSECSV_H
#define PARSECSV_H
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fileobj.h>
#include <config.h>

using namespace std;
class parseCSV : public QObject
{
    Q_OBJECT
public:
    int counter;            // Parse Line Counter
    int runCount;           // Overall Count of times run
    int colSize;            // Total default columns in first row
    long total;             // Total of $COUNT column
    QString qTotal;         // formatted total of $COUNT column
    string search;          // search query
    QString csv;            // csv data url
    QString csvPath;        // path to downloaded csv file
    QString verboseOut;     // path to verbose csv file containing results from searched query
    QString jsonOut;        // path to json file for output of parsed data
    QString jData;          // data read from json file
    QString verbData;       // data read from verbose csv file
    bool errorFound;        // Flag that an error was discovered

    parseCSV();
    virtual ~parseCSV();
    void init(int rCount, int colSz,string qry);
    void selectCfg(int choice);
    bool download();
    bool query(int count, QString qSearch);
    bool readColumns();
    bool readFile();
    bool fillJsonData(QString data);
    int  readJsonFile();
    bool appendJson(QStringList row, QString data);
    bool writeFile();
    void parse(QString line);
    void printFile();
    bool startProcess(QString bash);
    void setPaths(QString verb, QString jOut){
        verboseOut = verb;
        jsonOut = jOut;
    }
    void readCfg(){
        cfg.readCfgList();
    }

    QString *getCfgList(){
        return cfg.getCfgList();
    }
    int getCfgListSize(){
        return cfg.getCfgListSize();
    }

    QString getDataName(){
        return entry.getName();
    }
    QString getQTotal(){
        return entry.getQTotal();
    }

public slots:
    /*
     * Signal Error Codes:
     *  1 - 5 == process crash/error
     *  6 Download data error
     *  7 grep data error
     *  8 read verbose data error
     *  9 write json data error
     */
    void finished(int errorCode, QProcess::ExitStatus){
        if(errorCode > 0){
            errorFound = true;
            emit error(errorCode);
        }
    }
signals:
    void error(int);

private:
    fileObj entry;
    config cfg;
    QProcess *process;
};
#endif // PARSECSV_H
