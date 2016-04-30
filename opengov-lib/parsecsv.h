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

using namespace std;
class parseCSV
{
public:
    int counter;
    int runCount;
    long total;
    QString qTotal;
    string search;
    QString filename;
    QString csv;
    QString verboseOut;

    parseCSV();
    void init(int rCount, string qry);
    bool download();
    bool query(int count, QString qSearch);
    bool readFile(QString output);
    bool writeFile(QString stream);
    bool endJSON();
    void parse(QString line);
    void printFile();
private:
    fileObj entry;
};

#endif // PARSECSV_H
