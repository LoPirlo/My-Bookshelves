#include "admin_userinfo.h"
#include "ui_admin_userinfo.h"
#include "administratormainwindow.h"
#include <iostream>
#include <QMessageBox>

using std::cout;


Admin_UserInfo::Admin_UserInfo(Admin_Controller* controller,AdministratorMainWindow* temp_view,QWidget *parent) :
  contr(controller),view(temp_view),QMainWindow(parent),
  ui(new Ui::Admin_UserInfo)
{
  ui->setupUi(this);

  QStringList titles = {"ISBN","Title","Author","Publisher","Format","Rating"};
  ui->bookshelves_table->setColumnCount(6);
  ui->bookshelves_table->setHorizontalHeaderLabels(titles);
  ui->bookshelves_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



  connect(this,SIGNAL(SaveInfo(QString,QString,QString,QString,QString)),this,SLOT(SaveInfoSLOT(QString,QString,QString,QString,QString)));
  connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
}

Admin_UserInfo::~Admin_UserInfo()
{
  delete ui;
  delete temp;
}

void Admin_UserInfo::show_info(const QString &user)
{
  // I first get the pointer to the User
  temp = contr->getUser(user);

  this->setWindowTitle(temp->getUsername()+"'s Details");
  // and then I refull the fields

  ui->usernameLineEdit->setText(temp->getUsername());
  ui->nameLineEdit->setText(temp->getName());
  ui->surnameLineEdit->setText(temp->getSurname());
  ui->passwordLineEdit->setText(temp->getPassword());
  ui->emailLineEdit->setText(temp->getEmail());
  if(temp->getType() == "User_Normal")
    ui->typeComboBox->setCurrentIndex(0);
  else if(temp->getType() == "User_Pro")
    ui->typeComboBox->setCurrentIndex(1);
  else
    ui->typeComboBox->setCurrentIndex(2);

  // I hide the password
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  ui->typeComboBox->setEnabled(false);

  // Setting the Bookshelves
  for(int i = 0; i < temp->getBookshelf().size(); i++) {
      ui->bookshelves_list->addItem(temp->getBookshelf().at(i)->getName());
    }

  ui->description_text->setText(temp->getBookshelf().at(0)->getDescription());

  // settings the table

  for(auto it = 0; it < temp->getBookshelf().size(); ++it) {
      if(ui->bookshelves_list->currentText() == temp->getBookshelf().at(it)->getName())
        {
          ui->bookshelves_table->setRowCount(0);

          std::list<Book*> books_list = contr->returnBooksByISBN(temp->getBookshelf().at(it)->getBookList());

          for(auto z = books_list.begin(); z != books_list.end(); ++z) {
              ui->bookshelves_table->insertRow(ui->bookshelves_table->rowCount());
              int row = ui->bookshelves_table->rowCount()-1;

              ui->bookshelves_table->setItem(row,ISBN,new QTableWidgetItem((*z)->getISBN()));
              ui->bookshelves_table->setItem(row,TITLE,new QTableWidgetItem((*z)->getTitle()));
              ui->bookshelves_table->setItem(row,AUTHOR,new QTableWidgetItem((*z)->getAuthor()));
              ui->bookshelves_table->setItem(row,PUBLISHER,new QTableWidgetItem((*z)->getPublisher()));
              ui->bookshelves_table->setItem(row,FORMAT,new QTableWidgetItem((*z)->getFormat()));
              ui->bookshelves_table->setItem(row,RATING,new QTableWidgetItem(QString::number((*z)->getRating(),'f',2)));
            }
        }
    }

}

void Admin_UserInfo::SaveInfoSLOT(const QString &u, const QString &n, const QString &s, const QString &e, const QString &t) const
{
  contr->setUser(u,n,s,e,t);
}

void Admin_UserInfo::on_ModifyButton_pressed()
{
  ui->usernameLineEdit->setEnabled(false);
  ui->nameLineEdit->setEnabled(true);
  ui->surnameLineEdit->setEnabled(true);
  ui->emailLineEdit->setEnabled(true);
  ui->ModifyButton->setEnabled(false);
  ui->typeComboBox->setEnabled(true);

}

void Admin_UserInfo::on_saveButton_pressed()
{
  ui->usernameLineEdit->setEnabled(false);
  ui->nameLineEdit->setEnabled(false);
  ui->surnameLineEdit->setEnabled(false);
  ui->emailLineEdit->setEnabled(false);
  ui->typeComboBox->setEnabled(false);
  ui->ModifyButton->setEnabled(true);


  emit SaveInfo(ui->usernameLineEdit->text(),ui->nameLineEdit->text(),ui->surnameLineEdit->text(),ui->emailLineEdit->text(),ui->typeComboBox->itemText(ui->typeComboBox->currentIndex()));
  emit view->init_UserTable();

}

void Admin_UserInfo::on_bookshelves_list_currentTextChanged(const QString &arg1)
{
  ui->bookshelves_table->setRowCount(0);
  for(int it = 0; it < temp->getBookshelf().size(); ++it) {
      if(temp->getBookshelf().at(it)->getName() == arg1) {
          // change description
          ui->description_text->setText(temp->getBookshelf().at(it)->getDescription());

          std::list<Book*> books_list = contr->returnBooksByISBN(temp->getBookshelf().at(it)->getBookList());

          for(auto z = books_list.begin(); z != books_list.end(); ++z) {
              ui->bookshelves_table->insertRow(ui->bookshelves_table->rowCount());
              int row = ui->bookshelves_table->rowCount()-1;

              ui->bookshelves_table->setItem(row,ISBN,new QTableWidgetItem((*z)->getISBN()));
              ui->bookshelves_table->setItem(row,TITLE,new QTableWidgetItem((*z)->getTitle()));
              ui->bookshelves_table->setItem(row,AUTHOR,new QTableWidgetItem((*z)->getAuthor()));
              ui->bookshelves_table->setItem(row,PUBLISHER,new QTableWidgetItem((*z)->getPublisher()));
              ui->bookshelves_table->setItem(row,FORMAT,new QTableWidgetItem((*z)->getFormat()));
              ui->bookshelves_table->setItem(row,RATING,new QTableWidgetItem(QString::number((*z)->getRating(),'f',2)));
            }
          it = temp->getBookshelf().size();

        }
    }
}

void Admin_UserInfo::on_removeUser_clicked()
{

  int ret = QMessageBox::warning(this,tr("Attention!"),tr("The user will be PERMANENTLY removed! \n"
                                                          "Are you sure you want to remove it?"),QMessageBox::Save | QMessageBox::Cancel,
                                 QMessageBox::Save);
  switch(ret) {
    case QMessageBox::Save:
      contr->removeUser(ui->usernameLineEdit->text());
      this->close();
      emit view->init_UserTable();
      break;
    }


}
