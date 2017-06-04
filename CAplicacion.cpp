//detect numbers https://www.mkompf.com/cplus/emeocv.html
#include "CAplicacion.h"

#include "opencv2/imgcodecs.hpp" //MAT OPENCV
#include "opencv2/imgproc.hpp"    //SOBEL
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
#include <iostream>
using namespace cv;
using namespace std;

CAplicacion::CAplicacion() {

    setPathImagenActual(NULL); //Path al principio = NULL
    setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    panelPrincipal_ = new CLabel("Panel Principal", true);

    Mat aux = imread("/home/ivan/Documentos/Codigo-TFG/images/cartel.png", IMREAD_UNCHANGED);
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

    panelOpciones_ = new CPanelOpciones();
    panelHistograma_ = new CLabel("Info Imagen", false);
    //verde
    getPanelOpciones()->setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black");
    getPanelHistograma()->setStyleSheet("background-color: white; border: 1px solid black");

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
    actionAbrirImagen_      = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/abrir.png"), tr("Abrir Imagen"), this);
    actionAbrirFichero_     = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/fichero.png"), tr("Abrir Fichero"), this);
    actionAbout_            = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/about.png"), tr("About"), this);
    actionSalir_            = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/salir.png"), tr("Salir"), this);
    actionDetectarLineas_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/linea.png"), tr("Detectar Lineas"), this);
    actionDetectarCirculos_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/circulo.png"), tr("Detectar Circulos"), this);
    actionDetectarTransiciones_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/transition.png"), tr("Detectar Transiciones"), this);
    actionCodificarImagen_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/codificar.png"), tr("Codificar Imagen"), this);
    actionProcesarImagen_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/opencv.png"), tr("Procesar Imagen"), this);
    actionCargarImagenOriginal_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/imagenOriginal.png"), tr("Cargar ultima Imagen"), this);
    actionFiltroGray_ = new QAction(QIcon(""), tr("Filtro Gray"), this);
    actionFiltroGaussiano_   = new QAction(QIcon(""), tr("Filtro Gaussiano"), this);
    actionFiltroMediana_ = new QAction(QIcon(""), tr("Filtro Mediana"), this);
    actionFiltroSobel_ = new QAction(QIcon(""), tr("Filtro Sobel"), this);
    actionFiltroLaplaciano_ = new QAction(QIcon(""), tr("Filtro Laplaciano"), this);
    actionHistograma_ = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/histograma.png"), tr("Histograma"), this);


    //QAction* prueba = new QAction(QIcon("/home/ivan/Documentos/Codigo-TFG/release/abrir.png"), tr("Abrir Imagen"), this);
    getActionDetectarLineas()->setDisabled(true); //Hasta que no se cargue una imagen
    getActionDetectarCirculos()->setDisabled(true);
    getActionDetectarTransiciones()->setDisabled(true);
    getActionCodificarImagen()->setDisabled(true);
    getActionProcesarImagen()->setDisabled(true);
    getActionCargarImagenOriginal()->setDisabled(true);

    //Shortcuts
    getActionAbrirImagen()->setShortcuts(QKeySequence::New);
    getActionSalir()->setShortcut(QKeySequence::Close);

    getMenuArchivo()->addAction(getActionAbrirImagen());
    getMenuArchivo()->addAction(getActionAbrirFichero());
    getMenuArchivo()->addAction(getActionAbout());
    getMenuArchivo()->addAction(getActionSalir());
    getMenuEditar()->addAction(getActionDetectarCirculos());
    getMenuEditar()->addAction(getActionDetectarLineas());
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
    setMinimumSize(900, 700);
    setWindowTitle("Automatas y Lenguajes Formales, TFG");

    //Toolbar
    toolbar_ = new QToolBar(this);
    getToolBar()->addAction(getActionAbrirImagen());
    getToolBar()->addAction(getActionDetectarCirculos());
    getToolBar()->addAction(getActionDetectarLineas());
    getToolBar()->addAction(getActionDetectarTransiciones());
    getToolBar()->addAction(getActionCodificarImagen());
    getToolBar()->addAction(getActionProcesarImagen());
    getToolBar()->addAction(getActionProcesarImagen());
    getToolBar()->addAction(getActionAbout());
    getToolBar()->setStyleSheet("background-color: white;");
    this->addToolBar(getToolBar());


    nodo_inicio = new CLineEdit;
    getNodoInicio()->setPlaceholderText("Nodo de Inicio");
    nodos_finales = new CLineEdit;
    getNodosFinales()->setPlaceholderText("Nodos Finales, Formato: 0 1 2 ...");
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
    connect(getActionDetectarCirculos(), SIGNAL(triggered()), this, SLOT(slotDetectarCirculos()));
    connect(getActionDetectarLineas(), SIGNAL(triggered()), this, SLOT(slotDetectarLineas()));
    connect(getActionDetectarTransiciones(), SIGNAL(triggered()), this, SLOT(slotDetectarTransiciones()));
    connect(getActionCodificarImagen(), SIGNAL(triggered()), this, SLOT(slotCodificarImagen()));
    connect(getActionProcesarImagen(), SIGNAL(triggered()), this, SLOT(slotProcesarImagen()));
    connect(getActionCargarImagenOriginal(), SIGNAL(triggered()), this, SLOT(slotCargarImagenOriginal()));
    connect(getActionFiltroGray(), SIGNAL(triggered()), this, SLOT(slotFiltroGray()));
    connect(getActionFiltroGaussiano(), SIGNAL(triggered()), this, SLOT(slotFiltroGaussiano()));
    connect(getActionFiltroMediana(), SIGNAL(triggered()), this, SLOT(slotFiltroMediana()));
    connect(getActionFiltroSobel(), SIGNAL(triggered()), this, SLOT(slotFiltroSobel()));
    connect(getActionFiltroLaplaciano(), SIGNAL(triggered()), this, SLOT(slotFiltroLaplaciano()));
    connect(getActionHistograma(), SIGNAL(triggered()), this, SLOT(slotHistograma()));

    connect(getPanelOpciones()->getCannyThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
    connect(getPanelOpciones()->getAccumulatorThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
    connect(getPanelOpciones()->getHoughLinesP(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
}

CAplicacion::~CAplicacion() {}

//SLOTS
void CAplicacion::slotAbrirImagen() {
    QFileDialog dialog(this, tr("Abrir Imagen"));
    dialog.setStyleSheet("background-color: white;");
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
        //si leemos un jpg, lo convertimos a png guardamos y la cargamos, no borramos la jpg
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
        //Size size(800, 350);//the dst image size,e.g.100x100

        //Mat src;//src image
        //cv::resize(aux,aux,size);//resize image

        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
        //getPanelPrincipal()->setImagen(newImage);
        getPanelHistograma()->setImagen(getOperacionesImagen()->Mat2QImage(getOperacionesImagen()->calcularHistograma(getOperacionesImagen()->QImage2Mat(newImage))));

        getActionDetectarCirculos()->setDisabled(false);
        getActionProcesarImagen()->setDisabled(false);
        /*getActionDetectarAutomata()->setDisabled(false); //Habilitamos la posibilidad de detectar automata
        getActionDetectarTransiciones()->setDisabled(false);
        */
        getActionCargarImagenOriginal()->setDisabled(false);
        /*        getActionCodificarImagen()->setDisabled(true);*/
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
    QMessageBox mensaje;
    mensaje.setText("Trabajo fin de grado. Iván García Campos.");
    mensaje.setIcon(QMessageBox::Information);
    mensaje.exec();
}

void CAplicacion::slotSalir() {
    exit(0);
}

void CAplicacion::slotDetectarCirculos() {
    getActionProcesarImagen()->setDisabled(true);
    cout << "Detectando imagen" << endl;
    Mat aux = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());

    Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
    getActionDetectarCirculos()->setDisabled(true);
    getActionDetectarLineas()->setDisabled(false);
}

void CAplicacion::slotDetectarLineas() {
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

void CAplicacion::slotDetectarTransiciones() {

    getActionProcesarImagen()->setEnabled(true);
    // CDetectarTransiciones* prueba = new CDetectarTransiciones();
    Mat resultado = getOperacionesImagen()->QImage2Mat(getPanelPrincipal()->getImagen());
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

    getOperacionesImagen()->detectarTransiciones()->ejecutar(aux);

    for (int i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
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
    if(getNodoInicio()->text().isEmpty() || getNodosFinales()->text().isEmpty()) {
        QMessageBox mensaje;
        mensaje.setText("Recuerde introducir el nodo inicio y los nodos finales. \nRecuerde configurar el alfabeto.");
        mensaje.setIcon(QMessageBox::Warning);
        mensaje.exec();
    } else {
        if(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() == 0)
                slotDetectarTransiciones();
        getOperacionesImagen()->codificarDeteccion(getNodoInicio()->text().toUtf8().constData(), getNodosFinales()->text().toUtf8().constData());
    }
    //Mat aux3 = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    //imshow("", aux3);
    //waitKey(0);
    /*
     *         char cadena[128];
        QString aux;
        ifstream fe("/home/ivan/Documentos/Codigo-TFG/codificaciones/codificacion.txt");
        while (!fe.eof()) {
            fe.getline (cadena, 256);
            aux.append("\n");
            aux.append(cadena);
            cout << cadena;
        }
        fe.close();

        getPanelHistograma()->setText(aux);*/
}

void CAplicacion::slotProcesarImagen() {
    slotCargarImagenOriginal(); //evitar doble lectura cuando los campos nodos no estan rellenos
    slotDetectarCirculos();
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

void CAplicacion::slotCargarImagenOriginal() {
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    getActionDetectarCirculos()->setDisabled(false);
    getActionProcesarImagen()->setDisabled(false);
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

void CAplicacion::slotCirculosCannyAccumulatorHoughLinesP() {
    getPanelOpciones()->getValorCannyThresHold()->setText(QString::number(getPanelOpciones()->getCannyThresHold()->value()));
    getPanelOpciones()->getValorAccumulatorThresHold()->setText(QString::number(getPanelOpciones()->getAccumulatorThresHold()->value()));
    getPanelOpciones()->getValorHoughLinesP()->setText(QString::number(getPanelOpciones()->getHoughLinesP()->value()));

    //Ya hemos detectado circulos, será cambiarlos segun las variables
    if(getActionDetectarLineas()->isEnabled()) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));

        //Es circulos y lineas, calculamos ambos
    } else if (getActionDetectarTransiciones()->isEnabled()) {
        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
        //Tenemos circulos, lineas y transiciones
    } else if (getActionCodificarImagen()->isEnabled()) {

        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());

        aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));

        aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarTransiciones()->ejecutar(aux);

        for (int i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
            cv::rectangle(resultado,                            // draw rectangle on original image
                          getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                          cv::Scalar(0, 255, 0),                        // green
                          2);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
    } else {  //No deberia ocurrir nada
        cout << "No debe ocurrir " << endl;
    }
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

CPanelOpciones* CAplicacion::getPanelOpciones() {
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

QAction* CAplicacion::getActionAbout() {
    return actionAbout_;
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

QAction* CAplicacion::getActionProcesarImagen() {
    return actionProcesarImagen_;
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
