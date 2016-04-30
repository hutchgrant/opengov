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
#include <QCoreApplication>
#include <src/control.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    control cntrl;
    bool exit = false;
    if(cntrl.manageInstall()){
        if(!argv[1]){
            argv[1] = "data.json";
        }
        while(exit == false){
            if(cntrl.manageQueries(argv[1])){
                exit = cntrl.manageLoop();
            }
        }
        return 0;
    }

    return a.exec();
}