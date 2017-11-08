#include <QString>
#include "user.h"

QString User::getUsername() const {return username;}
void User::setUsername(QString u) { username = u;}

QString User::getName() const {return name;}
void User::setName(QString n) {name = n;}

QString User::getSurname() const {return surname;}
void User::setSurname(QString s) {surname = s;}

QString User::getPassword() const {return password;}
void User::setPassword(QString p){password=p;}

QString User::getEmail() const {return email;}
void User::setEmail(QString e) {email = e;}

QString User::getType() const { return type;}
void User::setType(QString t) { type = t;}

bool User::checkIfBookExistsInBS(const QString &isbn, const QString &bookshelf)
{
  for(int it=0; it < bsl.size(); ++it) {
      if(bsl.at(it)->getName() == bookshelf) {
          for(int z = 0; z < bsl.at(it)->getBookList().size(); ++z) {
              if(bsl.at(it)->getBookList().at(z) == isbn) {
                  return true;
                }
            }
        }
    }
  return false;
}

QVector<Bookshelf*> User::getBookshelf() const
{
  return bsl;
}

QVector<Bookshelf *> *User::getBookshelfToModify()
{
  return &bsl;
}

void User::setBookshelf(QVector<Bookshelf*> temp)
{
  bsl = temp;
}

bool User::checkIfBSExists(const QString &name) const
{
  for(int it = 0; it < bsl.size(); ++it) {
      if(bsl.at(it)->getName() == name) {
          return true;
        }
    }
  return false;
}


User::User(const User &u):username(u.getUsername()),name(u.getName()),
  surname(u.getSurname()),password(u.getPassword()),email(u.getEmail()), type(u.getType())
{}

User::User(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t="User")
  : username(u),name(n),surname(s),password(p),email(e),type(t){
  bsl.push_back(new Bookshelf("Read","It contains books I've already read."));
  bsl.push_back(new Bookshelf("To Read","It contains books I'm willing to read."));
  bsl.push_back(new Bookshelf("Reading","It contains books I'm currently reading."));

}

User::User(const QString& u,const QString& n,const QString& s,const QString& p,const QString& e,const QString& t,const QVector<Bookshelf*>& l)
  : username(u),name(n),surname(s),password(p),email(e),type(t),bsl(l){
}

User::~User() {
  bsl.clear();
}