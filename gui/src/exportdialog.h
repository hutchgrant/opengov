#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class exportDialog;
}

class exportDialog : public QDialog
{
    Q_OBJECT

public:
    QString jsonPath;
    explicit exportDialog(QWidget *parent = 0);
    virtual ~exportDialog();

private slots:
    void on_browsePath_clicked();

    void on_buttonBox_accepted();
signals:
    void pathChanged(QString path);
private:
    Ui::exportDialog *ui;
};

#endif // EXPORTDIALOG_H
