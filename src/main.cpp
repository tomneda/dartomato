#include "dartomat_mainwindow.h"

#include <QApplication>
//#include <QStyleFactory>

#ifndef TESTING
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setStyle("fusion");
  CDartomatMain w;
  w.show();
  return a.exec();
}
#endif
