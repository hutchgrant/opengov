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
#include "parsecsv.h"

/*
 * Constructor
 */
parseCSV::parseCSV()
{
    init(0, "");
}

/*
 * (re)Initialize globals
 */
void parseCSV::init(int rCount, string qry){
    counter = 0;
    runCount = rCount;
    search = qry;
    total = 0;
    qTotal = "";
    errorFound = false;
    entry = fileObj();
    entry.initFile(100);
    jData = "";
    verbData = "";
}

/*
 * Download CSV using wget
 */
bool parseCSV::download(){

    if(!QFile(csvPath).exists()){
        if(startProcess("wget "+csv)){
            return true;
        }else{
           emit error(6);
        }
    }
    return true;
}

/*
 * Extract queried data, output to file, read from file
 */
bool parseCSV::query(int count, QString qSearch){
    QString qFind = "";

    init(count, qSearch.toStdString());

    qFind = "bash -c \"grep -i -a '"+ qSearch +"' "+ csvPath +" > " + verboseOut + "\"";
    if(QFile(csvPath).exists()){
        if(startProcess(qFind)){
            fillVerbData();
            return true;
        }
    }
    emit error(7);
    return false;
}

/*
 * read text file for grep'd data, send to parser
 */
bool parseCSV::readFile(){
    QFile inputFile(verboseOut);
    if(inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          parse(in.readLine());
       }
       inputFile.close();
    }else{
        emit error(8);
        return false;
    }

    entry.school = search;
    entry.provTotal = total;
    return true;
}

/*
 *  Write formatted JSON data to text file
 */
bool parseCSV::writeFile(){
    QString data = "";
    data = entry.covertToJSON(runCount);

    QFile file(jsonOut);
    if(file.exists() && runCount == 0){
        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate )) {
            QTextStream stream(&file);
            data.insert(0, "[");
            stream << data << endl << "]";
            file.close();
            readJsonFile();
            return true;
        }
    }else{
        if (file.open(QIODevice::ReadWrite )&& runCount == 0) {
            QTextStream stream(&file);
            data.insert(0, "[");
            stream << data << endl << "]";
            file.close();
            readJsonFile();
            return true;
       }else{
            if(file.exists() && runCount > 0){
                file.close();
                if(fillJsonData(data)){
                    return true;
                }
            }
        }
        emit error(9);
        return false;
    }
    return true;
}

/*
 * Fill previously written json data
 */
bool parseCSV::fillJsonData(QString data){
    int streamSize = readJsonFile();
    QFile file(jsonOut);
    if (file.open(QIODevice::ReadWrite )) {
        QTextStream stream(&file);
        QStringList row;
        int count = 0;
        bool end = false;

        while (!stream.atEnd() && !end)
        {
            if(count == streamSize-1){
                row.append("");
                count++;
                end = true;
            }else if(count < streamSize-1){
                row.append(stream.readLine().toStdString().c_str());
                count++;
            }
        }
        file.close();
        if(appendJson(row, data)){
            readJsonFile();
            return true;
        }
    }
    return false;
}

/*
 *  Read JsonFile, count lines, fill global jsonData string
 */
int parseCSV::readJsonFile(){
    int count = 0;
    jData = "";
    QFile file(jsonOut);
    if(file.open(QIODevice::ReadOnly))
    {
       QTextStream stream(&file);
       while (!stream.atEnd())
       {
          jData.append(stream.readLine().toStdString().c_str()).append("\n");
          count++;
       }
       file.close();
       return count;
    }
    return 0;
}

/*
 * append previous json file to a new json file (with ] removed )
 */
bool parseCSV::appendJson(QStringList row, QString data){
    QFile file(jsonOut);
    QTextStream stream(&file);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate )) {
        for(int i=0; i<row.size(); i++){
            stream << row[i] << endl;
        }
        stream << data << endl << "]"<< endl;
        file.close();
        return true;
    }else{
        return false;
    }
}

/*
 * Fill verbose csv data from txt
 */
bool parseCSV::fillVerbData(){
    verbData = "";
    QFile file(verboseOut);
    if(file.open(QIODevice::ReadOnly))
    {
       QTextStream stream(&file);
       while (!stream.atEnd())
       {
          verbData.append(stream.readLine().toStdString().c_str()).append("\n");
       }
       file.close();
       return true;
    }
    return 0;
}

/*
 *  Parse data, seperate the necessary columns into variables, pre-formatting
 *  calculate the total of all financial figures found
 */
void parseCSV::parse(QString line){

    QString amtClean = "";
    string amt = "", reason = "", institution = "";
    if(line.section(',', 0, 0).indexOf("\"") == 0){
        //  first column
        // their is an exception within some ministry titles, where some columns contain a comma, accompanied by a quote,
        institution = line.section(',', 0, 0).replace(QString("\""),QString("")).toStdString();
        if(line.section(',', 2, 2).indexOf("\"") == 0){
             //third column; same exception
            if(line.section(',', 4, 4).indexOf("\"") == 0){
                //fifth column; same exception
                reason = line.section(',', 4, 5).toStdString();
                amt = line.section(',', 14, 15).toStdString();
            }else{
                reason = line.section(',', 4, 4).toStdString();
                amt = line.section(',', 13, 15).toStdString();
            }
        }else{
            reason = line.section(',', 3, 3).toStdString();
            amt = line.section(',', 12, 15).toStdString();
        }
        // format for integer conversion, add for total, remove quotes and $
        amtClean = QString(amt.substr(2, amt.length()-3).c_str()).replace(QString(","), QString(""));
        total += amtClean.toLong();
    }else{
        institution = line.section(',', 0, 0).toStdString();
            if(line.section(',', 2, 2).indexOf("\"") == 0){
                 //third column; same exception
                if(line.section(',', 4, 4).indexOf("\"") == 0){
                     //fifth column; same exception
                    reason = line.section(',', 4, 5).toStdString();
                    amt = line.section(',', 13, 16).toStdString();
                }else{
                    reason = line.section(',', 4, 4).toStdString();
                    amt = line.section(',', 13, 15).toStdString();
                }
            }else{
                if(line.section(',', 4, 4).indexOf("\"") == 0){
                    // if quotes found in the fifth column; same exception
                    reason = line.section(',', 2, 2).toStdString();
                    amt = line.section(',', 13, 16).toStdString();
                }else{
                    reason = line.section(',', 2, 2).toStdString();
                    amt = line.section(',', 11, 15).toStdString();
                }
            }
        // format for integer conversion, add for total
        amtClean = QString(amt.substr(2, amt.length()-3).c_str()).replace(QString(","), QString(""));
        total += amtClean.toLong();
    }
    entry.set(counter, institution.c_str(), amt.c_str(), reason.c_str());
    counter++;
}

bool parseCSV::startProcess(QString bash){
    errorFound = false;
    process = new QProcess(this);
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));

    process->start(bash);
    process->waitForFinished();
    process->close();
    if(errorFound){
        return false;
    }
    return true;
}

parseCSV::~parseCSV(){
}
