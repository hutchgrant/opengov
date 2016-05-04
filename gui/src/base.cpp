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
#include "base.h"
#include "ui_base.h"

/*
 * Constructor
 */
base::base(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::base)
{
    ui->setupUi(this);

    init();
    addWidgets();
    addConnections();
}

/*
 * (re)Initialize
 */
void base::init(){
    runCount = 0;
    search = "";
    verboseOut = "verbose.txt";
    jsonDefault = "data.json";
    cfgChoice = 0;
    parse.setPaths(verboseOut, jsonDefault);
}

/*
 *  Initialize and add each widget to its corresponding layout
 */
void base::addWidgets(){
   display = new jsonDisplay(this);
   opt = new options(this);
   expDg = new exportDialog(this);

   ui->jsondisplay_layout->addWidget(display, 0 ,0);
   ui->options_layout->addWidget(opt, 0 ,0);
   ui->menubar->show();

    resetJsonPath(jsonDefault);

    opt->setCfgList(parse.getCfgList(), parse.getCfgListSize());
}

/*
 * Initialize Connections
 */
void base::addConnections(){
    connect(&parse,SIGNAL(error(int)), this, SLOT(error(int)));
    connect(opt,SIGNAL(btnSearchClick(QString)), this, SLOT(getSearch(QString)));
    connect(ui->actionExport_JSON_Path, SIGNAL(triggered()), this, SLOT(showExport()));
    connect(expDg, SIGNAL(pathChanged(QString)), this, SLOT(resetJsonPath(QString)));
    connect(opt, SIGNAL(cfgChoiceChange(int)), this, SLOT(setCfgChoice(int)));
}

/*
 *  Query grep, read verbose + parse, write json file
 */
bool base::extract(QString input){
    parse.selectCfg(cfgChoice);
    if(parse.download()){
        if(parse.query(runCount, input)){
            if(parse.readFile()){
                display->setView(1,parse.verbData);
                if(parse.writeFile()){
                    display->setView(0, parse.jData);
                    opt->setResults(parse.getQTotal(), parse.counter);
                    runCount++;
                    return true;
                }
            }
         }
     }
     return false;
}

/*
 * Destructor
 */
base::~base()
{
    delete ui;
    delete display;
    delete opt;
}
