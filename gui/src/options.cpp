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
#include "options.h"
#include "ui_options.h"

options::options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::options)
{
    ui->setupUi(this);
    appendDoc = true;
}

void options::on_btnSearch_clicked()
{
    emit btnSearchClick(ui->search->text(), appendDoc);
}

/*
 * Set text result displays
 */
void options::setResults(QString total, int resCount){
    ui->entryResults->setText(QString::number(resCount));
    if(!total.isEmpty()){
        ui->fundingTotal->setText("$"+total);
    }else{
        ui->fundingLayout->hide();
    }
}

/*
 * Set spinner list
 */
void options::setCfgList(QString *list, int listSize){
    for(int i =0; i< listSize; i++){
        ui->cfgListBox->addItem(list[i]);
    }
}

options::~options()
{
    delete ui;
}

void options::on_cfgListBox_currentIndexChanged(int index)
{
    emit cfgChoiceChange(index);
}

void options::on_checkBox_clicked()
{
    if(ui->checkBox->checkState()){
        appendDoc = true;
    }else{
        appendDoc = false;
    }
}
