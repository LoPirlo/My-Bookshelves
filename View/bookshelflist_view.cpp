#include "bookshelflist_view.h"
#include "ui_bookshelflist_view.h"
#include <QMessageBox>

BookshelfList_View::BookshelfList_View(User*u,User_Controller* contr,const QString& i,User_View*view,QWidget *parent) :
  user(u),controller(contr),isbn(i),user_view(view),QDialog(parent),
  ui(new Ui::BookshelfList_View)
{
  ui->setupUi(this);

  this->setWindowTitle("Add to bookshelf");
  // Replenish the bookshelf list

  for(auto it = 0; it < user->getBookshelf().size(); ++it) {
      ui->comboBox->addItem(user->getBookshelf().at(it)->getName());
    }
}

BookshelfList_View::~BookshelfList_View()
{
  delete ui;
}

void BookshelfList_View::on_buttonBox_accepted()
{
  for(int it = 0; it < user->getBookshelf().size(); ++it) {
      if(user->getBookshelf().at(it)->getName() == ui->comboBox->currentText()) {

          if(user->getBookshelf().at(it)->getName() == "Reading") {

              if(user->checkIfBookExistsInBS(isbn,"Reading")) {
                  QMessageBox::warning(0,"Attention!","You're already reading this Book!");
                } else
                {
                  controller->addBookToBS(it,isbn);
                  emit user_view->updateReadingTable();
                }}
          else if(user->getBookshelf().at(it)->getName() == "To Read") {
              if(user->checkIfBookExistsInBS(isbn,"To Read")) {
                  QMessageBox::warning(0,"Attention!","You're already planning to read this Book!");
                } else
                {
                  controller->addBookToBS(it,isbn);
                  emit user_view->updateBSTable();
                }


            } else if(user->checkIfBookExistsInBS(isbn,user->getBookshelf().at(it)->getName())) {
              QMessageBox::warning(0,"Attention!","This book already exists in the selected Bookshelf");
            } else {
              controller->addBookToBS(it,isbn);
              emit user_view->updateBSTable();
            }

        }
    }
}
