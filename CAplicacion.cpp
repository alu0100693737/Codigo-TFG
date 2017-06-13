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
    setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    /// Creamos los Paneles de la Aplicacion y su disposicion
    panelPrincipal_ = new CLabel("Panel Principal", true);

    Mat aux = imread("/home/ivan/Documentos/Codigo-TFG/images/cartel.png", IMREAD_UNCHANGED);
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

    panelOpciones_ = new CPanelOpciones();
    panelHistograma_ = new CLabel("Info Imagen", false);

    panelComparacion_ = new CLabel("Panel Comparativa", true);

    getPanelHistograma()->setStyleSheet("background-color: white; border: 1px solid black");

    operacionesImagen_ = new COperacionesImagen();

    QWidget* centralWidget        = new QWidget();
    layout_ = new QGridLayout();

    perspectivaActual_ = new CLabel("Deteccion", true);
    cambiarPerspectiva_ = new CPushButton("Cambiar Perspectiva", false);
    restaurarValores_ = new CPushButton("Restaurar ScrollBar's", false);

    centralWidget->setLayout (getLayout());
    inicializarVentanaAplicacionDeteccion();

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

    setCentralWidget(centralWidget);
    setMinimumSize(900, 700);
    setWindowTitle("Automatas y Lenguajes Formales, TFG");

    ///Añadimos Toolbar
    toolbar_ = new QToolBar(this);
    getToolBar()->addAction(getActionAbrirImagen());
    getToolBar()->addAction(getActionAbrirFichero());
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

    checkEliminarAnadirLinea_ = new QCheckBox();
    getCheckEliminarAnadirLinea()->click();
    textEliminarAnadirLinea_ = new CLabel("Eliminar Lineas", true);
    lineaAceptada_ = false;

    // Add values in the combo box
    this->getToolBar()->addWidget(getNodoInicio());
    this->getToolBar()->addWidget(getNodosFinales());
    this->getToolBar()->addWidget(getAlfabetoActual());
    this->getToolBar()->addWidget(getTextAnadirEliminar());
    this->getToolBar()->addWidget(getCheckEliminarAnadirLinea());

    checkUpdatesTimer_ = new QTimer(this); //timer para asistente codificacion

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
}

CAplicacion::~CAplicacion() {}

void CAplicacion::inicializarVentanaAplicacionDeteccion() {
    setStyleSheet("background-color: black");

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
        Mat aux = imread("/home/ivan/Documentos/Codigo-TFG/images/cartel.png", IMREAD_UNCHANGED);
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));
    }
    QVBoxLayout* layout1 = new QVBoxLayout();
    layout1->addWidget(getPerspectivaActual());
    layout1->addWidget(getCambiarPerspectiva());
    layout1->setSpacing(10);
    layout1->addWidget(getRestaurarValores());/* layout1->addWidget(getGuardarComoFichero()); layout1->addWidget(getCorregirAutomata());
    layout1->addWidget(getHelp());*/

    layout1->setSpacing(10);
    getLayout()->addLayout(layout1, 4, 3, 1, 1);
    //getLayout()->addWidget (getPanelHistograma(), 4, 4, 1, 1);
}

void CAplicacion::inicializarVentanaAplicacionCorreccion() {

    getPanelPrincipal()->clear();

    getLayout()->addWidget(getPanelComparacion(), 0, 2, 3, 2);
    getLayout()->addWidget (getPanelPrincipal(), 0, 0, 3, 2);

    setStyleSheet("background-color: black");
}

