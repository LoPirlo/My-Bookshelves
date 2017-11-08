#include "accountinfoview.h"
#include "ui_accountinfoview.h"
#include "Controller/user_controller.h"
#include "View/user_view.h"
#include <QMessageBox>

AccountInfoView::AccountInfoView(User* u, User_Controller*contr,User_View* temp_view,QWidget *parent) :
  user(u),controller(contr),view(temp_view),QMainWindow(parent),
  ui(new Ui::AccountInfoView)
{
  ui->setupUi(this);

  this->setWindowTitle(u->getUsername());
  // show all the necessary info

  // user_info

  ui->usernameLineEdit->setText(user->getUsername());
  ui->nameLineEdit->setText(user->getName());
  ui->surnameLineEdit->setText(user->getSurname());
  ui->passwordLineEdit->setText(user->getPassword());
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  ui->emailLineEdit->setText(user->getEmail());
  ui->typeLineedit->setText(user->getType());

  if(user->getType() == "User_Normal") {
      hideFromNormal();
    }

  for(auto it = 0; it < user->getBookshelf().size(); ++it) {
      ui->bsComboBox->addItem(user->getBookshelf().at(it)->getName());
    }
  ui->bsname->setText(user->getBookshelf().at(0)->getName());
  ui->bsDescription->setText(user->getBookshelf().at(0)->getDescription());

  ui->saveModification->setVisible(false);
  ui->SaveBookshelf->setVisible(false);
  ui->removeBookshelf->setVisible(false);



  if(ui->bsComboBox->currentText() == "Read" || ui->bsComboBox->currentText() == "Reading" || ui->bsComboBox->currentText() == "To read") {
      ui->modifyBookshelf->setEnabled(false);
    }




  connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
  connect(this,SIGNAL(updateBSFields()),this,SLOT(updateBSFieldsSlot()));
}

AccountInfoView::~AccountInfoView()
{
  delete ui;
  delete user;
  delete controller;
  delete view;
}

void AccountInfoView::hideFromNormal()
{
  ui->modifyBookshelf->setVisible(false);
}

void AccountInfoView::updateBSFieldsSlot()
{
  ui->bsComboBox->clear();
  // refresh all the infos of the BS

  for(auto it = 0; it < user->getBookshelf().size(); ++it) {
      ui->bsComboBox->addItem(user->getBookshelf().at(it)->getName());
    }
  ui->bsname->setText(user->getBookshelf().at(0)->getName());
  ui->bsDescription->setText(user->getBookshelf().at(0)->getDescription());

}

void AccountInfoView::on_modifyUser_clicked()
{
  ui->nameLineEdit->setEnabled(true);
  ui->surnameLineEdit->setEnabled(true);
  ui->passwordLineEdit->setEnabled(true);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
  ui->emailLineEdit->setEnabled(true);
  ui->modifyUser->setVisible(false);
  ui->saveModification->setVisible(true);
  ui->deleteAccount->setEnabled(true);

}

void AccountInfoView::on_modifyBookshelf_clicked()
{
  ui->bsDescription->setEnabled(true);
  ui->bsname->setEnabled(true);
  ui->removeBookshelf->setVisible(true);
  ui->SaveBookshelf->setVisible(true);
}

void AccountInfoView::on_saveModification_clicked()
{
  ui->nameLineEdit->setEnabled(false);
  ui->surnameLineEdit->setEnabled(false);
  ui->passwordLineEdit->setEnabled(false);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  ui->emailLineEdit->setEnabled(false);
  ui->modifyUser->setVisible(true);
  ui->saveModification->setVisible(false);

  // save modifications of the user
  controller->setUser(ui->nameLineEdit->text(),ui->surnameLineEdit->text(),ui->passwordLineEdit->text(),ui->emailLineEdit->text());
}

void AccountInfoView::on_SaveBookshelf_clicked()
{
  if(ui->bsname->text().isEmpty()) {
      QMessageBox::warning(0,"Attention!","A bookshelf need a name!",QMessageBox::Cancel);
    } else {
      ui->bsDescription->setEnabled(false);
      ui->bsname->setEnabled(false);
      ui->SaveBookshelf->setVisible(false);
      ui->removeBookshelf->setVisible(false);

      controller->setBookshelf(ui->bsComboBox->currentText(),ui->bsname->text(),ui->bsDescription->toPlainText());

      emit updateBSFields();
      emit view->updateBSList();
    }
}

void AccountInfoView::on_bsComboBox_currentTextChanged(const QString &arg1)
{
  for(auto it = 0; it != user->getBookshelf().size(); ++it) {
      if( user->getBookshelf().at(it)->getName()== arg1) {
          ui->bsname->setText(user->getBookshelf().at(it)->getName());
          ui->bsDescription->setText(user->getBookshelf().at(it)->getDescription());
          if(ui->bsComboBox->currentText() != "Read" || ui->bsComboBox->currentText() != "Reading" || ui->bsComboBox->currentText() != "To read") {
              ui->modifyBookshelf->setEnabled(true);
          }

        }
    }
}

void AccountInfoView::on_removeBookshelf_clicked()
{
  if(ui->bsComboBox->currentText() == "Read" || ui->bsComboBox->currentText() == "To Read" || ui->bsComboBox->currentText() == "Reading") {
      QMessageBox::warning(this,"Attention!","You can't remove standard Bookshelves!");
    } else {
      controller->removeBS(ui->bsComboBox->currentText());
      // update BSList Combo Box on parent widget
      emit view->updateBSList();
      emit updateBSFields();
    }
}

void AccountInfoView::on_deleteAccount_clicked()
{
  int ret = QMessageBox::warning(this,tr("Attention!"),tr("You will be PERMANENTLY removed from My Bookshelves! \n"
                                                          "All your details and Bookshelves will also be deleted. \n"
                                                          "Are you sure you want to delete your account?"),QMessageBox::Save | QMessageBox::Cancel,
                                 QMessageBox::Save);
  switch(ret) {
    case QMessageBox::Save:
      controller->removeAccount(user->getUsername());
      this->close();
      view->close();
      break;
    }
}
