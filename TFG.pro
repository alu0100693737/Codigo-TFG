QT += core
QT -= gui
QT += widgets
CONFIG += c++11

TARGET = TFG
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    prueba.cpp \
    COperacionesImagen.cpp \
    uiprueba.cpp \
    Principal.cpp \
    CAplicacion.cpp \
    CLabel.cpp \
    CFiltrosImagenes.cpp \
    CDetectarAutomata.cpp \
    pruebanumeros.cpp \
    pruebawidget.cpp


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_ml -lopencv_imgproc -lopencv_videoio -lopencv_video

DISTFILES += \
    grafo.jpg \
    release/about.png \
    images/0.png \
    images/1.png \
    images/2.png \
    images/3.png \
    images/4.png \
    images/5.png \
    images/6.png \
    images/7.png \
    images/8.png \
    images/9.png

HEADERS += \
    COperacionesImagen.h \
    CAplicacion.h \
    CLabel.h \
    CFiltrosImagenes.h \
    CDetectarAutomata.h
