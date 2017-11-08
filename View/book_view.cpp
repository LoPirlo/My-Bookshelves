#include "book_view.h"
#include "ui_book_view.h"
#include "View/bookshelflist_view.h"
#include "View/reviewslistview.h"
#include "View/user_view.h"
#include <QMessageBox>
#include <iostream>
using std::cout;


Book_View::Book_View(User* user,User_Controller* controller,User_View* view,QWidget *parent) :
  user_temp(user),contr(controller),user_view(view),QMainWindow(parent),
  ui(new Ui::Book_View)
{
  ui->setupUi(this);

  ui->actionModify_Details->setVisible(false);
  ui->actionSave_Modifications->setVisible(false);

  if(user->getType() == "User_Normal") {
      hideFromUser_Normal();
    }

  if(user->getType() == "Moderator") {
      ui->actionModify_Details->setVisible(true);
      ui->actionSave_Modifications->setVisible(true);
      ui->actionSave_Modifications->setEnabled(false);
    }


  // setting the EditFields read-only

  ui->Title_TextEdit->setReadOnly(true);
  ui->ISBN_textEdit->setReadOnly(true);
  ui->Author_TextEdit->setReadOnly(true);
  ui->Description_TextEdit->setReadOnly(true);
  ui->Ratings_textEdit->setReadOnly(true);
  ui->Rating_textEdit->setReadOnly(true);
  ui->published_textEdit->setReadOnly(true);
  ui->published_by_textEdit->setReadOnly(true);
  ui->Format_textEdit->setReadOnly(true);
  ui->Edition_textEdit->setReadOnly(true);

  connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
  connect(ui->actionAdd_Book_to_Bookshelf,SIGNAL(triggered()),this,SLOT(addToBookshelf()));
  connect(ui->actionRemove_from_Bookshelf,SIGNAL(triggered()),this,SLOT(removeFromBookshelves()));
  connect(ui->actionSee_Reviews,SIGNAL(triggered()),this,SLOT(seeReviewsList()));
  connect(ui->actionModify_Details,SIGNAL(triggered()),this,SLOT(setEditable()));
  connect(ui->actionSave_Modifications,SIGNAL(triggered()),this,SLOT(saveModifications()));
}

Book_View::~Book_View()
{
  delete ui;
}

void Book_View::showInfo(const QString &isbn)
{
  Book* temp = contr->getBooks().value(isbn);
  this->setWindowTitle(temp->getTitle());

  ui->Title_TextEdit->setText(temp->getTitle());
  ui->ISBN_textEdit->setText(temp->getISBN());
  ui->Author_TextEdit->setText(temp->getAuthor());
  ui->Description_TextEdit->setText(temp->getDescription());
  ui->Ratings_textEdit->setText(QString::number(temp->getRatings().size()));
  ui->Rating_textEdit->setText(QString::number(temp->getRating(),1,2));
  ui->published_textEdit->setDate(temp->getPublishingDate());
  ui->published_by_textEdit->setText(temp->getPublisher());
  ui->Format_textEdit->setText(temp->getFormat());
  ui->Edition_textEdit->setText(temp->getEdition());

  if(!(temp->getReviews()->isEmpty()) && user_temp->getType() != "User_Normal" && temp->getReviews()->find(user_temp->getUsername()) != temp->getReviews()->end()) {
      ui->Review_TextEdit->setPlainText(temp->getReviews()->find(user_temp->getUsername()).value());

    }
}

void Book_View::hideFromUser_Normal() const
{
  delete ui->Review_TextEdit;
  delete ui->add_review_button;
  delete ui->add_review_label;
}

void Book_View::addToBookshelf()
{
  // I open a new window
  BookshelfList_View* temp = new BookshelfList_View(user_temp,contr,ui->ISBN_textEdit->toPlainText(),user_view);
  temp->show();
}

