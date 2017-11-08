#ifndef ACCOUNTINFOVIEW_H
#define ACCOUNTINFOVIEW_H

#include <QMainWindow>

namespace Ui {
  class AccountInfoView;
}

class User;
class User_Controller;
class User_View;

class AccountInfoView : public QMainWindow
{
  Q_OBJECT

public:
  explicit AccountInfoView(User*u, User_Controller*contr,User_View* temp_view, QWidget *parent = 0);
  ~AccountInfoView();
  void hideFromNormal();

signals:
  void updateBSFields();

private slots:
  void updateBSFieldsSlot();
  void on_modifyUser_clicked();
  void on_modifyBookshelf_clicked();
  void on_saveModification_clicked();
  void on_SaveBookshelf_clicked();
  void on_bsComboBox_currentTextChanged(const QString &arg1);
  void on_removeBookshelf_clicked();
  void on_deleteAccount_clicked();

private:
  User* user;
  User_Controller* controller;
  User_View* view;
  Ui::AccountInfoView *ui;
};

#endif // ACCOUNTINFOVIEW_H
