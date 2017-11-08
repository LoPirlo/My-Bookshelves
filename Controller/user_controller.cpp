#include "Controller/user_controller.h"
#include "View/bookshelflist_view.h"
#include "View/newbookshelfview.h"
#include "View/accountinfoview.h"
#include "View/finishbookview.h"

#include <iostream>
using std::cout;

User_Controller::User_Controller(Database * database, User *u):
  db(database),user(u)
{
  view = new User_View(user,this);
  view->show();
  view->showInCommon();
}

User_Controller::~User_Controller()
{
  delete db;
  delete user;
  delete view;
}
// OK
std::list<const Book *> User_Controller::searchBooks(const QString &query)
{
  // polymorphism in action
  std::list<const Book*> temp = user->searchBooks(db,query);
  return temp;
}
// OK
void User_Controller::showBookInfo(Book_View *book_info, const QString &isbn) const
{
  book_info->show();
  book_info->showInfo(isbn);
}
// OK
Book *User_Controller::getBook(const QString &isbn) const
{
  return db->getBooks().value(isbn);
}
// OK
QMap<QString, Book *> User_Controller::getBooks() const
{
  return db->getBooks();
}
// OK
void User_Controller::finishBook(const QString &isbn,User_View* view)
{

  if(user->getType() == "User_Normal") {
      // remove from Reading and Add to Read
      for(int it = 0; it < user->getBookshelfToModify()->size(); it++) {
          if(user->getBookshelf().at(it)->getName() == "Reading") {
              for(int z = 0; z < (*user->getBookshelf().at(it)).getBookList().size(); z++) {
                  if((*user->getBookshelf().at(it)).getBookListToModify()->at(z) == isbn){
                      (*user->getBookshelf().at(it)).getBookListToModify()->removeAt(z);
                      for(int it = 0; it < user->getBookshelfToModify()->size(); it++) {
                          if(user->getBookshelfToModify()->at(it)->getName() == "Read") {
                              user->getBookshelfToModify()->at(it)->addBook(isbn);
                            }
                        }
                    }
                }
            }
        }
      view->updateReadingTable();
      emit view->updateBSTable();
    } else
    {
      // open new window for multiple selection for UserPro & Moderator

      FinishBookView* temp_view = new FinishBookView(user,this,db->getBooks().find(isbn).value(),view);
      temp_view->show();

  }
}
// OK
std::list<Book *> User_Controller::returnBooksByISBN(const QVector<QString> &temp) const
{
  return db->returnBooksByISBN(temp);
}
// OK
void User_Controller::addBookToBS(int it, const QString &isbn)
{
  user->getBookshelf().at(it)->addBook(isbn);
}
// OK
void User_Controller::showBookshelfList(BookshelfList_View *temp_view)
{
  temp_view->show();
}
// OK
void User_Controller::showNewBookshelf(NewBookshelfView *temp_view)
{
  temp_view->show();
}

void User_Controller::AddBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date, const double &br)
{
  db->AddBook(i,bt,ba,e,publ,bf,des,publ_date,br);
}

void User_Controller::SetBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date)
{
  db->SetBook(i,bt,ba,e,publ,bf,des,publ_date);
}
// OK
void User_Controller::showAccountInfo(AccountInfoView *temp_view)
{
  temp_view->show();
}
// OK
void User_Controller::setUser(const QString &n, const QString &s, const QString &p, const QString &e)
{
  user->setName(n);
  user->setSurname(s);
  user->setEmail(e);
  user->setPassword(p);
}
// OK
void User_Controller::removeAccount(const QString &username)
{
  db->RemoveUser(username);
}
// OK
void User_Controller::addBookshelf(const QString& name,const QString& description)
{
  (dynamic_cast<User_Pro*>(user))->addBookshelf(name,description);
}
// OK
void User_Controller::setBookshelf(const QString &current, const QString &name, const QString &description)
{
  for(int it = 0; it < user->getBookshelf().size(); it++) {
      if(user->getBookshelf().at(it)->getName() == current) {
          // I can modify the current bookshelf
          user->getBookshelf().at(it)->setName(name);
          user->getBookshelf().at(it)->setDescription(description);
        }
    }
}
// OK
void User_Controller::removeBS(const QString &name)
{
  for(int it = 0; it < user->getBookshelfToModify()->size(); it++) {
      if(user->getBookshelfToModify()->at(it)->getName() == name) {
          user->getBookshelfToModify()->removeAt(it);
        }
    }
}
// OK
void User_Controller::addReview(const QString &user,const QString &review, const QString &isbn)
{
  (*db->getBooks().find(isbn))->addReview(user,review);

}
// OK
void User_Controller::removeBookFromBS(const QString &isbn)
{
  for(auto it = user->getBookshelfToModify()->begin(); it != user->getBookshelfToModify()->end(); ++it) {
      for(auto z = (*it)->getBookListToModify()->begin(); z != (*it)->getBookListToModify()->end(); ++z) {
              if( *z == isbn) {
                  z = (*it)->getBookListToModify()->erase(z);
                  z--;
                }
          }
      }

}


