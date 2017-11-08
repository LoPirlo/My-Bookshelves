#include "newbookshelfview.h"
#include "ui_newbookshelfview.h"
#include <QMessageBox>

NewBookshelfView::NewBookshelfView(User* u,User_Controller* contr,User_View* temp_view,QWidget *parent) :
  user(u),controller(contr),view(temp_view),QDialog(parent),
  ui(new Ui::NewBookshelfView)
{
  ui->setupUi(this);
  this->setWindowTitle("New Bookshelf");
}

NewBookshelfView::~NewBookshelfView()
{
  delete ui;
  delete user;
  delete controller;
  delete view;
}

void NewBookshelfView::on_buttonBox_accepted()
{
  if(user->checkIfBSExists(ui->nameLineEdit->text())) {
      QMessageBox::information(0,"Attention!","A bookshelf with the same name already exists",QMessageBox::Cancel);
    } else if(ui->nameLineEdit->text().isEmpty()){

      QMessageBox::warning(0,"Attention!","A bookshelf need a name!",QMessageBox::Cancel); }
  else{
      controller->addBookshelf(ui->nameLineEdit->text(),ui->descriptionLineEdit->text());
      // I need to update the Main Window BSList
      emit view->updateBSList();

    }
}

void NewBookshelfView::on_buttonBox_rejected()
{
    this->close();
}
