#include "admin_bookview.h"
#include "ui_admin_bookview.h"
#include "admin_books.h"
#include "book.h"
#include <QMessageBox>

Admin_BookView::Admin_BookView(Admin_Controller* contr,Admin_books* temp_view,QWidget *parent) :
  controller(contr),view(temp_view),QDialog(parent),
  ui(new Ui::Admin_BookView)
{
  ui->setupUi(this);

  connect(this,SIGNAL(saveBookInfo(QString,QString,QString,QString,QString,QString,QString,QDate)),this,SLOT(saveBookInfoSlot(QString,QString,QString,QString,QString,QString,QString,QDate)));
}

Admin_BookView::~Admin_BookView()
{
  delete ui;
  delete controller;
  delete temp;
}

void Admin_BookView::show_info(const QString& i) {
  temp = controller->getBooks().find(i).value();
  this->setWindowTitle(temp->getTitle());
  ui->iSBNLineEdit->setText(temp->getISBN());
  ui->titleLineEdit->setText(temp->getTitle());
  ui->authorLineEdit->setText(temp->getAuthor());
  ui->editionLineEdit->setText(temp->getEdition());
  ui->publisherLineEdit->setText(temp->getPublisher());
  ui->formatLineEdit->setText(temp->getFormat());
  ui->DescriptionTextEdit->appendPlainText(temp->getDescription());
  ui->publishedDateEdit->setDate(temp->getPublishingDate());

  //setting all the infos disabled and only to be seen
  ui->iSBNLineEdit->setEnabled(false);
  ui->titleLineEdit->setEnabled(false);
  ui->authorLineEdit->setEnabled(false);
  ui->editionLineEdit->setEnabled(false);
  ui->publisherLineEdit->setEnabled(false);
  ui->formatLineEdit->setEnabled(false);
  ui->DescriptionTextEdit->setReadOnly(true);
  ui->publishedDateEdit->setEnabled(false);


  ui->saveChanges->setVisible(false);
}

void Admin_BookView::saveBookInfoSlot(const QString &i, const QString &t, const QString &a, const QString &e, const QString &p, const QString &f,const QString &d,  const QDate &date) const
{
  controller->modifyBook(i,t,a,e,p,f,d,date);
}

void Admin_BookView::on_saveChanges_clicked()
{
  ui->saveChanges->setVisible(false);

  ui->titleLineEdit->setEnabled(false);
  ui->authorLineEdit->setEnabled(false);
  ui->editionLineEdit->setEnabled(false);
  ui->publisherLineEdit->setEnabled(false);
  ui->formatLineEdit->setEnabled(false);
  ui->DescriptionTextEdit->setReadOnly(true);
  ui->publishedDateEdit->setEnabled(false);

  emit saveBookInfo(ui->iSBNLineEdit->text(),ui->titleLineEdit->text(),
                    ui->authorLineEdit->text(),ui->editionLineEdit->text(),
                    ui->publisherLineEdit->text(),ui->formatLineEdit->text(),
                    ui->DescriptionTextEdit->toPlainText(),ui->publishedDateEdit->date());
  emit view->signalShowBooks();
  ui->modifyBook->setEnabled(true);
}

void Admin_BookView::on_modifyBook_clicked()
{
  ui->modifyBook->setEnabled(false);
  ui->titleLineEdit->setEnabled(true);
  ui->authorLineEdit->setEnabled(true);
  ui->editionLineEdit->setEnabled(true);
  ui->publisherLineEdit->setEnabled(true);
  ui->formatLineEdit->setEnabled(true);
  ui->DescriptionTextEdit->setReadOnly(false);
  ui->publishedDateEdit->setEnabled(true);

  ui->saveChanges->setVisible(true);
}


void Admin_BookView::on_removeBook_clicked()
{
  int ret = QMessageBox::warning(this,tr("Attention!"),tr("The book will be PERMANENTLY removed! \n"
                                                          "Are you sure you want to remove it?"),QMessageBox::Save | QMessageBox::Cancel,
                                 QMessageBox::Save);
  switch(ret) {
    case QMessageBox::Save:
      controller->removeBook(ui->iSBNLineEdit->text());
      emit view->signalShowBooks();
      this->close();
      break;
    }
}

void Admin_BookView::on_backButton_clicked()
{
    this->close();
}
