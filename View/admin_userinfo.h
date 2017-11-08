#ifndef ADMIN_USERINFO_H
#define ADMIN_USERINFO_H

#include <QMainWindow>
class Admin_Controller;
class AdministratorMainWindow;
class User;

namespace Ui {
  class Admin_UserInfo;
}

class Admin_UserInfo : public QMainWindow
{
  Q_OBJECT

public:
  explicit Admin_UserInfo(Admin_Controller*,AdministratorMainWindow*,QWidget *parent = 0);
  ~Admin_UserInfo();

  void show_info(const QString&);

signals:
  void SaveInfo(const QString&,const QString&,const QString&,const QString&,const QString&) const;

private slots:

  void SaveInfoSLOT(const QString&,const QString&,const QString&,const QString&,const QString&) const;

  void on_ModifyButton_pressed();

  void on_saveButton_pressed();

  void on_bookshelves_list_currentTextChanged(const QString &arg1);

  void on_removeUser_clicked();

private:
  User* temp;
  Admin_Controller* contr;
  AdministratorMainWindow* view;
  Ui::Admin_UserInfo *ui;

  enum Columns_Book{
    ISBN,
    TITLE,
    AUTHOR,
    PUBLISHER,
    FORMAT,
    RATING
  };

};

#endif // ADMIN_USERINFO_H
