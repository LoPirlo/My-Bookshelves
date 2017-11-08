#include "View/selectionmenu.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QToolTip>
#include <QFormLayout>

SelectionMenu::SelectionMenu(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("My Bookshelves");

    this->setFixedSize(800,600);
    quit = new QPushButton(tr("Quit"),this);
    login = new QPushButton(tr("Login"),this);
    registration = new QPushButton(tr("Register"),this);



    quit->setFont(QFont("Times",14));
    quit->setGeometry(325,375,150,40);
    login->setFont(QFont("Times",16));
    login->setGeometry(175,275,200,50);
    registration->setFont(QFont("Times",16));
    registration->setGeometry(425,275,200,50);


    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    connect(login,SIGNAL(clicked()),this,SLOT(addLoginForm()));
    connect(registration,SIGNAL(clicked()),this,SLOT(addRegistrationForm()));
}

SelectionMenu::~SelectionMenu(){}

void SelectionMenu::addLoginForm()
{
    // I hide the main buttons
    quit->setVisible(false);
    login->setVisible(false);
    registration->setVisible(false);

    setWindowTitle("Login");

    // I need now to show a new layout for the login form
    QLabel* username_label = new QLabel("Username",this);
    username_label->setFont(QFont("Times",16));
    username_label->setFixedWidth(200);
    QLineEdit* username_edit = new QLineEdit(this);
    username_edit->setFixedSize(250,50);
    username_edit->setFont(QFont("Times",13));
    username_edit->setToolTip(tr("Insert your username"));
    username_edit->setToolTipDuration(3000);

    QLabel* password_label = new QLabel("Password",this);
    password_label->setFont(QFont("Times",16));
    password_label->setFixedWidth(200);
    QLineEdit* password_edit = new QLineEdit(this);
    password_edit->setFixedSize(250,50);
    password_edit->setToolTip(tr("Insert your password"));
    password_edit->setFont(QFont("Times",13));
    password_edit->setToolTipDuration(3000);
    password_edit->setEchoMode(QLineEdit::Password);


    QLabel* admin_check_label = new QLabel("Admin",this);
    admin_check_label->setFont(QFont("Times",13));
    QCheckBox* admin_check = new QCheckBox(this);
    admin_check->setToolTip(tr("Are you an administrator?"));
    admin_check->setToolTipDuration(3000);
    // admin_check->setGeometry(100,100,50,20);


    QPushButton* confirm_login = new QPushButton(tr("Login"),this);
    confirm_login->setFixedSize(120,40);
    confirm_login->setFont(QFont("Times",12));
    QPushButton* cancel_login = new QPushButton(tr("Cancel"),this);
    cancel_login->setFixedSize(120,40);
    cancel_login->setFont(QFont("Times",12));

    login_layout = new QVBoxLayout();
    QHBoxLayout* username_layout = new QHBoxLayout();
    QHBoxLayout* password_layout = new QHBoxLayout();
    QHBoxLayout* admin_check_layout = new QHBoxLayout();
    QHBoxLayout* buttons_layout = new QHBoxLayout();

    username_layout->addStretch(1);
    username_layout->addWidget(username_label);
    username_layout->addWidget(username_edit);
    username_layout->addStretch(1);


    password_layout->addStretch(1);
    password_layout->addWidget(password_label);
    password_layout->addWidget(password_edit);
    password_layout->addStretch(1);

    admin_check_layout->addStretch(1);
    admin_check_layout->addWidget(admin_check_label);
    admin_check_layout->addWidget(admin_check);
    admin_check_layout->addStretch(1);

    buttons_layout->addStretch(1);
    buttons_layout->addWidget(cancel_login);
    buttons_layout->addSpacerItem(new QSpacerItem(20,0,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
    buttons_layout->addWidget(confirm_login);
    buttons_layout->addStretch(1);

    login_layout->addStretch(1);
    login_layout->addLayout(username_layout);
    login_layout->addLayout(password_layout);
    login_layout->addSpacerItem(new QSpacerItem(0,20,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
    login_layout->addLayout(admin_check_layout);
    login_layout->addSpacerItem(new QSpacerItem(0,20,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
    login_layout->addLayout(buttons_layout);
    login_layout->addStretch(1);

    setLayout(login_layout);

    connect(cancel_login,SIGNAL(clicked()),this,SLOT(backToMenu()));

}

void SelectionMenu::addRegistrationForm()
{


    // I hide the main buttons
    quit->setVisible(false);
    login->setVisible(false);
    registration->setVisible(false);

    setWindowTitle("Registration");



    QLabel* username_label = new QLabel("Username:",this);
    username_label->setFont(QFont("Times",16));
    username_label->setFixedWidth(200);
    QLineEdit* username_edit = new QLineEdit(this);
    username_edit->setFont(QFont("Times",13));
    username_edit->setFixedSize(250,50);

    QLabel* password_label = new QLabel("Password:",this);
    password_label->setFont(QFont("Times",16));
    password_label->setFixedWidth(200);
    QLineEdit* password_edit = new QLineEdit(this);
    password_edit->setFont(QFont("Times",13));
    password_edit->setFixedSize(250,50);

    QLabel* name_label = new QLabel("Name:",this);
    name_label->setFont(QFont("Times",16));
    name_label->setFixedWidth(200);
    QLineEdit* name_edit = new QLineEdit(this);
    name_edit->setFont(QFont("Times",13));
    name_edit->setFixedSize(250,50);

    QLabel* surname_label = new QLabel("Surname:",this);
    surname_label->setFont(QFont("Times",16));
    surname_label->setFixedWidth(200);
    QLineEdit* surname_edit = new QLineEdit(this);
    surname_edit->setFont(QFont("Times",13));
    surname_edit->setFixedSize(250,50);

    QLabel* email_label = new QLabel("Email:",this);
    email_label->setFont(QFont("Times",16));
    email_label->setFixedWidth(200);
    QLineEdit* email_edit = new QLineEdit(this);
    email_edit->setFont(QFont("Times",13));
    email_edit->setFixedSize(250,50);

    QPushButton* confirm_register = new QPushButton(tr("Register"),this);
    confirm_register->setFixedSize(120,40);
    confirm_register->setFont(QFont("Times",12));
    QPushButton* cancel_register = new QPushButton(tr("Cancel"),this);
    cancel_register->setFixedSize(120,40);
    cancel_register->setFont(QFont("Times",12));

    register_layout = new QVBoxLayout();
    QHBoxLayout* username_layout = new QHBoxLayout();
    QHBoxLayout* password_layout = new QHBoxLayout();
    QHBoxLayout* name_layout = new QHBoxLayout();
    QHBoxLayout* surname_layout = new QHBoxLayout();
    QHBoxLayout* email_layout = new QHBoxLayout();
    QHBoxLayout* buttons_layout = new QHBoxLayout();


    username_layout->addStretch(1);
    username_layout->addWidget(username_label);
    username_layout->addWidget(username_edit);
    username_layout->addStretch(1);


    password_layout->addStretch(1);
    password_layout->addWidget(password_label);
    password_layout->addWidget(password_edit);
    password_layout->addStretch(1);

    name_layout->addStretch(1);
    name_layout->addWidget(name_label);
    name_layout->addWidget(name_edit);
    name_layout->addStretch(1);

    surname_layout->addStretch(1);
    surname_layout->addWidget(surname_label);
    surname_layout->addWidget(surname_edit);
    surname_layout->addStretch(1);

    email_layout->addStretch(1);
    email_layout->addWidget(email_label);
    email_layout->addWidget(email_edit);
    email_layout->addStretch(1);

    buttons_layout->addStretch(1);
    buttons_layout->addWidget(cancel_register);
    buttons_layout->addSpacerItem(new QSpacerItem(20,0,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
    buttons_layout->addWidget(confirm_register);
    buttons_layout->addStretch(1);

    register_layout->addStretch(1);
    register_layout->addLayout(username_layout);
    register_layout->addLayout(password_layout);
    register_layout->addLayout(name_layout);
    register_layout->addLayout(surname_layout);
    register_layout->addLayout(email_layout);
    register_layout->addSpacerItem(new QSpacerItem(0,50,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
    register_layout->addLayout(buttons_layout);
    register_layout->addStretch(2);

    setLayout(register_layout);

    connect(cancel_register,SIGNAL(clicked()),this,SLOT(backToMenu()));

}

void SelectionMenu::backToMenu()
{
    if(this->layout()==login_layout)
    {
        clearLayout(login_layout);
        delete login_layout;
        setWindowTitle("My Bookshelves");
    }   else {
        clearLayout(register_layout);
        delete register_layout;
        setWindowTitle("My Bookshelves");
    }

    quit->setVisible(true);
    login->setVisible(true);
    registration->setVisible(true);

}


void SelectionMenu::clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
    if(child->layout() != 0)
    clearLayout( child->layout() );
    else if(child->widget() != 0)
    delete child->widget();

        delete child;
    }

}

