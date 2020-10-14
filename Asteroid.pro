TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
PRECOMPILED_HEADER = Asteroid.h
SOURCES += \
        Asteroid.cpp

LIBS += -L"/usr/lib/x86_64-linux-gnu"


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system



INCLUDEPATH += "$/usr/lib/x86_64-linux-gnu"
DEPENDPATH += "/usr/lib/x86_64-linux-gnu"
