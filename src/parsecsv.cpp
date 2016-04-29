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
    filename = "";
    init(0, "");
}

/*
 * (re)Initialize globals
 */
void parseCSV::init(int rCount, string qry){
    counter = 0;
    runCount = rCount;
    query = qry;
    total = 0;
    qTotal = "";
    entry = fileObj();
    entry.initFile(100);
}

/*
 * read text file for grep'd data, send to parser
 */
bool parseCSV::readFile(QString input, QString output){
    filename = output;

    QFile inputFile(input);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          parse(in.readLine());
       }
       inputFile.close();
    }

    entry.school = query;
    entry.provTotal = total;

    if(writeFile(entry.covertToJSON(runCount))){
        return true;
    }
}

/*
 *  Write formatted JSON data to text file
 */
bool parseCSV::writeFile(QString data){
    QFile file(filename);
    if(file.exists() && runCount == 0){
        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate )) {
            QTextStream stream(&file);
            data.insert(0, '[');
            stream << data << endl;
        }
    }else{
        if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
            QTextStream stream(&file);
            if(runCount == 0){
                data.insert(0, '[');
             }
                stream << data << endl;
        }
    }
    return true;
}

/*
 *  End formatting of JSON text file
 */
bool parseCSV::endJSON(){
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "]" << endl;
    }
    QTextStream sout(stdout);
    if(filename == "data.json"){
        sout << "JSON File exported to: " << QDir::currentPath() << "/data.json" << endl;
    }else{
        sout << "JSON File exported to: " << filename << endl;
    }
    return true;
}

/*
 *  Parse data, seperate the necessary columns into variables, pre-formatting
 *  calculate the total of all financial figures found
 */
void parseCSV::parse(QString line){

    QString amtClean = "";
    string amt = "", reason = "", institution = "";
    if(line.section(',', 0, 0).indexOf("\"") == 0){
        // if quote found at start of line, strange but some lines do
        // their is an exception within some ministry titles, where some columns contain a comma, accompanied by a quote,
        institution = line.section(',', 0, 0).replace(QString("\""),QString("")).toStdString();
        reason = line.section(',', 3, 3).toStdString();
        amt = line.section(',', 12, 15).toStdString();

        // format for integer conversion, add for total, remove quotes and $
        amtClean = QString(amt.substr(2, amt.length()-3).c_str()).replace(QString(","), QString(""));
        total += amtClean.toInt();
    }else{
        institution = line.section(',', 0, 0).toStdString();
        reason = line.section(',', 2, 2).toStdString();
        amt = line.section(',', 11, 15).toStdString();

        // format for integer conversion, add for total
        amtClean = QString(amt.substr(2, amt.length()-3).c_str()).replace(QString(","), QString(""));
        total += amtClean.toInt();
    }
    entry.set(counter, institution.c_str(), amt.c_str(), reason.c_str());
    counter++;
}
