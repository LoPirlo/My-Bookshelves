#ifndef FINISHBOOKVIEW_H
#define FINISHBOOKVIEW_H

#include <QDialog>

namespace Ui {
  class FinishBookView;
}

class User;
class User_Controller;
class Book;
class User_View;
class FinishBookView : public QDialog
{
  Q_OBJECT

public:
  explicit FinishBookView(User*,User_Controller*,Book*,User_View*,QWidget *parent = 0);
  ~FinishBookView();

private slots:
  void on_reviewButton_clicked();

private:
  Book* book;
  User* user;
  User_View* user_view;
  User_Controller* controller;
  Ui::FinishBookView *ui;
};

#endif // FINISHBOOKVIEW_H
