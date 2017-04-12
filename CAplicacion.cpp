#include "CAplicacion.h"
#include "CLabel.h"

#include "opencv2/imgcodecs.hpp" //MAT OPENCV
#include "opencv2/imgproc.hpp"    //SOBEL
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
using namespace cv;

CAplicacion::CAplicacion() {

    panelPrincipal_ = new CLabel("Panel Principal", true);
    panelOpciones_ = new CLabel("Opciones", false);
    panelHistograma_ = new CLabel("Info Imagen", false);

    operacionesImagen_ = new COperacionesImagen();

    QWidget* centralWidget        = new QWidget();

    QGridLayout *layout = new QGridLayout();
    centralWidget->setLayout (layout);
    layout->addWidget (getPanelPrincipal(), 0, 0, 3, 5);
    layout->addWidget (getPanelOpciones(), 4, 0, 1, 4);
    layout->addWidget (getPanelHistograma(), 4, 4, 1, 1);

    //MENU
    QMenuBar* menu                = new QMenuBar(centralWidget);
    QMenu* menuFile               = new QMenu("File");
    QAction* actionAbrirImagen    = new QAction(QIcon("/home/ivan/TFG/release/abrir.png"), tr("Abrir Imagen"), this);
    QAction* actionAbout          = new QAction(QIcon("/home/ivan/TFG/release/about.png"), tr("About"), this);
    menuFile->addAction(actionAbrirImagen);
    menuFile->addAction(actionAbout);
    //añadiendo elementos
    menu->addMenu(menuFile);

    setCentralWidget(centralWidget);
    setMinimumSize(400, 400);
    setWindowTitle("TFG");

    //conexiones con slots
    connect(actionAbrirImagen, SIGNAL(triggered()),this,SLOT(slotAbrirImagen()));
    connect(actionAbout, SIGNAL(triggered()),this,SLOT(slotAbout()));
}

CAplicacion::~CAplicacion() {}

CLabel* CAplicacion::getPanelPrincipal() {
    return panelPrincipal_;
}

CLabel* CAplicacion::getPanelOpciones() {
    return panelOpciones_;
}

CLabel* CAplicacion::getPanelHistograma() {
    return panelHistograma_;
}

COperacionesImagen* CAplicacion::getOperacionesImagen() {
    return operacionesImagen_;
}

void CAplicacion::slotAbrirImagen() {
    QFileDialog dialog(this, tr("Open File"));
    //inicializarVentanaAbrirImagen(dialog, QFileDialog::AcceptOpen);
    //while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

/*static void CAplicacion::inicializarVentanaAbrirImagen(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
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
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

bool CAplicacion::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
*/
void CAplicacion::slotAbout() {
    QMessageBox::about(this,"About","Trabajo fin de grado. Iván García Campos.");
}
