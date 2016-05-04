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
#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class options;
}

class options : public QWidget
{
    Q_OBJECT

public:
    explicit options(QWidget *parent = 0);
    void setResults(QString total, int resCount);
    virtual ~options();
    void setCfgList(QString *list, int listSize);
private:
    Ui::options *ui;
    QString search;
private slots:
    void on_btnSearch_clicked();
    void on_cfgListBox_currentIndexChanged(int index);

signals:
    void btnSearchClick(QString);
    void cfgChoiceChange(int);
};

#endif // OPTIONS_H
