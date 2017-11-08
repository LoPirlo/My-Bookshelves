#include "admin_books.h"
#include "ui_admin_books.h"
#include "View/addbookform.h"
#include "book.h"
#include <QMessageBox>

Admin_books::Admin_books(Admin_Controller* contr,QWidget *parent) :
  admin_contr(contr),QMainWindow(parent),
  ui(new Ui::Admin_books)
{
  ui->setupUi(this);

  QStringList titles = {"ISBN","Title","Author","Publisher","Format","Rating"};

  ui->tableWidget->setColumnCount(6);
  ui->tableWidget->setHorizontalHeaderLabels(titles);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  connect(ui->actionAdd_Book,SIGNAL(triggered()),this,SLOT(on_addBook_button_clicked()));
  connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
  connect(this,SIGNAL(signalShowBooks()),this,SLOT(slotShowBooks()));
  connect(this,SIGNAL(showSearchedBooks(std::list<const Book*>)),this,SLOT(showSearchedBooksSlot(std::list<const Book*>)));
}

Admin_books::~Admin_books()
{
  delete book_view;
  delete admin_contr;
  delete ui;
}

void Admin_books::showBookList() const
{
  emit signalShowBooks();
}

void Admin_books::slotShowBooks() const
{
  ui->tableWidget->setRowCount(0);
  // I need to refill the table
  for(auto it: admin_contr->getBooks().keys()) {
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());
      int row = ui->tableWidget->rowCount()-1;

      ui->tableWidget->setItem(row,ISBN,new QTableWidgetItem(admin_contr->getBooks().value(it)->getISBN()));
      ui->tableWidget->setItem(row,TITLE,new QTableWidgetItem(admin_contr->getBooks().value(it)->getTitle()));
      ui->tableWidget->setItem(row,AUTHOR,new QTableWidgetItem(admin_contr->getBooks().value(it)->getAuthor()));
      ui->tableWidget->setItem(row,PUBLISHER,new QTableWidgetItem(admin_contr->getBooks().value(it)->getPublisher()));
      ui->tableWidget->setItem(row,FORMAT,new QTableWidgetItem(admin_contr->getBooks().value(it)->getFormat()));
      ui->tableWidget->setItem(row,RATING,new QTableWidgetItem(QString::number(admin_contr->getBooks().value(it)->getRating(),'f',2)));
    }

}

void Admin_books::showSearchedBooksSlot(std::list<const Book *>temp) const
{
  ui->tableWidget->setRowCount(0);

  for(auto it = temp.begin(); it != temp.end(); ++it) {
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());
      int row = ui->tableWidget->rowCount()-1;

      ui->tableWidget->setItem(row,ISBN,new QTableWidgetItem((*it)->getISBN()));
      ui->tableWidget->setItem(row,TITLE,new QTableWidgetItem((*it)->getTitle()));
      ui->tableWidget->setItem(row,AUTHOR,new QTableWidgetItem((*it)->getAuthor()));
      ui->tableWidget->setItem(row,PUBLISHER,new QTableWidgetItem((*it)->getPublisher()));
      ui->tableWidget->setItem(row,FORMAT,new QTableWidgetItem((*it)->getFormat()));
      ui->tableWidget->setItem(row,RATING,new QTableWidgetItem(QString::number((*it)->getRating(),'f',2)));

    }
}

void Admin_books::on_addBook_button_clicked()
{
  AddBookForm* addBook = new AddBookForm(admin_contr,this);
  addBook->show();
}

void Admin_books::on_tableWidget_doubleClicked(const QModelIndex &index)
{
  book_view = new Admin_BookView(admin_contr,this);

  QString temp = ui->tableWidget->item(index.row(),0)->text();

  admin_contr->showBookInfo(book_view,temp);
}

void Admin_books::on_searchBook_button_clicked()
{
  std::list<const Book*> books = admin_contr->searchBooks(ui->searchBook_lineEdit->text());
  if(books.size() != 0) emit showSearchedBooks(books);
  else QMessageBox::warning(0,"Error","No books found!");
}
