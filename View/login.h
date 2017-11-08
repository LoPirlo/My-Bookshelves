#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>


#include "administratormainwindow.h"
#include "Controller/admin_controller.h"
#include "database.h"
#include "administrator.h"
#include "Controller/client.h"

class Admin_Controller;
class AdministratorMainWindow;

namespace Ui {
  class Login;
}

class Client;

class Login : public QMainWindow
{
  Q_OBJECT

public:
  explicit Login(Database*,Client*,QWidget *parent = 0);
  ~Login();

private slots:

  void on_User_clicked();

  void on_confirmLogin_clicked();

  void on_Register_clicked();

  void on_confirmRegistration_clicked();

  void on_isAdmin_toggled(bool checked);

  void on_cancelRegistration_clicked();

  void on_cancelLogin_clicked();

private:
  Database* database;
  Ui::Login *ui;

  Client* client;
  Administrator* admin;
  Admin_Controller* admin_contr;
  AdministratorMainWindow *admin_view;
};

#endif // LOGIN_H
