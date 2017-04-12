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

    QWidget* centralWidget        = new QWidget();

    QGridLayout *layout = new QGridLayout();
    centralWidget->setLayout (layout);
    layout->addWidget (getPanelPrincipal(), 0, 0, 3, 5);
    layout->addWidget (getPanelOpciones(), 4, 0, 1, 4);
    layout->addWidget (getPanelHistograma(), 4, 4, 1, 1);

    //MENU
    QMenuBar* menu                = new QMenuBar(centralWidget);
    QMenu* menuFile               = new QMenu("File");
    QAction* actionAbout          = new QAction(QIcon("/home/ivan/TFG/release/about.png"), tr("About"), this);
    menuFile->addAction(actionAbout);
    //añadiendo elementos
    menu->addMenu(menuFile);

    setCentralWidget(centralWidget);
    setMinimumSize(400, 400);
    setWindowTitle("TFG");

    //conexiones con slots
    connect(actionAbout, SIGNAL(triggered()),this,SLOT(slotAbout()));

    prueba();
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

void CAplicacion::prueba() {
    Mat img = imread("/home/ivan/Documentos/TFG/grafo.jpg", IMREAD_COLOR);
    namedWindow("Foto original", WINDOW_AUTOSIZE);
    imshow("Foto original", img);
    waitKey(0);
    Mat dst;
    Sobel(img, dst, -1, 1, 1 );
    namedWindow("Foto cambio", WINDOW_AUTOSIZE);
    imshow("Foto cambiol", dst);
}

void CAplicacion::slotAbout() {
    QMessageBox::about(this,"About","Trabajo fin de grado. Iván García Campos.");
}
