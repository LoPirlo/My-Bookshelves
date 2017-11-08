#include "login.h"
#include "ui_login.h"
#include <iostream>
#include <QMessageBox>
#include <QRegularExpression>

using std::cout;

Login::Login(Database* db,Client* cli,QWidget *parent) :
  QMainWindow(parent),database(db),client(cli),
  ui(new Ui::Login)
{
  ui->setupUi(this);

  this->setWindowTitle("My Bookshelves");

  ui->confirmLogin->setVisible(false);
  ui->passwordLabel->setVisible(false);
  ui->passwordLineEdit->setVisible(false);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  ui->usernameLabel->setVisible(false);
  ui->usernameLineEdit->setVisible(false);
  ui->isAdmin->setVisible(false);
  ui->line_2->setVisible(false);
  ui->cancelLogin->setVisible(false);
  ui->loginLabel->setVisible(false);

  ui->logoLabel->move(250,50);

  ui->formWidget->hide();
  ui->line->hide();
  ui->registrationLabel->hide();
  ui->interactionBox->hide();




}

Login::~Login()
{
  delete ui;
  delete admin_view;
  delete admin_contr;
}

void Login::on_User_clicked()
{
  ui->line_2->setVisible(true);
  ui->isAdmin->setVisible(true);
  ui->cancelLogin->setVisible(true);
  ui->loginLabel->setVisible(true);

  ui->logoLabel->move(50,50);

  ui->confirmLogin->setVisible(true);
  ui->passwordLabel->setVisible(true);
  ui->passwordLineEdit->setVisible(true);
  ui->usernameLabel->setVisible(true);
  ui->usernameLineEdit->setVisible(true);
}

void Login::on_confirmLogin_clicked()
{
  if(ui->isAdmin->isChecked()) {
      admin = new Administrator(database);
      admin_contr = new Admin_Controller(admin);

      // do Login method
      admin_contr->Login();
      this->hide();
    } else
    {
      client->checkCredentials(ui->usernameLineEdit->text(),ui->passwordLineEdit->text());
    }
}

void Login::on_Register_clicked()
{
  // show the registration form

  ui->formWidget->show();
  ui->line->show();
  ui->registrationLabel->show();
  ui->interactionBox->show();
  this->setFixedHeight(600);

}


void Login::on_confirmRegistration_clicked()
{
  // control the email format

  QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

  if(database->getUsers().contains(ui->reUsernameLineEdit->text())) {
      QMessageBox::warning(0,"Attention","This username has already been taken!");
    } else if(ui->reUsernameLineEdit->text().isEmpty() || ui->reNameLineEdit->text().isEmpty() || ui->reSurnameLineEdit->text().isEmpty() || ui->rePasswordLineEdit->text().isEmpty() ||
              ui->reEmailLineEdit->text().isEmpty()){
      QMessageBox::warning(0,"Attention","No field should be left empty. Fill all the fields and try again!");
    } else if(ui->reUsernameLineEdit->text().length() <= 5) {
      QMessageBox::warning(0,"Attention","The Username field should contain at least 6 characters!");

    } else if(ui->rePasswordLineEdit->text().length() <= 5) {
      QMessageBox::warning(0,"Attention","The Password field should contain at least 6 characters!");
    } else if(!regex.match(ui->reEmailLineEdit->text()).hasMatch()) {
      QMessageBox::warning(0,"Attention","Email has to be in format: name@me.something!");
    } else {
      ui->formWidget->hide();
      ui->line->hide();
      ui->registrationLabel->hide();
      this->setFixedHeight(240);

      client->AddUser(ui->reUsernameLineEdit->text(),ui->reNameLineEdit->text(),ui->reSurnameLineEdit->text(),
                      ui->rePasswordLineEdit->text(),ui->reEmailLineEdit->text(),ui->ReaccountTypeLineEdit->currentText());


    }

}

void Login::on_isAdmin_toggled(bool checked)
{   if(checked) {
      ui->usernameLineEdit->setEnabled(false);
      ui->passwordLineEdit->setEnabled(false);
    } else {
      ui->usernameLineEdit->setEnabled(true);
      ui->passwordLineEdit->setEnabled(true);
    }
}

void Login::on_cancelRegistration_clicked()
{
  ui->formWidget->hide();
  ui->line->hide();
  ui->registrationLabel->hide();
  ui->interactionBox->hide();
  this->setFixedHeight(240);
}

void Login::on_cancelLogin_clicked()
{
  ui->line_2->setVisible(false);
  ui->isAdmin->setVisible(false);
  ui->cancelLogin->setVisible(false);
  ui->loginLabel->setVisible(false);

  ui->logoLabel->move(250,50);

  ui->confirmLogin->setVisible(false);
  ui->passwordLabel->setVisible(false);
  ui->passwordLineEdit->setVisible(false);
  ui->usernameLabel->setVisible(false);
  ui->usernameLineEdit->setVisible(false);
}
