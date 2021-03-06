﻿//detect numbers https://www.mkompf.com/cplus/emeocv.html
///////////////////////////////////////////////////////////////
//   CAplicacion.h - Implementación de la clase CAplicacion  //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////
#include "CAplicacion.h"

#include "opencv2/imgcodecs.hpp" //MAT OPENCV
#include "opencv2/imgproc.hpp"    //SOBEL
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
#include "DFA_min.cpp"
#include "Estado.cpp"
#include <iostream>
using namespace cv;
using namespace std;


#include <time.h>
#include <sys/time.h>

void delay(int secs) {
      for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

CAplicacion::CAplicacion() {
    setWindowIcon(QIcon(":/release/icon.ico"));

    setPathImagenActual(NULL); //Path al principio = NULL

    setStyleSheet("background-color: rgba(255, 255, 168, 1);");

    /// Creamos los Paneles de la Aplicacion y su disposicion
    panelPrincipal_ = new CLabel("Panel Principal", true);
    //getPanelPrincipal()->setScaledContents(true);
    panelOpciones_ = new CPanelOpciones();
    //getPanelOpciones()->setScaledContents(true);
    panelHistograma_ = new CLabel("Info Imagen", false);
    panelComparacion_ = new CLabel("", true);

    getPanelHistograma()->setStyleSheet("background-color: white; border: 1px solid black");

    operacionesImagen_ = new COperacionesImagen();

    QWidget* centralWidget        = new QWidget();
    layout_ = new QGridLayout();

    perspectivaActual_ = new CLabel("Perspectiva actual: \nDeteccion", true);
    getPerspectivaActual()->setAlignment(Qt::AlignCenter);
    //getPerspectivaActual()->setStyleSheet("border: 1px solid black");
    cambiarPerspectiva_ = new CPushButton("Cambiar Perspectiva", false);
    restaurarValores_ = new CPushButton("Restaurar ScrollBar's", false);

    centralWidget->setLayout (getLayout());

    /// Creamos el Menu
    menu_                   = this->menuBar();//w QMenuBar(centralWidget);
    menuArchivo_            = new QMenu("Archivo");
    menuEditar_             = new QMenu("Deteccion");
    menuCorreccion_         = new QMenu("Correccion");
    menuFiltro_             = new QMenu("Filtros");

    actionAbrirImagen_      = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/imagenOriginal.png"), tr("Abrir imagen para su detección"), this);
    actionAbrirFichero_     = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/fichero.png"), tr("Abrir fichero para su correccion"), this);
    actionCrearNuevoFichero_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/nuevoFichero.png"), tr("Crear nuevo automata"), this);
    actionMostrarAyuda_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/eye.png"), tr("No mostrar ayuda"), this);
    actionAbout_            = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/about.png"), tr("About"), this);
    actionAboutQT_          = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/aboutQT.png"), tr("About QT"), this);
    actionSalir_            = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/salir.png"), tr("Salir"), this);

    actionDetectarLineas_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/linea.png"), tr("Detectar lineas"), this);
    actionDetectarCirculos_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/circulo.png"), tr("Detectar circulos"), this);
    actionDetectarTransiciones_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/transition.png"), tr("Detectar transiciones"), this);

    //Busca la codificacion de la imagen
    actionCodificarImagen_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/codificar.png"), tr("Detectar Sentidos"), this);
    actionConfirmarImagen_ =new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/check.png"), tr("Confirmar deteccion"));
    actionProcesarImagen_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/opencv.png"), tr("Procesar imagen"), this);
    actionCargarImagenOriginal_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/imagenOriginal.png"), tr("Cargar ultima imagen"), this);

    actionAbrirFicheroCorrecto_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/check.png"), tr("Abrir fichero correcto"));

    actionFiltroGray_ = new QAction(QIcon(""), tr("Filtro gray"), this);
    actionFiltroGaussiano_   = new QAction(QIcon(""), tr("Filtro gaussiano"), this);
    actionFiltroMediana_ = new QAction(QIcon(""), tr("Filtro mediana"), this);
    actionFiltroSobel_ = new QAction(QIcon(""), tr("Filtro sobel"), this);
    actionFiltroLaplaciano_ = new QAction(QIcon(""), tr("Filtro laplaciano"), this);
    actionHistograma_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/histograma.png"), tr("Histograma"), this);

    getActionDetectarLineas()->setDisabled(true); //Hasta que no se cargue una imagen
    getActionDetectarCirculos()->setDisabled(true);
    getActionDetectarTransiciones()->setDisabled(true);
    getActionCodificarImagen()->setDisabled(true);
    getActionProcesarImagen()->setDisabled(true);
    getActionConfirmarImagen()->setDisabled(true);
    getActionCargarImagenOriginal()->setDisabled(true);

    getActionFiltroGaussiano()->setDisabled(true);
    getActionFiltroGray()->setDisabled(true);
    getActionFiltroLaplaciano()->setDisabled(true);
    getActionFiltroMediana()->setDisabled(true);
    getActionFiltroSobel()->setDisabled(true);
    getActionHistograma()->setDisabled(true);

    getActionAbrirFicheroCorrecto()->setDisabled(true);

    ayuda_ = new QWidget();
    ventanaFinal_ = new QWidget();

    ///Shortcuts
    getActionAbrirImagen()->setShortcuts(QKeySequence::New);
    getActionSalir()->setShortcut(QKeySequence::Close);

    getMenuArchivo()->addAction(getActionAbrirImagen());
    getMenuArchivo()->addAction(getActionAbrirFichero());
    getMenuArchivo()->addAction(getActionCrearNuevoFichero());
    getMenuArchivo()->addAction(getActionMostrarAyuda());
    getMenuArchivo()->addAction(getActionAbout());
    getMenuArchivo()->addAction(getActionAboutQT());
    getMenuArchivo()->addAction(getActionSalir());
    getMenuDeteccion()->addAction(getActionDetectarCirculos());
    getMenuDeteccion()->addAction(getActionDetectarLineas());
    getMenuDeteccion()->addAction(getActionDetectarTransiciones());
    getMenuDeteccion()->addAction(getActionCodificarImagen());
    getMenuDeteccion()->addAction(getActionConfirmarImagen());
    getMenuDeteccion()->addAction(getActionProcesarImagen());
    getMenuDeteccion()->addAction(getActionCargarImagenOriginal());

    getMenuCorreccion()->addAction(getActionAbrirFicheroCorrecto());

    getMenuFiltro()->addAction(getActionFiltroGaussiano());
    getMenuFiltro()->addAction(getActionFiltroMediana());
    getMenuFiltro()->addAction(getActionFiltroSobel());
    getMenuFiltro()->addAction(getActionFiltroLaplaciano());
    getMenuFiltro()->addAction(getActionHistograma());

    // getPanelPrincipal()->addAction(getActionPanelPrincipal());

    //añadiendo elementos
    getMenuBar()->addMenu(getMenuArchivo());
    getMenuBar()->addMenu(getMenuDeteccion());
    getMenuBar()->addMenu(getMenuCorreccion());
    getMenuBar()->addMenu(getMenuFiltro());
    getMenuBar()->adjustSize();
    getMenuBar()->setStyleSheet("background-color: white");

    inicializarVentanaAplicacionDeteccion();

    setCentralWidget(centralWidget);

    setWindowTitle("DCAFI");

    ///Añadimos Toolbar
    toolbar_ = new QToolBar(this);
    getToolBar()->addAction(getActionAbrirImagen());
    getToolBar()->addAction(getActionAbrirFichero());

    getToolBar()->addAction(getActionProcesarImagen());

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    getToolBar()->addWidget(empty);

    getToolBar()->addAction(getActionDetectarCirculos());
    getToolBar()->addAction(getActionDetectarLineas());
    getToolBar()->addAction(getActionDetectarTransiciones());
    getToolBar()->addAction(getActionCodificarImagen());
    getToolBar()->addAction(getActionConfirmarImagen());

    getToolBar()->setStyleSheet("background-color: white;");
    this->addToolBar(getToolBar());

    nodo_inicio = new CLineEdit;
    getNodoInicio()->setPlaceholderText("Nodo de Inicio");
    nodos_finales = new CLineEdit;
    getNodosFinales()->setPlaceholderText("Nodos Finales, Formato: 0 1 2 ...");
    getNodoInicio()->setFocus();

    alfabeto_ = new QComboBox;

    getAlfabetoActual()->addItem(tr("Introduzca el alfabeto"));
    getAlfabetoActual()->addItem(tr("Letras"));
    getAlfabetoActual()->addItem(tr("Numeros"));

    checkEliminarAnadirLinea_ = new QComboBox();
    getCheckEliminarAnadirLinea()->addItem(tr("Eliminar Lineas"));
    getCheckEliminarAnadirLinea()->addItem(tr("Añadir Lineas"));

    lineaAceptada_ = false;
    sentidoAceptado_ = false;

    QWidget* empty1 = new QWidget();
    empty1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    getToolBar()->addWidget(empty1);

    getToolBar()->addAction(getActionAbout());
    // Add values in the combo box
    this->getToolBar()->addWidget(getNodoInicio());
    this->getToolBar()->addWidget(getNodosFinales());
    this->getToolBar()->addWidget(getAlfabetoActual());
    //this->getToolBar()->addWidget(getTextAnadirEliminar());
    this->getToolBar()->addWidget(getCheckEliminarAnadirLinea());

    checkUpdatesTimer_ = new QTimer(this); //timer para asistente codificacion
    cargarImagenParaPanelComparacion_ = false;
    auxContenidoAnterior_ = new CLabel();
    posActualPanelOpciones_= 0;

    dibujadaTransiciones_ = false;

    ///conexiones con slots
    connect(getActionAbrirImagen(), SIGNAL(triggered()),this,SLOT(slotAbrirImagen()));
    connect(getActionAbrirFichero(), SIGNAL(triggered()),this,SLOT(slotAbrirFichero()));
    connect(getActionCrearNuevoFichero(), SIGNAL(triggered()), this, SLOT(slotCrearNuevoFichero()));
    connect(getActionMostrarAyuda(), SIGNAL(triggered()), this, SLOT(slotMostrarAyuda()));
    connect(getActionAbout(), SIGNAL(triggered()),this,SLOT(slotAbout()));
    connect(getActionAboutQT(), SIGNAL(triggered()), this, SLOT(slotAboutQT()));
    connect(getActionSalir(), SIGNAL(triggered()), this, SLOT(slotSalir()));

    connect(getActionDetectarCirculos(), SIGNAL(triggered()), this, SLOT(slotDetectarCirculos()));
    connect(getActionDetectarLineas(), SIGNAL(triggered()), this, SLOT(slotDetectarLineas()));
    connect(getActionDetectarTransiciones(), SIGNAL(triggered()), this, SLOT(slotDetectarTransiciones()));
    connect(getActionCodificarImagen(), SIGNAL(triggered()), this, SLOT(slotCodificarImagen()));
    connect(getActionProcesarImagen(), SIGNAL(triggered()), this, SLOT(slotProcesarImagen()));
    connect(getActionConfirmarImagen(), SIGNAL(triggered()), this, SLOT(slotConfirmarImagen()));
    connect(getActionCargarImagenOriginal(), SIGNAL(triggered()), this, SLOT(slotCargarImagenOriginal()));

    connect(getActionAbrirFicheroCorrecto(), SIGNAL(triggered()), this, SLOT(slotAbrirFicheroCorrecto()));

    connect(getActionFiltroGray(), SIGNAL(triggered()), this, SLOT(slotFiltroGray()));
    connect(getActionFiltroGaussiano(), SIGNAL(triggered()), this, SLOT(slotFiltroGaussiano()));
    connect(getActionFiltroMediana(), SIGNAL(triggered()), this, SLOT(slotFiltroMediana()));
    connect(getActionFiltroSobel(), SIGNAL(triggered()), this, SLOT(slotFiltroSobel()));
    connect(getActionFiltroLaplaciano(), SIGNAL(triggered()), this, SLOT(slotFiltroLaplaciano()));
    connect(getActionHistograma(), SIGNAL(triggered()), this, SLOT(slotHistograma()));

    connect(getPanelOpciones()->getCannyThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
    connect(getPanelOpciones()->getAccumulatorThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
    connect(getPanelOpciones()->getHoughLinesP(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));

    connect(getPanelPrincipal(), SIGNAL(clicked(QMouseEvent*)), this, SLOT(slotPanelPrincipal(QMouseEvent*)));

    connect(getRestaurarValores(), SIGNAL(clicked()), this, SLOT(slotRestaurarValores()));
    connect(getCambiarPerspectiva(), SIGNAL(clicked()), this, SLOT(slotCambiarPerspectiva()));

    connect(getCheckUpdatesTimer(), SIGNAL(timeout()), this, SLOT(checkFicheroTemporalCreado()));

    slotCambiarPerspectiva(); //Empezamos con la perspectiva codificacion
}

CAplicacion::~CAplicacion() {}

void CAplicacion::inicializarVentanaAplicacionDeteccion() {

    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

    getPanelComparacion()->setAlignment(Qt::AlignCenter);
    getPanelPrincipal()->setAlignment(Qt::AlignCenter);
    getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 6px;");

    getLayout()->addWidget(getPanelComparacion(), 0, 0, 3, 4);

    getLayout()->addWidget (getPanelPrincipal(), 0, 0, 3, 4);
    getLayout()->addWidget (getPanelOpciones(), 4, 0, 1, 3);

    //Si teniamos una imagen previamente cargada
    if(getPathImagenActual() != NULL) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
        //Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        resize(aux.dims,height());
    } else {
        getActionCargarImagenOriginal()->setDisabled(true);
        /* Mat aux = imread("/home/ivan/Documentos/Codigo-TFG/images/cartel1.png", IMREAD_UNCHANGED);
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));*/
    }
    QVBoxLayout* layout1 = new QVBoxLayout();
    layout1->addWidget(getPerspectivaActual());
    layout1->addWidget(getCambiarPerspectiva());
    layout1->setSpacing(10);
    layout1->addWidget(getRestaurarValores());
    /* layout1->addWidget(getGuardarComoFichero()); layout1->addWidget(getCorregirAutomata());
    layout1->addWidget(getHelp());*/

    layout1->setSpacing(10);
    getLayout()->addLayout(layout1, 4, 3, 1, 1);
    //green
    getPanelOpciones()->setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black ;");
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");
    cout << "Llegue a iniciarlizar la venta deteccion" << endl;
}

void CAplicacion::inicializarVentanaAplicacionCorreccion() {
    getActionFiltroGaussiano()->setDisabled(true);
    getActionFiltroGray()->setDisabled(true);
    getActionFiltroLaplaciano()->setDisabled(true);
    getActionFiltroMediana()->setDisabled(true);
    getActionFiltroSobel()->setDisabled(true);
    getActionHistograma()->setDisabled(true);
    setMinimumWidth(850);
    getPanelPrincipal()->clear();
    //getPanelComparacion()->clear();
    if(getAuxContenidoAnterior()->text() == "")
        getPanelPrincipal()->setText("Introduzca aqui la imagen o fichero a corregir ");
    else {

        getPanelPrincipal()->setText(getAuxContenidoAnterior()->text());
    }
    getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");

    if(getPanelComparacion()->text() == "")
        getPanelComparacion()->setText("Introduzca aqui la imagen o fichero de referencia ");

    getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");

    getLayout()->addWidget(getPanelComparacion(), 0, 2, 3, 2);
    getLayout()->addWidget (getPanelPrincipal(), 0, 0, 3, 2);
    getPanelComparacion()->setAlignment(Qt::AlignAbsolute);
    getPanelPrincipal()->setAlignment(Qt::AlignAbsolute);
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

    getPanelOpciones()->setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 4px solid black");
}

//SLOTS
void CAplicacion::slotAbrirImagen() {
    cout << "NO LLEGO" << endl;
    //inicializarVentanaAplicacionDeteccion();
    //por si estuviera el modo fichero abierto
    //getLayout()->addWidget (getPanelPrincipal(), 0, 0, 3, 5);

    QFileDialog dialog(this, tr("Abrir Imagen"));
    dialog.setStyleSheet("background-color: white;");
    inicializarVentanaAbrirImagen(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void CAplicacion::slotAbrirFichero() {
    QString line = ventanaAbrirFichero();
    if(!line.isEmpty()) {
        //inicializarVentanaAplicacionCorreccion();
        if(getPerspectivaActual()->text() == "Perspectiva actual: \nDeteccion")
            slotCambiarPerspectiva();
        if(!getCargarImagenParaPanelComparacion()) {
            getPanelPrincipal()->setText(line);
            getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");
            getActionAbrirFicheroCorrecto()->setDisabled(false);
            if(getPosActualPanelOpciones() == 0) {
                posActualPanelOpciones_ = 1;
            } else if (getPosActualPanelOpciones() == 2){
                posActualPanelOpciones_ = 3;
            }
            getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
            if(getPosActualPanelOpciones() == 3) {
                //getPanelOpciones()->setFixedHeight(180);
                connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
                connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
                connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
                connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));
                connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
                connect(getPanelOpciones()->getCorregirFichero(), SIGNAL(clicked()), this, SLOT(slotCorregirFinal()));
                connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
            } else if(getPosActualPanelOpciones() == 1) {
                connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
                connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));
            }

            //poner analizar cadena y simplificar
        } else {
            getPanelComparacion()->setText(line);
            getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");
            cout << "hetrfrg" << posActualPanelOpciones_ << endl;
            if(posActualPanelOpciones_ == 0) {
                posActualPanelOpciones_ = 2;
            } else {
                posActualPanelOpciones_ = 3;
            }
            cargarImagenParaPanelComparacion_ = false;
            getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
            if(getPosActualPanelOpciones() == 3) {
                //getPanelOpciones()->setFixedHeight(180);
                connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
                connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
                connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));
                connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
                connect(getPanelOpciones()->getCorregirFichero(), SIGNAL(clicked()), this, SLOT(slotCorregirFinal()));
                connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));

            } else if(getPosActualPanelOpciones() == 2) {
                connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
                connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
                connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
            }
            //poner simplificar
        }
    }
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");
}
void CAplicacion::inicializarVentanaAbrirImagen(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
            ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");
    if (acceptMode == QFileDialog::AcceptSave) {
        dialog.setDefaultSuffix("png");
    }
}

