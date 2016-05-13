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
#include "config.h"

config::config()
{
    cfgAmt = 0;
    initCfgList();
}

/*
 *  Initialize
 */
void config::initCfgList(){
    if(cfgAmt > 0){
        delete cfgList;
    }
    cfgPath = "config";
    cfgRowCount = 0;
    cfgList = new QString[10];
    for(int i=0; i<10; i++){
        cfgList[i] = "-";
    }
}

/*
 *  Read and list all cfg files in config directory
 */
bool config::readCfgList(){
    cfgPath = QDir::currentPath() + "/config/";
    QDirIterator directories(cfgPath,  QDir::Files);

    while(directories.hasNext()){
        directories.next();
        cfgList[cfgAmt] = directories.fileName();
        cfgAmt++;
    }
    return true;
}

/*
 *  read config file
 */
bool config::readCfg(int pos,cfgObj *obj){
    cfgRowCount = 0;
    obj->initFile(10);
    QFile file("./config/"+cfgList[pos]);
    if(file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
            parseCfg(in.readLine(), obj);
       }
       file.close();
       return true;
    }
    return false;
}

/*
 *  Parse config file
 */
void config::parseCfg(QString line, cfgObj *obj){
    QString firstCol = line.section(' ', 0, 0);
    QString secCol = line.section(' ', 1, 1);
    QString thirdCol = line.section(' ', 2, 2);
    QString fourthCol = line.section(' ', 3, 3);
    if(secCol.indexOf("\"")==0){
        secCol = line.section(("\""), 1,1);
    }
    if(thirdCol.indexOf("\"")==0){
        thirdCol = line.section(("\""), 1,1);
    }
    if(fourthCol.indexOf("\"")==0){
        fourthCol = line.section(("\""), 1,1);
    }


    if(firstCol == "list"){
        obj->setListName(secCol);
    }else if(firstCol == "col"){
        if(thirdCol == "$IGNORE"){
            obj->setIgnoreRow(secCol.toInt()-1, fourthCol.toStdString());
        }else{
            obj->setColNamePos(cfgRowCount, thirdCol.toStdString(), secCol.toInt()-1);
            if(fourthCol == "$COUNT"){
                obj->setCountingColumn(cfgRowCount, secCol.toInt()-1);
            }
            cfgRowCount++;
        }
    }else if(firstCol == "name"){
        obj->setName(secCol);
    }else if(firstCol == "url"){
        obj->setURL(secCol);
    }
}
/*
 *  destructor
 */
config::~config(){
}
