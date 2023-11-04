QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimediawidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QtHello.cpp \
    include/Defences/Defences.cpp \
    include/Enemy/Dijk.cpp \
    include/Enemy/Enemy.cpp \
    include/Menu/Menu.cpp \
    include/QtBattel/QtBattel.cpp \
    include/QtWelcome/QtWelcome.cpp \
    include/init/init.cpp \
    main.cpp

HEADERS += \
    QtHello.hpp \
    include/Defences/Defences.hpp \
    include/Enemy/Dijk.hpp \
    include/Enemy/Enemy.hpp \
    include/Menu/Menu.hpp \
    include/QtBattel/QtBattel.hpp \
    include/QtWelcome/QtWelcome.hpp \
    include/init/init.hpp \
    ui_Qtgame.h

FORMS += \
    Qtgame.ui

TRANSLATIONS += \
    QtHello_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