bool CAplicacion::loadFile(const QString &fileName) {
    QImageReader reader(fileName);
    setPathImagenActual(fileName); //Introduciendo la path de la imagen actual cargada
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    } else {
        ///Si se lee un jpg, se convierte a png guardamos y la cargamos, no borramos la jpg
        if(getPathImagenActual().endsWith(".jpg")) {
            Mat aux1 = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            setPathImagenActual(getPathImagenActual().remove(getPathImagenActual().size() - 4, 4));
            setPathImagenActual(getPathImagenActual().append(".png"));
            //si no existe la misma imagen en formato png
            Mat aux2 = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            if(aux2.empty())
                imwrite(getPathImagenActual().toStdString(), aux1);
        }

        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

        getPanelPrincipal()->clear();

        inicializarVentanaAplicacionDeteccion();
        adjustSize();

        if(getPerspectivaActual()->text() == "Perspectiva actual: \nCorreccion")
            slotCambiarPerspectiva();
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
        setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
        setMinimumSize(0,0);
        resize(aux.dims,height());

        getActionDetectarCirculos()->setDisabled(false);
        getActionProcesarImagen()->setDisabled(false);

        getActionCargarImagenOriginal()->setDisabled(false);
        getActionFiltroGaussiano()->setDisabled(false);
        getActionFiltroGray()->setDisabled(false);
        getActionFiltroLaplaciano()->setDisabled(false);
        getActionFiltroMediana()->setDisabled(false);
        getActionFiltroSobel()->setDisabled(false);
        getActionHistograma()->setDisabled(false);
        setStyleSheet("background-color: rgba(191, 191, 191, 1);");

        //getPanelOpciones()->getAnalizarCadena()->setEnabled(true);
        //getPanelOpciones()->getSimplificarFichero()->setEnabled(true);
        return true;
    }
}

QString CAplicacion::ventanaAbrirFichero()  {
    ///Creamos ventana
    QFileDialog* window = new QFileDialog();

    ///Cargamos el directorio por defecto
    const QStringList documentsLocations = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    window->setDirectory(documentsLocations.last());

    setStyleSheet("background-color: white");

    ///Cargamos la ventana con filtro txt
    QString fileName1 = window->getOpenFileName(this,tr("Abrir Codificación"), "", tr("Text Files (*.txt)"));
    QFile file1(fileName1);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, fichero invalido" << endl;
        setStyleSheet("background-color: rgba(191, 191, 191, 1);");

        return QString();
    }

    QTextStream in(&file1);
    QString line;
    while(!in.atEnd()){
        line += in.readLine();
        line += "\n";
    }
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

    return line;

}