void Book_View::setEditable()
{
  ui->actionSave_Modifications->setEnabled(true);

  ui->Title_TextEdit->setReadOnly(false);
  ui->Author_TextEdit->setReadOnly(false);
  ui->Description_TextEdit->setReadOnly(false);
  ui->published_textEdit->setReadOnly(false);
  ui->published_by_textEdit->setReadOnly(false);
  ui->Format_textEdit->setReadOnly(false);
  ui->Edition_textEdit->setReadOnly(false);
}

void Book_View::saveModifications()
{
  ui->actionSave_Modifications->setEnabled(false);

  ui->Title_TextEdit->setReadOnly(true);
  ui->Author_TextEdit->setReadOnly(true);
  ui->Description_TextEdit->setReadOnly(true);
  ui->published_textEdit->setReadOnly(true);
  ui->published_by_textEdit->setReadOnly(true);
  ui->Format_textEdit->setReadOnly(true);
  ui->Edition_textEdit->setReadOnly(true);

  if(ui->ISBN_textEdit->toPlainText().isEmpty()) {
      QMessageBox::warning(this,tr("Attention!"),tr("ISBN can't be left empty!"),QMessageBox::Cancel);
    } else if(ui->Title_TextEdit->toPlainText().isEmpty() || ui->Author_TextEdit->toPlainText().isEmpty() ||
     ui->Edition_textEdit->toPlainText().isEmpty() || ui->published_by_textEdit->toPlainText().isEmpty() || ui->Format_textEdit->toPlainText().isEmpty() ||
     ui->Description_TextEdit->toPlainText().isEmpty())
    {
      int ret = QMessageBox::warning(this,tr("Attention!"),tr("There are some empty fields. \n"
                                                              "Are you sure you want to continue?"),QMessageBox::Save | QMessageBox::Cancel,
                                     QMessageBox::Save);
      switch(ret) {
        case QMessageBox::Save:
          contr->SetBook(ui->ISBN_textEdit->toPlainText(),ui->Title_TextEdit->toPlainText(),ui->Author_TextEdit->toPlainText(),
                         ui->Edition_textEdit->toPlainText(),ui->published_by_textEdit->toPlainText(),ui->Format_textEdit->toPlainText(),
                         ui->Description_TextEdit->toPlainText(),ui->published_textEdit->date());
          // update tables under it
          emit user_view->updateBSTable();
          emit user_view->updateReadingTable();
          break;
        }


  // I need to save the book details

    } else {
      contr->SetBook(ui->ISBN_textEdit->toPlainText(),ui->Title_TextEdit->toPlainText(),ui->Author_TextEdit->toPlainText(),
                     ui->Edition_textEdit->toPlainText(),ui->published_by_textEdit->toPlainText(),ui->Format_textEdit->toPlainText(),
                     ui->Description_TextEdit->toPlainText(),ui->published_textEdit->date());
      // update tables under it
      emit user_view->updateBSTable();
      emit user_view->updateReadingTable();
    }


}

void Book_View::on_add_review_button_clicked()
{
  contr->addReview(user_temp->getUsername(),ui->Review_TextEdit->toPlainText(),ui->ISBN_textEdit->toPlainText());

}

void Book_View::removeFromBookshelves()
{
  int ret = QMessageBox::warning(this,tr("Attention!"),tr("You will remove the current book from ALL the bookshelves! \n"
                                                          "Are you sure you want to continue?"),QMessageBox::Save | QMessageBox::Cancel,
                                 QMessageBox::Save);
  switch(ret) {
    case QMessageBox::Save:
      contr->removeBookFromBS(ui->ISBN_textEdit->toPlainText());
      emit user_view->updateBSTable();
      emit user_view->updateReadingTable();
      break;
    }



}

void Book_View::seeReviewsList()
{
  // show reviews window
  QMap<QString,QString>* temp = (*contr->getBooks().find(ui->ISBN_textEdit->toPlainText()))->getReviews();

  ReviewsListView* view_temp = new ReviewsListView(temp);
  view_temp->show();

}
