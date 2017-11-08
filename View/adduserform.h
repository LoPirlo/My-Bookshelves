#ifndef ADDUSERFORM_H
#define ADDUSERFORM_H

#include <QDialog>
#include <Controller/admin_controller.h>


class Admin_Controller;
class AdministratorMainWindow;

namespace Ui {
  class AddUserForm;
}

class AddUserForm : public QDialog
{
  Q_OBJECT


public:
  explicit AddUserForm(Admin_Controller* admin,AdministratorMainWindow* temp_view,QWidget *parent = 0);
  ~AddUserForm();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::AddUserForm *ui;

  Admin_Controller* admin;
  AdministratorMainWindow* view;
};

#endif // ADDUSERFORM_H
