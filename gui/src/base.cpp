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
    verboseOut = "verbose.csv";
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
   detach = new detached();

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
    connect(&parse,SIGNAL(downloadStarted(QString, bool, bool)), this, SLOT(setStatusBar(QString, bool, bool)));
    connect(&parse,SIGNAL(downloadFinished(QString, bool, bool)), this, SLOT(setStatusBar(QString, bool, bool)));

    connect(opt,SIGNAL(btnSearchClick(QString, bool)), this, SLOT(getSearch(QString, bool)));
    connect(ui->actionExport_JSON_Path, SIGNAL(triggered()), this, SLOT(showExport()));
    connect(expDg, SIGNAL(pathChanged(QString)), this, SLOT(resetJsonPath(QString)));
    connect(opt, SIGNAL(cfgChoiceChange(int)), this, SLOT(setCfgChoice(int)));
}

/*
 *  Query grep, read verbose + parse, write json file
 */
bool base::extract(QString input, bool append){
     if(parse.selectCfg(cfgChoice)){
        setStatusBar(input, true, false);
        if(parse.query(runCount, input)){
            parse.setAppend(append);
           if(parse.readFile()){
                if(parse.writeFile()){
                    display->setView(parse.jData,parse.verbData);
                    setStatusBar("", true, true);
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
 * Fill the status bar
 */
void base::setStatusBar(QString name, bool query, bool finished){
    if(!query && !finished){
        ui->statusbar->showMessage("Downloading: "+name);
    }else if(query && !finished){
        ui->statusbar->showMessage("Querying");
    }else{
        ui->statusbar->showMessage("OpenGov");
    }
}

/*
 * Open html5 view
 */
void base::openWebView(){
    detach->setOrientation(Html5ApplicationViewer::ScreenOrientationLockLandscape);
    QSize screenSz = QSize(1024,570);
    detach->showNormal();
    detach->setMinimumSize(screenSz);
    detach->loadFile("gui/res/html/index.html");
}

/*
 * Destructor
 */
base::~base()
{
    delete ui;
    delete display;
    delete opt;
    delete expDg;
    delete detach;
}
