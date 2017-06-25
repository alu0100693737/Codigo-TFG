//detect numbers https://www.mkompf.com/cplus/emeocv.html
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
#include <iostream>
using namespace cv;
using namespace std;

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

    actionAbrirImagen_      = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/imagenOriginal.png"), tr("Abrir Imagen para su detección"), this);
    actionAbrirFichero_     = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/fichero.png"), tr("Abrir Fichero para su correccion"), this);
    actionCrearNuevoFichero_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/nuevoFichero.png"), tr("Crear Nuevo Automata"), this);
    actionAbout_            = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/about.png"), tr("About"), this);
    actionAboutQT_          = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/aboutQT.png"), tr("About QT"), this);
    actionSalir_            = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/salir.png"), tr("Salir"), this);

    actionDetectarLineas_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/linea.png"), tr("Detectar Lineas"), this);
    actionDetectarCirculos_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/circulo.png"), tr("Detectar Circulos"), this);
    actionDetectarTransiciones_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/transition.png"), tr("Detectar Transiciones"), this);
    actionCodificarImagen_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/codificar.png"), tr("Codificar Imagen"), this);
    actionConfirmarImagen_ =new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/check.png"), tr("Confirmar Deteccion"));
    actionProcesarImagen_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/opencv.png"), tr("Procesar Imagen"), this);
    actionCargarImagenOriginal_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/imagenOriginal.png"), tr("Cargar ultima Imagen"), this);

    actionAbrirFicheroCorrecto_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/check.png"), tr("Abrir Fichero Correcto"));

    actionFiltroGray_ = new QAction(QIcon(""), tr("Filtro Gray"), this);
    actionFiltroGaussiano_   = new QAction(QIcon(""), tr("Filtro Gaussiano"), this);
    actionFiltroMediana_ = new QAction(QIcon(""), tr("Filtro Mediana"), this);
    actionFiltroSobel_ = new QAction(QIcon(""), tr("Filtro Sobel"), this);
    actionFiltroLaplaciano_ = new QAction(QIcon(""), tr("Filtro Laplaciano"), this);
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

    ///Shortcuts
    getActionAbrirImagen()->setShortcuts(QKeySequence::New);
    getActionSalir()->setShortcut(QKeySequence::Close);

    getMenuArchivo()->addAction(getActionAbrirImagen());
    getMenuArchivo()->addAction(getActionAbrirFichero());
    getMenuArchivo()->addAction(getActionCrearNuevoFichero());
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
    getAlfabetoActual()->addItem(tr("Alfabeto a, b, c, d"));
    getAlfabetoActual()->addItem(tr("Alfabeto Numerico"));

    checkEliminarAnadirLinea_ = new QCheckBox();
    getCheckEliminarAnadirLinea()->click();
    textEliminarAnadirLinea_ = new CLabel("Eliminar Lineas", false);
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
    this->getToolBar()->addWidget(getTextAnadirEliminar());
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

    connect(getCheckEliminarAnadirLinea(), SIGNAL(clicked()), this, SLOT(slotCambiarTextEliminarAnadirLinea()));
    connect(getCheckUpdatesTimer(), SIGNAL(timeout()), this, SLOT(checkFicheroTemporalCreado()));

    slotCambiarPerspectiva(); //Empezamos con la perspectiva codificacion
}

CAplicacion::~CAplicacion() {}

