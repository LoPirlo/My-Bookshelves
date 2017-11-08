#include "user_normal.h"
#include <iostream>
using namespace std;
#include "database.h"

User_Normal::User_Normal(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t="User_Normal")
  : User(u,n,s,p,e,t){

}

User_Normal::User_Normal(const User & u):User(u)
{}


//void User_Normal::addBookshelf(const QString &n, const QString &des,const QVector<QString>& ls) {
//  getBookshelf().push_back(new Bookshelf(n,des,ls));
//}


std::list<const Book*>  User_Normal::searchBooks(Database*db,const QString &query)
{
  std::list<const Book*> temp;

  for(auto it: db->getBooks().keys()) {
      if(it.contains(query,Qt::CaseInsensitive) ||
         db->getBooks().value(it)->getTitle().contains(query,Qt::CaseInsensitive))

        // if any of the above is fitting then I push the book into the results
        temp.push_back(db->getBooks().value(it));
    }

  return temp;
}

User_Normal::User_Normal(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t,const QVector<Bookshelf*>& l )
  : User(u,n,s,p,e,t,l){

}