void CAplicacion::dibujarSentidoTransiciones() {
    dibujadaTransiciones_ = true;

    Mat prueba = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

    Scalar rojo = Scalar(0, 0, 200);
    Scalar azul = Scalar(200, 0, 0);
    Scalar verde = Scalar(0, 200, 0);
    vector<Scalar> colores;
    colores.push_back(rojo); colores.push_back(azul); colores.push_back(verde);

    for(int i= 0; i < getOperacionesImagen()->getIniciosAsistente()->size(); i++) {
        arrowedLine(prueba,
                    Point(
                        getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[getOperacionesImagen()->getIniciosAsistente()->at(i)][0],
                getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[getOperacionesImagen()->getIniciosAsistente()->at(i)][1]
                ),
                Point(
                    getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[getOperacionesImagen()->getDestinosAsistente()->at(i)][0],
                getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[getOperacionesImagen()->getDestinosAsistente()->at(i)][1]
                ),
                colores.at(i % 3), 3, LINE_AA);
    }

    for(size_t i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++ ) {
        ///Dibujamos el num del circulo en la imagen
        Point center(cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]), cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1])); //x y
        int radius = cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]);

        stringstream ss;
        ss << i;
        string text = ss.str();
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        int thickness = 2;
        cv::putText(prueba, text, Point(center.x - radius/2, center.y + radius/2), fontFace, fontScale, Scalar::all(255), thickness,8);
    }

    for (size_t i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
        cv::rectangle(prueba,                            // draw rectangle on original image
                      getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                      cv::Scalar(255, 255, 255),                        // green
                      2);
    }

    //No he borrado lineas y circulos, hay que volver a buscar la transicion ahora entre los encontrados y las lineas que hay
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(prueba));
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    resize(aux.dims,height());
}

void CAplicacion::slotAbout() {
    QWidget* window = new QWidget(); QHBoxLayout* a = new QHBoxLayout();
    QLabel* aux = new QLabel(); QImage myImage;

    myImage.load("/home/ivan/Documentos/Codigo-TFG/images/cartel1.png");
    aux->setPixmap(QPixmap::fromImage(myImage));
    a->addWidget(aux);

    window->setLayout(a);
    window->setStyleSheet("background-color: black;");
    window->setWindowTitle("Ayuda del asistente");
    //this->setFixedSize(this->width(), this->height());
    window->show();
}

void CAplicacion::slotCrearNuevoFichero() {
    ventanaCrearFichero_ = new QWidget(); QGridLayout* layout = new QGridLayout();

    textEditCrearFichero_ = new QTextEdit();
    getTextEditCrearFichero()->setPlaceholderText("4 \n 2 \n 1 0 2 a 2 b 1 \n 2 0 2 b 3 a 2 \n 3 1 2 a 0 b 1\n");
    getTextEditCrearFichero()->setFontWeight(14);
    getTextEditCrearFichero()->setStyleSheet("background-color: white");
    getTextEditCrearFichero()->setFixedWidth(350);
    getTextEditCrearFichero()->setFixedHeight(400);

    CLabel* text = new CLabel("Cree un nuevo automata ", true);

    CPushButton* cancelar = new CPushButton("Help", true);
    CPushButton* guardar = new CPushButton("Guardar", true);
    CPushButton* codificar = new CPushButton("Codificar", true);

    layout->addWidget(text, 0, 0, 1, 3);
    layout->addWidget(getTextEditCrearFichero(), 1, 0, 1, 3);
    layout->addWidget(cancelar, 4, 0, 1, 1);
    layout->addWidget(guardar, 4, 1, 1, 1);
    layout->addWidget(codificar, 4, 2, 1, 1);

    connect(cancelar, SIGNAL(clicked()), this, SLOT(slotHelp()));
    connect(guardar, SIGNAL(clicked()), this, SLOT(slotGuardar()));

    connect(codificar, SIGNAL(clicked()), this, SLOT(slotCodificarNuevoFichero()));

    getVentanaCrearFichero()->setLayout(layout);
    getVentanaCrearFichero()->setStyleSheet("background-color: grey;");
    getVentanaCrearFichero()->setWindowTitle("Crear nuevo fichero");
    getVentanaCrearFichero()->show();
}

void CAplicacion::slotMostrarAyuda() {
    if(getActionMostrarAyuda()->text() == "No mostrar ayuda")
        getActionMostrarAyuda()->setText("Mostrar ayuda");
    else {
        getActionMostrarAyuda()->setText("No mostrar ayuda");
        //Deberia mostrar la ayuda
        if(getPerspectivaActual()->text() == "Perspectiva actual: \nCorreccion") {
            delete getAyuda();
            ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();
            QLabel* aux1 = new QLabel("Bienvenido a la herramienta DCAFI. \n\nSi desea corregir un autómata, introduzca \nel autómata a corregir y el de referencia en\nlos paneles correspondientes. \n\nSi desea solo detectar un autómata en una imagen, \ncambie de perspectiva en el botón inferior derecho \nde la aplicación. \n\nSi desea crear una nueva codificación en \nformato de texto plano entre en: \n Archivo -> Crear nuevo fichero.");

            a->addWidget(aux1, 0, 0, 2, 2);

            CCheckBox* noMostrarAyuda = new CCheckBox();
            a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 2, 0, 1, 1);
            a->addWidget(noMostrarAyuda, 2, 1, 1, 1);
            a->setSpacing(10);
            CPushButton* aceptar = new CPushButton("Aceptar", true);
            a->addWidget(aceptar, 3, 0, 1, 2);

            getAyuda()->setLayout(a);
            getAyuda()->setStyleSheet("background-color: white");

            getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
            //this->setFixedSize(this->width(), this->height());
            getAyuda()->show();

            connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
            connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
        } else if (getPerspectivaActual()->text() == "Perspectiva actual: \nDeteccion") {
            if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
                delete getAyuda();
                ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();

                QLabel* aux1 = new QLabel("\nPuede realizar la detección automática de la\nimagen pulsando sobre el boton \nProcesar Imagen: ");
                QImage myImage;
                myImage.load("/home/ivan/Documentos/Codigo-TFG/images/procesarImagen.png");

                QLabel* myLabel = new QLabel();
                myLabel->setPixmap(QPixmap::fromImage(myImage));

                a->addWidget(aux1, 0, 0, 2, 2);
                a->addWidget(myLabel, 2, 0, 1, 2);

                QLabel* aux2 = new QLabel(" o realizar una detección paso a paso detectando \ncirculos, lineas, transiciones \ny sentidos.");
                QImage myImage1;
                myImage1.load("/home/ivan/Documentos/Codigo-TFG/images/pasoApaso.png");

                QLabel* myLabel1 = new QLabel();
                myLabel1->setPixmap(QPixmap::fromImage(myImage1));
                myLabel1->show();
                a->addWidget(aux2, 3, 0, 2, 2);
                a->addWidget(myLabel1, 5, 0, 1, 2);

                CCheckBox* noMostrarAyuda = new CCheckBox();
                a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 6, 0, 1, 1);
                a->addWidget(noMostrarAyuda, 6, 1, 1, 1);
                a->setSpacing(20);
                CPushButton* aceptar = new CPushButton("Aceptar", true);
                a->addWidget(aceptar, 7, 0, 1, 2);

                getAyuda()->setLayout(a);
                getAyuda()->setStyleSheet("background-color: white");

                getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
                //this->setFixedSize(this->width(), this->height());
                getAyuda()->show();

                connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
                connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
            }
        }
    }
    //falta redactar cada mensaje, ponerle un checkbox para no volver a mostrar
}

void CAplicacion::slotAboutQT() {
    QMessageBox::aboutQt(this, "About QT");
}

void CAplicacion::slotSalir() {
    exit(0);
}

void CAplicacion::slotDetectarCirculos() {
    getActionProcesarImagen()->setDisabled(true);
    cout << "Detectando imagen" << endl;
    Mat aux = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());

    Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
    //Dibujamos circulos
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(mostrarCirculosFinales(resultado)));
    resize(resultado.dims,height());
    getActionDetectarCirculos()->setDisabled(true);
    getActionDetectarLineas()->setDisabled(false);

    if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
        delete getAyuda();
        ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();

        QLabel* aux1 = new QLabel("\nSi la detección no fuera correcta, se podrá refinar la búsqueda de dos formas distintas: \n");
        QLabel* aux2 = new QLabel("1. Cambiando los valores de los Scrollbar CannyThresHold y AccumulatorThresHold. \nSi estos valores son bajos, se detectaran falsos circulos en la imagen y \nradios de diversa amplitud. Si es muy alto, es posible que no \nse detecten todos los elementos.\nPodrán restaurarse los valores \npor deferecto a partir del botón Restaurar ScrollBar's en la parte \ninferior derecha de la aplicacion.");
        QLabel* aux3 = new QLabel("2. Se pueden añadir o eliminar círculos interactuando directamente con la imagen. \nSi se pulsa sobre un circulo ya detectado, este se eliminará, si se pulsa \nsobre una zona de la imagen en la que no ha sido detectado ningún \nelemento, se añadirá uno nuevo en esa posición.");

        a->addWidget(aux1, 0, 0, 2, 2);
        a->addWidget(aux2, 2, 0, 1, 2);
        a->addWidget(aux3, 4, 0, 2, 2);

        CCheckBox* noMostrarAyuda = new CCheckBox();
        a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 6, 0, 1, 1);
        a->addWidget(noMostrarAyuda, 6, 1, 1, 1);
        a->setSpacing(20);
        CPushButton* aceptar = new CPushButton("Aceptar", true);
        a->addWidget(aceptar, 7, 0, 1, 2);

        getAyuda()->setLayout(a);
        getAyuda()->setStyleSheet("background-color: white");

        getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
        //this->setFixedSize(this->width(), this->height());
        getAyuda()->show();

        connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
        connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
    }

}

