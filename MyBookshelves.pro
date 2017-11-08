#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T16:46:14
#
#-------------------------------------------------

QT       += core gui
QT       += xml

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyBookshelves
TEMPLATE = app


SOURCES += main.cpp\
    book.cpp \
    bookshelf.cpp \
    database.cpp \
    user.cpp \
    user_normal.cpp \
    user_pro.cpp \
    View/addbookform.cpp \
    View/book_view.cpp \
    administrator.cpp \
    Controller/client.cpp \
    View/administratormainwindow.cpp \
    View/login.cpp \
    View/adduserform.cpp \
    Controller/admin_controller.cpp \
    View/admin_userinfo.cpp \
    View/admin_books.cpp \
    View/admin_bookview.cpp \
    Controller/user_controller.cpp \
    View/user_view.cpp \
    View/bookshelflist_view.cpp \
    View/newbookshelfview.cpp \
    View/reviewslistview.cpp \
    View/accountinfoview.cpp \
    View/finishbookview.cpp \
    moderator.cpp \
    View/reviewview.cpp \
    View/addbookformuser.cpp

HEADERS  += book.h \
    bookshelf.h \
    database.h \
    user.h \
    user_normal.h \
    user_pro.h \
    View/addbookform.h \
    View/book_view.h \
    administrator.h \
    Controller/client.h \
    View/administratormainwindow.h \
    View/login.h \
    View/adduserform.h \
    Controller/admin_controller.h \
    View/admin_userinfo.h \
    View/admin_books.h \
    View/admin_bookview.h \
    Controller/user_controller.h \
    View/user_view.h \
    View/bookshelflist_view.h \
    View/newbookshelfview.h \
    View/reviewslistview.h \
    View/accountinfoview.h \
    View/finishbookview.h \
    moderator.h \
    View/reviewview.h \
    View/addbookformuser.h

FORMS    += View/addbookform.ui \
    View/book_view.ui \
    View/administratormainwindow.ui \
    View/login.ui \
    View/adduserform.ui \
    View/admin_userinfo.ui \
    View/admin_books.ui \
    View/admin_bookview.ui \
    View/user_view.ui \
    View/bookshelflist_view.ui \
    View/newbookshelfview.ui \
    View/reviewslistview.ui \
    View/accountinfoview.ui \
    View/finishbookview.ui \
    View/reviewview.ui \
    View/addbookformuser.ui

RC_ICONS = icon.png

RESOURCES += \
    resources.qrc
