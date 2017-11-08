#include "administratormainwindow.h"
#include "ui_administratormainwindow.h"
#include "admin_userinfo.h"
#include "Controller/admin_controller.h"

#include <QMessageBox>
#include <iostream>

using std::cout;
AdministratorMainWindow::AdministratorMainWindow(Admin_Controller* temp,QWidget *parent) :
  QMainWindow(parent),controller(temp),
  ui(new Ui::AdministratorMainWindow)
{
  ui->setupUi(this);

  this->setWindowTitle("administrator");

  QStringList titles = {"Username","Name","Surname","Email","Type"};
  ui->user_table->setColumnCount(5);
  ui->user_table->setHorizontalHeaderLabels(titles);
  ui->user_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  connect(this,SIGNAL(init_UserTable()),this,SLOT(refull_UserTable()));
  connect(this,SIGNAL(showSearchedUsers(std::list<const User*>)),this,SLOT(showSearchedUsersSlot(std::list<const User*>)));


  // Action set
  connect(ui->actionOpen_Book,SIGNAL(triggered()),this,SLOT(showBooksTable()));
  connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
  connect(ui->actionAdd_User_2,SIGNAL(triggered()),this,SLOT(on_AddUser_Button_clicked()));
}

AdministratorMainWindow::~AdministratorMainWindow()
{
  delete ui;
  delete controller;
  delete addUser;
  delete ad_b;
}

void AdministratorMainWindow::LoadUserTable() const
{

  emit init_UserTable();
}


void AdministratorMainWindow::refull_UserTable() const {
  ui->user_table->setRowCount(0);
  for(auto it: controller->getUsers().keys()){

      ui->user_table->insertRow(ui->user_table->rowCount());
      int row = ui->user_table->rowCount()-1;

      ui->user_table->setItem(row,USERNAME,new QTableWidgetItem(controller->getUsers().value(it)->getUsername()));
      ui->user_table->setItem(row,NAME,new QTableWidgetItem(controller->getUsers().value(it)->getName()));
      ui->user_table->setItem(row,SURNAME,new QTableWidgetItem(controller->getUsers().value(it)->getSurname()));
      ui->user_table->setItem(row,EMAIL,new QTableWidgetItem(controller->getUsers().value(it)->getEmail()));
      ui->user_table->setItem(row,TYPE,new QTableWidgetItem(controller->getUsers().value(it)->getType()));

    }
}

void AdministratorMainWindow::showSearchedUsersSlot(std::list<const User *> temp) const
{
  ui->user_table->setRowCount(0);

  for(auto it = temp.begin(); it != temp.end(); ++it) {
      ui->user_table->insertRow(ui->user_table->rowCount());
      int row = ui->user_table->rowCount()-1;


      ui->user_table->setItem(row,USERNAME,new QTableWidgetItem((*it)->getUsername()));
      ui->user_table->setItem(row,NAME,new QTableWidgetItem((*it)->getName()));
      ui->user_table->setItem(row,SURNAME,new QTableWidgetItem((*it)->getSurname()));
      ui->user_table->setItem(row,EMAIL,new QTableWidgetItem((*it)->getEmail()));
      ui->user_table->setItem(row,TYPE,new QTableWidgetItem((*it)->getType()));


    }
}

void AdministratorMainWindow::showBooksTable()
{
  // I show the Books interface
  ad_b = new Admin_books(controller);
  controller->showBookList(ad_b);

}

void AdministratorMainWindow::showUserInfo()
{
  addUser = new AddUserForm(controller,this);
  addUser->show();
}


void AdministratorMainWindow::on_AddUser_Button_clicked()
{

  addUser = new AddUserForm(controller,this);
  addUser->show();
}

void AdministratorMainWindow::on_user_table_doubleClicked(const QModelIndex &index)
{
  Admin_UserInfo* user_info_window = new Admin_UserInfo(controller,this);

  // I get the Username from the first column in the row I've clicked
  QString temp = ui->user_table->item(index.row(),0)->text();
  controller->showUserInfo(user_info_window,temp);

}


void AdministratorMainWindow::on_searchButton_clicked()
{
  std::list<const User*> users = controller->searchUsers(ui->searchEdit->text());
  if(users.size() != 0) emit showSearchedUsers(users);
  else QMessageBox::warning(0,"Error","No users found!");
}
