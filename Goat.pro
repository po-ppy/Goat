#-------------------------------------------------
#
# Project created by QtCreator 2018-07-23T13:12:13
#
#-------------------------------------------------

QT       += core gui sql charts
RC_ICONS = nu.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Goat
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mainform.cpp \
    sportdataform.cpp \
    goatinfoform.cpp \
    goatqueryform.cpp \
    devicequeryform.cpp \
    db.cpp \
    changegoatinfodialog.cpp \
    bindingdialog.cpp \
    logindialog.cpp \
    informationform.cpp \
    addgoatdialog.cpp \
    helpdialog.cpp

HEADERS  += mainwindow.h \
    mainform.h \
    sportdataform.h \
    goatinfoform.h \
    goatqueryform.h \
    devicequeryform.h \
    db.h \
    changegoatinfodialog.h \
    bindingdialog.h \
    logindialog.h \
    informationform.h \
    addgoatdialog.h \
    helpdialog.h

FORMS    += mainwindow.ui \
    form.ui \
    mainform.ui \
    sportdataform.ui \
    goatinfoform.ui \
    goatqueryform.ui \
    devicequeryform.ui \
    changegoatinfodialog.ui \
    bindingdialog.ui \
    logindialog.ui \
    informationform.ui \
    addgoatdialog.ui \
    helpdialog.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
