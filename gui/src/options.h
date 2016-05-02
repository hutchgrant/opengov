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

private:
    Ui::options *ui;
    QString search;
private slots:
    void on_btnSearch_clicked();

signals:
    void btnSearchClick(QString);
};

#endif // OPTIONS_H
