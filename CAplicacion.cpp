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

    panelPrincipal_ = new CLabel("Panel Principal");
    panelOpciones_ = new CLabel("Opciones");
    panelHistograma_ = new CLabel("Info Imagen");

    operacionesImagen_ = new COperacionesImagen();

    QWidget* centralWidget        = new QWidget();

    QGridLayout *layout = new QGridLayout();
    centralWidget->setLayout (layout);
    layout->addWidget (getPanelPrincipal(), 0, 0, 3, 5);
    layout->addWidget (getPanelOpciones(), 4, 0, 1, 4);
    layout->addWidget (getPanelHistograma(), 4, 4, 1, 1);

    //MENU
    menu_                   = new QMenuBar(centralWidget);
    menuArchivo_            = new QMenu("Archivo");
    menuEditar_             = new QMenu("Edicion");
    actionAbrirImagen_      = new QAction(QIcon("/home/ivan/Documentos/TFG/release/abrir.png"), tr("Abrir Imagen"), this);
    actionAbout_            = new QAction(QIcon("/home/ivan/Documentos/TFG/release/about.png"), tr("About"), this);
    actionSalir_            = new QAction(QIcon("/home/ivan/Documentos/TFG/release/salir.png"), tr("Salir"), this);
    actionDetectarAutomata_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/opencv.png"), tr("Detectar Automata"), this);
    actionDetectarTransiciones_ = new QAction(QIcon("/home/ivan/Documentos/TFG/release/transition.png"), tr("Detectar Transiciones"), this);
    getActionDetectarAutomata()->setDisabled(true); //Hasta que no se cargue una imagen
    getActionDetectarTransiciones()->setDisabled(true);

    getMenuArchivo()->addAction(getActionAbrirImagen());
    getMenuArchivo()->addAction(getActionAbout());
    getMenuArchivo()->addAction(getActionSalir());
    getMenuEditar()->addAction(getActionDetectarAutomata());
    getMenuEditar()->addAction(getActionDetectarTransiciones());
    //añadiendo elementos
    getMenuBar()->addMenu(getMenuArchivo());
    getMenuBar()->addMenu(getMenuEditar());
    getMenuBar()->adjustSize();
    getMenuBar()->setStyleSheet("background-color: white");
    setCentralWidget(centralWidget);
    setMinimumSize(700, 400);
    setWindowTitle("TFG");

    //conexiones con slots
    connect(getActionAbrirImagen(), SIGNAL(triggered()),this,SLOT(slotAbrirImagen()));
    connect(getActionAbout(), SIGNAL(triggered()),this,SLOT(slotAbout()));
    connect(getActionSalir(), SIGNAL(triggered()), this, SLOT(slotSalir()));
    connect(getActionDetectarAutomata(), SIGNAL(triggered()), this, SLOT(slotDetectarAutomata()));
    connect(getActionDetectarTransiciones(), SIGNAL(triggered()), this, SLOT(slotDetectarTransiciones()));
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

QAction* CAplicacion::getActionAbrirImagen() {
    return actionAbrirImagen_;
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

//OPERACIONES CON LA IMAGEN
COperacionesImagen* CAplicacion::getOperacionesImagen() {
    return operacionesImagen_;
}

//SLOTS
void CAplicacion::slotAbrirImagen() {
    QFileDialog dialog(this, tr("Open File"));
    inicializarVentanaAbrirImagen(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
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
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave) {
        dialog.setDefaultSuffix("jpg");
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
        getPanelPrincipal()->setImagen(newImage);
        getPanelHistograma()->setImagen(getOperacionesImagen()->Mat2QImage(getOperacionesImagen()->calcularHistograma(getOperacionesImagen()->QImage2Mat(newImage))));
        getActionDetectarAutomata()->setDisabled(false); //Habilitamos la posibilidad de detectar automata
        getActionDetectarTransiciones()->setDisabled(false);
        return true;
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
    Mat aux = imread(getPathImagenActual().toUtf8().constData(), IMREAD_COLOR );
    Mat resultado = getOperacionesImagen()->detectarAutomata()->iniciarDeteccion(aux);
    getPanelPrincipal()->setImagen(getOperacionesImagen()->Mat2QImage(resultado));
}

void CAplicacion::slotDetectarTransiciones() {
  //
   // CDetectarTransiciones* prueba = new CDetectarTransiciones();
      getOperacionesImagen()->detectarTransiciones()->ejecutar();

}
