#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include <QMainWindow>
#include "addbookwindow.h"
#include "book.h"

namespace Ui {
class Home_window;
}

class Home_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home_window(QWidget *parent = 0);
    ~Home_window();

private slots:
    void on_addBook_button_clicked();
    void on_exit_button_clicked();

    void on_open_file_clicked();

    void on_remove_book_clicked();

    void on_save_file_clicked();

private:
    Ui::Home_window *ui;

    void addBook(const Book& book);

    // enum list needed to write into the row
    enum Columns {
        ISBN_,
        TITLE,
        AUTHOR,
        ADDED_DATE,
        READ_DATE,
        RATING

    };
};

#endif // HOME_WINDOW_H
