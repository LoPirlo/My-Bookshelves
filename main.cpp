#include <QApplication>
#include <QDebug>
#include <QCoreApplication>
#include "Controller/client.h"

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  a.setStyle("fusion");

  QPalette p(a.palette());
  p.setBrush(QPalette::Window,QColor(244, 241, 234));
  p.setBrush(QPalette::ButtonText,QColor(91,45,0));
  QFont newFont("Yu Gothic UI Semilight",8,QFont::Bold);
  a.setFont(newFont);
  a.setPalette(p);

  Client client;

  return a.exec();


}
