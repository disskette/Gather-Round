QT       += core gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS	    =   mainwindow.h \
    griditem.h \
    menuwindow.h \
    tcpserv.h \
    tcpcli.h \
    network_subscription.h \
    item.h \
    scene.h \
    map.h

SOURCES	    =   mainwindow.cpp \
    griditem.cpp \
    item.cpp \
    main.cpp \
    menuwindow.cpp \
    tcpserv.cpp \
    tcpcli.cpp \
    scene.cpp \
    map.cpp

RESOURCES   =	\
    scene.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
