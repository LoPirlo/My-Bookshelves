#include "adduserform.h"
#include "ui_adduserform.h"
#include "administratormainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

#include <iostream>
using std::cout;

AddUserForm::AddUserForm(Admin_Controller* controller,AdministratorMainWindow* temp_view,QWidget *parent) :
  QDialog(parent), view(temp_view),admin(controller),
  ui(new Ui::AddUserForm)
{
  ui->setupUi(this);

}

AddUserForm::~AddUserForm()
{
  delete ui;
  delete view;
  delete admin;
}

void AddUserForm::on_buttonBox_accepted()
{
  // control the email format

  QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

  if(admin->getUser(ui->usernameLineEdit->text()) != nullptr) {
      QMessageBox::warning(0,"Attention","This username has already been taken!",QMessageBox::Cancel);
    } else if(ui->usernameLineEdit->text().isEmpty() || ui->nameLineEdit->text().isEmpty() || ui->surnameLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty()
              || ui->emailLineEdit->text().isEmpty()){
      QMessageBox::warning(0,"Attention","No field should be left empty. Fill all the fields and try again!",QMessageBox::Cancel);
    } else if(ui->usernameLineEdit->text().length() <= 5) {
      QMessageBox::warning(0,"Attention","The Username field should contain at least 6 characters!",QMessageBox::Cancel);

    } else if(ui->passwordLineEdit->text().length() <= 5) {
      QMessageBox::warning(0,"Attention","The Password field should contain at least 6 characters!",QMessageBox::Cancel);
    } else  if(!regex.match(ui->emailLineEdit->text()).hasMatch()){
      QMessageBox::warning(0,"Attention","Email has to be in format: name@me.something!");
    } else {

      admin->addUser(ui->usernameLineEdit->text(),ui->nameLineEdit->text(),ui->surnameLineEdit->text(),ui->passwordLineEdit->text(),
                     ui->emailLineEdit->text(),ui->typeComboBox->currentText());
      emit view->init_UserTable();
    }}
