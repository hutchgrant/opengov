#include "jsondisplay.h"
#include "ui_jsondisplay.h"

jsonDisplay::jsonDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jsonDisplay)
{
    ui->setupUi(this);
}

/*
 * Fill tabs with plain text data
 */
void jsonDisplay::setView(int tab, QString data){

    if(tab == 0){
        ui->jsonView->clear();
        ui->jsonView->insertPlainText(data);
    }else{
        ui->csvView->insertPlainText(data);
    }
}

/*
 *  Set tab export path
 */
void jsonDisplay::setExportPath(QString jPath, QString csvPath){
    ui->exportPath->setText(jPath);
    ui->exportPath_2->setText(csvPath);
}

jsonDisplay::~jsonDisplay()
{
    delete ui;
}
