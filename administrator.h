#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "database.h"

using std::list;

class Administrator {
private:
  Database* database;
public:
  Administrator(Database*);

  void AddUser(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t);
  void PromoteUser(const QString& u,const QString& t);
  void setUser(const QString&,const QString&,const QString&,const QString&, const QString&);


  void RemoveUser(const QString& u);
  list<const User*> SearchUser(const QString& u) const;
  User* getUser(const QString& u) const;
  bool checkForUser(const QString& u) const;
  QMap<QString,User*> getUsers() const;

  // book stuff
  void AddBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date, const double &br);
  void setBook(const QString &i, const QString &t, const QString &a, const QString &e, const QString &p, const QString &f, const QString &d, const QDate &date);
  void removeBook(const QString &i);
  QMap<QString,Book*> getBooks() const;

  std::list<Book*> returnBooksByISBN(const QVector<QString>&) const;

  bool isEmpty() const;
  std::list<const Book*> SearchBook(const QString &query);

};

#endif // ADMINISTRATOR_H
