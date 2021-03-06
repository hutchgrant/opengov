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
#ifndef CONTROL_H
#define CONTROL_H

#include <QDebug>
#include <QTextStream>
#include <cstring>
#include <parsecsv.h>
#include <fileobj.h>

using namespace std;
class control: public QObject
{
    Q_OBJECT
public:
    parseCSV parse;
    int runCount;
    QString verboseOut;
    QString jsonOut;
    QString jsonDefault;
    fileObj obj;
    int cfgChoice;

    control(QString jPath);
    virtual ~control();
    bool manageInstall();
    bool manageQueries();
    bool manageLoop();
    void printCfgList();

public slots:
    void error(int errorCode){
        QTextStream sout(stdout);
        if(errorCode > 0 && errorCode <=5){
            sout << "Problem was encountered while performing a task." << endl;
        }else if(errorCode == 6){
            sout << "Error Installing Data. Check the data link and try again." << endl;
        }else if(errorCode == 7){
            sout << "Error querying data" << endl;
        }else if(errorCode == 8){
            sout << "Error reading verbose file" << endl;
        }else if(errorCode == 9){
            sout << "Error writing JSON file" << endl;
        }
    }
};

#endif // CONTROL_H
