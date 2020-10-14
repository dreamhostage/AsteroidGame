TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CosmoStation.cpp \
        Improvements.cpp \
        asteroids.cpp \
        clissans.cpp \
        framework.cpp \
        laser.cpp \
        main.cpp \
        objects.cpp \
        rockets.cpp \
        ship.cpp
PRECOMPILED_HEADER = Asteroid.h
SOURCES +=

LIBS += -L"/usr/lib/x86_64-linux-gnu"


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system



INCLUDEPATH += "$/usr/lib/x86_64-linux-gnu"
DEPENDPATH += "/usr/lib/x86_64-linux-gnu"

HEADERS +=
