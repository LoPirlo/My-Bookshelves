#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QVector>
#include <QString>
#include <list>
#include "book.h"

class Bookshelf {

private:
  QString name, description;

  QVector<QString> bl;
public:
  // ===========================
  //  Constructors & Destructor
  // ===========================

  Bookshelf();
  Bookshelf(const Bookshelf&);
  Bookshelf(const QString&,const QString&);
  Bookshelf(const QString &, const QString &,const QVector<QString>&);

  ~Bookshelf();
  // ========================================
  //  Methods used to retrieve and save data
  // ========================================

  QString getName() const;
  void setName(QString);

  QString getDescription() const;
  void setDescription(QString);
  QVector<QString> getBookList() const;
  QVector<QString>* getBookListToModify();
  void setBookList(QVector<QString>);
  // ================================================
  //  Other methods needed to manipulate the objects
  // ================================================

  void addBook(const QString&);

  // removes one book from the bookshelf
  void remBook_BS(const QString&);

  // check if Bookshelf is empty
  bool isEmpty() const;

  // modify the name and description of the Bookshelf
  void modifyBookshelf(const QString&,const QString&);

};

#endif // BOOKSHELF_H
