QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    pics/800px-FC_Internazionale_Milano_2014.svg.png \
    pics/UEFA-Champions-League.jpeg \
    pics/arsenal.jpeg \
    pics/barca.jpeg \
    pics/champ.png \
    pics/chelsea.png \
    pics/chelsea.svg \
    pics/city.png \
    pics/juve2.jpeg \
    pics/juventus.png \
    pics/manchesterUtd.jpeg \
    pics/milan1.png \
    pics/milan2.png \
    pics/pobrane.png \
    pics/real.png \
    pics/real2.jpeg
