#include "user_view.h"
#include "ui_user_view.h"
#include <typeinfo>
#include <QMessageBox>
#include <iostream>
#include "book_view.h"
#include "newbookshelfview.h"
#include "accountinfoview.h"
#include "addbookformuser.h"


using std::cout;

User_View::User_View(User* u, User_Controller* contr,QWidget *parent) :
 user(u),controller(contr),QMainWindow(parent),
  ui(new Ui::User_View)
{
  ui->setupUi(this);

  this->setWindowTitle(u->getUsername()+" - "+u->getType());

  ui->Finished->setEnabled(false);

  QStringList titles = {"ISBN","Title","Author","Publisher","Format","Rating"};
  ui->bookshelves_table->setColumnCount(6);
  ui->bookshelves_table->setHorizontalHeaderLabels(titles);
  ui->bookshelves_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  QStringList reading_titles = {"ISBN","Title"};
  ui->readingNow_table->setColumnCount(2);
  ui->readingNow_table->setHorizontalHeaderLabels(reading_titles);
  ui->readingNow_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->searched_books->setColumnCount(6);
  ui->searched_books->setHorizontalHeaderLabels(titles);
  ui->searched_books->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


  if(user->getType() == "User_Normal")
    hideThings();

  if(user->getType() != "Moderator")
      ui->actionAdd_new_Book->setVisible(false);


  connect(this,SIGNAL(showSearchedBooks(std::list<const Book*>)),this,SLOT(showSearchedBooksSlot(std::list<const Book*>)));
  connect(ui->actionLogout,SIGNAL(triggered()),this,SLOT(close()));
  connect(this,SIGNAL(showBook(QModelIndex,const QTableWidget*)),this,SLOT(showBookSlot(QModelIndex,const QTableWidget*)));
  connect(ui->actionAccount,SIGNAL(triggered()),this,SLOT(showAccountInfo()));
  connect(this,SIGNAL(finishBook(QString)),this,SLOT(finishBookSLOT(QString)));
  connect(this,SIGNAL(updateReadingTable()),this,SLOT(updateReadingTableSlot()));
  connect(this,SIGNAL(updateBSList()),this,SLOT(updateBSListSlot()));
  connect(this,SIGNAL(updateBSTable()),this,SLOT(updateBSTableSlot()));
  connect(ui->actionAdd_new_Book,SIGNAL(triggered()),this,SLOT(addBookSlot()));

}

User_View::~User_View()
{
  delete ui;
  delete user;
  delete controller;
}

void User_View::showInCommon() const
{

  // Bookshelf stuff

  for(auto it = 0; it < user->getBookshelf().size(); ++it) {
      if(user->getBookshelf().at(it)->getName() != "Reading")


        ui->bookshelves_list->addItem(user->getBookshelf().at(it)->getName());
    }

  ui->description_text->setText(user->getBookshelf().at(0)->getDescription());

  // table
  for(auto it = 0; it < user->getBookshelf().size(); ++it) {

      // If is Reading Bookshelf I replenish the top-left table
      if(user->getBookshelf().at(it)->getName() == "Reading") {

          QVector<QString> temp = user->getBookshelf().at(it)->getBookList();
          // I need to search into the database for the ISBN books and return a list

          std::list<Book*> read_books = controller->returnBooksByISBN(temp);

          for(auto z = read_books.begin(); z != read_books.end(); ++z) {
              ui->readingNow_table->insertRow(ui->readingNow_table->rowCount());
              int row = ui->readingNow_table->rowCount()-1;

              ui->readingNow_table->setItem(row,ISBN,new QTableWidgetItem((*z)->getISBN()));
              ui->readingNow_table->setItem(row,TITLE,new QTableWidgetItem((*z)->getTitle()));


            } }
    }

  // search stuff

  for(auto it: controller->getBooks().keys()) {
      ui->searched_books->insertRow(ui->searched_books->rowCount());
      int row = ui->searched_books->rowCount()-1;

      ui->searched_books->setItem(row,ISBN,new QTableWidgetItem(controller->getBooks().value(it)->getISBN()));
      ui->searched_books->setItem(row,TITLE,new QTableWidgetItem(controller->getBooks().value(it)->getTitle()));
      ui->searched_books->setItem(row,AUTHOR,new QTableWidgetItem(controller->getBooks().value(it)->getAuthor()));
      ui->searched_books->setItem(row,PUBLISHER,new QTableWidgetItem(controller->getBooks().value(it)->getPublisher()));
      ui->searched_books->setItem(row,FORMAT,new QTableWidgetItem(controller->getBooks().value(it)->getFormat()));
      ui->searched_books->setItem(row,RATING,new QTableWidgetItem(QString::number(controller->getBooks().value(it)->getRating(),'f',2)));
    }


}

