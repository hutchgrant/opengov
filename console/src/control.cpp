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
}

/*
 * Download the government's opendata using wget
 */
bool control::manageInstall(){
    QTextStream sin(stdin);
    QTextStream sout(stdout);
    QString qInstall = "";

    sout << "Install 2014-2015 data? <y/n>" << endl;
    qInstall = sin.readLine();
    if(qInstall == "y"){
       sout << "downloading..." << endl;
       if(parse.download()){
        sout << "data installed" << endl;
       }
     }
     return true;
}

/*
 *  Input Query for government data
 *  Grep all data for lines containing query
 *  export to file, parse file
 */
bool control::manageQueries(string outputPath){

    QTextStream sin(stdin);
    QTextStream sout(stdout);
    QString qSearch = "";

    sout << "Enter a string to search:" << endl;
    qSearch = sin.readLine();

    if(parse.query(runCount, qSearch)){
        sout << "data extracted from budget" << endl;
    }
    if(parse.readFile(QString(outputPath.c_str()))){
        sout << "data successfully exported to JSON" << endl;
    }
    runCount++;
    return true;
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
