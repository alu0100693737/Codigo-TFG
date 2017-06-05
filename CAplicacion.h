///////////////////////////////////////////////////////////////
//      CAplicacion.h - Declaración de la clase CAplicacion  //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CAPLICACION_H
#define CAPLICACION_H
#include <QtWidgets>
#include "CLabel.h"
#include "CLineEdit.h"
#include "COperacionesImagen.h"
#include "CPanelOpciones.h"

class CAplicacion: public QMainWindow {
  Q_OBJECT
private:

    QImage imagenPanelPrincipal;

    QString pathImagenActual_;

    CLabel* panelPrincipal_;
    CLabel* panelComparacion_;

    CPanelOpciones* panelOpciones_;
    CLabel* panelHistograma_;

    QGridLayout * layout_; //Layout de la aplicacion

    QMenuBar* menu_;
    QMenu* menuArchivo_;
    QMenu* menuEditar_;
    QMenu* menuCorreccion_;
    QMenu* menuFiltro_;

    QAction* actionAbrirImagen_;
    QAction* actionAbrirFichero_;
    QAction* actionAbout_;
    QAction* actionAboutQT_;
    QAction* actionSalir_;

    //Proceso paso a paso
    QAction* actionDetectarLineas_;
    QAction* actionDetectarCirculos_;
    QAction* actionDetectarTransiciones_;
    QAction* actionCodificarImagen_;
    QAction* actionProcesarImagen_; //todo de golpe
    QAction* actionCargarImagenOriginal_;

    QAction* actionAbrirFicheroCorrecto_;

    QAction* actionFiltroGray_;
    QAction* actionFiltroGaussiano_;
    QAction* actionFiltroMediana_;
    QAction* actionFiltroSobel_;
    QAction* actionFiltroLaplaciano_;
    QAction* actionHistograma_;

    QToolBar* toolbar_;

    CLineEdit* nodo_inicio;
    CLineEdit* nodos_finales;
    QComboBox* alfabeto_; //0 -> alfabeto a, b, c   1 -> Alfabeto numerico

    COperacionesImagen* operacionesImagen_;

    //Abrir Imagen
    bool loadFile(const QString &fileName); //Utilizado slot abrirImagen
    //Guarda localizacion elegida, por defecto carpeta imagenes, ordena los archivos y filtra por jpg
    void inicializarVentanaAbrirImagen(QFileDialog&, QFileDialog::AcceptMode);

    //Abrir fichero, devuelve la path
    QString ventanaAbrirFichero();

 public:
    CAplicacion();

    ~CAplicacion();

    QString getPathImagenActual();
    void setPathImagenActual(QString newPath);

    CLabel* getPanelPrincipal();
    CLabel* getPanelComparacion();

    CPanelOpciones* getPanelOpciones();
    CLabel* getPanelHistograma();

    QGridLayout* getLayout();

    QMenuBar* getMenuBar();
    QMenu* getMenuArchivo();
    QMenu* getMenuEditar();
    QMenu* getMenuCorreccion();
    QMenu* getMenuFiltro();

    QToolBar* getToolBar();
    CLineEdit* getNodoInicio();
    CLineEdit* getNodosFinales();
    QComboBox* getAlfabetoActual();

    QAction* getActionAbrirImagen();
    QAction* getActionAbrirFichero();
    QAction* getActionAbout();
    QAction* getActionAboutQT();
    QAction* getActionSalir();

    QAction* getActionDetectarLineas();
    QAction* getActionDetectarCirculos();
    QAction* getActionDetectarTransiciones();
    QAction* getActionCodificarImagen();
    QAction* getActionProcesarImagen();
    QAction* getActionCargarImagenOriginal();

    QAction* getActionAbrirFicheroCorrecto();

    QAction* getActionFiltroGray();
    QAction* getActionFiltroGaussiano();
    QAction* getActionFiltroMediana();
    QAction* getActionFiltroSobel();
    QAction* getActionFiltroLaplaciano();
    QAction* getActionHistograma();

    COperacionesImagen* getOperacionesImagen();

public slots:
    void slotAbrirImagen();
    void slotAbrirFichero();
    void slotAbout();
    void slotAboutQT();
    void slotSalir();

    void slotDetectarLineas();
    void slotDetectarCirculos();
    void slotDetectarTransiciones();
    void slotCodificarImagen();
    void slotProcesarImagen();
    void slotCargarImagenOriginal();

    void slotAbrirFicheroCorrecto();

    void slotFiltroGray();
    void slotFiltroGaussiano();
    void slotFiltroMediana();
    void slotFiltroSobel();
    void slotFiltroLaplaciano();
    void slotHistograma();

    //QScrollbars
    void slotCirculosCannyAccumulatorHoughLinesP();
   //void slotHoughLinesP();
};
#endif
