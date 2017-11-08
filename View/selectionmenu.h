#ifndef SELECTIONMENU_H
#define SELECTIONMENU_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QMainWindow>

class SelectionMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SelectionMenu(QWidget *parent = 0);
    ~SelectionMenu();

signals:

private slots:
    void addLoginForm();
    void addRegistrationForm();
    void backToMenu();


private:
    QPushButton* quit;
    QPushButton* login;
    QPushButton* registration;

    QVBoxLayout* login_layout;
    QVBoxLayout* register_layout;


    // clearLayout is needed to clear the layout when
    void clearLayout(QLayout *);

};

#endif // SELECTIONMENU_H
