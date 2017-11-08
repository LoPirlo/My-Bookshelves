#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "database.h"
#include "View/user_view.h"
#include "View/book_view.h"
class NewBookshelfView;
class Book_View;
class User_View;
class BookshelfList_View;
class AccountInfoView;


class User_Controller {
private:
  Database* db;
  User* user;
  User_View* view;


public:
  User_Controller(Database*,User*);
  ~User_Controller();

  std::list<const Book*> searchBooks(const QString &query);
  void showBookInfo(Book_View* book_info,const QString& isbn) const;
  Book* getBook(const QString&) const;
  QMap<QString, Book *> getBooks() const;
  void finishBook(const QString&,User_View*);
  std::list<Book *> returnBooksByISBN(const QVector<QString>& temp) const;
  void addBookToBS(int,const QString&);

  void showBookshelfList(BookshelfList_View*);
  void showNewBookshelf(NewBookshelfView*);

  void AddBook(const QString& i,const QString& bt
               ,const QString& ba,const QString& e,
               const QString& publ,const QString& bf,const QString& des,
               const QDate& publ_date,
               const double& br);

  void SetBook(const QString& i,const QString& bt
               ,const QString& ba,const QString& e,
               const QString& publ,const QString& bf,const QString& des,
               const QDate& publ_date);

  void showAccountInfo(AccountInfoView*);
  void setUser(const QString&,const QString&,const QString&,const QString&);
  void removeAccount(const QString&);

  void addBookshelf(const QString& name,const QString& description);
  void setBookshelf(const QString&,const QString&,const QString&);
  void removeBS(const QString&);

  void addReview(const QString&,const QString&,const QString&);
  void removeBookFromBS(const QString&);
};

#endif // USER_CONTROLLER_H