void User_View::hideThings() const
{
  ui->AddBookshelf_button->hide();
}

void User_View::updateBSListSlot()
{
  ui->bookshelves_list->clear();
  for(auto it = 0; it < user->getBookshelf().size(); ++it) {
      if(user->getBookshelf().at(it)->getName() != "Reading")

        ui->bookshelves_list->addItem(user->getBookshelf().at(it)->getName());
    }
}

void User_View::updateBSTableSlot()
{

  ui->bookshelves_table->setRowCount(0);
  for(auto it = 0; it < user->getBookshelf().size(); ++it) {
      if(ui->bookshelves_list->currentText() == user->getBookshelf().at(it)->getName())
        {
          ui->bookshelves_table->setRowCount(0);

          std::list<Book*> books_list = controller->returnBooksByISBN(user->getBookshelf().at(it)->getBookList());

          for(auto z = books_list.begin(); z != books_list.end(); ++z) {
              ui->bookshelves_table->insertRow(ui->bookshelves_table->rowCount());
              int row = ui->bookshelves_table->rowCount()-1;

              ui->bookshelves_table->setItem(row,ISBN,new QTableWidgetItem((*z)->getISBN()));
              ui->bookshelves_table->setItem(row,TITLE,new QTableWidgetItem((*z)->getTitle()));
              ui->bookshelves_table->setItem(row,AUTHOR,new QTableWidgetItem((*z)->getAuthor()));
              ui->bookshelves_table->setItem(row,PUBLISHER,new QTableWidgetItem((*z)->getPublisher()));
              ui->bookshelves_table->setItem(row,FORMAT,new QTableWidgetItem((*z)->getFormat()));
              ui->bookshelves_table->setItem(row,RATING,new QTableWidgetItem(QString::number((*z)->getRating(),'f',2)));
            }
        }
    }

}

void User_View::updateReadingTableSlot() const
{

  ui->readingNow_table->setRowCount(0);
  for(auto it = 0; it < user->getBookshelf().size(); ++it) {

      // If is Reading Bookshelf I replenish the top-left table
      if(user->getBookshelf().at(it)->getName() == "Reading") {

          QVector<QString> temp = user->getBookshelf().at(it)->getBookList();
          // I need to search into the database for the ISBN books and return a list

          std::list<Book*> read_books = controller->returnBooksByISBN(temp);

          for(auto z = read_books.begin(); z != read_books.end(); ++z) {
              ui->readingNow_table->insertRow(ui->readingNow_table->rowCount());
              int row = ui->readingNow_table->rowCount()-1;

              ui->readingNow_table->setItem(row,ISBN,new QTableWidgetItem((*z)->getISBN()));
              ui->readingNow_table->setItem(row,TITLE,new QTableWidgetItem((*z)->getTitle()));


            }}}
}

void User_View::finishBookSLOT(const QString &isbn)
{
  controller->finishBook(isbn,this);
}

void User_View::addBookSlot() const
{
  AddBookFormUser* tempview = new AddBookFormUser(controller);
  tempview->show();
}

void User_View::showAccountInfo()
{
  AccountInfoView* temp_view = new AccountInfoView(user,controller,this);
  controller->showAccountInfo(temp_view);
}

