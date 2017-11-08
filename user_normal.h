#ifndef USER_NORMAL_H
#define USER_NORMAL_H

#include "user.h"


class User_Normal: public User {

private:
public:
  User_Normal(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&);
  virtual ~User_Normal(){}
  User_Normal(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QVector<Bookshelf*>&);

  User_Normal(const User&);

  virtual std::list<const Book*>  searchBooks(Database*,const QString&);

};

#endif // USER_NORMAL_H