void CAplicacion::inicializarVentanaAplicacionDeteccion() {

    //setStyleSheet("background-color: black");
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

    getPanelComparacion()->setAlignment(Qt::AlignCenter);
    getPanelPrincipal()->setAlignment(Qt::AlignCenter);
    getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 6px;");

    //getLayout()->removeWidget(getPanelComparacion());
    //getPanelComparacion()->clear();
    getLayout()->addWidget(getPanelComparacion(), 0, 0, 3, 4);

    getLayout()->addWidget (getPanelPrincipal(), 0, 0, 3, 4);
    getLayout()->addWidget (getPanelOpciones(), 4, 0, 1, 3);

    //Si teniamos una imagen previamente cargada
    if(getPathImagenActual() != NULL) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    } else {
        getActionCargarImagenOriginal()->setDisabled(true);
        /* Mat aux = imread("/home/ivan/Documentos/Codigo-TFG/images/cartel1.png", IMREAD_UNCHANGED);
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));*/
    }
    QVBoxLayout* layout1 = new QVBoxLayout();
    layout1->addWidget(getPerspectivaActual());
    layout1->addWidget(getCambiarPerspectiva());
    layout1->setSpacing(10);
    layout1->addWidget(getRestaurarValores());/* layout1->addWidget(getGuardarComoFichero()); layout1->addWidget(getCorregirAutomata());
    layout1->addWidget(getHelp());*/

    layout1->setSpacing(10);
    getLayout()->addLayout(layout1, 4, 3, 1, 1);
    //green
    getPanelOpciones()->setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black ;");
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

}

void CAplicacion::inicializarVentanaAplicacionCorreccion() {

    getPanelPrincipal()->clear();
    //getPanelComparacion()->clear();
    if(getAuxContenidoAnterior()->text() == "")
        getPanelPrincipal()->setText("Introduzca aqui la imagen o fichero a corregir ");
    else {

        getPanelPrincipal()->setText(getAuxContenidoAnterior()->text());
    }
    getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");

    if(getPanelComparacion()->text() == "")
        getPanelComparacion()->setText("Introduzca aqui el fichero de referencia");

    getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");

    getLayout()->addWidget(getPanelComparacion(), 0, 2, 3, 2);
    getLayout()->addWidget (getPanelPrincipal(), 0, 0, 3, 2);
    getPanelComparacion()->setAlignment(Qt::AlignAbsolute);
    getPanelPrincipal()->setAlignment(Qt::AlignAbsolute);
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

    getPanelOpciones()->setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 4px solid black");
}

//SLOTS
void CAplicacion::slotAbrirImagen() {
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
            getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");
            getActionAbrirFicheroCorrecto()->setDisabled(false);
            posActualPanelOpciones_ = 1;
            getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
            connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
            connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));
            //poner analizar cadena y simplificar
        } else {
            getPanelComparacion()->setText(line);
            getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");
            posActualPanelOpciones_ = 2;
            getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
            connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
            connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
            //poner simplificar
        }
    }
    setStyleSheet("background-color: rgba(191, 191, 191, 1);");

    //setStyleSheet("background-color: black");
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
    //cout << "File name: " << fileName.toUtf8().constData() << endl;
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

    /*for(int i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++ ) {
        Point center(cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][0]), cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][1])); //x y
        int radius = cvRound(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados()[i][2]);
        //cout << "Circulo num " << i << " con centro (" << center.x << ", " << center.y << " y radio " << radius << endl;
        //punto central
        circle( prueba, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( prueba, center, radius, Scalar(255,255,255), 2, 8, 0 );
    }*/

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
    this->setFixedSize(this->width(), this->height());
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
    getVentanaCrearFichero()->setWindowTitle("Crear Nuevo Fichero");
    getVentanaCrearFichero()->show();
}

void CAplicacion::slotAboutQT() {
    QMessageBox::aboutQt(this, "About QT");
}

void CAplicacion::slotSalir() {
    exit(0);
}

void CAplicacion::slotDetectarCirculos() {
    //getCirculosEliminar()->clear();
    //getCirculosAnadir().clear();

    getActionProcesarImagen()->setDisabled(true);
    cout << "Detectando imagen" << endl;
    Mat aux = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());

    Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
    //Dibujamos circulos
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(mostrarCirculosFinales(resultado)));
    getActionDetectarCirculos()->setDisabled(true);
    getActionDetectarLineas()->setDisabled(false);
}

