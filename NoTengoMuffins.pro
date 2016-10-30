TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    NoTengoMuffins.cpp \
    Game.cpp \
    Character.cpp \
    button.cpp \
    scene.cpp \
    menu.cpp \
    Zombie.cpp \
    Player.cpp \
    InputManager.cpp \
    Map.cpp \
    party.cpp \
    bullet.cpp

HEADERS += \
    commons.hpp \
    NoTengoMuffins.hpp \
    Game.hpp \
    Character.hpp \
    button.hpp \
    scene.hpp \
    menu.h \
    Zombie.hpp \
    Player.hpp \
    InputManager.hpp \
    Map.hpp \
    party.hpp \
    bullet.hpp
