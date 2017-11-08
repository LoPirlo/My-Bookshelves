#include "database.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <iostream>

#include <QVector>


using std::cout;


QString Database::db_file = "./resources/Databases/User_Database.xml";
QString Database::bc_file = "./resources/Databases/Book_Database.xml";

Database::Database() {
  Load();
}

Database::~Database() {
  // I close the database

  Save();
  container.clear();
  book_container.clear();
  //bookshelf_container.clear();
}


QMap<QString,User*> Database::getUsers()const { return container;}
QMap<QString,Book*> Database::getBooks()const { return book_container;}
//QMap<QString,Bookshelf*> Database::getBookshelves()const { return bookshelf_container;}


// ==== USER MANIPULATION =====

// OK
void Database::RemoveUser(const QString& u)
{
  container.remove(u);
}
// OK
void Database::AddUser(const QString &u, const QString &n, const QString &s,
                       const QString &p, const QString &e,const QString& t)
{
  if(t == "User_Normal")
    {
      container[u] = new User_Normal(u,n,s,p,e,t);
    }   else if(t == "User_Pro")
    {
      container[u] = new User_Pro(u,n,s,p,e,t);
    } else // t == "Moderator"
      container[u] = new Moderator(u,n,s,p,e,t);
}


// OK
void Database::UpdateUserType(const QString &u, const QString &t)
{
  container.find(u).value()->setType(t);
}


User* Database::SearchUser(const QString &u) const
{
  if(checkIfExists(u)) {
      return container.find(u).value();
    }
  // if the user doesn't exists
  return 0;
}


bool Database::checkIfExists(const QString& u) const {
  if(container.find(u) != container.end())
    return true;
  return false;
}


// ==== BOOK STUFF ====

// OK
void Database::AddBook(const QString& i,const QString& bt
                       ,const QString& ba,const QString& e,
                       const QString& publ,const QString& bf,const QString& des,
                       const QDate& publ_date,
                       const double& br)
{
  book_container[i] = new Book(i,bt,ba,e,publ,bf,des,publ_date,br);
}
// OK
void Database::RemoveBook(const QString&i){

  book_container.remove(i);

}

void Database::SetBook(const QString &i, const QString &bt, const QString &ba, const QString &e, const QString &publ, const QString &bf, const QString &des, const QDate &publ_date)
{
 Book* temp = SearchSpecificBook(i);

 temp->setTitle(bt);
 temp->setAuthor(ba);
 temp->setEdition(e);
 temp->setPublisher(publ);
 temp->setFormat(bf);
 temp->setDescription(des);
 temp->setPublishingDate(publ_date);

}
// OK
std::list<const Book*> Database::SearchBook(const QString& query)
{   std::list<const Book*> temp;

    for(auto it: book_container.keys()) {
        if(it.contains(query,Qt::CaseInsensitive) ||
           book_container.value(it)->getTitle().contains(query,Qt::CaseInsensitive) ||
           book_container.value(it)->getAuthor().contains(query,Qt::CaseInsensitive) ||
           book_container.value(it)->getPublisher().contains(query,Qt::CaseInsensitive) ||
           book_container.value(it)->getFormat().contains(query,Qt::CaseInsensitive))

          // if any of the above is fitting then I push the book into the results
          temp.push_back(book_container.value(it));
      }

      return temp;

}

Book* Database::SearchSpecificBook(const QString& isbn) const {
  if(checkIfBookExists(isbn)) {
      return book_container.find(isbn).value();
    }
  return 0;
}


bool Database::checkIfBookExists(const QString&i) const{
  if(book_container.find(i) != book_container.end())
    return true;
  return false;
}
// OK
std::list<Book *> Database::returnBooksByISBN(const QVector<QString>& temp) const
{
  std::list<Book*> book_list;

  for(int z = 0; z < temp.size(); z++) {
      if(book_container.contains(temp.at(z))) {
          book_list.push_back(book_container.value(temp.at(z)));
        }
    }

  return book_list;

}

// ==== DATABASE MANIPULATION =====