void CAplicacion::slotDetectarLineas() {
    if(getNodoInicio()->text().isEmpty() || getNodosFinales()->text().isEmpty()) {
        QMessageBox mensaje;
        mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \nRecuerde configurar el alfabeto.");
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

        getActionDetectarLineas()->setDisabled(true);
        getActionDetectarTransiciones()->setDisabled(false);
    }
}

void CAplicacion::slotDetectarTransiciones() {
    getActionProcesarImagen()->setEnabled(true);

    Mat resultado = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

    getOperacionesImagen()->detectarTransiciones()->ejecutar(aux, getAlfabetoActual()->currentIndex());

    for (size_t i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
        cv::rectangle(resultado,                            // draw rectangle on original image
                      getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                      cv::Scalar(0, 255, 0),                        // green
                      2);
    }
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
    getActionDetectarTransiciones()->setDisabled(true);
    getActionCodificarImagen()->setEnabled(true);
}

void CAplicacion::slotCodificarImagen() {
    cout << "Se borro el fichero temporal de la ejecucion anterior" << remove(PATH_TEMPORAL);
    if(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() == 0)
        slotDetectarTransiciones();
    getOperacionesImagen()->codificarDeteccion();
    /// Abrimos asistente
    //asistente_ = new CAsistenteCodificacion(getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(), getNodoInicio()->text().toUtf8().constData(), getNodosFinales()->text().toUtf8().constData(), getOperacionesImagen()->getIniciosAsistente(), getOperacionesImagen()->getDestinosAsistente(), getOperacionesImagen()->getLetrasAsistente());

    dibujarSentidoTransiciones();
    getActionConfirmarImagen()->setEnabled(true);

    //getAsistente()->show();
    //slotCambiarPerspectiva();
    //getCheckUpdatesTimer()->start(1000);

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
        slotDetectarLineas();
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

void CAplicacion::slotCargarImagenOriginal() {
    dibujadaTransiciones_ = false;
    if(getPerspectivaActual()->text() == "Perspectiva actual: \nCorreccion") {
        slotCambiarPerspectiva();
    }
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    getActionDetectarCirculos()->setDisabled(false);
    getActionProcesarImagen()->setDisabled(false);
    getActionCodificarImagen()->setDisabled(true);
}

void CAplicacion::slotAbrirFicheroCorrecto() {
    QString line = ventanaAbrirFichero();
    if(!line.isEmpty()) {
        getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");

        getPanelComparacion()->setText(line);
    }

    //getPanelOpciones()->iniciarVistaCorreccion(0);
    //connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));
    //connect(getPanelOpciones()->getSimplificarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotSimplificarFicheroReferencia()));
    //setStyleSheet("background-color: black;");
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
        //getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(mostrarCirculosFinales(resultado)));

        //Es circulos y lineas, calculamos ambos
    } else if (getActionDetectarTransiciones()->isEnabled()) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

        //Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        aux = mostrarCirculosFinales(aux);

        //aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        //Dibujamos lineas
        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( aux, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
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
    this->setFixedSize(this->width(), this->height());
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
        filename.append(".txt");
        cout << filename.toStdString() << endl;
        ofstream fs(filename.toStdString());
        fs << getTextEditCrearFichero()->toPlainText().toStdString();
        fs.close();
    }

    setStyleSheet("background-color:  rgba(126, 156, 232, 1);");
}

