#ifndef REVIEWVIEW_H
#define REVIEWVIEW_H

#include <QDialog>

namespace Ui {
  class reviewview;
}

class reviewview : public QDialog
{
  Q_OBJECT

public:
  explicit reviewview(QMap<QString,QString>*,QString,QWidget *parent = 0);
  ~reviewview();

private slots:

  void on_closeButton_clicked();

private:
  Ui::reviewview *ui;
};

#endif // REVIEWVIEW_H