//SLOTS
void CAplicacion::slotAbrirImagen() {
    if(getPerspectivaActual()->text() == "Correccion")
        slotCambiarPerspectiva();
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

    //inicializarVentanaAplicacionCorreccion();
    if(getPerspectivaActual()->text() == "Deteccion")
        slotCambiarPerspectiva();
    getPanelPrincipal()->setText(line);
    getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 6px;");
    getActionAbrirFicheroCorrecto()->setDisabled(false);
    setStyleSheet("background-color: black");
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

        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(aux));

        //si se desea poner el histograma en panel Histograma
        //getPanelHistograma()->setImagen(getOperacionesImagen()->Mat2QImage(getOperacionesImagen()->calcularHistograma(getOperacionesImagen()->QImage2Mat(newImage))));

        getActionDetectarCirculos()->setDisabled(false);
        getActionProcesarImagen()->setDisabled(false);

        getActionCargarImagenOriginal()->setDisabled(false);
        getActionFiltroGaussiano()->setDisabled(false);
        getActionFiltroGray()->setDisabled(false);
        getActionFiltroLaplaciano()->setDisabled(false);
        getActionFiltroMediana()->setDisabled(false);
        getActionFiltroSobel()->setDisabled(false);
        getActionHistograma()->setDisabled(false);
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
        return QString();
    }

    QTextStream in(&file1);
    QString line;
    while(!in.atEnd()){
        line += in.readLine();
        line += "\n";
    }
    return line;
}

void CAplicacion::slotAbout() {
    QMessageBox mensaje;
    mensaje.setText("Trabajo fin de grado. Iván García Campos.");
    mensaje.setIcon(QMessageBox::Information);
    mensaje.exec();
}

void CAplicacion::slotCrearNuevoFichero() {
    ventanaCrearFichero_ = new QWidget(); QGridLayout* layout = new QGridLayout();

    textEditCrearFichero_ = new QTextEdit();
    getTextEditCrearFichero()->setPlaceholderText("6 \n 5 \n 0 2 0 b 2 a 4\n 1 5 1 a 3 5 b ");
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
    setStyleSheet("background-color:white");
    QMessageBox::aboutQt(this, "About QT");
    setStyleSheet("background-color:black");
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
        cout << "Se borro el fichero temporal de la ejecucion anterior" << remove(PATH_TEMPORAL);
        if(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() == 0)
            slotDetectarTransiciones();
        getOperacionesImagen()->codificarDeteccion(getNodoInicio()->text().toUtf8().constData(), getNodosFinales()->text().toUtf8().constData());
        //slotCambiarPerspectiva();
        getCheckUpdatesTimer()->start(1000);
    }
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

void CAplicacion::slotAbrirFicheroCorrecto() {
    QString line = ventanaAbrirFichero();

    getPanelComparacion()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 6px;");
    getPanelComparacion()->setText(line);
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

        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
        resultado = mostrarCirculosFinales(resultado);

        aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        //Dibujamos lineas
        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
        //Tenemos circulos, lineas y transiciones
    } else if (getActionCodificarImagen()->isEnabled()) {

        Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());

        //Dibujamos circulos
        resultado = mostrarCirculosFinales(resultado);

        aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

        //Dibujamos lineas
        for( size_t i = 0; i <  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++ ) {
            Vec4i l =  getOperacionesImagen()->detectarLineas()->getLineasDetectadas().at(i);
            line( resultado, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        }

        aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
        getOperacionesImagen()->detectarTransiciones()->ejecutar(aux);

        //Dibujar Transiciones
        for (int i = 0; i < getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size(); i++) {
            cv::rectangle(resultado,                            // draw rectangle on original image
                          getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno,        // rect to draw
                          cv::Scalar(0, 255, 0),                        // green
                          2);
        }
        getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
    } else {
        cout << "Error!, Debe cargar una imagen previamente " << endl;
    }
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
    setStyleSheet("background-color: black;");
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

void CAplicacion::slotPanelPrincipal(QMouseEvent* evt) {

    if(getActionDetectarLineas()->isEnabled()) { // ya se han detectado circulos
        unsigned x( evt -> x() ), y( evt -> y() );
        bool borrado = false;
        //Comprobamos sobre los nodos principales
        for(int i = 0; i < getOperacionesImagen()->detectarCirculos()->getCirculosDetectados().size(); i++) {
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

            for(int i = 0; i < getOperacionesImagen()->detectarLineas()->getLineasDetectadas().size(); i++) {
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
                Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );

                Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());
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
    } else if (getActionCodificarImagen()->isEnabled()) {
        if(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() > 0) {
            cout << "contornos antes " << getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() << endl;
            getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().erase(getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().begin());
            cout << "contornos despues " << getOperacionesImagen()->detectarTransiciones()->getContornosEncontrados().size() << endl;
            cout << "Trabajando con las transiciones " << endl;

            Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            Mat resultado = getOperacionesImagen()->detectarCirculos()->iniciarDeteccion(aux, getPanelOpciones()->getCannyThresHold()->value(), getPanelOpciones()->getAccumulatorThresHold()->value());

            //Dibujamos circulos
            resultado = mostrarCirculosFinales(resultado);

            aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
            getOperacionesImagen()->detectarLineas()->iniciarDeteccion(aux, getPanelOpciones()->getHoughLinesP()->value());

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
        }
    }
}

