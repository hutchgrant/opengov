#include "jsondisplay.h"
#include "ui_jsondisplay.h"

jsonDisplay::jsonDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jsonDisplay)
{
    ui->setupUi(this);
}

void jsonDisplay::setView(QString data){
    ui->jsonView->clear();
    ui->jsonView->insertPlainText(data);
}

jsonDisplay::~jsonDisplay()
{
    delete ui;
}