void CAplicacion::slotCodificarNuevoFichero() {
    cout << "Se borro el fichero temporal de la ejecucion anterior" << remove(PATH_TEMPORAL);
    ofstream fs(PATH_TEMPORAL);
    fs << getTextEditCrearFichero()->toPlainText().toStdString();
    fs.close();
    checkFicheroTemporalCreado();
    getVentanaCrearFichero()->close();
    //cout << text.toStdString() << endl;

    /*ifstream fich(PATH_TEMPORAL, ios::in | ios::binary);

    if(fich.good()) {
        cout << "HOLA" << endl;
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
            if(getPerspectivaActual()->text() == "Deteccion")
                slotCambiarPerspectiva();*/
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

        if(getCheckEliminarAnadirLinea()->isChecked()) {
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
            //find (myvector.begin(), myvector.end(), 30);

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
                    cv::rectangle(resultado,                            // draw rectangle on original image
                                  getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                                  cv::Scalar(0, 255, 0),                        // green
                                  2);
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

                    /*inicializarVentanaAplicacionCorreccion();*
            getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 6px;");
            */
                    if(!getCargarImagenParaPanelComparacion()) {
                        getPanelPrincipal()->setText(line);
                        getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");
                        getActionAbrirFicheroCorrecto()->setDisabled(false);
                        posActualPanelOpciones_ = 1;
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
                        if(encontrado == false)
                            posActualPanelOpciones_ = 0;

                        connect(getPanelOpciones()->getCargarImagenCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirImagen()));
                        connect(getPanelOpciones()->getCargarFicheroCorregir(), SIGNAL(clicked()), this, SLOT(slotAbrirFichero()));

                        getCheckUpdatesTimer()->stop();
                    } else {
                        if(getAuxContenidoAnterior()->text() != "") {
                            cout << "Antes habia contenido en el panel principal, recuperando" << endl;
                            getPanelPrincipal()->setText(getAuxContenidoAnterior()->text());
                        }
                        getPanelComparacion()->setText(line);
                        getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 60px;");
                        posActualPanelOpciones_ = 2;
                        getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
                        connect(getPanelOpciones()->getCargarImagenReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirImagenReferencia()));
                        connect(getPanelOpciones()->getCargarFicheroReferencia(), SIGNAL(clicked()), this, SLOT(slotAbrirFicheroCorrecto()));

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
        cout << "Fichero Codificado aun no creado \n Error al leer de Fichero" << endl;
        if(fich.fail()) cout << "Bit fail activo" << endl;
        if(fich.eof())  cout << "Bit eof activo" << endl;
        if(fich.bad())  cout << "Bit bad activo" << endl;
    }
    fich.close();
}

void CAplicacion::slotRestaurarValores() {
    if(getRestaurarValores()->text() == "Cargar Fichero Correcto") {
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
    cout << "Panel Principal " << getPanelPrincipal()->text().toStdString() << endl;
    cout << "HEY " << auxContenidoAnterior_->text().toStdString() << endl;
    slotAbrirImagen();
}

void CAplicacion::slotCambiarPerspectiva() {
    if(getPerspectivaActual()->text() == "Perspectiva actual: \nDeteccion") {
        inicializarVentanaAplicacionCorreccion();
        if(getPanelPrincipal()->text() == "Introduzca aqui la imagen o fichero a corregir ") {
            cout << "HEYS" << endl;

        posActualPanelOpciones_ = 0;
        }
        cout << getPanelPrincipal()->text().toStdString() << endl;

        getPanelOpciones()->iniciarVistaCorreccion(getPosActualPanelOpciones());
        getRestaurarValores()->setText("Cargar Fichero Correcto");
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

    } else {
        inicializarVentanaAplicacionDeteccion();
        getActionCargarImagenOriginal()->setEnabled(true);
        if(getPathImagenActual() != NULL) {
            getActionDetectarCirculos()->setEnabled(true);
            getActionProcesarImagen()->setEnabled(true);
        }
        getPanelPrincipal()->clear();
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
    }
}

void CAplicacion::slotCambiarTextEliminarAnadirLinea() {
    if(getCheckEliminarAnadirLinea()->isChecked())
        getTextAnadirEliminar()->setText("Eliminar Lineas");
    else
        getTextAnadirEliminar()->setText("Añadir Lineas");
}

void CAplicacion::slotSimplificarFicheroCorregir() {

}

void CAplicacion::slotSimplificarFicheroReferencia() {

}

void CAplicacion::slotAnalizarCadena() {

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

QCheckBox* CAplicacion::getCheckEliminarAnadirLinea() {
    return checkEliminarAnadirLinea_;
}

CLabel* CAplicacion::getTextAnadirEliminar() {
    return textEliminarAnadirLinea_;
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
