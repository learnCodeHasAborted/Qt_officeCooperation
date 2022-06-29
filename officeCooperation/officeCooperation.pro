#-------------------------------------------------
#
# Project created by QtCreator 2022-05-18T13:02:24
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = officeCooperation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    addfriend.cpp \
chatclient.cpp \
    configuration.cpp \
    dialog.cpp \
fileclient.cpp \
friendwidget.cpp \
    main.cpp \
    login.cpp \
    mainsiderbar.cpp \
mainwindow.cpp \
    myapp.cpp \
mydatabase.cpp \
    newproject.cpp \
    passwordreset.cpp \
    personcard.cpp \
    picture.cpp \
register.cpp \
doc.cpp \
    todo.cpp \
    todolist.cpp

HEADERS += \
    addfriend.h \
chatclient.h \
    configuration.h \
    dialog.h \
    doc.h \
fileclient.h \
friendwidget.h \
    login.h \
    mainsiderbar.h \
mainwindow.h \
    myapp.h \
mydatabase.h \
    newproject.h \
    passwordreset.h \
    personcard.h \
    picture.h \
register.h \
    todo.h \
    todolist.h

FORMS += \
    addfriend.ui \
chatclient.ui \
    dialog.ui \
fileclient.ui \
friendwidget.ui \
    login.ui \
    mainsiderbar.ui \
mainwindow.ui \
    newproject.ui \
    passwordreset.ui \
    personcard.ui \
register.ui \
doc.ui \
    todolist.ui

RESOURCES += \
image.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
