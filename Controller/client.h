#ifndef CLIENT_H
#define CLIENT_H

#include "database.h"
#include "View/login.h"
#include "user_controller.h"

class Login;
class User_Controller;
class Client {
private:
  Database* database;
  User* user;
  User_Controller* controller;

  // view main
  Login* main;
public:
  Client();
  ~Client();

  void checkCredentials(const QString&,const QString&);
  void AddUser(const QString &u,const QString &n,const QString &s,const QString &p,const QString &e,const QString &t);


};

#endif // CLIENT_H