void CAplicacion::checkFicheroTemporalCreado() {
    ifstream fich(PATH_TEMPORAL, ios::in | ios::binary);
    //fich.read(mes, 20);
    if(fich.good()) {
        if(!fich.peek() == std::ifstream::traits_type::eof() ) { // si el fichero no esta vacio
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
                    slotCambiarPerspectiva();
                /*inicializarVentanaAplicacionCorreccion();*
            getPanelPrincipal()->setStyleSheet("background-color: beige; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 14px; padding: 6px;");
            */getPanelPrincipal()->setText(line);
                getCheckUpdatesTimer()->stop();
            }
        } else  //si fichero vacio ->opcion cancelar del asistente
            getCheckUpdatesTimer()->stop();
    } else {
        cout << "Fichero Codificado aun no creado \n Error al leer de Fichero" << endl;
        if(fich.fail()) cout << "Bit fail activo" << endl;
        //if(fich.eof())  cout << "Bit eof activo" << endl;
        //if(fich.bad())  cout << "Bit bad activo" << endl;
    }
    fich.close();
}

void CAplicacion::slotRestaurarValores() {
    if(getRestaurarValores()->text() == "Cargar Fichero Correcto") {
        slotAbrirFicheroCorrecto();
        setStyleSheet("background-color: black");
    } else {
        getPanelOpciones()->getCannyThresHold()->setValue(CANNYTHRESHOLD);
        getPanelOpciones()->getAccumulatorThresHold()->setValue(ACCUMULATORTHRESHOLD);
        getPanelOpciones()->getHoughLinesP()->setValue(HOUGHLINESP);
    }
}

void CAplicacion::slotCambiarPerspectiva() {
    if(getPerspectivaActual()->text() == "Deteccion") {
        inicializarVentanaAplicacionCorreccion();
        getPanelOpciones()->iniciarVistaCorreccion();
        getRestaurarValores()->setText("Cargar Fichero Correcto");
        getPerspectivaActual()->setText("Correccion");
        getActionDetectarLineas()->setEnabled(false);
        getActionDetectarCirculos()->setEnabled(false);
        getActionDetectarTransiciones()->setEnabled(false);
    } else {
        inicializarVentanaAplicacionDeteccion();
        if(getPathImagenActual() != NULL) {
            getActionDetectarCirculos()->setEnabled(true);
            getActionProcesarImagen()->setEnabled(true);
        }
        getPanelOpciones()->iniciarVistaDeteccion();
        getRestaurarValores()->setText("Restaurar ScrollBar's");
        getPerspectivaActual()->setText("Deteccion");
        //connect(getCheckUpdatesTimer(), SIGNAL(timeout()), this, SLOT(checkFicheroTemporalCreado()));
        connect(getPanelOpciones()->getCannyThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
        connect(getPanelOpciones()->getAccumulatorThresHold(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
        connect(getPanelOpciones()->getHoughLinesP(), SIGNAL(valueChanged(int)), this, SLOT(slotCirculosCannyAccumulatorHoughLinesP()));
    }
}

void CAplicacion::slotCambiarTextEliminarAnadirLinea() {
    if(getCheckEliminarAnadirLinea()->isChecked())
        getTextAnadirEliminar()->setText("Eliminar Lineas");
    else
        getTextAnadirEliminar()->setText("Añadir Lineas");
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

QCheckBox* CAplicacion::getCheckEliminarAnadirLinea() {
    return checkEliminarAnadirLinea_;
}

CLabel* CAplicacion::getTextAnadirEliminar() {
    return textEliminarAnadirLinea_;
}

bool CAplicacion::getLineaAceptada() {
    return lineaAceptada_;
}

Point* CAplicacion::getPuntoInicioNuevaLinea() {
    return puntoInicioNuevaLinea_;
}
