#ifndef USER_VIEW_H
#define USER_VIEW_H

#include <QMainWindow>
#include "Controller/user_controller.h"
#include <QTableWidget>

class User_Controller;


namespace Ui {
  class User_View;
}

class User_View : public QMainWindow
{
  Q_OBJECT

public:
  explicit User_View(User*,User_Controller*,QWidget *parent = 0);
  ~User_View();

  void showInCommon() const;
  void hideThings() const;

signals:

  void updateReadingTable() const;
  void finishBook(const QString&) const;
  void showSearchedBooks(std::list<const Book*>);
  void showBook(const QModelIndex &,const QTableWidget*);
  void updateBSList();
  void updateBSTable();
private slots:

  void updateBSListSlot();
  void updateBSTableSlot();

  void updateReadingTableSlot() const;
  void finishBookSLOT(const QString&);
  void addBookSlot() const;


  void showAccountInfo();
  void showBookSlot(const QModelIndex&,const QTableWidget*);

  void on_search_books_button_clicked();
  void showSearchedBooksSlot(std::list<const Book*>);

  void on_readingNow_table_doubleClicked(const QModelIndex &index);

  void on_searched_books_doubleClicked(const QModelIndex &index);

  void on_bookshelves_table_doubleClicked(const QModelIndex &index);

  void on_AddBookshelf_button_clicked();

  void on_bookshelves_list_currentTextChanged(const QString &arg1);

  void on_readingNow_table_clicked(const QModelIndex &index);

  void on_Finished_clicked();

private:
  User* user;
  User_Controller* controller;
  QString isbn_temp;

  enum Columns_Book{
    ISBN,
    TITLE,
    AUTHOR,
    PUBLISHER,
    FORMAT,
    RATING
  };

  Ui::User_View *ui;

};

#endif // USER_VIEW_H
