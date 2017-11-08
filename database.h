#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include "moderator.h"
#include <QFile>
#include "book.h"
#include "bookshelf.h"


class Database {
private:
  QMap<QString,User*> container;
  static QString db_file;
  QMap<QString,Book*> book_container;
  static QString bc_file;

public:
  // ==== CONSTRUCTOR, DESTRUCTOR ====
  // =================================

  Database();
  ~Database();

  QMap<QString,User*> getUsers()const;
  QMap<QString,Book*> getBooks()const;

  // --- User Management ---

  void AddUser(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&);
  void AddUser(const User&);
  void RemoveUser(const QString&);
  void UpdateUserType(const QString&, const QString&);
  User* SearchUser(const QString&) const;
  bool checkIfExists(const QString&) const;



  // --- Books Management ---

  void AddBook(const QString& i,const QString& bt
               ,const QString& ba,const QString& e,
               const QString& publ,const QString& bf,const QString& des,
               const QDate& publ_date,
               const double& br);
  void RemoveBook(const QString&);
  void SetBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date);

  std::list<const Book*> SearchBook(const QString& query);
  bool checkIfBookExists(const QString&) const;
  std::list<Book*> returnBooksByISBN(const QVector<QString>&) const;
  Book* SearchSpecificBook(const QString& isbn) const;


  // ==== DATABASE MANIPULATION =====
  void Save();
  void Load();
  bool isUserEmpty() const;
  bool isBookEmpty() const;
  bool isBookshelfEmpty() const;

};


#endif // DATABASE_H
