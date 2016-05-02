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

#ifndef FILEOBJ_H
#define FILEOBJ_H

#define INITSIZE 3
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <QObject>
#include <QDebug>

using namespace std;
class fileObj : public QObject
{
    Q_OBJECT
public:
    string school;
    string *institution;    // ministry name
    string *amt;            // amt of funding
    string *reason;         // reason for funding
    int objSize;            // Number of Items
    int InitSize;           // Number size before reallocate
    long provTotal;

    explicit fileObj();
    fileObj(const fileObj& src);
    fileObj& operator=(const fileObj& src);
    fileObj* operator=(const fileObj* src);

    void initFile(int initSZ);
    void REinitFile(int oldsize, int newsize);

    virtual ~fileObj();
public slots:
    void setInstitution(int item, const char *inst){
        if(item >= 0 && item <= objSize){
            institution[item] = inst;
        }
    }
    void setAmt(int item, const char *amount){
        if(item >= 0 && item <= objSize){
            amt[item] = amount;
        }
    }
    void setReason(int item, const char *res){
        if(item >= 0 && item <= objSize){
            reason[item] = res;
        }
    }
    void set(int item, const char *inst, const char *amount, const char *res){
        if (objSize >= InitSize-1){
            REinitFile(InitSize, 100);
        }
        setInstitution(item, inst);
        setAmt(item, amount);
        setReason(item, res);
        objSize++;
    }
    void setInit(int item, const char *inst, const char *amount, const char *res){
        setInstitution(item, inst);
        setAmt(item, amount);
        setReason(item, res);
        InitSize++;
    }
    void setSize(int size){
        objSize = size;

    }

    char *getInst(int item){
        char *final;
        if(item <= objSize){
            final = new char[institution[item].length()+1];
            strcpy(final, institution[item].c_str());
        }else{
            string name = "-";
            final = new char[name.length()+1];
            strcpy(final, name.c_str());
        }
        return final;
    }
    char *getAmt(int item){
        char *final;
        final = new char[amt[item].length()+1];
        strcpy(final, amt[item].c_str());
        return final;
    }
    char *getReason(int item){
        char *final;
        final = new char[reason[item].length()+1];
        strcpy(final, reason[item].c_str());
        return final;
    }

    int getSize(){
        return objSize;
    }
    void setInit(int initItem){
        InitSize = initItem;
    }
    int getInit(){
        return InitSize;
    }
    QString getQStrName(int pos){
        return QString(institution[pos].c_str());
    }
    void display();
    QString covertToJSON(int runCount);

};
#endif // FILEOBJ_H
