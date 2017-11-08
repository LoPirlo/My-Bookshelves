#ifndef ADMIN_BOOKVIEW_H
#define ADMIN_BOOKVIEW_H

#include <QDialog>
#include "Controller/admin_controller.h"

class Admin_Controller;
class Admin_books;
class Book;

namespace Ui {
  class Admin_BookView;
}

class Admin_BookView : public QDialog
{
  Q_OBJECT

public:
  explicit Admin_BookView(Admin_Controller*,Admin_books*,QWidget *parent = 0);
  ~Admin_BookView();

  void show_info(const QString&);

signals:
  void saveBookInfo(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QDate&) const;
private slots:

  void saveBookInfoSlot(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QDate&) const;

  void on_saveChanges_clicked();

  void on_modifyBook_clicked();

  void on_removeBook_clicked();

  void on_backButton_clicked();

private:
  Ui::Admin_BookView *ui;
  Admin_Controller* controller;
  Admin_books* view;
  Book * temp;

};

#endif // ADMIN_BOOKVIEW_H
