#include <QApplication>
#include <QPushButton>
#include "doctorwindow.h"

int main(int argc, char *argv[]) {
    Repository* r=new Repository();
    Service* s=new Service(r);
    QApplication a(argc, argv);
  for(Doctor* d:s->get_doctors())
  {
      DoctorWindow* w=new DoctorWindow(s,d);
      s->add_obs(w);
      w->show();

  }
    return QApplication::exec();


}
