TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    NoTengoMuffins.cpp \
    Game.cpp

HEADERS += \
    commons.hpp \
    NoTengoMuffins.hpp \
    Game.hpp
