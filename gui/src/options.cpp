#include "options.h"
#include "ui_options.h"

options::options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::options)
{
    ui->setupUi(this);
}

void options::on_btnSearch_clicked()
{
    emit btnSearchClick(ui->search->text());
}

/*
 * Set text result displays
 */
void options::setResults(QString total, int resCount){
    ui->entryResults->setText(QString::number(resCount));
    ui->fundingTotal->setText("$"+total);
}

options::~options()
{
    delete ui;
}
