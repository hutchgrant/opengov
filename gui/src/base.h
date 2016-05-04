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
#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <src/jsondisplay.h>
#include <src/options.h>
#include <src/exportdialog.h>
#include <parsecsv.h>

namespace Ui {
class base;
}

class base : public QMainWindow
{
    Q_OBJECT

public:
    int runCount;
    QString search;
    QString verboseOut;
    QString jsonDefault;
    int cfgChoice;
    parseCSV parse;

    explicit base(QWidget *parent = 0);
    void addWidgets();
    void addConnections();
    void init();
    bool extract(QString input);
    virtual ~base();

private:
    Ui::base *ui;
    jsonDisplay * display;
    options *opt;
    exportDialog *expDg;

private slots:
    void getSearch(QString input){
         search = input;
         extract(input);
    }
    void showExport(){
        expDg->show();
    }
    void resetJsonPath(QString path){
        QString jPath = "", vPath = "";
        if(path == jsonDefault){
            jPath =  QDir::currentPath() + "/" + jsonDefault;
            vPath = QDir::currentPath() + "/" + verboseOut;
            display->setExportPath(jPath, vPath);
        }else{
            jsonDefault = path;
            parse.jsonOut = jsonDefault;
            vPath = QDir::currentPath() + "/" + verboseOut;
            display->setExportPath(jsonDefault, vPath);
        }
        parse.setPaths(verboseOut, jsonDefault);
    }

    void setCfgChoice(int choice){
        cfgChoice = choice;
    }

    void error(int errorCode){
    }
};

#endif // BASE_H
