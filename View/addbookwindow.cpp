#include "addbookwindow.h"
#include "ui_addbookwindow.h"

#include <iostream>
    
using std::cout;
AddBookWindow::AddBookWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookWindow)
{

    ui->setupUi(this);
}

AddBookWindow::~AddBookWindow()
{
    delete ui;
}


Book AddBookWindow::getBook() const
{
    return mbook;
}

void AddBookWindow::on_confirmation_accepted()
{
    mbook.setISBN(ui->ISBN_2->text());
    mbook.setTitle(ui->Title_2->text());
    mbook.setAuthor(ui->Author_2->text());
    mbook.setRating(ui->rating->value());
    accept();
}

void AddBookWindow::on_confirmation_rejected()
{
    reject();
}


