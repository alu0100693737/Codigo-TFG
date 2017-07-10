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
    pruebanumeros.cpp \
    CContourWithData.cpp \
    CDetectarTransiciones.cpp \
    GenerarClasificador.cpp \
    pruebablobs.cpp \
    pruebalineas.cpp \
    CDetectarLineas.cpp \
    CDetectarCirculos.cpp \
    CPanelOpciones.cpp \
    CAsistenteCodificacion.cpp \
    CLineEdit.cpp \
    CCheckBox.cpp \
    CPushButton.cpp \
    CNfa.cpp \
    CTransicion.cpp \
    CEstadoNFA.cpp \
    DFA_min.cpp \
    Estado.cpp


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
    images/9.png \
    classifications.xml \
    grafoReal1.png \
    documentos TFG/Apuntes.odt \
    images.xml \
    TFG.pro.user \
    TFG.pro.user.2a461cd \
    images/grafoReal.jpg \
    images/training.jpg \
    circulos.jpg \
    Clase1.jpg \
    Clase2.jpg \
    Clasif.jpg \
    grafo1.jpg \
    image001.jpg \
    ivvi.jpg \
    linea1.jpg \
    lineas.jpg \
    lineas1.jpg \
    documentos TFG/ejecucionesCirculosLineas/DeteccionCirculos1.png \
    documentos TFG/ejecucionesCirculosLineas/DeteccionCirculos2.png \
    documentos TFG/ejecucionesCirculosLineas/DeteccionLineas1.png \
    images/GrafoconLetras.png \
    images/NumerosAMano.png \
    images/training.png \
    release/abrir.png \
    release/opencv.png \
    release/salir.png \
    release/icon.ico \
    release/transition.png \
    grafo.png \
    release/icon.ico \
    prueba.txt.txt \
    images/procesarImagen.png \
    images/pasoApaso.png

HEADERS += \
    COperacionesImagen.h \
    CAplicacion.h \
    CLabel.h \
    CFiltrosImagenes.h \
    CContourWithData.h \
    CDetectarTransiciones.h \
    CDetectarLineas.h \
    CDetectarCirculos.h \
    CPanelOpciones.h \
    CAsistenteCodificacion.h \
    CLineEdit.h \
    CCheckBox.h \
    CPushButton.h \
    CNfa.h \
    CTransicion.h \
    CEstadoNFA.h \
    DFA_min.h \
    Estado.h


RC_ICONS = release/icon.ico \
            release/icon.png

RESOURCES += \
    resource.qrc
