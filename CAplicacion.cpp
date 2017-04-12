#include "CAplicacion.h"
#include "CWidgetOpciones.h"
#include "CLabel.h"
CAplicacion::CAplicacion() {

  QWidget* centralWidget = new QWidget();
  CWidgetOpciones* Widget1 = new CWidgetOpciones();
  CWidgetOpciones* Widget2 = new CWidgetOpciones();

  /*QLabel *label1 = new QLabel(Widget1);
  label1->setText("first line\nsecond line");
  QLabel *label2 = new QLabel(Widget1);
  label2->setText("third line\nforth line");*/


  QGridLayout *layout = new QGridLayout();
  centralWidget->setLayout (layout);

  layout->addWidget (new CLabel(), 0, 0, -1, 1);
  //layout->addWidget (new QLabel("HOLA"), 1, 0, 2, 2);
  layout->addWidget (new CLabel("Pepe"), 1, 2, 2, 2);
  //QGridLayout *layout = new QGridLayout();
  //layout->addWidget(Widget1);
  //layout->addWidget(Widget1, 0, 1);

  //layout->addWidget(Widget2, 1, 0);
  //MENU
  //elementos del menu File

  setCentralWidget(centralWidget);

  setWindowTitle("TFG");
  setFixedSize(400,400);
}

CAplicacion::~CAplicacion() {}

void CAplicacion::slotAbout() {
  QMessageBox::about(this,"About","Trabajo fin de grado. Iván García Campos.");
}


/*MEnu
 * QMenuBar* menu  	 = new QMenuBar(centralWidget);
  QMenu* menuFile 	 = new QMenu("File");
  QAction* actionAbout        = new QAction(QIcon("/home/ivan/TFG/release/about.png"), tr("About"), this);
  menuFile->addAction(actionAbout);
  //añadiendo elementos
  menu->addMenu(menuFile);
  //conexiones con slots
  connect(actionAbout, SIGNAL(triggered()),this,SLOT(slotAbout()));*/
