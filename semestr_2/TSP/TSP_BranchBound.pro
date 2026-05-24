QT += core widgets

CONFIG += c++17

TARGET = TSP_BranchBound
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tspscene.cpp \
    tspsolver.cpp

HEADERS += \
    mainwindow.h \
    tspsolver.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
