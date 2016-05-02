#include "base.h"
#include "ui_base.h"

/*
 * Constructor
 */
base::base(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::base)
{
    ui->setupUi(this);

    addWidgets();
    connect(opt,SIGNAL(btnSearchClick(QString)), this, SLOT(getSearch(QString)));

    init();
}

/*
 * (re)Initialize
 */
void base::init(){
    runCount = 0;
    search = "";
    csv = "https://www.ontario.ca/sites/default/files/opendata/pa_volume_3_0.csv";
    csvPath = "pa_volume_3_0.csv";
    verboseOut = "verbose.txt";
    jsonDefault = "data.json";
    parse.setPaths(csv, csvPath, verboseOut, jsonDefault);
    connect(&parse,SIGNAL(error(int)), this, SLOT(error(int)));
}

/*
 *  Initialize and add each widget to its corresponding layout
 */
void base::addWidgets(){
   display = new jsonDisplay(this);
   opt = new options(this);

   ui->jsondisplay_layout->addWidget(display, 0 ,0);
   ui->options_layout->addWidget(opt, 0 ,0);
}

/*
 *  Query grep, read verbose + parse, write json file
 */
bool base::extract(QString input){
    if(parse.download()){
        if(parse.query(runCount, input)){
            display->setView(1,parse.verbData);
            if(parse.readFile()){
                if(parse.writeFile()){
                    display->setView(0, parse.jData);
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