void CAplicacion::slotDetectarLineas() {
    if(getNodoInicio()->text().isEmpty() || getNodosFinales()->text().isEmpty()) {
        QMessageBox mensaje;
        mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \n Solo habŕa un estado inicial \nRecuerde configurar el alfabeto.");
        mensaje.setIcon(QMessageBox::Warning);
        mensaje.exec();
    } else {
        if(getNodoInicio()->text().size() > 2){
            cout << "Error" << endl;
            QMessageBox mensaje;
            mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \nSolo habŕa un estado inicial \nRecuerde configurar el alfabeto.");
            mensaje.setIcon(QMessageBox::Warning);
            mensaje.exec();
        } else {
            Mat resultado = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());
            Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

            for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
                Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
                line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
            }
            getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
            //Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            resize(resultado.dims,height());
            getActionDetectarLineas()->setDisabled(true);
            getActionDetectarTransiciones()->setDisabled(false);

            if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
                delete getAyuda();
                ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();

                QLabel* aux1 = new QLabel("\nSi la detección no fuera correcta, se podrá refinar la búsqueda de dos formas distintas: \n");
                QLabel* aux2 = new QLabel("1. Cambiando los valores del Scrollbar HougLinesP. \nSi el valor de esta variable fuera bajo, se detectarán segmentos \nde líneas más pequeños, siendo algunas de ellas, falsos positivos. \nSi el valor fuera muy elevado, no se detectarán todos los contornos \ndeseados. La modificación de esta variable afectará directamente sobre \nlas líneas detectadas en el momento. Podrán restaurarse los valores por \ndefecto a partir del botón Restaurar ScrollBar's en la parte inferior \nderecha de la aplicacion.");
                QLabel* aux3 = new QLabel("2. Se pueden añadir o eliminar líneas interactuando directamente sobre la imagen. \nEn la parte superior derecha del asistente, hay un ComboBox que permite \ndecidir cual de las dos opciones es la deseada. \n Si se decide elegir la opción de eliminar líneas bastará con pulsar sobre \nellas para descartarlas. Si la opción elegida es añadir nuevas líneas, \ndeberá introducirse el punto inicial y final de estas pulsando sobre la \nzona deseada de la imagen.");
                a->addWidget(aux1, 0, 0, 2, 2);
                a->addWidget(aux2, 2, 0, 1, 2);
                a->addWidget(aux3, 4, 0, 2, 2);

                CCheckBox* noMostrarAyuda = new CCheckBox();
                a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 6, 0, 1, 1);
                a->addWidget(noMostrarAyuda, 6, 1, 1, 1);
                a->setSpacing(20);
                CPushButton* aceptar = new CPushButton("Aceptar", true);
                a->addWidget(aceptar, 7, 0, 1, 2);

                getAyuda()->setLayout(a);
                getAyuda()->setStyleSheet("background-color: white");

                getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
                //this->setFixedSize(this->width(), this->height());
                getAyuda()->show();

                connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
                connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
            }
        }
    }
}

void CAplicacion::slotDetectarTransiciones() {
    if(getAlfabetoActual()->currentIndex() == 0) {
        QMessageBox mensaje;
        mensaje.setText("Recuerde introducir el alfabeto del autómata.");
        mensaje.setIcon(QMessageBox::Warning);
        mensaje.exec();
    } else {
        Mat resultado = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

        //getActionProcesarImagen()->setEnabled(true);

        getOperacionesImagen()->detectarTransiciones()->ejecutar(aux, getAlfabetoActual()->currentIndex());

        for (size_t i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
            cv::rectangle(resultado,                            // draw rectangle on original image
                          getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                          cv::Scalar(0, 255, 0),                        // green
                          2);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
        //Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        resize(resultado.dims,height());
        getActionDetectarTransiciones()->setDisabled(true);
        getActionCodificarImagen()->setEnabled(true);

        if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
            delete getAyuda();
            ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();

            QLabel* aux1 = new QLabel("\nSi la detección no fuera correcta, se podrá refinar la búsqueda de dos formas distintas: \n");
            QLabel* aux2 = new QLabel("1. Para eliminar una transición se podrá pulsar sobre ella en la imagen. De esta manera, \nse descarta.");
            QLabel* aux3 = new QLabel("2. Si desea añadir una nueva transición, se podrá pulsar en una zona de la imagen donde no \nhaya una definida. Se deberá introducir por teclado el carácter. \nPara introducir una transición vacia se debe introducir el símbolo ~.");
            a->addWidget(aux1, 0, 0, 2, 2);
            a->addWidget(aux2, 2, 0, 1, 2);
            a->addWidget(aux3, 4, 0, 2, 2);

            CCheckBox* noMostrarAyuda = new CCheckBox();
            a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 6, 0, 1, 1);
            a->addWidget(noMostrarAyuda, 6, 1, 1, 1);
            a->setSpacing(20);
            CPushButton* aceptar = new CPushButton("Aceptar", true);
            a->addWidget(aceptar, 7, 0, 1, 2);

            getAyuda()->setLayout(a);
            getAyuda()->setStyleSheet("background-color: white");

            getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
            //this->setFixedSize(this->width(), this->height());
            getAyuda()->show();

            connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
            connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
        }
    }
}

void CAplicacion::slotCodificarImagen() {
    cout << "Se borro el fichero temporal de la ejecucion anterior" << remove(PATH_TEMPORAL);
    if(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() == 0)
        slotDetectarTransiciones();
    getOperacionesImagen()->codificarDeteccion();

    dibujarSentidoTransiciones();
    getActionConfirmarImagen()->setEnabled(true);
    if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
        delete getAyuda();
        ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();

        QLabel* aux1 = new QLabel("\nSi el sentido de las transiciones no fuera correcto, se podrá cambiar pulsando \nsobre el estado que deseamos que sea el inicial y a continuación el nodo destino");
        a->addWidget(aux1, 0, 0, 2, 2);

        CCheckBox* noMostrarAyuda = new CCheckBox();
        a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 2, 0, 1, 1);
        a->addWidget(noMostrarAyuda, 2, 1, 1, 1);
        a->setSpacing(20);
        CPushButton* aceptar = new CPushButton("Aceptar", true);
        a->addWidget(aceptar, 3, 0, 1, 2);

        getAyuda()->setLayout(a);
        getAyuda()->setStyleSheet("background-color: white");

        getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
        //this->setFixedSize(this->width(), this->height());
        getAyuda()->show();

        connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
        connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
    }
}

void CAplicacion::slotProcesarImagen() {
    slotCargarImagenOriginal(); //evitar doble lectura cuando los campos nodos no estan rellenos
    slotDetectarCirculos();
    if(getNodoInicio()->text().isEmpty() || getNodosFinales()->text().isEmpty()) {
        QMessageBox mensaje;
        mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \nRecuerde configurar el alfabeto.");
        mensaje.setIcon(QMessageBox::Warning);
        mensaje.exec();
        getActionProcesarImagen()->setEnabled(true);
    } else {
        if(getNodoInicio()->text().size() > 2){
            cout << "Error" << endl;
            QMessageBox mensaje;
            mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \nSolo habŕa un estado inicial \nRecuerde configurar el alfabeto.");
            mensaje.setIcon(QMessageBox::Warning);
            mensaje.exec();
            getActionProcesarImagen()->setEnabled(true);
        } else {
            slotDetectarLineas();

            if(getAlfabetoActual()->currentIndex() == 0) {
                QMessageBox mensaje;
                mensaje.setText("Recuerde introducir el alfabeto del autómata.");
                mensaje.setIcon(QMessageBox::Warning);
                mensaje.exec();
                getActionProcesarImagen()->setEnabled(true);
            } else {
                slotDetectarTransiciones();
                if(getNodoInicio()->text().isEmpty() || getNodosFinales()->text().isEmpty()) {
                    QMessageBox mensaje;
                    mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \n\nPulse a continuación el botón Codificar Imagen.");
                    mensaje.setIcon(QMessageBox::Warning);
                    mensaje.exec();
                    getActionProcesarImagen()->setEnabled(true);
                } else {
                    slotCodificarImagen();
                }
            }
        }
    }
}

void CAplicacion::slotCargarImagenOriginal() {
    dibujadaTransiciones_ = false;
    if(getPerspectivaActual()->text() == "Perspectiva actual: \nCorreccion") {
        slotCambiarPerspectiva();
    }
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    resize(aux.dims,height());
    getActionDetectarCirculos()->setDisabled(false);
    getActionProcesarImagen()->setDisabled(false);
    getActionCodificarImagen()->setDisabled(true);
}

void CAplicacion::slotAbrirFicheroCorrecto() {
    QString line = ventanaAbrirFichero();
    if(!line.isEmpty()) {
        getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");
        getPanelComparacion()->setText(line);
        cout << "Mostrando aux " << getPosActualPanelOpciones() << endl;
        if(getPosActualPanelOpciones() == 0)
            posActualPanelOpciones_ = 2;
        else if(getPosActualPanelOpciones() == 1)
            posActualPanelOpciones_ = 3;
        getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());

        if(getPosActualPanelOpciones() == 3) {
            //getPanelOpciones()->setFixedHeight(180);
            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
            connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
            connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));
            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
            connect(getPanelOpciones()->getCorregirFichero(), SIGNAL(clicked()), this, SLOT(slotCorregirFinal()));
            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
        } else if(getPosActualPanelOpciones() == 2) {
            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
        }
    }
}

void CAplicacion::slotFiltroGray() {
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_GRAYSCALE );
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
}

void CAplicacion::slotFiltroGaussiano() {
    Mat aux = getOperacionesImagen()->aplicarFiltro()->filtroGaussianBlur(imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR ));
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
}

void CAplicacion::slotFiltroMediana() {
    Mat aux = getOperacionesImagen()->aplicarFiltro()->filtroMedianBlur(imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR ));
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
}

void CAplicacion::slotFiltroSobel() {
    Mat aux = getOperacionesImagen()->aplicarFiltro()->filtroSobel(imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR ));
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
}

void CAplicacion::slotFiltroLaplaciano() {
    Mat aux = getOperacionesImagen()->aplicarFiltro()->filtroLaplacian(imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR ));
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
}

void CAplicacion::slotHistograma() {
    Mat aux = getOperacionesImagen()->calcularHistograma(imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR ));
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
}

void CAplicacion::slotCirculosCannyAccumulatorHoughLinesP() {
    //getCirculosEliminar()->clear();

    ///Se consideran los distintos pasos de deteccion que pueda tener la imagen aplicados
    getPanelOpciones()->getValorCannyThresHold()->setText(QString::number(getPanelOpciones()->getCannyThresHold()->value()));
    getPanelOpciones()->getValorAccumulatorThresHold()->setText(QString::number(getPanelOpciones()->getAccumulatorThresHold()->value()));
    getPanelOpciones()->getValorHoughLinesP()->setText(QString::number(getPanelOpciones()->getHoughLinesP()->value()));

    //Ya hemos detectado circulos, será cambiarlos segun las variables
    if(getActionDetectarLineas()->isEnabled()) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(mostrarCirculosFinales(resultado)));
        resize(resultado.dims,height());
        //Es circulos y lineas, calculamos ambos
    } else if (getActionDetectarTransiciones()->isEnabled()) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        //Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        aux = mostrarCirculosFinales(aux);

        getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        //Dibujamos lineas
        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( aux, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
        resize(aux.dims,height());
        //Tenemos circulos, lineas y transiciones
    } else if (getActionCodificarImagen()->isEnabled()) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        //Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        //Dibujamos circulos
        aux = mostrarCirculosFinales(aux);
        //aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        //getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        //Dibujamos lineas
        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( aux, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }

        Mat resultado = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarTransiciones()->ejecutar(resultado, getAlfabetoActual()->currentIndex());

        //Dibujar Transiciones
        for (size_t i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
            cv::rectangle(aux,                            // draw rectangle on original image
                          getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                          cv::Scalar(0, 255, 0),                        // green
                          2);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    } else {
        cout << "Error!, Debe cargar una imagen previamente " << endl;
    }
    getPanelOpciones()->setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black");
}

