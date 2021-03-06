QT       += core gui network sql xml serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data/allaction.cpp \
    data/databasecon.cpp \
    data/globaldata.cpp \
    data/xmlmanipulation.cpp \
    main.cpp \
    kitchen.cpp \
    server/serversocket.cpp \
    widget/login/login.cpp \
    widget/orderWindow/customWidget/itemwidget.cpp \
    widget/orderWindow/customWidget/orderdatawidget.cpp \
    widget/orderWindow/orderwindow.cpp \
    widget/serverConnection/serverconnection.cpp

HEADERS += \
    data/allaction.h \
    data/databasecon.h \
    data/globaldata.h \
    data/xmlmanipulation.h \
    kitchen.h \
    server/serversocket.h \
    widget/login/login.h \
    widget/orderWindow/customWidget/itemwidget.h \
    widget/orderWindow/customWidget/orderdatawidget.h \
    widget/orderWindow/orderwindow.h \
    widget/serverConnection/serverconnection.h

FORMS += \
    kitchen.ui \
    widget/login/login.ui \
    widget/orderWindow/customWidget/itemwidget.ui \
    widget/orderWindow/customWidget/orderdatawidget.ui \
    widget/orderWindow/orderwindow.ui \
    widget/serverConnection/serverconnection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
