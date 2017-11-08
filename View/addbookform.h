#ifndef ADDBOOKFORM_H
#define ADDBOOKFORM_H

#include <QWidget>
#include "book.h"
#include "Controller/admin_controller.h"

namespace Ui {
  class AddBookForm;
}

class Admin_Controller;
class Admin_books;
class AddBookForm : public QWidget
{
  Q_OBJECT

public:
  explicit AddBookForm(Admin_Controller*,Admin_books*,QWidget *parent = 0);
  ~AddBookForm();
  Book getBook() const;

private slots:
  void on_confirmation_accepted();

  void on_confirmation_rejected();

private:
  Ui::AddBookForm *ui;
  Book mbook;

  Admin_Controller* controller;
  Admin_books* view;
};

#endif // ADDBOOKFORM_H
