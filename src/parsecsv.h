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
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <src/fileobj.h>

using namespace std;
class parseCSV
{
public:
    int counter;
    int runCount;
    int total;
    QString qTotal;
    string query;
    QString filename;

    parseCSV();
    void init(int rCount, string qry);
    bool readFile(QString input);
    bool writeFile(QString stream);
    bool endJSON();
    void parse(QString line);
    void printFile();

    void setSearch(string search){
        query = search;
    }

private:
    fileObj entry;
};

#endif // PARSECSV_H
