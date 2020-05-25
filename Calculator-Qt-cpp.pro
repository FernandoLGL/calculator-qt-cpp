QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 precompile_header
PRECOMPILED_HEADER = extlib/exprtk.hpp

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
    ClickHandler/ClickHandler.cpp \
    Evaluator/Evaluator.cpp \
    KeypressHandler/KeypressHandler.cpp \
    main.cpp \
    Calculator/Calculator.cpp

HEADERS += \
    Calculator/Calculator.h \
    ClickHandler/ClickHandler.h \
    Evaluator/Evaluator.h \
    KeypressHandler/KeypressHandler.h

FORMS += \
    gui/Calculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
