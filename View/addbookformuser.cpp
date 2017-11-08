#include "addbookformuser.h"
#include "ui_addbookformuser.h"
#include <QMessageBox>


AddBookFormUser::AddBookFormUser(User_Controller* contr,QWidget *parent) :
  controller(contr),QDialog(parent),
  ui(new Ui::AddBookFormUser)
{
  ui->setupUi(this);
  this->setWindowTitle("New Book");
}

AddBookFormUser::~AddBookFormUser()
{
  delete ui;
}

void AddBookFormUser::on_buttonBox_accepted()
{

  if(ui->iSBNLineEdit->text().isEmpty() || ui->titleLineEdit->text().isEmpty() ||
     ui->authorLineEdit->text().isEmpty() || ui->editionLineEdit->text().isEmpty() ||
     ui->publisherLineEdit->text().isEmpty() || ui->formatLineEdit->text().isEmpty() ||
     ui->DescriptionTextEdit->toPlainText().isEmpty()) {

      QMessageBox::warning(this,tr("Attention!"),tr("Fields cannot be left empty!"),QMessageBox::Cancel);

    } else {
      controller->AddBook(ui->iSBNLineEdit->text(),ui->titleLineEdit->text(),
                          ui->authorLineEdit->text(),ui->editionLineEdit->text(),
                          ui->publisherLineEdit->text(),ui->formatLineEdit->text(),
                          ui->DescriptionTextEdit->toPlainText(),ui->publishingDateDateEdit->date(),0);
      this->close(); }
}

void AddBookFormUser::on_buttonBox_rejected()
{
  this->close();
}