void CAplicacion::slotHelp() {
    ///Crea una ventana que tenga la imagen infoAsistente con informacion relevante
    QWidget* window = new QWidget(); QGridLayout* a = new QGridLayout();
    window->setStyleSheet("background-color: white");
    CLabel* text = new CLabel("Información, formato de codificación", true);
    QLabel* aux = new QLabel(); QImage myImage;

    myImage.load("/home/ivan/Documentos/Codigo-TFG/images/explicacionNuevoFichero.png");
    aux->setPixmap(QPixmap::fromImage(myImage));
    a->addWidget(text, 0, 0, 1, 1);
    a->addWidget(aux, 1, 0, 1, 1);

    window->setLayout(a);
    window->setStyleSheet("background-color: black;");
    window->setWindowTitle("Ayuda");
    //this->setFixedSize(this->width(), this->height());
    window->show();
}

void CAplicacion::slotGuardar() {
    //this->ma//cout << "Text " << text.toStdString() << endl;
    cout << textEditCrearFichero_->toPlainText().toStdString() << endl;
    ///Abre una ventana para guardar la codificacion en un fichero
    setStyleSheet("background-color: white;");
    QFileDialog dialogFile(this, tr("Guardar Codificacion"));
    dialogFile.setDefaultSuffix(".txt");
    const QStringList documentsLocations = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    dialogFile.setDirectory(documentsLocations.last());

    QString filename = dialogFile.getSaveFileName(
                this,
                tr("Save File"),
                documentsLocations.last(),
                tr("Documentos (*.txt)") );

    if( !filename.isNull() ) {
        if(!filename.endsWith(".txt")) {
            filename.append(".txt");
        }
        cout << filename.toStdString() << endl;
        ofstream fs(filename.toStdString());
        fs << getTextEditCrearFichero()->toPlainText().toStdString();
        fs.close();
    }
    //grey
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

}

void CAplicacion::slotCodificarNuevoFichero() {
    cout << "Se borro el fichero temporal de la ejecucion anterior" << remove(PATH_TEMPORAL);
    ofstream fs(PATH_TEMPORAL);
    fs << getTextEditCrearFichero()->toPlainText().toStdString();
    fs.close();
    checkFicheroTemporalCreado();
    getVentanaCrearFichero()->close();
}

void CAplicacion::slotConfirmarImagen() {
    asistente_ = new CAsistenteCodificacion(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(), getNodoInicio()->text().toUtf8().constData(), getNodosFinales()->text().toUtf8().constData(), getOperacionesImagen()->getIniciosAsistente(), getOperacionesImagen()->getDestinosAsistente(), getOperacionesImagen()->getLetrasAsistente());
    //dibujarSentidoTransiciones();
    getAsistente()->show();
    //slotCambiarPerspectiva();
    getCheckUpdatesTimer()->start(1000);
    dibujadaTransiciones_ = false;
}

void CAplicacion::slotPanelPrincipal(QMouseEvent* evt) {

    if(getActionDetectarLineas()->isEnabled()) { // ya se han detectado circulos
        unsigned x( evt -> x() ), y( evt -> y() );
        bool borrado = false;
        //Comprobamos sobre los nodos principales
        for(size_t i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++) {
            if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(x, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(y, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                    //Borramos
                    cout << "Borrando circulo" << endl;
                    getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().erase(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().begin() + i);
                    borrado = true;
                }
            }
        }
        if(borrado == true) { //se Borro un circulo
            //Se vuelve a dibujar la imagen con los nuevos circulos
            Mat resultado = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(mostrarCirculosFinales(resultado)));
        } else { //Añadiendo circulos
            //Añadir circulos a la imagen
            cout << "Añadido circulo" << endl;
            cout << getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size() << " antes" << endl;
            getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().push_back(Vec3f(x, y, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[0][2]));
            cout << getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size() << " despues" << endl;

            Mat resultado = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(mostrarCirculosFinales(resultado)));
        }
    } else if(getActionDetectarTransiciones()->isEnabled()) { //Trabajando sobre lineas
        cout << "Lineas" << endl;
        unsigned x( evt -> x() ), y( evt -> y() );
        cout << "He pulsado " << x << ", " << y << endl;

        if(getCheckEliminarAnadirLinea()->currentIndex() == 0) {
            bool borrado = false;
            cout << "Lineas iniciales" << getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size() << endl;

            for(size_t i = 0; i < getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++) {
                if(borrado == false) {
                    //cout << "Evaluando linea " << getOperacionesImagen()->detectarLineas()->getLineasDetectadas()[i] << endl;
                    //cout << "Posicion " << i << endl;

                    if(getOperacionesImagen()->calcularDatoEnRectaEntreDosPuntos(
                                Point(
                                    getOperacionesImagen()->detectarLineas()->getLineasDetectadas()[i][0],
                                    getOperacionesImagen()->detectarLineas()->getLineasDetectadas()[i][1]
                                    ),
                                Point(
                                    getOperacionesImagen()->detectarLineas()->getLineasDetectadas()[i][2],
                                    getOperacionesImagen()->detectarLineas()->getLineasDetectadas()[i][3]
                                    ),
                                Point(x, y))
                            )  {
                        //si se detecta linea, elimino corto la busqueda y recargo imagen

                        borrado = true;
                        //cout << "Lineas iniciales" << getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size() << endl;
                        getOperacionesImagen()->detectarLineas()->getLineasDetectadas().erase(getOperacionesImagen()->detectarLineas()->getLineasDetectadas().begin() + i);
                        //cout << "Lineas Despues de borrar" << getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size() << endl;
                    } else {
                        //cout << "No toca" << endl;
                    }
                }
            }

            if(borrado == true) {
                //Pintamos el final
                Mat resultado = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
                resultado = mostrarCirculosFinales(resultado);

                //Dibujamos lineas
                cout << "Lineas detectadas " << getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size() << endl;
                for( int i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
                    Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
                    line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
                }
                getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
            }
            else {
                cout << "No se esta pulsando un lugar donde se detecte linea a borrar" << endl;
            }
        } else {
            if (!getLineaAceptada()) {
                puntoInicioNuevaLinea_ = new Point(x, y);
                QMessageBox mensaje;
                mensaje.setText("Clikee en otro punto de la imagen para agregar el punto final de la linea");
                mensaje.setIcon(QMessageBox::Information);
                mensaje.exec();
                lineaAceptada_ = true;
            } else {
                Mat aux = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());

                Vec4i l = Vec4i(getPuntoInicioNuevaLinea()->x, getPuntoInicioNuevaLinea()->y, x, y);
                getOperacionesImagen()->detectarLineas()->getLineasDetectadas().push_back(l);
                line( aux, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
                getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
                cout << "debemos añadir linea" << endl;
                lineaAceptada_ = false;
            }
        }
    } else if (getActionCodificarImagen()->isEnabled() && !getDibujadaTransiciones()) {
        if(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() > 0) {
            bool borrado = false;
            cout << "Lineas" << endl;
            unsigned x( evt -> x() ), y( evt -> y() );
            cout << "He pulsado " << x << ", " << y << endl;

            cout << "x y valen " << x << ", " << y << endl;
            for(int i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++)
                //dimension de contorno 30 pixeles
                if(borrado == false) {
                    if((x - getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno.x) <= 30) {
                        if((y - getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno.y) <= 50) {
                            getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().erase(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().begin() + i);
                            getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().erase(getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().begin() + i);
                            borrado = true;
                            cout << "He encontrado una transicion" << endl;
                        }
                    }
                }

            if(borrado == true) {
                Mat resultado = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
                //Dibujamos circulos
                resultado = mostrarCirculosFinales(resultado);

                //Dibujamos lineas
                for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
                    Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
                    line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
                }

                //Deteccion de transiciones
                for (int i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
                    if((getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).ptContour.size() != 0)) {
                        cv::rectangle(resultado,                            // draw rectangle on original image
                                      getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                                      cv::Scalar(0, 255, 0),                        // green
                                      2);
                    } else {
                        cout << "YESSSSSSSSSSS" << endl;
                        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
                        double fontScale = 1;
                        int thickness = 2;
                        stringstream ss;


                        ss << getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().at(i);

                        string caracter = "";// = new getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().at(i).toString();
                        ss >> caracter;
                        cv::putText(resultado, caracter, Point(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno.x + 10, getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno.y + 10), fontFace, fontScale, Scalar::all(255), thickness,8);
                    }
                }

                getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
            } else { //Creacion de transicion
                QString text;
                //cout << text.toStdString() << endl;
                bool ok;

                text = QInputDialog::getText(0, "Nueva Transicion",
                                             "¿Quiere añadir una nueva transición?", QLineEdit::Normal,
                                             text, &ok);
                if(!text.isEmpty()) {
                    CContourWithData contourWithData;
                    contourWithData.dimensionContorno.x = x;
                    contourWithData.dimensionContorno.y = y;
                    cout << "HEYS" << contourWithData.dimensionContorno << endl;
                    cout << "antes " << getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() << endl;

                    getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().push_back(contourWithData);
                    //getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().push_back();

                    const char* pepe = text.toStdString().c_str();
                    char * p2;

                    p2 = const_cast<char *>(pepe);
                    char hola = *p2;
                    cout << p2 << endl;
                    getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().push_back(hola);


                    //getOperacionesImagen()->detectarTransiciones()->getLetrasEncontradas().push_back(&p);
                    cout << "despues " << getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() << endl;
                    Mat resultado = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());
                    cv::rectangle(resultado,                            // draw rectangle on original image
                                  contourWithData.dimensionContorno,        // rect to draw
                                  cv::Scalar(0, 255, 0),                        // green
                                  2);
                    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
                    double fontScale = 1;
                    int thickness = 2;
                    cv::putText(resultado, text.toStdString(), Point(contourWithData.dimensionContorno.x + 10, contourWithData.dimensionContorno.y + 10), fontFace, fontScale, Scalar::all(255), thickness,8);


                    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
                }
            }
        }
    } else if (getDibujadaTransiciones()) {
        getActionConfirmarImagen()->setEnabled(true);
        unsigned x( evt -> x() ), y( evt -> y() );
        if(!getSentidoAceptado()) {
            //Comprobamos sobre los nodos principales
            for(size_t i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++) {
                if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(x, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                    if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(y, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                        //Borramos
                        QMessageBox mensaje;
                        mensaje.setText("Clikee el otro nodo ");
                        mensaje.setIcon(QMessageBox::Information);
                        mensaje.exec();
                        sentidoAceptado_ = true;
                        puntoInicioSentidoAceptado_ = new Point(x, y);
                        cout << "x y " << x << " " << y << endl;
                        ///Creamos una lista de candidatos si hubiera varios disponibles para cambiar
                        /// si es uno cambiamos directamente, si es dos, o mas preguntamos cual quiere por mensaje con qlineedit

                    }
                }
            }
        } else {
            cout << "2x y " << x << " " << y << endl;
            //cout << "Puntos conseguidos " << getPuntoInicioSentidoAceptado() << " x " << x << " y " << y << endl;
            sentidoAceptado_ = false;
            bool pulsado = false;
            int inicio = -1;
            int destino = -1;
            for(int i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++) {
                if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(x, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                    if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(y, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {

                        inicio = i;
                        //getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().erase(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().begin() + i);
                        pulsado = true;
                    }
                }
            }
            if(pulsado == true) {
                cout << " 2 " << endl;
                pulsado = false;
                for(int i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++) {
                    if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(getPuntoInicioSentidoAceptado()->x, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                        if(getOperacionesImagen()->detectarLineas()->distanciaEuclidea(getPuntoInicioSentidoAceptado()->y, getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1]) < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]) {
                            //Borramos
                            //getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().erase(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().begin() + i);
                            destino = i;
                            pulsado = true;
                        }
                    }
                }
            }

            if(pulsado == true) {
                for(int i = 0; i < getOperacionesImagen()->getIniciosAsistente()->size(); i++){

                    if(inicio == getOperacionesImagen()->getIniciosAsistente()->at(i)) {
                        if(destino == getOperacionesImagen()->getDestinosAsistente()->at(i)) {
                            int aux = getOperacionesImagen()->getIniciosAsistente()->at(i);
                            getOperacionesImagen()->getIniciosAsistente()->at(i) = getOperacionesImagen()->getDestinosAsistente()->at(i);
                            getOperacionesImagen()->getDestinosAsistente()->at(i) = aux;
                            /*replace(getOperacionesImagen()->getIniciosAsistente()->begin() + i - 1 , getOperacionesImagen()->getIniciosAsistente()->end() - i,
                                    getOperacionesImagen()->getIniciosAsistente()->at(i),
                                    getOperacionesImagen()->getDestinosAsistente()->at(i));
                            cout << "AUX " << aux << endl;
                            replace(getOperacionesImagen()->getDestinosAsistente()->begin() + i - 1, getOperacionesImagen()->getDestinosAsistente()->end() - i ,
                                    getOperacionesImagen()->getDestinosAsistente()->at(i),
                                    aux);
                            */cout << "i vale " << i << endl;
                            cout << " inicio " << getOperacionesImagen()->getIniciosAsistente()->at(i) << " destino " << getOperacionesImagen()->getDestinosAsistente()->at(i) << endl;
                            dibujarSentidoTransiciones();
                            /*getAsistente()->slotCancelar();
                                asistente_ = new CAsistenteCodificacion(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(), getNodoInicio()->text().toUtf8().constData(), getNodosFinales()->text().toUtf8().constData(), getOperacionesImagen()->getIniciosAsistente(), getOperacionesImagen()->getDestinosAsistente(), getOperacionesImagen()->getLetrasAsistente());
                            getAsistente()->show();*/

                            /* getAsistente()->getInicios()->at(i) = new CLineEdit(QString::number(getOperacionesImagen()->getIniciosAsistente()->at(i)));
                            getAsistente()->getDestinos()->at(i)->text() = getOperacionesImagen()->getDestinosAsistente()->at(i);
                            cout << "HOLA" << endl;*/
                            break;
                        }
                    }
                }
            }
        }
    }
}

