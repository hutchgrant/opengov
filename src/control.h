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
#ifndef CONTROL_H
#define CONTROL_H

#include <QDebug>
#include <QTextStream>
#include <QProcess>
#include <cstring>
#include <src/parsecsv.h>

using namespace std;
class control
{
public:
    parseCSV parse;
    string *query;
    int runCount;
    QString csv;

    control();
    bool manageInstall();
    bool manageQueries();
    bool manageLoop();
};

#endif // CONTROL_H
