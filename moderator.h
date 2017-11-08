#ifndef MODERATOR_H
#define MODERATOR_H

#include "user_pro.h"
#include "database.h"

class Moderator:public User_Pro {
public:
  Moderator(const QString&u, const QString&n, const QString&s, const QString&p, const QString&e, const QString&t);
  Moderator(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&,const QVector<Bookshelf*> &);
  Moderator(const User&);
  virtual ~Moderator();

  virtual void AddBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date, const double &br,Database* db);


};



#endif // MODERATOR_H
