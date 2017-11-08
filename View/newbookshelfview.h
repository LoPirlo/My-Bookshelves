#ifndef NEWBOOKSHELFVIEW_H
#define NEWBOOKSHELFVIEW_H

#include <QDialog>
#include "Controller/user_controller.h"
namespace Ui {
  class NewBookshelfView;
}

class NewBookshelfView : public QDialog
{
  Q_OBJECT

public:
  explicit NewBookshelfView(User*,User_Controller*,User_View*,QWidget *parent = 0);
  ~NewBookshelfView();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  User* user;
  User_Controller* controller;
  User_View* view;
  Ui::NewBookshelfView *ui;
};

#endif // NEWBOOKSHELFVIEW_H
