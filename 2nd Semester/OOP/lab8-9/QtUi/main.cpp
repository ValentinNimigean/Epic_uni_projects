#include "QtUi.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtUi w;
    w.show();
    return a.exec();
}
