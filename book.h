#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QDate>
#include <QMap>
#include <QVector>

class Book {
private:

  QString isbn,title,author,edition,publisher,
  format,description;
  double rating;
  QDate publishing_date;


  // Book multiple information
  QVector<QString> genres;

  QVector<int> ratings;

  QMap<QString,QString> quotes;   //Author, review

  QMap<QString,QString> reviews;  //Username, Review


public:
  // ===========================
  //  Constructors & Destructor
  // ===========================

  Book(const QString&,const QString&,const QString&,const QString&,const QString&,
       const QString&,const QString&,const QDate&,const double&);
  Book();
  virtual ~Book();

  // ========================================
  //  Methods used to retrieve and save data
  // ========================================

  QString getISBN() const;
  void setISBN(QString);

  QString getTitle() const;
  void setTitle(QString);

  QString getAuthor() const;
  void setAuthor(QString);

  QString getEdition() const;
  void setEdition(QString);

  QString getPublisher() const;
  void setPublisher(QString);

  QString getFormat() const;
  void setFormat(QString);

  QDate getPublishingDate() const;
  void setPublishingDate(QDate);

  QString getDescription() const;
  void setDescription(QString);

  double getRating() const;
  void setRating(int);


  // MULTIPLE INFO

  QVector<int> getRatings() const;
  void setRatings(QVector<int>);
  void addRating(int);

  QMap<QString,QString> getQuotes() const;
  void setQuotes(QMap<QString,QString>);
  void addQuote(QString,QString);

  QMap<QString,QString>* getReviews();
  void setReviews(QMap<QString,QString>);
  void addReview(QString, QString);

  QVector<QString> getGenres() const;
  void setGenres(QVector<QString>);
  void addGenres(QString);


};

#endif // BOOK_H
