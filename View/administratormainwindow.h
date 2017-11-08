#ifndef ADMINISTRATORMAINWINDOW_H
#define ADMINISTRATORMAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "addbookform.h"
#include "adduserform.h"
#include "administrator.h"
#include "login.h"
#include "admin_books.h"

class Admin_Controller;
class AddUserForm;
class Admin_books;

namespace Ui {
  class AdministratorMainWindow;
}

class AdministratorMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AdministratorMainWindow(Admin_Controller*,QWidget *parent = 0);
  ~AdministratorMainWindow();

  void LoadUserTable() const;
signals:
  void init_UserTable() const;
  void showSearchedUsers(std::list<const User*>) const;

public slots:
  void refull_UserTable() const;
  void showSearchedUsersSlot(std::list<const User*>) const;
  void showBooksTable();
  void showUserInfo();
private slots:
  void on_AddUser_Button_clicked();

  void on_user_table_doubleClicked(const QModelIndex &index);

  void on_searchButton_clicked();

private:
  Ui::AdministratorMainWindow *ui;

  AddUserForm *addUser;

  enum Columns_Users {
    USERNAME,
    NAME,
    SURNAME,
    EMAIL,
    TYPE

  };


  Admin_Controller* controller;
  Admin_books* ad_b;

};

#endif // ADMINISTRATORMAINWINDOW_H
