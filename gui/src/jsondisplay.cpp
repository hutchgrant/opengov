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
