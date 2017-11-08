#include <iostream>
#include <QDate>

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

#include "home_window.h"
#include "ui_home_window.h"
#include "addbookwindow.h"

#include <iostream>

using std::cout;

Home_window::Home_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home_window)
{
    ui->setupUi(this);
    QStringList titles = {"ISBN","Title","Author","AddedDate","ReadDate","Rating"};
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(titles);
}

Home_window::~Home_window()
{
    delete ui;
}

void Home_window::on_addBook_button_clicked()
{

    AddBookWindow bookm(this);
    // I do nothing if I press "Cancel"
    if(bookm.exec() == QDialog::Rejected)
            return;

    addBook(bookm.getBook());
}

void Home_window::on_exit_button_clicked()
{
    close();
}

// METHODS TO MANIPULATE THE XMLFile

void Home_window::addBook(const Book &book)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int row = ui->tableWidget->rowCount()-1;

    // I add each element to the new row
    ui->tableWidget->setItem(row,ISBN_,new QTableWidgetItem(book.getISBN()));
    ui->tableWidget->setItem(row,TITLE,new QTableWidgetItem(book.getTitle()));
    ui->tableWidget->setItem(row,AUTHOR,new QTableWidgetItem(book.getAuthor()));
   /* ui->tableWidget->setItem(row,ADDED_DATE,
                             new QTableWidgetItem(book.getAddedDate().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row,READ_DATE,
                             new QTableWidgetItem(book.getReadDate().toString("dd.MM.yyyy")));
    */
    ui->tableWidget->setItem(row,RATING,
                             new QTableWidgetItem(QString::number(book.getRating())));
}


void Home_window::on_remove_book_clicked()
{
   ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void Home_window::on_save_file_clicked()
{   auto filename = QFileDialog::getSaveFileName(this,"Save File",QDir::rootPath(),"XML file (*.xml)");

    if(filename.isEmpty())
        return;

    QDomDocument doc;
    // I create the root of the document
    auto root = doc.createElement("Books");

    doc.appendChild(root);

    const int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i < rowCount; ++i) {

        /*QDate added_date_temp = QDate::fromString(ui->tableWidget->item(i,ADDED_DATE)->text(),"dd.MM.yyyy");
        QDate read_date_temp = QDate::fromString(ui->tableWidget->item(i,READ_DATE)->text(),"dd.MM.yyyy");
        int rating_temp = ui->tableWidget->item(i,RATING)->text().toInt();
        Book temp_book(ui->tableWidget->item(i,ISBN_)->text(), ui->tableWidget->item(i,TITLE)->text(),
                       ui->tableWidget->item(i,AUTHOR)->text(),
                       rating_temp,
                       added_date_temp,
                       read_date_temp);
        auto elementBook = doc.createElement("Book");
        // I set the attribute of Book, which must be ISBN
        elementBook.setAttribute("ISBN",temp_book.getISBN());

        // I will now create the elements tags

        auto eTitle = doc.createElement("title");
        auto eAuthor = doc.createElement("author");
        auto eAddedDate = doc.createElement("addeddate");
        auto eReadDate = doc.createElement("readdate");
        auto eRating = doc.createElement("rating");

        // And insert the text into the right place

        eTitle.appendChild(doc.createTextNode(temp_book.getTitle()));
        eAuthor.appendChild(doc.createTextNode(temp_book.getAuthor()));
        eAddedDate.appendChild(doc.createTextNode(temp_book.getAddedDate().toString("dd.MM.yyyy")));
        eReadDate.appendChild(doc.createTextNode(temp_book.getReadDate().toString("dd.MM.yyyy")));
        eRating.appendChild(doc.createTextNode(QString::number(temp_book.getRating())));

        // Connecting the tags between them
        elementBook.appendChild(eTitle);
        elementBook.appendChild(eAuthor);
        elementBook.appendChild(eAddedDate);
        elementBook.appendChild(eReadDate);
        elementBook.appendChild(eRating);
        root.appendChild(elementBook);


    }
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Error!",file.errorString());
        return;
    }

    QTextStream xout(&file);
    xout << doc.toString();
    file.flush();
    file.close();

}

void Home_window::on_open_file_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,
                                                 "Open File",QDir::rootPath(),"XML file(*.xml)");
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this,"Error!",file.errorString());
        return;
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();   // we can close it because we've got all in "doc" variable

    auto root = doc.firstChild().toElement();
    auto ix = root.firstChild().toElement();
    while(!ix.isNull()) {
        auto ISBN = ix.attribute("ISBN");
        auto title = ix.firstChild().toElement().text();
        auto author = ix.firstChild().nextSibling().toElement().text();
        QDate added_date = QDate::fromString(ix.firstChild().nextSibling().nextSibling().toElement().text(),"dd.MM.yyyy");
        QDate read_date = QDate::fromString(ix.firstChild().nextSibling().nextSibling().nextSibling().toElement().text(),"dd.MM.yyyy");
        auto rating = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text().toInt();

        addBook(Book(ISBN,title,author,rating,added_date,read_date));
        ix = ix.nextSibling().toElement();
    }

}
