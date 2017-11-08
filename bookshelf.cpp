#include "bookshelf.h"


// ===========================
//  Constructors & Destructor
// ===========================
Bookshelf::Bookshelf(){}

Bookshelf::Bookshelf(const Bookshelf &temp):name(temp.getName()),description(temp.getDescription()){}
Bookshelf::Bookshelf(const QString& n,const QString& d = 0):name(n),description(d){}

Bookshelf::Bookshelf(const QString & n, const QString & d,const QVector<QString>& l)
{
  name = n;
  description = d;
  bl = l;
}


Bookshelf::~Bookshelf(){
  //    if(!isEmpty())
  //    bl.clear();
}
// ========================================
//  Methods used to retrieve and save data
// ========================================

QString Bookshelf::getName() const {return name;}
void Bookshelf::setName(QString n) { name = n;}

QString Bookshelf::getDescription() const { return description;}
void Bookshelf::setDescription(QString d){ description = d;}

QVector<QString> Bookshelf::getBookList() const
{
  return bl;
}
QVector<QString>* Bookshelf::getBookListToModify(){
  return &bl;
}

void Bookshelf::setBookList(QVector<QString> temp){
  bl = temp;
}

// ================================================
//  Other methods needed to manipulate the objects
// ================================================

void Bookshelf::addBook(const QString& isbn) {
  bl.push_back(isbn);
}

void Bookshelf::remBook_BS(const QString& isbn){

  for(int it = 0; it != bl.size(); ++it) {
      if(bl[it] == isbn) {
          bl.remove(it);
        }
    }
}

// It checks if the Bookshelf is empty or not
bool Bookshelf::isEmpty() const {
  if(bl.size()==0) return true;
  else return false;
}

// It modifies the name and the description
// of the Bookshelf
void Bookshelf::modifyBookshelf(const QString& n,const QString& d){
  setName(n);
  setDescription(d);
}

