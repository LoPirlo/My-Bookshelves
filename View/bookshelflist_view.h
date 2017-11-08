#ifndef BOOKSHELFLIST_VIEW_H
#define BOOKSHELFLIST_VIEW_H

#include <QDialog>
#include "Controller/user_controller.h"

class User_Controller;

namespace Ui {
  class BookshelfList_View;
}

class BookshelfList_View : public QDialog
{
  Q_OBJECT

public:
  explicit BookshelfList_View(User*,User_Controller*,const QString&,User_View*,QWidget *parent = 0);
  ~BookshelfList_View();

private slots:
  void on_buttonBox_accepted();

private:
  User* user;
  User_Controller* controller;
  QString isbn;
  User_View* user_view;
  Ui::BookshelfList_View *ui;
};

#endif // BOOKSHELFLIST_VIEW_H
