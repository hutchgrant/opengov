#include "exportdialog.h"
#include "ui_exportdialog.h"

exportDialog::exportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportDialog)
{
    ui->setupUi(this);
    jsonPath = "";
}

exportDialog::~exportDialog()
{
    delete ui;
}

void exportDialog::on_browsePath_clicked()
{
    QDir usrDir = QString(getenv("HOME"));
    QFileDialog iDirect;
    usrDir = QFileDialog::getSaveFileName(this, tr("Select JSON export path"), QDir::currentPath(), tr("JSON (*.json)"));
    if(usrDir.dirName() != NULL || usrDir.dirName() != ""){
        jsonPath = usrDir.absolutePath();
         ui->absoluteJPath->setText(jsonPath);
    }

}

void exportDialog::on_buttonBox_accepted()
{
    emit pathChanged(jsonPath);
}
