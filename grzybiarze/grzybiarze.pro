TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        booster.cpp \
        bush.cpp \
        character.cpp \
        cmap.cpp \
        main.cpp \
        mushroom.cpp \
        object.cpp \
        przeszkoda.cpp
INCLUDEPATH += "C:/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    booster.h \
    bush.h \
    character.h \
    cmap.h \
    mushroom.h \
    object.h \
    przeszkoda.h