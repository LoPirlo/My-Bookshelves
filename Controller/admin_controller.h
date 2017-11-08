#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

#include "View/admin_userinfo.h"
#include "View/admin_books.h"

class Admin_UserInfo;
class Admin_BookView;
class Administrator;
class Admin_books;
class Book;

class Admin_Controller {
private:
  Administrator* adm;

public:
  Admin_Controller(Administrator*);
  ~Admin_Controller();

  void Login();
  void addUser(const QString &,const QString &,const QString &,const QString &,const QString &,const QString &);
  void showUserInfo(Admin_UserInfo*,const QString&) const;

  void showBookList(Admin_books*);
  void setUser(const QString&,const QString&,const QString&,const QString&,const QString&) const;


  void removeUser(const QString&);
  void promoteUser(const QString&,const QString&);

  User* getUser(const QString&) const;
  QMap<QString,User*> getUsers() const;
  std::list<const User*> searchUsers(const QString&) const;


  // Book Stuff
  QMap<QString,Book*> getBooks() const;
  void AddBook(const QString& i,const QString& bt
               ,const QString& ba,const QString& e,
               const QString& publ,const QString& bf,const QString& des,
               const QDate& publ_date,
               const double& br);

  void showBookInfo(Admin_BookView*,const QString&);
  void modifyBook(const QString &i, const QString &t, const QString &a, const QString &e, const QString &p, const QString &f,const QString &d,  const QDate &date);
  void removeBook(const QString &i);
  std::list<const Book*> searchBooks(const QString &query);
  std::list<Book*> returnBooksByISBN(const QVector<QString>&) const;

};

#endif // ADMIN_CONTROLLER_H
