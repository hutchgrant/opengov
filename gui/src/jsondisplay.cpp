#include "jsondisplay.h"
#include "ui_jsondisplay.h"

jsonDisplay::jsonDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jsonDisplay)
{
    ui->setupUi(this);
}

void jsonDisplay::setView(int tab, QString data){

    if(tab == 0){
        ui->jsonView->clear();
        ui->jsonView->insertPlainText(data);
    }else{
        ui->csvView->insertPlainText(data);
    }
}

jsonDisplay::~jsonDisplay()
{
    delete ui;
}
