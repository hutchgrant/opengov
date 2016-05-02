#ifndef JSONDISPLAY_H
#define JSONDISPLAY_H

#include <QWidget>

namespace Ui {
class jsonDisplay;
}

class jsonDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit jsonDisplay(QWidget *parent = 0);
    void setView(QString data);
    virtual ~jsonDisplay();

private:
    Ui::jsonDisplay *ui;
};

#endif // JSONDISPLAY_H
