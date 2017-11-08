#ifndef USER_H
#define USER_H

#include <QString>
#include "book.h"
#include "bookshelf.h"
#include <list>
#include <QVector>


using std::ostream;
using std::list;

class Database;


class User {
private:
  QString username,name,surname,password,email,type;

  // type : User
  //      : User_Normal
  //      : User_Pro

  // I need a list to scan all the bookshelfs
  QVector<Bookshelf*> bsl;

public:

  // ==== CONSTRUCTOR & DESTRUCTOR ====
  User(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&);
  User(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QVector<Bookshelf*> &);
  User(const User&);
  virtual ~User();

  // ==== METHODS TO GATHER & SET VARIABLES ====

  QString getUsername() const;
  void setUsername(QString);

  QString getName() const;
  void setName(QString);

  QString getSurname() const;
  void setSurname(QString);

  QString getPassword() const;
  void setPassword(QString);

  QString getEmail() const;
  void setEmail(QString);

  QString getType() const;
  void setType(QString);

  bool checkIfBookExistsInBS(const QString&,const QString&);


  QVector<Bookshelf*>  getBookshelf() const;
  QVector<Bookshelf*>* getBookshelfToModify();
  void setBookshelf(QVector<Bookshelf*>);
  bool checkIfBSExists(const QString&) const;

  virtual std::list<const Book*> searchBooks(Database*,const QString&)=0;

};


#endif // USER_H
