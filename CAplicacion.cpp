#include "CAplicacion.h"

CAplicacion::CAplicacion() {
  QWidget* centralWidget = new QWidget();
  QMenuBar* menu  	 = new QMenuBar(centralWidget);
  QMenu* menuFile 	 = new QMenu("File");

  //elementos del menu File
  QAction* actionAbout        = new QAction(QIcon("/home/ivan/TFG/release/about.png"), tr("About"), this);
  menuFile->addAction(actionAbout);

  //añadiendo elementos
  menu->addMenu(menuFile);

  //conexiones con slots
  connect(actionAbout, SIGNAL(triggered()),this,SLOT(slotAbout()));

  setCentralWidget(centralWidget);
  setWindowTitle("TFG");
  setFixedSize(400,400);
}

CAplicacion::~CAplicacion() {}

void CAplicacion::slotAbout() {
  QMessageBox::about(this,"About","This is an about box \n shown with QAction of QMenu.");
}
