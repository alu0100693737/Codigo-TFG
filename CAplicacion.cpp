//detect numbers https://www.mkompf.com/cplus/emeocv.html


#include "CAplicacion.h"
#include "CLabel.h"

#include "opencv2/imgcodecs.hpp" //MAT OPENCV
#include "opencv2/imgproc.hpp"    //SOBEL
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
#include <iostream>
using namespace cv;
using namespace std;

CAplicacion::CAplicacion() {

    setPathImagenActual(NULL); //Path al principio = NULL

    panelPrincipal_ = new CLabel("Panel Principal", true);
    panelOpciones_ = new CLabel("Opciones", true);
    panelHistograma_ = new CLabel("Info Imagen", false);

    operacionesImagen_ = new COperacionesImagen();

    QWidget* centralWidget        = new QWidget();

    QGridLayout *layout = new QGridLayout();
    centralWidget->setLayout (layout);
    layout->addWidget (getPanelPrincipal(), 0, 0, 3, 5);
    layout->addWidget (getPanelOpciones(), 4, 0, 1, 4);
    layout->addWidget (getPanelHistograma(), 4, 4, 1, 1);

    //MENU
    menu_                   = this->menuBar();//w QMenuBar(centralWidget);
    menuArchivo_            = new QMenu("Archivo");
    menuEditar_             = new QMenu("Edicion");
    menuFiltro_             = new QMenu("Filtros");
    actionAbrirImagen_      = new QAction(QIcon("/home/ivan/Documentos/TFG/release/abrir.png"), tr("Abrir Imagen"), this);
    actionAbrirFichero_     = new QAction(QIcon("/home/ivan/Documentos/TFG/release/fichero.png"), tr("Abrir Fichero"), this);
    actionAbout_            = new QAction(QIcon("/home/ivan/Documentos/TFG/release/about.png"), tr("About"), this);
    actionSalir_            = new QAction(QIcon("/home/ivan/Documentos/TFG/release/salir.png"), tr("Salir"), this);
    actionDetectarAutomata_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/opencv.png"), tr("Detectar Automata"), this);
    actionDetectarTransiciones_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/transition.png"), tr("Detectar Transiciones"), this);
    actionCodificarImagen_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/codificar.png"), tr("Codificar Imagen"), this);
    actionCargarImagenOriginal_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/imagenOriginal.png"), tr("Cargar ultima Imagen"), this);
    actionFiltroGray_ = new QAction(QIcon(""), tr("Filtro Gray"), this);
    actionFiltroGaussiano_   = new QAction(QIcon(""), tr("Filtro Gaussiano"), this);
    actionFiltroMediana_ = new QAction(QIcon(""), tr("Filtro Mediana"), this);
    actionFiltroSobel_ = new QAction(QIcon(""), tr("Filtro Sobel"), this);
    actionFiltroLaplaciano_ = new QAction(QIcon(""), tr("Filtro Laplaciano"), this);
    actionHistograma_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/histograma.png"), tr("Histograma"), this);


    //QAction* prueba = new QAction(QIcon("/home/ivan/Documentos/TFG/release/abrir.png"), tr("Abrir Imagen"), this);
    getActionDetectarAutomata()->setDisabled(true); //Hasta que no se cargue una imagen
    getActionDetectarTransiciones()->setDisabled(true);
    getActionCodificarImagen()->setDisabled(true);
    getActionCargarImagenOriginal()->setDisabled(true);

    //Shortcuts
    getActionAbrirImagen()->setShortcuts(QKeySequence::New);
    getActionSalir()->setShortcut(QKeySequence::Close);

    getMenuArchivo()->addAction(getActionAbrirImagen());
    getMenuArchivo()->addAction(getActionAbrirFichero());
    getMenuArchivo()->addAction(getActionAbout());
    getMenuArchivo()->addAction(getActionSalir());
    getMenuEditar()->addAction(getActionDetectarAutomata());
    getMenuEditar()->addAction(getActionDetectarTransiciones());
    getMenuEditar()->addAction(getActionCodificarImagen());
    getMenuEditar()->addAction(getActionCargarImagenOriginal());
    //getMenuFiltro()->addAction(getActionFiltroGray());
    getMenuFiltro()->addAction(getActionFiltroGaussiano());
    getMenuFiltro()->addAction(getActionFiltroMediana());
    getMenuFiltro()->addAction(getActionFiltroSobel());
    getMenuFiltro()->addAction(getActionFiltroLaplaciano());
    getMenuFiltro()->addAction(getActionHistograma());

    //añadiendo elementos
    getMenuBar()->addMenu(getMenuArchivo());
    getMenuBar()->addMenu(getMenuEditar());
    getMenuBar()->addMenu(getMenuFiltro());
    getMenuBar()->adjustSize();
    getMenuBar()->setStyleSheet("background-color: white");

    setCentralWidget(centralWidget);
    setMinimumSize(700, 500);
    setWindowTitle("Automatas y Lenguajes Formales, TFG");

    //Toolbar
    toolbar_ = new QToolBar(this);
    getToolBar()->addAction(getActionAbrirImagen());
    getToolBar()->addAction(getActionDetectarAutomata());
    getToolBar()->addAction(getActionDetectarTransiciones());
    getToolBar()->addAction(getActionCodificarImagen());
    getToolBar()->addAction(getActionAbout());
    this->addToolBar(getToolBar());


    nodo_inicio = new QLineEdit;
    getNodoInicio()->setPlaceholderText("Nodo de Inicio");
    nodos_finales = new QLineEdit;
    getNodosFinales()->setPlaceholderText("Nodos Finales");
    getNodoInicio()->setFocus();

    alfabeto_ = new QComboBox;
    getAlfabetoActual()->addItem(tr("Alfabeto a, b, c"));
    getAlfabetoActual()->addItem(tr("Alfabeto Numerico"));

    // Add values in the combo box
    this->getToolBar()->addWidget(getNodoInicio());
    this->getToolBar()->addWidget(getNodosFinales());
    this->getToolBar()->addWidget(getAlfabetoActual());

    //conexiones con slots
    connect(getActionAbrirImagen(), SIGNAL(triggered()),this,SLOT(slotAbrirImagen()));
    connect(getActionAbrirFichero(), SIGNAL(triggered()),this,SLOT(slotAbrirFichero()));
    connect(getActionAbout(), SIGNAL(triggered()),this,SLOT(slotAbout()));
    connect(getActionSalir(), SIGNAL(triggered()), this, SLOT(slotSalir()));
    connect(getActionDetectarAutomata(), SIGNAL(triggered()), this, SLOT(slotDetectarAutomata()));
    connect(getActionDetectarTransiciones(), SIGNAL(triggered()), this, SLOT(slotDetectarTransiciones()));
    connect(getActionCodificarImagen(), SIGNAL(triggered()), this, SLOT(slotCodificarImagen()));
    connect(getActionCargarImagenOriginal(), SIGNAL(triggered()), this, SLOT(slotCargarImagenOriginal()));
    connect(getActionFiltroGray(), SIGNAL(triggered()), this, SLOT(slotFiltroGray()));
    connect(getActionFiltroGaussiano(), SIGNAL(triggered()), this, SLOT(slotFiltroGaussiano()));
    connect(getActionFiltroMediana(), SIGNAL(triggered()), this, SLOT(slotFiltroMediana()));
    connect(getActionFiltroSobel(), SIGNAL(triggered()), this, SLOT(slotFiltroSobel()));
    connect(getActionFiltroLaplaciano(), SIGNAL(triggered()), this, SLOT(slotFiltroLaplaciano()));
    connect(getActionHistograma(), SIGNAL(triggered()), this, SLOT(slotHistograma()));
}

