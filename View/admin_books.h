#ifndef ADMIN_BOOKS_H
#define ADMIN_BOOKS_H

#include <QMainWindow>
#include "Controller/admin_controller.h"
#include "View/admin_bookview.h"

namespace Ui {
  class Admin_books;
}

class Admin_Controller;
class Admin_BookView;
class Book;

class Admin_books : public QMainWindow
{
  Q_OBJECT

public:
  explicit Admin_books(Admin_Controller*,QWidget *parent = 0);
  ~Admin_books();

  void showBookList() const;

signals:
  void signalShowBooks() const;
  void showSearchedBooks(std::list<const Book*>) const;

private slots:
  void slotShowBooks() const;
  void showSearchedBooksSlot(std::list<const Book*>) const;

  void on_addBook_button_clicked();

  void on_tableWidget_doubleClicked(const QModelIndex &index);

  void on_searchBook_button_clicked();

private:
  Ui::Admin_books *ui;

  enum Columns_Book{
    ISBN,
    TITLE,
    AUTHOR,
    PUBLISHER,
    FORMAT,
    RATING
  };

  Admin_Controller* admin_contr;
  Admin_BookView* book_view;


};

#endif // ADMIN_BOOKS_H
