QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = bst_qt
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    BST.cpp \
    main.cpp \
    MainWindow.cpp \
    TreeWidget.cpp

HEADERS += \
    BST.h \
    MainWindow.h \
    TreeWidget.h
