#include "admin_controller.h"
#include <iostream>
#include "View/administratormainwindow.h"
#include "View/admin_books.h"
#include "View/login.h"
#include "administrator.h"
#include "book.h"
using std::cout;
Admin_Controller::Admin_Controller(Administrator * admin)
  :adm(admin) {
  // Show the AdministratorMainWindow
}

Admin_Controller::~Admin_Controller()
{
  delete adm;
}

void Admin_Controller::Login() {

  // create AdministratorMainWindow here
  AdministratorMainWindow * admin_window = new AdministratorMainWindow(this);
  admin_window->show();
  admin_window->LoadUserTable();
}

void Admin_Controller::addUser(const QString &u,const QString &n,const QString &s,const QString &p,const QString &e,const QString &t)
{
  adm->AddUser(u,n,s,p,e,t);
}

User* Admin_Controller::getUser(const QString& user) const{
  User* temp = adm->getUser(user);
  return temp;
}

QMap<QString, User *> Admin_Controller::getUsers() const
{
  return adm->getUsers();
}

void Admin_Controller::showUserInfo(Admin_UserInfo * user_info,const QString& username) const
{
  user_info->show();
  user_info->show_info(username);
}

void Admin_Controller::showBookList(Admin_books * adm)
{
  adm->show();
  adm->showBookList();
}

void Admin_Controller::setUser(const QString &u, const QString &n, const QString &s, const QString &e,const QString& t) const
{
  adm->setUser(u,n,s,e,t);
}

void Admin_Controller::removeUser(const QString &u)
{
  adm->RemoveUser(u);
}

void Admin_Controller::promoteUser(const QString &u, const QString &t)
{
  adm->PromoteUser(u,t);
}

std::list<const User*> Admin_Controller::searchUsers(const QString & query) const
{

  std::list<const User*> temp = adm->SearchUser(query);

  return temp;
}

QMap<QString, Book *> Admin_Controller::getBooks() const
{
  return adm->getBooks();
}

void Admin_Controller::AddBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date, const double &br)
{
  adm->AddBook(i,bt,ba,e,publ,bf,des,publ_date,br);
}

void Admin_Controller::showBookInfo(Admin_BookView * book_view, const QString &isbn)
{
  book_view->show();
  book_view->show_info(isbn);
}

void Admin_Controller::modifyBook(const QString &i, const QString &t, const QString &a, const QString &e, const QString &p, const QString &f, const QString &d, const QDate &date)
{

  adm->setBook(i,t,a,e,p,f,d,date);

}

void Admin_Controller::removeBook(const QString &i)
{
  adm->removeBook(i);
}

std::list<const Book *> Admin_Controller::searchBooks(const QString &query)
{
  std::list<const Book *> temp = adm->SearchBook(query);
  return temp;
}

std::list<Book *> Admin_Controller::returnBooksByISBN(const QVector<QString> &temp) const
{
  return adm->returnBooksByISBN(temp);
}

