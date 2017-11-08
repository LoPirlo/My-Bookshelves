#include "Controller/client.h"
#include "View/login.h"
#include <iostream>
#include <QMessageBox>

Client::Client() {

  database = new Database();
  main = new Login(database,this);
  main->show();

}

Client::~Client()
{
  delete database;
}

void Client::checkCredentials(const QString &u, const QString &p)
{
  if(database->getUsers().contains(u)) {
      if(database->getUsers().find(u).value()->getPassword() == p) {
          // DO LOGIN
          // Create User Controller and pass the User* to the controller who will
          // open the proper window
          user = database->getUsers().find(u).value();
          controller = new User_Controller(database,user);
          main->hide();
        } else // WRONG PASSWORD
        QMessageBox::warning(0,"Access Denied","Wrong password!");
    } else // USER DOESN'T EXIST
    QMessageBox::warning(0,"Access Denied","This user doesn't exist!");
}

void Client::AddUser(const QString &u, const QString &n, const QString &s, const QString &p, const QString &e, const QString &t)
{
  if(database->getUsers().contains(u)) {

    } else {
      database->AddUser(u,n,s,p,e,t);
    }

}
