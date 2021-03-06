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
#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QDir>
#include <QDirIterator>
#include <fileobj.h>
#include <cfgobj.h>

using namespace std;
class config
{
public:
    QString cfgPath;
    QString *cfgList;
    int cfgAmt, cfgRowCount, initSize;

    config();
    void initCfgList();
    void reInitCfgList(int newsize);
    bool readCfgList();
    bool readCfg(int pos, cfgObj *obj);
    void parseCfg(QString line, cfgObj *obj);
    virtual ~config();
    void setCfg(QString path){
        if(cfgAmt >= initSize-1){
            reInitCfgList(cfgAmt+10);
        }
        cfgList[cfgAmt] = path;
        cfgAmt++;
    }

    QString *getCfgList(){
        return cfgList;
    }
    int getCfgListSize(){
        return cfgAmt;
    }
};

#endif // CONFIG_H
