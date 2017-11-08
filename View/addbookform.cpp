#include "addbookform.h"
#include "ui_addbookform.h"
#include <QDialogButtonBox>
#include <QMessageBox>
#include "admin_books.h"

AddBookForm::AddBookForm(Admin_Controller* contr,Admin_books* temp_view,QWidget *parent) :
  controller(contr),view(temp_view),QWidget(parent),
  ui(new Ui::AddBookForm)
{
  ui->setupUi(this);

  connect(ui->confirmation,SIGNAL(accepted()),this,SLOT(on_confirmation_accepted()));
  connect(ui->confirmation,SIGNAL(rejected()),this,SLOT(on_confirmation_rejected()));
}

AddBookForm::~AddBookForm()
{
  delete controller;
  delete view;
  delete ui;
}

Book AddBookForm::getBook() const
{
  return mbook;
}


void AddBookForm::on_confirmation_accepted()
{

  if(ui->iSBNLineEdit->text().isEmpty() || ui->titleLineEdit->text().isEmpty() || ui->authorLineEdit->text().isEmpty() ||
     ui->editionLineEdit->text().isEmpty() || ui->publisherLineEdit->text().isEmpty() || ui->formatLineEdit->text().isEmpty() ||
     ui->DescriptionTextEdit->toPlainText().isEmpty())
    {
          QMessageBox::warning(0,tr("Attention!"),tr("Fields can't be left empty!"),QMessageBox::Cancel);

     } else {

      controller->AddBook(ui->iSBNLineEdit->text(),ui->titleLineEdit->text(),
                          ui->authorLineEdit->text(),ui->editionLineEdit->text(),
                          ui->publisherLineEdit->text(),ui->formatLineEdit->text(),
                          ui->DescriptionTextEdit->toPlainText(),ui->publishingDateDateEdit->date(),0);

     // emit view->signalShowBooks();
      this->close();
    }

}
void AddBookForm::on_confirmation_rejected()
{
  this->close();
}
