#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QGraphicsWebView>
#include <QWebFrame>
#include "html5applicationviewer.h"

using namespace std;
class detached : public Html5ApplicationViewer
{
    Q_OBJECT

public:
    explicit detached(QWidget *parent = 0);
    virtual ~detached();
    void displayHistory();
public slots:
    void remotePage(QString page);
private slots:
    void addToJavaScript();
signals:
    void detachClose();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
