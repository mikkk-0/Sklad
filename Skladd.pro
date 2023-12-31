QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clwi_4.cpp \
    customwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    product.cpp \
    query.cpp \
    selling_point.cpp \
    shipment.cpp \
    storage.cpp

HEADERS += \
    Classes.h \
    Includes.h \
    clwi_4.h \
    customwidget.h \
    mainwindow.h \
    model.h \
    product.h \
    query.h \
    selling_point.h \
    shipment.h \
    storage.h

FORMS += \
    mainwindow.ui \
    model.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
