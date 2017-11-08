#ifndef REVIEWSLISTVIEW_H
#define REVIEWSLISTVIEW_H

#include <QWidget>

namespace Ui {
  class ReviewsListView;
}

class ReviewsListView : public QWidget
{
  Q_OBJECT

public:
  explicit ReviewsListView(QMap<QString,QString>*,QWidget *parent = 0);
  ~ReviewsListView();

private slots:
  void on_review_list_doubleClicked(const QModelIndex &index);

  void on_backButton_clicked();

private:
  Ui::ReviewsListView *ui;

  QMap<QString,QString>* reviews;

  enum Columns_Book{
    USERNAME,
    REVIEW
  };

};

#endif // REVIEWSLISTVIEW_H
