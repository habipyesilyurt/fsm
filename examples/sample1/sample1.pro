TEMPLATE = app
QT += widgets
TARGET = sample1
SOURCES += \
    ../../src/fsm.c \
    main.cpp \
    mainwindow.cpp \
    samplemachine.c

HEADERS += \
    ../../src/fsm.h \
    mainwindow.h \
    samplemachine.h


INCLUDEPATH += ../../src/

FORMS += \
    mainwindow.ui
