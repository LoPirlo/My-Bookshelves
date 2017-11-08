#include "user_pro.h"
#include "database.h"
#include <iostream>
using std::cout;

User_Pro::User_Pro(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t ="User_Pro")
  : User_Normal(u,n,s,p,e,t){

}


User_Pro::User_Pro(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t,const QVector<Bookshelf*>& l)
  : User_Normal(u,n,s,p,e,t,l){
}

User_Pro::User_Pro(const User &u):User_Normal(u)
{

}

void User_Pro::addBookshelf(const QString &name, const QString &des)
{
  (*User::getBookshelfToModify()).push_back(new Bookshelf(name,des));
}


std::list<const Book*>  User_Pro::searchBooks(Database*db, const QString &query)
{
  std::list<const Book*> temp;

  for(auto it: db->getBooks().keys()) {
      if(it.contains(query,Qt::CaseInsensitive) ||
         db->getBooks().value(it)->getTitle().contains(query,Qt::CaseInsensitive) ||
         db->getBooks().value(it)->getAuthor().contains(query,Qt::CaseInsensitive) ||
         db->getBooks().value(it)->getPublisher().contains(query,Qt::CaseInsensitive) ||
         db->getBooks().value(it)->getFormat().contains(query,Qt::CaseInsensitive) ||
         db->getBooks().value(it)->getDescription().contains(query,Qt::CaseInsensitive))

        // if any of the above is fitting then I push the book into the results
        temp.push_back(db->getBooks().value(it));
    }

  return temp;
}