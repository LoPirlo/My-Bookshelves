#ifndef ADDBOOKFORMUSER_H
#define ADDBOOKFORMUSER_H

#include <QDialog>
#include "Controller/user_controller.h"

namespace Ui {
  class AddBookFormUser;
}

class AddBookFormUser : public QDialog
{
  Q_OBJECT

public:
  explicit AddBookFormUser(User_Controller*,QWidget *parent = 0);
  ~AddBookFormUser();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  User_Controller* controller;
  Ui::AddBookFormUser *ui;
};

#endif // ADDBOOKFORMUSER_H
