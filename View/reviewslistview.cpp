#include "reviewslistview.h"
#include "ui_reviewslistview.h"
#include "reviewview.h"
#include <iostream>

using std::cout;
using std::endl;

ReviewsListView::ReviewsListView(QMap<QString,QString>* revs,QWidget *parent) :
  reviews(revs),QWidget(parent),
  ui(new Ui::ReviewsListView)
{
  ui->setupUi(this);
  this->setWindowTitle("Reviews");

  QStringList titles = {"Username","Review"};
  ui->review_list->setColumnCount(2);
  ui->review_list->setHorizontalHeaderLabels(titles);

  if(!reviews->empty()) {
      for(auto e: reviews->keys()) {
          ui->review_list->insertRow(ui->review_list->rowCount());
          int row = ui->review_list->rowCount()-1;

          ui->review_list->setItem(row,USERNAME,new QTableWidgetItem(e));
          ui->review_list->setItem(row,REVIEW,new QTableWidgetItem(reviews->value(e)));
        }
    }


}

ReviewsListView::~ReviewsListView()
{
  delete ui;
}

void ReviewsListView::on_review_list_doubleClicked(const QModelIndex &index)
{
  // create here the window
    cout << reviews->size();


  QString username = ui->review_list->item(index.row(),0)->text();
  reviewview* temp = new reviewview(reviews,username);

  temp->show();
}

void ReviewsListView::on_backButton_clicked()
{
    this->close();
}
