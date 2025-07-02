QT += core gui widgets multimedia multimediawidgets
CONFIG += c++17
TARGET = SimuladorGrafico

HEADERS += \
    mainwindow.h \
    broker.h \
    videopublisher.h \
    videofollower.h \
    gpscarpublisher.h \
    gpscarfollower.h \
    drawingwidget.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    broker.cpp \
    videopublisher.cpp \
    videofollower.cpp \
    gpscarpublisher.cpp \
    gpscarfollower.cpp \
    drawingwidget.cpp