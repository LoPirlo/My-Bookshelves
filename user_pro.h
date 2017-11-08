#ifndef USER_PRO_H
#define USER_PRO_H

#include "user_normal.h"

class User_Pro:public User_Normal {
public:
  User_Pro(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&);
  User_Pro(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QVector<Bookshelf*> &);
  User_Pro(const User&);
  virtual ~User_Pro(){}

  virtual void addBookshelf(const QString&,const QString&);
  virtual std::list<const Book*>  searchBooks(Database*,const QString&);
};

#endif // USER_PRO_H
