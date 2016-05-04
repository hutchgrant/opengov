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
    readCfg();
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
    jData = "";
    verbData = "";
}

void parseCSV::selectCfg(int choice){
    entry.initFile(10,INITCOLSIZE);
    cfg.readCfg(choice, &entry);
    csv = entry.getURL();
    csvPath = csv.mid(csv.lastIndexOf("/")+1, csv.size());
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
    int colSize = entry.getColSize();
    verbData = "";
    QString line = "";
    QFile inputFile(verboseOut);
    if(inputFile.open(QIODevice::ReadOnly))
    {
       if(runCount != 0){
           verbData.insert(0, "\n");
       }
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
            line = in.readLine();
            verbData.append(line.toStdString().c_str()).append("\n");
            parse(line, colSize);
       }
       inputFile.close();
    }else{
        emit error(8);
        return false;
    }

    entry.setTotal(total);
    entry.setTitle(QString(search.c_str()));
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
 *  Parse data, seperate the necessary columns into variables, pre-formatting
 *  calculate the total of all financial figures found
 */
void parseCSV::parse(QString line, int colSize){
    int commaAmt = 0;
    QString amtWComma = "";
    QString *cols;
    cols = new QString[colSize];
    for(int i=0; i<colSize; i++){
        cols[i] = "";
    }
    for(int i=0; i<colSize; i++){
        cols[i] = line.section(",",entry.getColPos(i)+commaAmt,entry.getColPos(i)+commaAmt);
        if(cols[i].indexOf("\"") == 0){
            if(!cols[i].endsWith("\"")){
                int count = 0;
                while(!cols[i].endsWith("\"")){
                    cols[i] = line.section(",",entry.getColPos(i)+commaAmt,entry.getColPos(i)+commaAmt+count);
                    count++;
                }
                commaAmt += cols[i].count(",");
                cols[i].replace("\"", "");
            }
        }
        if(i == entry.getCountColumnPos()){
            cols[i].replace("$", "");
            amtWComma = cols[i];
            amtWComma.replace(",", "");
            total += amtWComma.toLong();
        }
    }
    entry.setLine(counter, colSize, cols);
    delete [] cols;
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
