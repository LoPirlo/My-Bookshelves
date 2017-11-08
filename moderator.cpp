#include "moderator.h"

Moderator::Moderator(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t ="Moderator")
  :User_Pro(u,n,s,p,e,t){
}

Moderator::Moderator(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t,const QVector<Bookshelf*>& l)
  :User_Pro(u,n,s,p,e,t,l){

}

Moderator::Moderator(const User &u):User_Pro(u)
{

}

Moderator::~Moderator()
{

}

void Moderator::AddBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date, const double &br, Database *db)
{
  db->AddBook(i,bt,ba,e,publ,bf,des,publ_date,br);
}