void CAplicacion::checkFicheroTemporalCreado() {
    ifstream fich(PATH_TEMPORAL, ios::in | ios::binary);
    //fich.read(mes, 20);
    if(fich.good()) {
        if(!fich.eof()) {//peek() == std::ifstream::traits_type::eof() ) { // si el fichero no esta vacio
            QFile newFile(PATH_TEMPORAL);
            newFile.open( QIODevice::WriteOnly|QIODevice::Append );
            if (newFile.pos() == 0) {
                cout << "Cancelado" << endl;// is empty
                getCheckUpdatesTimer()->stop();

            } else {
                QFile file1(PATH_TEMPORAL);
                if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    cout << "Error Guardando el fichero codificado" << endl;
                } else {
                    QTextStream in(&file1);
                    QString line;
                    while(!in.atEnd()){
                        line += in.readLine();
                        line += "\n";
                    }
                    if(getPerspectivaActual()->text() == "Perspectiva actual: \nDeteccion") {
                        slotCambiarPerspectiva();
                    }

                    if(!getCargarImagenParaPanelComparacion()) {

                        getPanelPrincipal()->setText(line);
                        getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");
                        getActionAbrirFicheroCorrecto()->setDisabled(false);
                        if(getPosActualPanelOpciones() == 0)
                            posActualPanelOpciones_ = 1;
                        else if(getPosActualPanelOpciones() == 2)
                            posActualPanelOpciones_ = 3;
                        getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());

                        //En el caso que cambiemos la perspectiva habiendo tenido ya cargado el fichero a corregir con los 4 botones puestos
                        bool encontrado = false;
                        for (int i = 0; i < getPanelOpciones()->getLayout()->count(); ++i) {
                            QWidget *widget = getPanelOpciones()->getLayout()->itemAt(i)->widget();
                            if (widget == getPanelOpciones()->getAnalizarCadena()) {
                                encontrado = true;
                                break;
                            }
                        }
                        if(encontrado == false) {
                            if(getPosActualPanelOpciones() == 1) {
                                posActualPanelOpciones_ = 0;
                                getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
                            } else if(getPosActualPanelOpciones() == 3) {
                                posActualPanelOpciones_ = 2;

                                getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
                            }
                        }

                        if(getPosActualPanelOpciones() == 3) {
                            //getPanelOpciones()->setFixedHeight(200);
                            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));

                            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
                            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
                            connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
                            connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));
                            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
                            connect(getPanelOpciones()->getCorregirFichero(), SIGNAL(clicked()), this, SLOT(slotCorregirFinal()));
                            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
                        }
                        else if(getPosActualPanelOpciones() == 1) {
                            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));

                            connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
                            connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));

                        } else if(getPosActualPanelOpciones() == 2) {
                            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
                            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
                            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
                            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
                            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
                        }
                        getCheckUpdatesTimer()->stop();
                    } else {
                        if(getAuxContenidoAnterior()->text() != "") {
                            if(getAuxContenidoAnterior()->text() != "Introduzca aqui la imagen o fichero a corregir ") {
                                cout << getAuxContenidoAnterior()->text().toStdString() << endl;
                                cout << "Antes habia contenido en el panel principal, recuperando" << endl;
                                getPanelPrincipal()->setText(getAuxContenidoAnterior()->text());
                                posActualPanelOpciones_ = 3;
                            }
                        }
                        getPanelComparacion()->setText(line);
                        getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 40px;");
                        if(getPosActualPanelOpciones() == 0)
                            posActualPanelOpciones_ = 2;
                        else if(getPosActualPanelOpciones() == 1)
                            posActualPanelOpciones_ = 3;
                        getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());

                        if(getPosActualPanelOpciones() == 3) {
                            //getPanelOpciones()->setFixedHeight(180);
                            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
                            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
                            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
                            connect(getPanelOpciones()->getAnalizarCadena(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadena()));
                            connect(getPanelOpciones()->getSimplificarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroCorregir()));
                            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
                            connect(getPanelOpciones()->getCorregirFichero(), SIGNAL(clicked()), this, SLOT(slotCorregirFinal()));
                            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));

                        } else if(getPosActualPanelOpciones() == 2) {
                            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
                            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
                            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
                            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
                            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
                        }
                        cargarImagenParaPanelComparacion_ = false;
                        getCheckUpdatesTimer()->stop();
                    }
                }
            }
        }
        else { //si fichero vacio ->opcion cancelar del asistente
            getCheckUpdatesTimer()->stop();
            cout << "fichero vacio" << endl;
        }
    } else {
        /*cout << "Fichero Codificado aun no creado \n Error al leer de Fichero" << endl;
        if(fich.fail()) cout << "Bit fail activo" << endl;
        if(fich.eof())  cout << "Bit eof activo" << endl;
        if(fich.bad())  cout << "Bit bad activo" << endl;*/
    }
    fich.close();
}

void CAplicacion::slotRestaurarValores() {
    if(getRestaurarValores()->text() == "Cargar fichero de referencia") {
        slotAbrirFicheroCorrecto();
        //setStyleSheet("background-color: black");
    } else {
        getPanelOpciones()->getCannyThresHold()->setValue(CANNYTHRESHOLD);
        getPanelOpciones()->getAccumulatorThresHold()->setValue(ACCUMULATORTHRESHOLD);
        getPanelOpciones()->getHoughLinesP()->setValue(HOUGHLINESP);
    }
}

void CAplicacion::slotAbrirImagenReferencia() {
    cargarImagenParaPanelComparacion_ = true;
    auxContenidoAnterior_ = new CLabel(getPanelPrincipal()->text(), true);
    //cout << "Panel Principal " << getPanelPrincipal()->text().toStdString() << endl;
    //cout << "HEY " << auxContenidoAnterior_->text().toStdString() << endl;
    slotAbrirImagen();
}

