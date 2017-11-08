#include "administrator.h"

Administrator::Administrator(Database* db):database(db){}

void Administrator::AddUser(const QString &u, const QString &n, const QString &s, const QString &p,
                            const QString &e, const QString &t)
{
  database->AddUser(u,n,s,p,e,t);
}

// OK
void Administrator::PromoteUser(const QString &u, const QString &t){
  database->UpdateUserType(u,t);
}
// OK
void Administrator::setUser(const QString &u, const QString &n, const QString &s, const QString &e, const QString &t) {

  User* user = database->SearchUser(u);
  user->setName(n);
  user->setSurname(s);
  user->setEmail(e);
  if(user->getType() != t) {
      user->setType(t);
    }
}
// OK
void Administrator::RemoveUser(const QString& u){
  database->RemoveUser(u);
}
// OK
std::list<const User*> Administrator::SearchUser(const QString& s) const
{
  std::list<const User*> temp;

  for(auto it: database->getUsers().keys()) {
      if(it.contains(s,Qt::CaseInsensitive) ||
         database->getUsers().value(it)->getName().contains(s,Qt::CaseInsensitive) ||
         database->getUsers().value(it)->getSurname().contains(s,Qt::CaseInsensitive) ||
         database->getUsers().value(it)->getEmail().contains(s,Qt::CaseInsensitive) ||
         database->getUsers().value(it)->getType().contains(s,Qt::CaseInsensitive)
         )

        temp.push_back(database->getUsers().value(it));

    }

  return temp;
}

User* Administrator::getUser(const QString& u) const{
  return database->SearchUser(u);
}

bool Administrator::checkForUser(const QString& u) const{
  return database->checkIfExists(u);
}
// OK
QMap<QString, User *> Administrator::getUsers() const
{
  return database->getUsers();
}
// OK
void Administrator::AddBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date, const double &br)
{
  database->AddBook(i,bt,ba,e,publ,bf,des,publ_date,br);
}
// OK
void Administrator::setBook(const QString &i, const QString &t, const QString &a, const QString &e, const QString &p, const QString &f, const QString &d, const QDate &date)
{
  Book* temp_book = database->SearchSpecificBook(i);

  temp_book->setISBN(i);
  temp_book->setTitle(t);
  temp_book->setAuthor(a);
  temp_book->setEdition(e);
  temp_book->setPublisher(p);
  temp_book->setFormat(f);
  temp_book->setDescription(d);
  temp_book->setPublishingDate(date);

}
// OK
void Administrator::removeBook(const QString &i)
{
  database->RemoveBook(i);
}
// OK
QMap<QString, Book *> Administrator::getBooks() const
{
  return database->getBooks();
}
// OK
std::list<Book *> Administrator::returnBooksByISBN(const QVector<QString> &temp) const
{
  return database->returnBooksByISBN(temp);
}

bool Administrator::isEmpty() const{
  return database->isUserEmpty();
}
// OK
std::list<const Book *> Administrator::SearchBook(const QString &query)
{
  std::list<const Book*> temp = database->SearchBook(query);
  return temp;
}