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
    cfg.readCfgList();
    jData = "";
    verbData = "";
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
    appendDoc = true;
}

/*
 * Choose a cfg, read the cfg, initialize parse paths
 */
bool parseCSV::selectCfg(int choice){
    cfg.readCfg(choice, &cObj);
    csv = cObj.getURL();
    csvPath = csv.mid(csv.lastIndexOf("/")+1, csv.size());
    if(!download()){
        return false;
    }
    entry.reInitCols(10,cObj.getColSize());
    return true;
}

/*
 * Download CSV using wget
 */
bool parseCSV::download(){
    if(!QFile(csvPath).exists()){
        if(!startProcess("wget "+csv)){
            emit error(6);
            return false;
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
    QString line = "";
    bool colDefaultLine = false;
    if(!appendDoc || runCount == 0){
        verbData = "";
        jData = "";
    }else{
        verbData.append("\n");
    }

    QFile inputFile(verboseOut);
    if(inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
            line = in.readLine();
            verbData.append(line.toStdString().c_str()).append("\n");
            if(search == "" && !colDefaultLine){
                colDefaultLine = true;
            }else{
                parse(line);
            }
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
 *  Organize formatted JSON data to text file
 */
bool parseCSV::writeFile(){
    QString data = "";
    data = entry.convertToJSON(runCount, appendDoc, &cObj);

    QFile file(jsonOut);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate )) {
        QTextStream stream(&file);
        if(!appendDoc || runCount == 0){
             jData.append("["+data+"\n]");
        }else{
            jData.chop(1);
            jData.append("\n"+data+"\n]");
        }
        stream << jData <<endl;
        file.close();
        return true;
    }
    return false;
}

/*
 *  Parse data, seperate the necessary columns into variables, pre-formatting
 *  calculate the total of all financial figures found
 */
void parseCSV::parse(QString line){
    int count = 0, x = 0;
    int skipColumn = 0, originalSkip = 0;
    bool skipFlag = false, ignoreFlag = false;
    QString amtWComma = "",  column = "";
    QString *cols;
    int approxSize = line.count(",");
    cols = new QString[cObj.colSize];
    for(int i=0; i<cObj.colSize; i++){
        cols[i] = "";
    }
    for(int i=0; i<=approxSize; i++){
        skipFlag = false;
        skipColumn = 0;
        column = line.section(",",i,i);

        // use as index for skipping to correct correct line section(after quotes)
        if(column.indexOf("\"") == 0){
            if(!column.endsWith("\"")){
                count = 0;
                while(!column.endsWith("\"")){
                    column = line.section(",",i,i+count);
                    count++;
                }
                skipColumn = count-1;
                skipFlag = true;
            }
        }
        if(i==cObj.getColPos(x)+originalSkip){
            cols[x] = line.section(",",i,i);
            // ignoreFlag Column condition
            if(cObj.getIgnoreText() == cols[x].toStdString().c_str()){
                if( cObj.getIgnoreRow() && cObj.getIgnoreColumn() == cObj.getColPos(x)+originalSkip){
                    ignoreFlag = true;
                }
            }else{
                // quotes found in column condition
                if(cols[x].indexOf("\"") == 0){
                    if(!cols[x].endsWith("\"")){
                        count = 0;
                        while(!cols[x].endsWith("\"")){
                            cols[x] = line.section(",",i,i+count);
                            count++;
                        }
                    }
                    cols[x].replace("\"", "");
                }
                // $COUNT column condition. if flagged, calculate total of all of these columns, format total and amounts
                if(cObj.getCountColumnFlag() && x == cObj.getCountColumnPos() && !ignoreFlag){
                    cols[x].replace("$", "");
                    amtWComma = cols[x];
                    amtWComma.replace(",", "");
                    total += amtWComma.toLong();
                }
            }
            x++;
        }
        if(skipFlag){
            i+=skipColumn;
            originalSkip += skipColumn;
        }
    }
    if(!ignoreFlag){
        entry.setLine(counter, x, cols);
        counter++;
    }
}

/*
 *  Run bash process
 */
bool parseCSV::startProcess(QString bash){
    errorFound = false;
    process = new QProcess(this);
    connect(process,SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));

    process->start(bash);
    process->waitForFinished();
    process->close();
    delete process;
    if(errorFound){
        return false;
    }
    return true;
}

parseCSV::~parseCSV(){
}
