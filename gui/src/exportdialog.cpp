#include "exportdialog.h"
#include "ui_exportdialog.h"

exportDialog::exportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportDialog)
{
    ui->setupUi(this);
    jsonPath = "";
    dialogMode = 0;
}

exportDialog::~exportDialog()
{
    delete ui;
}

void exportDialog::on_browsePath_clicked()
{
    QDir usrDir;
    usrDir = QFileDialog::getSaveFileName(this, tr("Select JSON export path"), QDir::currentPath(), tr("JSON (*.json)"));
    if(usrDir.dirName() != NULL || usrDir.dirName() != ""){
        jsonPath = usrDir.absolutePath();
         ui->absoluteJPath->setText(jsonPath);
    }
}
/*
 * Show file browser
 */
void exportDialog::showBrowse(){
    dialogMode = 0;
    ui->browsePath->show();
    ui->absoluteJPath->show();
    ui->dialogMsg->setText("Set JSON Export Path");
}

/*
 * Display error message
 */
void exportDialog::showError(int errorCode){
    QString errorMsg = "";
    dialogMode = 2;

    ui->browsePath->hide();
    ui->absoluteJPath->hide();

    if(errorCode <= 5 ){
        errorMsg = "A background task crashed. Check that you have bash/wget/grep and they're' functioning correctly. Error: " + QString::number(errorCode);
    }else if(errorCode == 6){
        errorMsg = "Couldn't complete download. Check the data set URL and try again. Error: " + QString::number(errorCode);
    }else if(errorCode == 7){
        errorMsg = "A problem was encountered while searching the dataset. Check that you aren't using any special characters in your query. Error: " + QString::number(errorCode);
    }else if(errorCode == 8){
        errorMsg = "Error reading from verbose CSV file. Check that the path and file are correct. Error: " + QString::number(errorCode);
    }else if(errorCode == 9){
        errorMsg = "Error writing to JSON file. Check that the path and file are correct. Error: " + QString::number(errorCode);
    }
    ui->dialogMsg->setText(errorMsg);
}

void exportDialog::on_buttonBox_accepted()
{
    if(dialogMode == 0){
        emit pathChanged(jsonPath);
    }
}
