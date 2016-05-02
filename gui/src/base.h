#ifndef BASE_H
#define BASE_H

#include <QWidget>
#include <src/jsondisplay.h>
#include <src/options.h>
#include <parsecsv.h>

namespace Ui {
class base;
}

class base : public QWidget
{
    Q_OBJECT

public:
    int runCount;
    QString search;
    QString csv;
    QString csvPath;
    QString verboseOut;
    QString jsonDefault;
    parseCSV parse;

    explicit base(QWidget *parent = 0);
    void addWidgets();
    void init();
    bool extract(QString input);
    virtual ~base();

private:
    Ui::base *ui;
    jsonDisplay * display;
    options *opt;

private slots:
    void getSearch(QString input){
         search = input;
         extract(input);
    }
    void error(int errorCode){
    }
};

#endif // BASE_H
