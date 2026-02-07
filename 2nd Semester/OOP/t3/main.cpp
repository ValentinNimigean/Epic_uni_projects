#include <QApplication>
#include <QPushButton>
#include "UI.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository* r=new Repository();
    Service* s=new Service(r);
   MainWindow b(s);
   b.show();
    return QApplication::exec();
}
