TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
#LIBS += -ludev

#INCLUDEPATH += /home/victorcrimea/projects/C++/sokoban/sokoban/SFML-2.0/include/
#DEPENDPATH += /home/victorcrimea/projects/C++/sokoban/sokoban/SFML-2.0/include/

#LIBS += -L"/home/victorcrimea/projects/C++/sokoban/sokoban/SFML-2.0/lib/"
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += main.cpp \
    map.cpp \
    actor.cpp

HEADERS += \
    map.h \
    actor.h