void User_View::showBookSlot(const QModelIndex &index,const QTableWidget* table)
{
  Book_View * temp_view = new Book_View(user,controller,this);
  QString temp = table->item(index.row(),0)->text();
  controller->showBookInfo(temp_view,temp);
}


void User_View::on_search_books_button_clicked()
{
  std::list<const Book*> books = controller->searchBooks(ui->search_books->text());
  if(books.size() != 0) emit showSearchedBooks(books);
  else QMessageBox::warning(0,"Error","No books found!");
}

void User_View::showSearchedBooksSlot(std::list<const Book *> temp)
{
  ui->searched_books->setRowCount(0);

  for(auto it = temp.begin(); it != temp.end(); ++it) {
      ui->searched_books->insertRow(ui->searched_books->rowCount());
      int row = ui->searched_books->rowCount()-1;

      ui->searched_books->setItem(row,ISBN,new QTableWidgetItem((*it)->getISBN()));
      ui->searched_books->setItem(row,TITLE,new QTableWidgetItem((*it)->getTitle()));
      ui->searched_books->setItem(row,AUTHOR,new QTableWidgetItem((*it)->getAuthor()));
      ui->searched_books->setItem(row,PUBLISHER,new QTableWidgetItem((*it)->getPublisher()));
      ui->searched_books->setItem(row,FORMAT,new QTableWidgetItem((*it)->getFormat()));
      ui->searched_books->setItem(row,RATING,new QTableWidgetItem(QString::number((*it)->getRating(),'f',2)));

    }
}

void User_View::on_readingNow_table_doubleClicked(const QModelIndex &index)
{
  emit showBook(index,ui->readingNow_table);
}

void User_View::on_searched_books_doubleClicked(const QModelIndex &index)
{
  emit showBook(index,ui->searched_books);
}

void User_View::on_bookshelves_table_doubleClicked(const QModelIndex &index)
{
  emit showBook(index,ui->bookshelves_table);
}

void User_View::on_AddBookshelf_button_clicked()
{
  NewBookshelfView* temp_view = new NewBookshelfView(user,controller,this);
  controller->showNewBookshelf(temp_view);
}

void User_View::on_bookshelves_list_currentTextChanged(const QString &arg1)
{
  ui->bookshelves_table->setRowCount(0);
  for(int it = 0; it < user->getBookshelf().size(); ++it) {
      if(user->getBookshelf().at(it)->getName() == arg1) {
          // change description
          ui->description_text->setText(user->getBookshelf().at(it)->getDescription());
          std::list<Book*> books_list = controller->returnBooksByISBN(user->getBookshelf().at(it)->getBookList());
          for(auto z = books_list.begin(); z != books_list.end(); ++z) {
              ui->bookshelves_table->insertRow(ui->bookshelves_table->rowCount());
              int row = ui->bookshelves_table->rowCount()-1;

              ui->bookshelves_table->setItem(row,ISBN,new QTableWidgetItem((*z)->getISBN()));
              ui->bookshelves_table->setItem(row,TITLE,new QTableWidgetItem((*z)->getTitle()));
              ui->bookshelves_table->setItem(row,AUTHOR,new QTableWidgetItem((*z)->getAuthor()));
              ui->bookshelves_table->setItem(row,PUBLISHER,new QTableWidgetItem((*z)->getPublisher()));
              ui->bookshelves_table->setItem(row,FORMAT,new QTableWidgetItem((*z)->getFormat()));
              ui->bookshelves_table->setItem(row,RATING,new QTableWidgetItem(QString::number((*z)->getRating(),'f',2)));
            }
          it = user->getBookshelf().size();

        }
    }
}

void User_View::on_readingNow_table_clicked(const QModelIndex &index)
{
  ui->Finished->setEnabled(true);
  isbn_temp = ui->readingNow_table->item(index.row(),0)->text();

}

void User_View::on_Finished_clicked()
{
  emit finishBook(isbn_temp);
}
