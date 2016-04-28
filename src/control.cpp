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
#include "control.h"

/*
 *  Constructor
 */
control::control()
{
    runCount = 0;
    csv = "https://www.ontario.ca/sites/default/files/opendata/pa_volume_3_0.csv";
}

/*
 * Download the government's opendata using wget
 */
bool control::manageInstall(){
    QTextStream sin(stdin);
    QTextStream sout(stdout);
    QString qInstall = "";
    QProcess process;
    bool retval = false;
    QByteArray buffer;

    sout << "Install 2014-2015 data? <y/n>" << endl;
    qInstall = sin.readLine();
    if(qInstall == "y"){
       sout << "downloading..." << endl;
       process.start("wget "+ csv);
       process.waitForFinished();
       sout << "data installed" << endl;
       process.close();
     }
     return true;
}

/*
 *  Input Query for government data
 *  Grep all data for lines containing query
 *  export to file, parse file
 */
bool control::manageQueries(){

    QTextStream sin(stdin);
    QTextStream sout(stdout);
    QString qSearch = "", qFind = "";
    QProcess process;
    bool retval= false;
    QByteArray buffer;

    sout << "Enter a string to search:" << endl;
    qSearch = sin.readLine();
    parse.init(runCount, qSearch.toStdString());

    qFind = "bash -c \"grep -i '"+qSearch+"' pa_volume_3_0.csv " +"> verbose.txt\"";
    process.start(qFind);
    process.waitForFinished();
    sout << "data installed" << endl;
    process.close();

    if(parse.readFile("verbose.txt")){
        qDebug() << "done" << endl;
    }
    runCount++;
}

/*
 *  Manage the program menu
 *  End JSON writing, just before program exits
 */
bool control::manageLoop(){
    QTextStream sin(stdin);
    QTextStream sout(stdout);
    QString qInput = "";
    sout << "Continue searching? <y/n>" << endl;
    qInput = sin.readLine();

    if(qInput == "y"){
        return false;
    }else{
        parse.endJSON();
        sout << "goodbye" <<endl;
        return true;
    }
}
