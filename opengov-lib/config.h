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

#define CFGSIZE 10
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <fileobj.h>

using namespace std;
class config
{
public:
    QString cfgPath;
    QString *cfgList;
    int cfgAmt, cfgLineCount, cfgColCount;

    config();
    void initCfgList();
    bool readCfgList();
    bool readCfg(int pos, fileObj *obj);
    void parseCfg(QString line, fileObj *obj);
    virtual ~config();

    QString *getCfgList(){
        return cfgList;
    }
    int getCfgListSize(){
        return cfgAmt;
    }
};

#endif // CONFIG_H
