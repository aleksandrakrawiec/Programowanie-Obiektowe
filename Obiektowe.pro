TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Database.cpp \
    Order.cpp \
    Person.cpp \
    Product.cpp \
    Program.cpp

HEADERS += \
    Database.h \
    Order.h \
    Person.h \
    Product.h \
    Program.h
