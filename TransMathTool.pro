QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingtoolsui.cpp

HEADERS += \
    mainwindow.h \
    settingtoolsui.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LeftArrow.svg \
    MathExpressionParser.py \
    Reset.svg \
    RightArrow.svg \
    image/t01Braille/A LSUB A.png \
    image/t01Braille/A LSUB A.png \
    image/t01Braille/A LSUP A.png \
    image/t01Braille/A LSUP A.png \
    image/t01Braille/A^A.png \
    image/t01Braille/A_A.png \
    image/t01Braille/A_LSUB_A.png \
    image/t01Braille/A_LSUP_A.png \
    image/t01Braille/UNDEROVER A_A^A.png \
    image/t01Braille/UNDEROVER A_A^A.png \
    image/t01Braille/UNDEROVER_A_A^A.png \
    image/t02DecorativeSymbol/DDOT A.png \
    image/t02DecorativeSymbol/DOT A.png \
    image/t02DecorativeSymbol/acute A.png \
    image/t02DecorativeSymbol/arch A.png \
    image/t02DecorativeSymbol/bar A.png \
    image/t02DecorativeSymbol/box A.png \
    image/t02DecorativeSymbol/check A.png \
    image/t02DecorativeSymbol/dyad A.png \
    image/t02DecorativeSymbol/grave A.png \
    image/t02DecorativeSymbol/hat A.png \
    image/t02DecorativeSymbol/tilde A.png \
    image/t02DecorativeSymbol/under A.png \
    image/t02DecorativeSymbol/vec A.png \
    image/t03Fountain/A1OverA2.png