void Database::Load() {
  // === USER STUFF ===

  QFile file(db_file);
  QString u,p,n,s,e,t,bs_t,bs_des;
  QVector<Bookshelf*> bookshelf_temp;
  QVector<QString> bs_book_temp;
  if(file.open(QIODevice::ReadOnly)) {

      QXmlStreamReader temp(&file);

      while(!temp.atEnd()){
          if(temp.isStartElement()){
              if(temp.name() == "users" || temp.name() =="user" || temp.name() == "bookshelves" || temp.name() == "bookshelf" || temp.name() == "books" ) {
                  temp.readNext();
                } else if(temp.name() == "username") {
                  u = temp.readElementText();

                } else if(temp.name() == "password") {
                  p = temp.readElementText();
                } else if(temp.name() == "name") {
                  n = temp.readElementText();
                } else if(temp.name() == "surname") {
                  s = temp.readElementText();
                } else if(temp.name() == "email"){
                  e = temp.readElementText();
                } else if(temp.name() == "type"){
                  t = temp.readElementText();
                }
              // HERE IS Bookshelves stuff
              else if(temp.name() == "title"){
                  bs_t = temp.readElementText();
                } else if(temp.name() == "description") {
                  bs_des = temp.readElementText();
                } else if(temp.name() == "isbn") {
                  bs_book_temp.push_back(temp.readElementText());
                }
            } else if(temp.isEndElement() && temp.name() == "bookshelf") {

              bookshelf_temp.push_back(new Bookshelf(bs_t,bs_des,bs_book_temp));

              // I need now to reset bs_t,bs_des, bs_book_temp for further Bookshelf additions

              bs_book_temp.clear();

              temp.readNext();

            } else if(temp.isEndElement() && temp.name() == "user") {
              //
              // I save the user into the Database

              if(t == "User_Normal") {
                  container[u] = new User_Normal(u,n,s,p,e,t,bookshelf_temp);
                } else if (t == "User_Pro") {
                  container[u] = new User_Pro(u,n,s,p,e,t,bookshelf_temp);
                } else if (t == "Moderator") {
                  container[u] = new Moderator(u,n,s,p,e,t,bookshelf_temp);
                }
              bookshelf_temp.clear();

              temp.readNext();
            } else temp.readNext();
        }
    }
  file.close();

  // === BOOK STUFF ===

  QFile file2(bc_file);
  QString i,bt,ba,e1,publ,bf,des,user,author,quote_auth,review_us,genre_temp;
  QDate publ_date;
  double br;
  int temp_rate;

  QVector<int> ratings_temp;
  QVector<QString> genres_temp;
  QMap<QString,QString> quotes_temp;
  QMap<QString,QString> reviews_temp;

  if(file2.open(QIODevice::ReadOnly)) {

      QXmlStreamReader temp2(&file2);
      temp2.readNext();


      while(!temp2.atEnd()) {
          if(temp2.isStartElement()){
              if(temp2.name()=="books" || temp2.name()=="book" || temp2.name() == "quotes" || temp2.name() == "quote" || temp2.name() == "genres" || temp2.name() == "ratings" || temp2.name() == "reviews" || temp2.name() == "review"){
                  temp2.readNext();
                }   else if(temp2.name()== "isbn") {
                  i = temp2.readElementText();
                }   else if(temp2.name() == "title") {
                  bt = temp2.readElementText();
                }   else if(temp2.name() == "author") {
                  ba = temp2.readElementText();
                }   else if(temp2.name() == "edition") {
                  e1 = temp2.readElementText();
                }   else if(temp2.name() == "publisher") {
                  publ = temp2.readElementText();
                }   else if(temp2.name() == "format") {
                  bf = temp2.readElementText();
                }   else if(temp2.name() == "description") {
                  des = temp2.readElementText();
                }   else if(temp2.name() == "publishing_date") {
                  publ_date = QDate::fromString(temp2.readElementText(),"dd/MM/yyyy");
                }   else if(temp2.name() == "genre") {
                  genre_temp = temp2.readElementText();
                }   else if(temp2.name() == "rating") {
                  br = temp2.readElementText().toDouble();
                }   else if(temp2.name() == "rating_u") {
                  temp_rate= temp2.readElementText().toDouble();
                }   else if(temp2.name() == "quote_content"){
                  quote_auth = temp2.readElementText();
                }   else if(temp2.name() == "review_content") {
                  review_us = temp2.readElementText();
                }   else if(temp2.name() == "author_quote") {
                  author = temp2.readElementText();
                } else if(temp2.name() == "user") {
                  user = temp2.readElementText();
                }

            }  else if(temp2.isEndElement() && temp2.name() == "book") {
              // I have to save the book to my container



              book_container[i] = new Book(i,bt,ba,e1,publ,bf,des,publ_date,br);

              book_container[i]->setGenres(genres_temp);
              genres_temp.clear();

              book_container[i]->setRatings(ratings_temp);
              ratings_temp.clear();

              book_container[i]->setQuotes(quotes_temp);
              quotes_temp.clear();

              book_container[i]->setReviews(reviews_temp);
              reviews_temp.clear();

              temp2.readNext();

            } else if(temp2.isEndElement() && temp2.name() == "review") {

              reviews_temp[user] = review_us;

              temp2.readNext();

            } else if(temp2.isEndElement() && temp2.name() == "quote") {
              quotes_temp[author] = quote_auth;

              temp2.readNext();

            } else if(temp2.isEndElement() && temp2.name() == "rating_u") {

              ratings_temp.push_back(temp_rate);

              temp2.readNext();
            } else if(temp2.isEndElement() && temp2.name() == "genre") {

              genres_temp.push_back(genre_temp);

              temp2.readNext();
            } else temp2.readNext();
        }

    }
  file2.close();

}
// OK
void Database::Save() {
  // === USER STUFF ===

  QFile file(db_file);
  file.open(QIODevice::WriteOnly);

  QXmlStreamWriter temp(&file);
  temp.setAutoFormatting(true);


  temp.writeStartDocument();

  // I create the radix
  temp.writeStartElement("users");

  for(QMap<QString,User*>::const_iterator it = container.begin(); it != container.end(); ++it) {
      temp.writeStartElement("user");

      temp.writeTextElement("username",it.key());
      temp.writeTextElement("name",it.value()->getName());
      temp.writeTextElement("surname",it.value()->getSurname());
      temp.writeTextElement("password",it.value()->getPassword());
      temp.writeTextElement("email",it.value()->getEmail());
      temp.writeTextElement("type",it.value()->getType());

      temp.writeStartElement("bookshelves");
      for(int i = 0; i < it.value()->getBookshelf().size(); i++){
          temp.writeStartElement("bookshelf");
          auto it1 = it.value()->getBookshelf().at(i);
          temp.writeTextElement("title",(it1)->getName());
          temp.writeTextElement("description",(it1)->getDescription());

          temp.writeStartElement("books");
          for(int j = 0;j != (it1)->getBookList().size(); ++j){
              temp.writeTextElement("isbn",it.value()->getBookshelf().at(i)->getBookList().at(j));
            }


          temp.writeEndElement(); //books
          temp.writeEndElement(); //bookshelf
        }


      temp.writeEndElement(); //bookshelves
      temp.writeEndElement(); //user
    }

  temp.writeEndElement(); //users

  temp.writeEndDocument();
  file.close();

  // === BOOK STUFF ===

  QFile file1(bc_file);
  file1.open(QIODevice::WriteOnly);

  QXmlStreamWriter temp1(&file1);
  temp1.setAutoFormatting(true);


  temp1.writeStartDocument();

  temp1.writeStartElement("books");

  for(auto it = book_container.begin(); it!=book_container.end();++it){
      temp1.writeStartElement("book");

      temp1.writeTextElement("isbn",it.key());
      temp1.writeTextElement("title",it.value()->getTitle());
      temp1.writeTextElement("author",it.value()->getAuthor());
      temp1.writeTextElement("edition",it.value()->getEdition());
      temp1.writeTextElement("publisher",it.value()->getPublisher());
      temp1.writeTextElement("format",it.value()->getFormat());
      temp1.writeTextElement("description",it.value()->getDescription());
      temp1.writeTextElement("publishing_date",it.value()->getPublishingDate().toString("dd/MM/yyyy"));
      temp1.writeTextElement("rating",QString::number(it.value()->getRating()));

      temp1.writeStartElement("genres");
      if(!it.value()->getGenres().empty()) {
          for(int it4 = 0; it4 < it.value()->getGenres().size(); ++it4) {
              temp1.writeTextElement("genre",it.value()->getGenres().at(it4));
            }
        }
      temp1.writeEndElement();

      temp1.writeStartElement("ratings");
      if(!it.value()->getRatings().empty()) {
          for(auto it1 = 0; it1 < it.value()->getRatings().size(); ++it1) {
              temp1.writeTextElement("rating_u",QString::number(it.value()->getRatings().at(it1)));
            }
        }
      temp1.writeEndElement();

      temp1.writeStartElement("quotes");
      if(!it.value()->getQuotes().empty()) {

          //        for(QMap<QString,QString>::const_iterator it2 = it.value()->getQuotes().begin(); it2 != it.value()->getQuotes().end(); it2++) {
          for(auto e: it.value()->getQuotes().keys()){
              temp1.writeStartElement("quote");
              temp1.writeTextElement("author_quote",e);
              temp1.writeTextElement("quote_content",it.value()->getQuotes().value(e));
              temp1.writeEndElement();
            }
        }
      temp1.writeEndElement();

      temp1.writeStartElement("reviews");
      if(!it.value()->getReviews()->empty()) {
          for(auto e: it.value()->getReviews()->keys()) {
              temp1.writeStartElement("review");
              temp1.writeTextElement("user", e);
              temp1.writeTextElement("review_content",it.value()->getReviews()->value(e));
              temp1.writeEndElement();
            }
        }
      temp1.writeEndElement();

      temp1.writeEndElement();
    }

  temp1.writeEndElement();




  temp1.writeEndDocument();
  file1.close();

}

bool Database::isUserEmpty() const {
  return container.empty();
}
bool Database::isBookEmpty() const {
  return book_container.empty();
}
