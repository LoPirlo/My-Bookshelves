#ifndef BOOK_VIEW_H
#define BOOK_VIEW_H

#include <QMainWindow>
#include "Controller/user_controller.h"

class User_Controller;
namespace Ui {
  class Book_View;
}

class User_View;
class Book_View : public QMainWindow
{
  Q_OBJECT

public:
  explicit Book_View(User*,User_Controller*,User_View*,QWidget *parent = 0);
  ~Book_View();

  void showInfo(const QString&);
  void hideFromUser_Normal() const;

private slots:
  void addToBookshelf();
  void setEditable();
  void saveModifications();

  void on_add_review_button_clicked();
  void removeFromBookshelves();
  void seeReviewsList();
private:
  Book* book;
  User* user_temp;
  User_Controller* contr;
  User_View* user_view;

  Ui::Book_View *ui;
};

#endif // BOOK_VIEW_H