CAplicacion::~CAplicacion() {}

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

CLabel* CAplicacion::getPanelOpciones() {
    return panelOpciones_;
}

CLabel* CAplicacion::getPanelHistograma() {
    return panelHistograma_;
}

QMenuBar* CAplicacion::getMenuBar() {
    return menu_;
}

QMenu* CAplicacion::getMenuArchivo() {
    return menuArchivo_;
}

QMenu* CAplicacion::getMenuEditar() {
    return menuEditar_;
}

QMenu* CAplicacion::getMenuFiltro() {
    return menuFiltro_;
}

QToolBar* CAplicacion::getToolBar() {
    return toolbar_;
}

QLineEdit* CAplicacion::getNodoInicio() {
    return nodo_inicio;
}

QLineEdit* CAplicacion::getNodosFinales() {
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

QAction* CAplicacion::getActionAbout() {
    return actionAbout_;
}

QAction* CAplicacion::getActionSalir() {
    return actionSalir_;
}

QAction* CAplicacion::getActionDetectarAutomata() {
    return actionDetectarAutomata_;
}

QAction* CAplicacion::getActionDetectarTransiciones() {
    return actionDetectarTransiciones_;
}

QAction* CAplicacion::getActionCodificarImagen() {
    return actionCodificarImagen_;
}

QAction* CAplicacion::getActionCargarImagenOriginal() {
    return actionCargarImagenOriginal_;
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

//OPERACIONES CON LA IMAGEN
COperacionesImagen* CAplicacion::getOperacionesImagen() {
    return operacionesImagen_;
}

//SLOTS
void CAplicacion::slotAbrirImagen() {
    QFileDialog dialog(this, tr("Abrir Imagen"));
    inicializarVentanaAbrirImagen(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void CAplicacion::slotAbrirFichero() {
    QFileDialog dialog(this, tr("Abrir Fichero"));
    inicializarVentanaAbrirFichero(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFileFichero(dialog.selectedFiles().first())) {}
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

void CAplicacion::inicializarVentanaAbrirFichero(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
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
    dialog.selectMimeTypeFilter("text/txt");
    if (acceptMode == QFileDialog::AcceptSave) {
        dialog.setDefaultSuffix("txt");
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
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        //Size size(800, 350);//the dst image size,e.g.100x100

        //Mat src;//src image
        //cv::resize(aux,aux,size);//resize image

        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
        //getPanelPrincipal()->setImagen(newImage);
        getPanelHistograma()->setImagen(getOperacionesImagen()->Mat2QImage(getOperacionesImagen()->calcularHistograma(getOperacionesImagen()->QImage2Mat(newImage))));
        getActionDetectarAutomata()->setDisabled(false); //Habilitamos la posibilidad de detectar automata
        getActionDetectarTransiciones()->setDisabled(false);
        getActionCargarImagenOriginal()->setDisabled(false);
        getActionCodificarImagen()->setDisabled(true);
        return true;
    }
}

bool CAplicacion::loadFileFichero(const QString &fileName) {
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
        cout << "He leido" << endl;/*
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        //Size size(800, 350);//the dst image size,e.g.100x100

        //Mat src;//src image
        //cv::resize(aux,aux,size);//resize image

        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
        //getPanelPrincipal()->setImagen(newImage);
        getPanelHistograma()->setImagen(getOperacionesImagen()->Mat2QImage(getOperacionesImagen()->calcularHistograma(getOperacionesImagen()->QImage2Mat(newImage))));
        getActionDetectarAutomata()->setDisabled(false); //Habilitamos la posibilidad de detectar automata
        getActionDetectarTransiciones()->setDisabled(false);
        getActionCargarImagenOriginal()->setDisabled(false);
        getActionCodificarImagen()->setDisabled(true);
        return true;*/
    }
}

void CAplicacion::slotAbout() {
    QMessageBox::about(this,"About","Trabajo fin de grado. Iván García Campos.");
}

void CAplicacion::slotSalir() {
    exit(0);
}

void CAplicacion::slotDetectarAutomata() {
    cout << "Detectando imagen" << endl;
    Mat aux = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());

    Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux);
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));

    Mat resultado1 = getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux);
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado1));

    getActionDetectarAutomata()->setDisabled(true);
    if(getActionDetectarTransiciones()->isEnabled() == false) {
        getActionCodificarImagen()->setEnabled(true);
    }
}

