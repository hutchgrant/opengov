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

options::~options()
{
    delete ui;
}