void CAplicacion::slotCambiarPerspectiva() {
    if(getPerspectivaActual()->text() == "Perspectiva actual: \nDeteccion") {
        inicializarVentanaAplicacionCorreccion();
        if(getPanelPrincipal()->text() == "Introduzca aqui la imagen o fichero a corregir ") {
            posActualPanelOpciones_ = 0;
            if(getPanelComparacion()->text() != "Introduzca aqui la imagen o fichero de referencia ")
                posActualPanelOpciones_ = 2;
        } else {
            /*cout << "PAnel actual " << posActualPanelOpciones_ << endl;
            if(getPanelComparacion()->text() != "Introduzca aqui la imagen o fichero a corregir ") {
                cout << "HOLA paxc " << endl;
                posActualPanelOpciones_ = 3;
                getPanelOpciones()->setFixedHeight(180);
            } else {*/
            posActualPanelOpciones_ = 2;
            getPanelPrincipal()->setText("Introduzca aqui la imagen o fichero a corregir");
        }

        getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
        getRestaurarValores()->setText("Cargar fichero de referencia");
        getPerspectivaActual()->setText("Perspectiva actual: \nCorreccion");
        getActionDetectarLineas()->setEnabled(false);
        getActionDetectarCirculos()->setEnabled(false);
        getActionDetectarTransiciones()->setEnabled(false);
        getActionCodificarImagen()->setEnabled(false);
        getActionProcesarImagen()->setEnabled(false);
        getActionCargarImagenOriginal()->setEnabled(false);
        getActionAbrirFicheroCorrecto()->setEnabled(true);
        getActionConfirmarImagen()->setEnabled(false);
        setStyleSheet("background-color: rgba(191, 191, 191, 1);");

        connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
        connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
        connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
        connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
        if(getPosActualPanelOpciones() == 2) {
            connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
            connect(getPanelOpciones()->getAnalizarCadenaReferencia(), SIGNAL(clicked()), this, SLOT(slotAnalizarCadenaReferencia()));
        }

        if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
            delete getAyuda();
            ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();
            QLabel* aux1 = new QLabel("Bienvenido a la herramienta DCAFI. \n\nSi desea corregir un autómata, introduzca \nel autómata a corregir y el de referencia en\nlos paneles correspondientes. \n\nSi desea solo detectar un autómata en una imagen, \ncambie de perspectiva en el botón inferior derecho \nde la aplicación. \n\nSi desea crear una nueva codificación en \nformato de texto plano entre en: \n Archivo -> Crear nuevo fichero.");

            a->addWidget(aux1, 0, 0, 2, 2);

            CCheckBox* noMostrarAyuda = new CCheckBox();
            a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 2, 0, 1, 1);
            a->addWidget(noMostrarAyuda, 2, 1, 1, 1);
            a->setSpacing(10);
            CPushButton* aceptar = new CPushButton("Aceptar", true);
            a->addWidget(aceptar, 3, 0, 1, 2);

            getAyuda()->setLayout(a);
            getAyuda()->setStyleSheet("background-color: white");

            getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
            //this->setFixedSize(this->width(), this->height());
            getAyuda()->show();

            connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
            connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
        }
        cout << getActionMostrarAyuda()->text().toStdString() << endl;

    } else {
        inicializarVentanaAplicacionDeteccion();
        getActionCargarImagenOriginal()->setEnabled(true);
        if(getPathImagenActual() != NULL) {
            getActionDetectarCirculos()->setEnabled(true);
            getActionProcesarImagen()->setEnabled(true);
        }
        getPanelPrincipal()->clear();
        getNodoInicio()->clear();
        getNodosFinales()->clear();

        getActionAbrirFicheroCorrecto()->setEnabled(false);
        getActionConfirmarImagen()->setEnabled(false);
        cout << "La posicion actual es " << getPosActualPanelOpciones() << endl;
        getPanelOpciones()->iniciarVistaDeteccion(getPosActualPanelOpciones());
        getRestaurarValores()->setText("Restaurar ScrollBar's");
        getPerspectivaActual()->setText("Perspectiva actual: \nDeteccion");
        //connect(getCheckUpdatesTimer(), SIGNAL(timeout()), this, SLOT(checkFicheroTemporalCreado()));
        connect(getPanelOpciones()->getCannyThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
        connect(getPanelOpciones()->getAccumulatorThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
        connect(getPanelOpciones()->getHoughLinesP(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
        setStyleSheet("background-color: rgba(191, 191, 191, 1);");

        //Mostrar ayuda
        if(getActionMostrarAyuda()->text() == "No mostrar ayuda") {
            delete getAyuda();
            ayuda_ = new QWidget(); QGridLayout* a = new QGridLayout();
            QLabel* aux1 = new QLabel("\nPuede realizar la detección automática de la\nimagen pulsando sobre el boton \nProcesar Imagen: ");
            QImage myImage;
            myImage.load("/home/ivan/Documentos/Codigo-TFG/images/procesarImagen.png");

            QLabel* myLabel = new QLabel();
            myLabel->setPixmap(QPixmap::fromImage(myImage));

            a->addWidget(aux1, 0, 0, 2, 2);
            a->addWidget(myLabel, 2, 0, 1, 2);

            QLabel* aux2 = new QLabel(" o realizar una detección paso a paso detectando \ncirculos, lineas, transiciones \ny sentidos.");
            QImage myImage1;
            myImage1.load("/home/ivan/Documentos/Codigo-TFG/images/pasoApaso.png");

            QLabel* myLabel1 = new QLabel();
            myLabel1->setPixmap(QPixmap::fromImage(myImage1));
            myLabel1->show();
            a->addWidget(aux2, 3, 0, 2, 2);
            a->addWidget(myLabel1, 5, 0, 1, 2);

            CCheckBox* noMostrarAyuda = new CCheckBox();
            a->addWidget(new CLabel("Dejar de mostrar la ayuda", false), 6, 0, 1, 1);
            a->addWidget(noMostrarAyuda, 6, 1, 1, 1);
            a->setSpacing(20);
            CPushButton* aceptar = new CPushButton("Aceptar", true);
            a->addWidget(aceptar, 7, 0, 1, 2);

            getAyuda()->setLayout(a);
            getAyuda()->setStyleSheet("background-color: white");

            getAyuda()->setWindowTitle("Info Panel Detección de Imagen");
            //this->setFixedSize(this->width(), this->height());
            getAyuda()->show();

            connect(noMostrarAyuda , SIGNAL(stateChanged(int)),this,SLOT(slotMostrarAyuda()));
            connect(aceptar, SIGNAL(pressed()), getAyuda(), SLOT(close()));
        }
        cout << getActionMostrarAyuda()->text().toStdString() << endl;
    }
}

void CAplicacion::slotSimplificarFicheroCorregir() {
    remove(PATH_TEMPORALDFA);
    cout << "Simplificando fichero referencia" << endl;
    CNFA nfa;

    nfa.ConstruirNFA(getPanelPrincipal()->text());
    nfa.CrearAlfabeto();
    vector<CEstado> Orden;
    cout << "A punto de convertir a DFA " << endl;
    Orden = nfa.ConverttoDFA();

    nfa.Exportar(Orden);
    QFile file1(PATH_TEMPORALDFA);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, hubo un error en la simplificación del DFA, fichero invalido" << endl;

    } else {

        QTextStream in(&file1);
        QString line;
        while(!in.atEnd()){
            line += in.readLine();
            line += "\n";
        }
        getPanelPrincipal()->setText(line);
    }

    //DFA minimo
    cout << "DFA minimo" << endl;
    //(2);
    DFA_MIN dfa;
    dfa.Leer_DFA(PATH_TEMPORALDFA);
    dfa.Divide_DFA();
    dfa.Minimizar_DFA();
    dfa.Exportar_DFA_min();

    QFile file2(PATH_TEMPORALDFA);
    if(!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, hubo un error en la simplificación del DFA, fichero invalido" << endl;

    } else {

        QTextStream in(&file2);
        QString line;
        while(!in.atEnd()){
            line += in.readLine();
            line += "\n";
        }
        getPanelPrincipal()->setText(line);
    }

    //Volvemos a aplicar NFA
    cout << "NFA de nuevo" << endl;
    CNFA nfa2;

    nfa2.ConstruirNFA(getPanelPrincipal()->text());
    nfa2.CrearAlfabeto();
    vector<CEstado> Orden2;
    cout << "A punto de convertir a DFA de nuevo" << endl;
    Orden2 = nfa2.ConverttoDFA();

    nfa2.Exportar(Orden2);
    QFile file3(PATH_TEMPORALDFA);
    if(!file3.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, hubo un error en la simplificación del DFA, fichero invalido" << endl;

    } else {

        QTextStream in(&file3);
        QString line;
        while(!in.atEnd()){
            line += in.readLine();
            line += "\n";
        }
        getPanelPrincipal()->setText(line);
    }
}

void CAplicacion::slotSimplificarFicheroReferencia() {

    remove(PATH_TEMPORALDFA);
    cout << "Simplificando fichero referencia" << endl;
    CNFA nfa;

    nfa.ConstruirNFA(getPanelComparacion()->text());
    nfa.CrearAlfabeto();
    vector<CEstado> Orden;
    cout << "A punto de convertir a DFA " << endl;
    Orden = nfa.ConverttoDFA();

    nfa.Exportar(Orden);
    QFile file1(PATH_TEMPORALDFA);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, hubo un error en la simplificación del DFA, fichero invalido" << endl;

    } else {

        QTextStream in(&file1);
        QString line;
        while(!in.atEnd()){
            line += in.readLine();
            line += "\n";
        }
        getPanelComparacion()->setText(line);
    }

    //delay(2);

    //DFA minimo
    cout << "DFA minimo" << endl;
    DFA_MIN dfa;
    dfa.Leer_DFA(PATH_TEMPORALDFA);
    dfa.Divide_DFA();
    dfa.Minimizar_DFA();
    dfa.Exportar_DFA_min();

    QFile file2(PATH_TEMPORALDFA);
    if(!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, hubo un error en la simplificación del DFA, fichero invalido" << endl;

    } else {

        QTextStream in(&file2);
        QString line;
        while(!in.atEnd()){
            line += in.readLine();
            line += "\n";
        }
        getPanelComparacion()->setText(line);
    }

    //Volvemos a aplicar NFA
    cout << "NFA de nuevo" << endl;
    CNFA nfa2;

    nfa2.ConstruirNFA(getPanelComparacion()->text());
    nfa2.CrearAlfabeto();
    vector<CEstado> Orden2;
    cout << "A punto de convertir a DFA de nuevo" << endl;
    Orden2 = nfa2.ConverttoDFA();

    nfa2.Exportar(Orden2);
    QFile file3(PATH_TEMPORALDFA);
    if(!file3.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Error, hubo un error en la simplificación del DFA, fichero invalido" << endl;

    } else {

        QTextStream in(&file3);
        QString line;
        while(!in.atEnd()){
            line += in.readLine();
            line += "\n";
        }
        getPanelComparacion()->setText(line);
    }

    cout << "referencia " << endl;
}

void CAplicacion::slotAnalizarCadena() {
    QString text;

    bool ok;

    text = QInputDialog::getText(0, "Cadena ",
                                 "Introduzca la cadena a analizar:", QLineEdit::Normal,
                                 text, &ok);
    if(!text.isEmpty()) {

        CNFA nfa;

        nfa.ConstruirNFA(getPanelPrincipal()->text());
        nfa.CrearAlfabeto();

        cout << endl << "--> Analizar Cadena" << endl;
        string aux = text.toStdString();

        QWidget* window = new QWidget(); QVBoxLayout* a = new QVBoxLayout();
        CLabel* aux4 = new CLabel("Cadena:  " + text, true);
        CLabel* aux1 = new CLabel(QString::fromStdString(nfa.AnalizarCadena(aux)), true);

        CLabel* aux2 = new CLabel(QString::fromStdString(nfa.MostrarEstadosMuerte()), true);

        CLabel* aux3 = new CLabel(QString::fromStdString(nfa.MostrarAlfabeto()), true);

        if(aux1->text() == "\nDecision final: Cadena SI aceptada") {
            aux1->setStyleSheet("background-color: rgb(95, 225, 110);");
        } else
            aux1->setStyleSheet("background-color: rgb(237, 130, 98);");

        a->addWidget(aux4);
        a->addWidget(aux3);
        a->addWidget(aux1);
        a->addWidget(aux2);

        window->setLayout(a);

        window->setWindowTitle("Cadena");
        //this->setFixedSize(this->width(), this->height());
        window->show();
    }
}

void CAplicacion::slotAnalizarCadenaReferencia() {
    QString text;

    bool ok;

    text = QInputDialog::getText(0, "Cadena ",
                                 "Introduzca la cadena a analizar:", QLineEdit::Normal,
                                 text, &ok);
    if(!text.isEmpty()) {

        CNFA nfa;

        nfa.ConstruirNFA(getPanelComparacion()->text());
        nfa.CrearAlfabeto();

        cout << endl << "--> Analizar Cadena" << endl;
        string aux = text.toStdString();

        QWidget* window = new QWidget(); QVBoxLayout* a = new QVBoxLayout();
        CLabel* aux4 = new CLabel("Cadena:  " + text, true);
        CLabel* aux1 = new CLabel(QString::fromStdString(nfa.AnalizarCadena(aux)), true);

        CLabel* aux2 = new CLabel(QString::fromStdString(nfa.MostrarEstadosMuerte()), true);

        CLabel* aux3 = new CLabel(QString::fromStdString(nfa.MostrarAlfabeto()), true);

        if(aux1->text() == "\nDecision final: Cadena SI aceptada") {
            aux1->setStyleSheet("background-color: rgb(95, 225, 110);");
        } else
            aux1->setStyleSheet("background-color: rgb(237, 130, 98);");

        a->addWidget(aux4);
        a->addWidget(aux3);
        a->addWidget(aux1);
        a->addWidget(aux2);

        window->setLayout(a);

        window->setWindowTitle("Cadena");
        //this->setFixedSize(this->width(), this->height());
        window->show();
    }
}

void CAplicacion::slotCorregirFinal() {
    cout << "Corrigiendo Final" << endl;
    delete getVentanaFinal();
    ventanaFinal_ = new QWidget();

    QHBoxLayout* a = new QHBoxLayout();
    CLabel* aux = new CLabel();
    if(getPanelPrincipal()->text() == getPanelComparacion()->text()){
        aux->setText("Los autómatas \nson Equivalentes");
        aux->setStyleSheet("background-color: rgb(154, 238, 127);"
                           "color: black; border-width: 1px;"
                           "border-top: 1px solid white;"
                           "border-left: 1px solid white;"
                           "border-right: 1px solid grey;"
                           "border-bottom: 1px solid grey;"
                           "border-style: solid; "
                           "border-radius: 5;"
                           "padding: 2px;"
                           "padding-left: 5px;"
                           "padding-right: 5px;"
                           "font: 16px;"
                           "font-weight: bold;");
    } else {
        slotSimplificarFicheroCorregir();
        slotSimplificarFicheroReferencia();
        if(getPanelPrincipal()->text() == getPanelComparacion()->text()){
            aux->setText("Los autómatas \nson equivalentes");
            aux->setStyleSheet("background-color: rgb(154, 238, 127);"
                               "color: black; border-width: 1px;"
                               "border-top: 1px solid white;"
                               "border-left: 1px solid white;"
                               "border-right: 1px solid grey;"
                               "border-bottom: 1px solid grey;"
                               "border-style: solid; "
                               "border-radius: 5;"
                               "padding: 2px;"
                               "padding-left: 5px;"
                               "padding-right: 5px;"
                               "font: 16px;"
                               "font-weight: bold;");
        } else {
            aux->setText("Los autómatas \nNO son equivalentes");
            aux->setStyleSheet("background-color: rgba(255, 20, 20, 0.5);"
                               "color: black; border-width: 1px;"
                               "border-top: 1px solid white;"
                               "border-left: 1px solid white;"
                               "border-right: 1px solid grey;"
                               "border-bottom: 1px solid grey;"
                               "border-style: solid; "
                               "border-radius: 5;"
                               "padding: 2px;"
                               "padding-left: 5px;"
                               "padding-right: 5px;"
                               "font: 16px;"
                               "font-weight: bold;");
        }
    }

    a->addWidget(aux);

    getVentanaFinal()->setLayout(a);
    getVentanaFinal()->setWindowTitle("Correccion final");
    getVentanaFinal()->setFixedSize(300, 200);
    getVentanaFinal()->show();
}

//get y sets
QString CAplicacion::getPathImagenActual() {
    return pathImagenActual_;
}

void CAplicacion::setPathImagenActual(QString path) {
    pathImagenActual_ = path;
}

//VENTANA
CLabel* CAplicacion::getPanelPrincipal() {
    return panelPrincipal_;
}

CLabel* CAplicacion::getPanelComparacion() {
    return panelComparacion_;
}

CPanelOpciones* CAplicacion::getPanelOpciones() {
    return panelOpciones_;
}

CLabel* CAplicacion::getPanelHistograma() {
    return panelHistograma_;
}

QGridLayout* CAplicacion::getLayout() {
    return layout_;
}

QMenuBar* CAplicacion::getMenuBar() {
    return menu_;
}

QMenu* CAplicacion::getMenuArchivo() {
    return menuArchivo_;
}

QMenu* CAplicacion::getMenuDeteccion() {
    return menuEditar_;
}

QMenu* CAplicacion::getMenuCorreccion() {
    return menuCorreccion_;
}

QMenu* CAplicacion::getMenuFiltro() {
    return menuFiltro_;
}

QToolBar* CAplicacion::getToolBar() {
    return toolbar_;
}

CLineEdit* CAplicacion::getNodoInicio() {
    return nodo_inicio;
}

CLineEdit* CAplicacion::getNodosFinales() {
    return nodos_finales;
}

QComboBox* CAplicacion::getAlfabetoActual() {
    return alfabeto_;
}

QAction* CAplicacion::getActionAbrirImagen() {
    return actionAbrirImagen_;
}

QAction* CAplicacion::getActionAbrirFichero() {
    return actionAbrirFichero_;
}

QAction* CAplicacion::getActionCrearNuevoFichero() {
    return actionCrearNuevoFichero_;
}

QAction* CAplicacion::getActionMostrarAyuda() {
    return actionMostrarAyuda_;
}

QAction* CAplicacion::getActionAbout() {
    return actionAbout_;
}

QAction* CAplicacion::getActionAboutQT() {
    return actionAboutQT_;
}

QAction* CAplicacion::getActionSalir() {
    return actionSalir_;
}

QAction* CAplicacion::getActionDetectarCirculos() {
    return actionDetectarCirculos_;
}

QAction* CAplicacion::getActionDetectarLineas() {
    return actionDetectarLineas_;
}

QAction* CAplicacion::getActionDetectarTransiciones() {
    return actionDetectarTransiciones_;
}

QAction* CAplicacion::getActionCodificarImagen() {
    return actionCodificarImagen_;
}

QAction* CAplicacion::getActionConfirmarImagen() {
    return actionConfirmarImagen_;
}

QAction* CAplicacion::getActionProcesarImagen() {
    return actionProcesarImagen_;
}

QAction* CAplicacion::getActionCargarImagenOriginal() {
    return actionCargarImagenOriginal_;
}

QAction* CAplicacion::getActionAbrirFicheroCorrecto() {
    return actionAbrirFicheroCorrecto_;
}

QAction* CAplicacion::getActionFiltroGray() {
    return actionFiltroGray_;
}

QAction* CAplicacion::getActionFiltroGaussiano() {
    return actionFiltroGaussiano_;
}

QAction* CAplicacion::getActionFiltroMediana() {
    return actionFiltroMediana_;
}

QAction* CAplicacion::getActionFiltroSobel() {
    return actionFiltroSobel_;
}

QAction* CAplicacion::getActionFiltroLaplaciano() {
    return actionFiltroLaplaciano_;
}

QAction* CAplicacion::getActionHistograma() {
    return actionHistograma_;
}

QAction* CAplicacion::getActionPanelPrincipal() {
    return actionPanelPrincipal_;
}

COperacionesImagen* CAplicacion::getOperacionesImagen() {
    return operacionesImagen_;
}

QTextEdit* CAplicacion::getTextEditCrearFichero() {
    return textEditCrearFichero_;
}

QTimer* CAplicacion::getCheckUpdatesTimer() {
    return checkUpdatesTimer_;
}

CPushButton* CAplicacion::getRestaurarValores() {
    return restaurarValores_;
}

CPushButton* CAplicacion::getCambiarPerspectiva() {
    return cambiarPerspectiva_;
}

CLabel* CAplicacion::getPerspectivaActual() {
    return perspectivaActual_;
}

Mat CAplicacion::mostrarCirculosFinales(Mat resultado) {
    //nodos originales que no se quieran eliminar
    for(int i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++ ) {
        Point center(cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]), cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1])); //x y
        int radius = cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]);
        //cout << "Circulo num " << i << " con centro (" << center.x << ", " << center.y << " y radio " << radius << endl;
        //punto central
        circle( resultado, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( resultado, center, radius, Scalar(0,0,255), 3, 8, 0 );

        ///Dibujamos el num del circulo en la imagen
        stringstream ss;
        ss << i;
        string text = ss.str();
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        int thickness = 2;
        cv::putText(resultado, text, Point(center.x - radius/2, center.y + radius/2), fontFace, fontScale, Scalar::all(255), thickness,8);
    }
    return resultado;
}

