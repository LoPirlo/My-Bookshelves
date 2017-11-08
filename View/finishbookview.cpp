#include "finishbookview.h"
#include "ui_finishbookview.h"
#include "Controller/user_controller.h"
#include "View/user_view.h"

FinishBookView::FinishBookView(User* u,User_Controller* contr,Book* b,User_View* view,QWidget *parent) :
  user(u),controller(contr),book(b),user_view(view),QDialog(parent),
  ui(new Ui::FinishBookView)
{

  ui->setupUi(this);

  this->setWindowTitle("Finished the book?");

  for(int it = 0; it < u->getBookshelf().size(); ++it) {
      ui->addToComboBox->addItem(u->getBookshelf().at(it)->getName());
    }

  // set user's review in order to edit it if user already read the book
  if(b->getReviews()->find(u->getUsername()) != b->getReviews()->end()) {
  ui->reviewLineEdit->setPlainText(b->getReviews()->find(u->getUsername()).value());
    }
}

FinishBookView::~FinishBookView()
{
  delete ui;
}

void FinishBookView::on_reviewButton_clicked()
{
  book->addRating(ui->ratingSpinBox->text().toInt());
  book->setRating(ui->ratingSpinBox->text().toInt());
  controller->addReview(user->getUsername(),ui->reviewLineEdit->toPlainText(),book->getISBN());

  // now I need to remove the Book from the reading Bookshelf and add it to the selected one

  for(int it = 0; it < user->getBookshelfToModify()->size(); it++) {
      if(user->getBookshelf().at(it)->getName() == "Reading") {
          for(int z = 0; z < (*user->getBookshelf().at(it)).getBookList().size(); z++) {
              if((*user->getBookshelf().at(it)).getBookListToModify()->at(z) == book->getISBN()){
                  (*user->getBookshelf().at(it)).getBookListToModify()->removeAt(z);
                  for(int it = 0; it < user->getBookshelfToModify()->size(); it++) {
                      if(user->getBookshelfToModify()->at(it)->getName() == ui->addToComboBox->currentText()) {
                          user->getBookshelfToModify()->at(it)->addBook(book->getISBN());
                        }
                    }
                }
            }
        }
    }
  if(ui->addToComboBox->currentText() != "Reading") {
      emit user_view->updateBSTable();
      emit user_view->updateReadingTable();
    } else emit user_view->updateReadingTable();

  this->close();
}
