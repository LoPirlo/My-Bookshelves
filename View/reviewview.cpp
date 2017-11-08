#include "reviewview.h"
#include "ui_reviewview.h"
#include <iostream>

using std::cout;
using std::endl;

reviewview::reviewview(QMap<QString,QString>* revs,QString username,QWidget *parent) :
  QDialog(parent),
  ui(new Ui::reviewview)
{
  ui->setupUi(this);

  ui->description->setText(revs->find(username).value());
  ui->title->setText(username+"'s review");

}

reviewview::~reviewview()
{
  delete ui;
}


void reviewview::on_closeButton_clicked()
{
    this->close();
}