QWidget* CAplicacion::getVentanaCrearFichero() {
    return ventanaCrearFichero_;
}

CAsistenteCodificacion* CAplicacion::getAsistente() {
    return asistente_;
}

QComboBox* CAplicacion::getCheckEliminarAnadirLinea() {
    return checkEliminarAnadirLinea_;
}

bool CAplicacion::getLineaAceptada() {
    return lineaAceptada_;
}

bool CAplicacion::getSentidoAceptado() {
    return sentidoAceptado_;
}

Point* CAplicacion::getPuntoInicioNuevaLinea() {
    return puntoInicioNuevaLinea_;
}

Point* CAplicacion::getPuntoInicioSentidoAceptado() {
    return puntoInicioSentidoAceptado_;
}

bool CAplicacion::getDibujadaTransiciones() {
    return dibujadaTransiciones_;
}

bool CAplicacion::getCargarImagenParaPanelComparacion() {
    return cargarImagenParaPanelComparacion_;
}

CLabel* CAplicacion::getAuxContenidoAnterior() {
    return auxContenidoAnterior_;
}

int CAplicacion::getPosActualPanelOpciones() {
    return posActualPanelOpciones_;
}

QWidget* CAplicacion::getAyuda() {
    return ayuda_;
}

QWidget* CAplicacion::getVentanaFinal() {
    return ventanaFinal_;
}