void CAplicacion::slotDetectarTransiciones() {
    // CDetectarTransiciones* prueba = new CDetectarTransiciones();
    Mat aux = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());
    getOperacionesImagen()->detectarTransiciones()->ejecutar(aux);
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(getOperacionesImagen()->detectarTransiciones()->getImagenTransicionActual()));
    getActionDetectarTransiciones()->setDisabled(true);
    if(getActionDetectarAutomata()->isEnabled() == false) {
        getActionCodificarImagen()->setEnabled(true);
    }
}

void CAplicacion::slotCodificarImagen() {
    if(getNodoInicio()->text().isEmpty() || getNodosFinales()->text().isEmpty()) {
        QMessageBox::warning(this,"Warning","Recuerde introducir el nodo inicio y los nodos finales.");
    } else {
        getOperacionesImagen()->codificarDeteccion(getNodoInicio()->text().toUtf8().constData(), getNodosFinales()->text().toUtf8().constData());

        char cadena[128];
        QString aux;
        ifstream fe("/home/ivan/Documentos/TFG/codificaciones/codificacion.txt");
        while (!fe.eof()) {
            fe.getline (cadena, 256);
            aux.append("\n");
            aux.append(cadena);
            cout << cadena;
        }
        fe.close();
        getPanelHistograma()->setText(aux);
        //getPanelHistograma()->adjustSize();

    }
}

void CAplicacion::slotCargarImagenOriginal() {
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    getActionDetectarAutomata()->setDisabled(false);
    getActionDetectarTransiciones()->setDisabled(false);
    getActionCodificarImagen()->setDisabled(true);
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


