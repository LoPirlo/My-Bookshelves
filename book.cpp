#include "book.h"

// I won't need any other constructor, since to create a Book I need
// all the information about it
Book::Book(const QString& i,const QString& bt
           ,const QString& ba,const QString& e,
           const QString& publ,const QString& bf,const QString& des,
           const QDate& publ_date,
           const double& br)
  :isbn(i),title(bt),author(ba),edition(e),publisher(publ),format(bf),description(des),
    rating(br),publishing_date(publ_date){}
Book::Book(){}
Book::~Book(){

  genres.clear();
  ratings.clear();
  quotes.clear();
  reviews.clear();
}


QString Book::getISBN() const{ return isbn;}
void Book::setISBN(QString i){ isbn = i;}

QString Book::getTitle() const { return title;}
void Book::setTitle(QString t) { title = t;}

QString Book::getAuthor() const {return author;}
void Book::setAuthor(QString a) {author = a;}

QString Book::getEdition() const { return edition;}
void Book::setEdition(QString e) { edition = e;}

QString Book::getPublisher() const { return publisher;}
void Book::setPublisher(QString publ) { publisher = publ;}

QString Book::getDescription() const { return description;}
void Book::setDescription(QString des) { description = des;}

QString Book::getFormat() const { return format;}
void Book::setFormat(QString bf) {format = bf;}

QDate Book::getPublishingDate() const { return publishing_date;}
void Book::setPublishingDate(QDate publ_date) {publishing_date = publ_date; }

double Book::getRating() const {return rating;}
void Book::setRating(int i){
  // I first of all add the new rating to the list
  addRating(i);

  // and I then calculate the average rate for the book
  double temp = 0;

  for(int i = 0; i < ratings.size(); ++i) {
      temp = temp + ratings.at(i);
    }

  temp = temp/(ratings.size());
  rating =  temp;
}


// BOOK MULTIPLE INFO

QVector<int> Book::getRatings() const { return ratings;}
void Book::setRatings(QVector<int> r) {
  ratings = r;
}

void Book::addRating(int r)
{
  ratings.push_back(r);
}

QMap<QString,QString> Book::getQuotes() const { return quotes;}

void Book::setQuotes(QMap<QString,QString> q){

  quotes = q;
}

void Book::addQuote(QString a, QString q)
{
  quotes[a] = q;
}

QMap<QString,QString>* Book::getReviews(){
  return &reviews;
}
void Book::setReviews(QMap<QString,QString> rev){
  reviews = rev;
}

void Book::addReview(QString u, QString r)
{
  reviews[u] = r;
}

QVector<QString> Book::getGenres() const { return genres;}
void Book::setGenres(QVector<QString> g){
  genres = g;
}
void Book::addGenres(QString genre){ genres.push_back(genre);}




