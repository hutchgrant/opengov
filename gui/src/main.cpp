#include "base.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    base b;
    b.show();

    return a.exec();
}
