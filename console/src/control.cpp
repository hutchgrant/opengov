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
control::control(QString jPath)
{
    runCount = 0;
    verboseOut = "verbose.csv";
    jsonDefault = "data.json";
    cfgChoice = 0;

    if(!jPath.isEmpty()){
        jsonOut = jPath;
    }else{
        jsonOut = jsonDefault;
    }
    parse.setPaths(verboseOut, jsonOut);
    connect(&parse,SIGNAL(error(int)), this, SLOT(error(int)));
}

/*
 * Download the government's opendata using wget
 */
bool control::manageInstall(){
    QTextStream sin(stdin);
    QString qInstall = "";

    cout << "Welcome to OpenGov" << endl;
    cout << "Select a Data Set for querying and extraction:" << endl;
    printCfgList();

    cout << "enter dataset index number: ";
    cfgChoice = sin.readLine().toInt();
    parse.selectCfg(cfgChoice);
    cout << "Install data from "<< parse.getDataName().toStdString().c_str()<<" <y/n>" << endl;
    qInstall = sin.readLine();
    if(qInstall == "y"){
       cout << "Downloading..." << endl;
       if(parse.download()){
         cout << "Data installed" << endl;
         return true;
       }else{
         return false;
       }
    }else{
        return true;
    }
}

/*
 *  Input Query for government data
 *  Grep all data for lines containing query
 *  export to file, parse file
 */
bool control::manageQueries(){
    QTextStream sin(stdin);
    QTextStream sout(stdout);
    QString qSearch = "";

    sout << "Enter a string to search:" << endl;
    qSearch = sin.readLine();

    parse.selectCfg(cfgChoice);
    if(parse.query(runCount, qSearch)){
        sout << "data extracted from budget" << endl;
        if(parse.readFile()){
            if(parse.writeFile()){
                sout << "data successfully exported to JSON" << endl;
                if(jsonOut == jsonDefault){
                    sout << "JSON File exported to: " << QDir::currentPath() << "/" << jsonDefault << endl;
                }else{
                    sout << "JSON File exported to: " << jsonOut << endl;
                }
                runCount++;
                return true;
            }
        }
    }
    return false;
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
        sout << "goodbye" <<endl;
        return true;
    }
}

/*
 *  Output the Config file list
 */
void control::printCfgList(){
    int cfgSize = parse.getCfgListSize();
    QString *cfg;
    cfg = new QString[cfgSize];
    cfg = parse.getCfgList();
    cout<< "\tIndex\t" << "|" << "\tData Set"<<endl;
    cout<<"---------------------------------" <<endl;
    for(int i=0; i<cfgSize; i++){
       cout<< "\t"<< i << "\t|\t" << cfg[i].toStdString() << endl;
    }
}

control::~control(){

}
