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
#include <stdio.h>  // remove file path temporal
#include "CLabel.h"
#include "CLineEdit.h"
#include "COperacionesImagen.h"
#include "CPanelOpciones.h"
#define PATH_TEMPORAL "/home/ivan/Documentos/Codigo-TFG/codificaciones/temporal.txt"
/**
 * @brief
 * Clase Aplicacion con ventana principal de la aplicacion
 * Consta de 3 Paneles. Principal, Opciones e Histograma
 * Si se utiliza la funcionalidad Codificar, ese panel cambia de forma
 * TERMINAR
 */
class CAplicacion: public QMainWindow {
    Q_OBJECT
private:

    /// Imagen actual del panel principal
    QImage imagenPanelPrincipal;
    /// Ruta de la imagen actual del panel principal
    QString pathImagenActual_;

    /// Panel Principal de la Aplicacion
    CLabel* panelPrincipal_;
    /// Panel secundario utilizado para introducir un fichero en la etapa de correccion de automatas
    CLabel* panelComparacion_;
    /// Panel Opciones de la Aplicacion
    CPanelOpciones* panelOpciones_;
    /// Panel Informacion de la Aplicacion
    CLabel* panelHistograma_;
    /// Layout de la aplicacion, formato GridLayout
    QGridLayout * layout_;

    /// Menu de la aplicacion, contiene Archivo, Editar, Correccion y Filtros
    QMenuBar* menu_;
    /// Submenu Archivo de la Aplicacion
    QMenu* menuArchivo_;
    /// Submenu Editar de la Aplicacion
    QMenu* menuEditar_;
    /// Submenu Correcion de la Aplicacion
    QMenu* menuCorreccion_;
    /// Submenu Filtro de la Aplicacion
    QMenu* menuFiltro_;

    /// Accion Abrir Imagen del Submenu Archivo
    QAction* actionAbrirImagen_;
    /// Accion Abrir Fichero del Submenu Archivo
    QAction* actionAbrirFichero_;
    /// Accion Nuevo Fichero del Submenu Archivo
    QAction* actionCrearNuevoFichero_;
    /// Accion About del Submenu Archivo
    QAction* actionAbout_;
    /// Accion About Qt del Submenu Archivo
    QAction* actionAboutQT_;
    /// Accion Salir del Submenu Archivo
    QAction* actionSalir_;

    /// Accion Detectar Lineas del Submenu Editar
    QAction* actionDetectarLineas_;
    /// Accion Detectar Circulos del Submenu Editar
    QAction* actionDetectarCirculos_;
    /// Accion Detectar Transiciones del Submenu Editar
    QAction* actionDetectarTransiciones_;
    /// Accion Codificar Imagen del Submenu Editar
    QAction* actionCodificarImagen_;
    /// Accion Procesar Imagen del Submenu Editar. ProcesarImagen = DetectarLineas() + DetectarCirculos() + DetectarTransiciones() + CodificarImagen()
    QAction* actionProcesarImagen_;
    /// Accion Cargar Imagen imagenPanelPrincipal_ . Submenu Editar
    QAction* actionCargarImagenOriginal_;

    /// Accion Abrir Fichero Correcto. Submenu Correccion
    QAction* actionAbrirFicheroCorrecto_;

    /// Accion Filtro Gray. Submenu Filtro
    QAction* actionFiltroGray_;
    /// Accion Filtro Gaussiano. Submenu Filtro
    QAction* actionFiltroGaussiano_;
    /// Accion Filtro Mediana. Submenu Filtro
    QAction* actionFiltroMediana_;
    /// Accion Filtro Sobel. Submenu Filtro
    QAction* actionFiltroSobel_;
    /// Accion Filtro Laplaciano. Submenu Filtro
    QAction* actionFiltroLaplaciano_;
    /// Accion Filtro Histograma. Submenu Filtro
    QAction* actionHistograma_;

    /// Toolbal de la aplicacion. Opciones de Deteccion de la imagen
    QToolBar* toolbar_;

    /// QLineEdit para introducir el nodo de inicio del automata
    CLineEdit* nodo_inicio;
    /// QLineEdit para introducir los nodos finales del automata
    CLineEdit* nodos_finales;
    /// QComboBox para definir el alfabeto. 0 -> alfabeto a, b, c   1 -> Alfabeto numerico
    QComboBox* alfabeto_;

    /// Clase para aplicar operaciones sobre la Imagen. Deteccion, filtros y Asistente
    COperacionesImagen* operacionesImagen_;

    QTextEdit* textEditCrearFichero_;
    QTimer* checkUpdatesTimer_;

    /**
     * @brief
     * Metodo para Abrir Imagen, utilizado en slotAbrirImagen
     * @param &fileName
     * Path de la Imagen que se desea abrir
     * @return bool
     * True si ha sido leida la imagen
     */
    bool loadFile(const QString &fileName);

    /**
     * @brief
     *  Metodo que inicializa la ventana Abrir Imagen en la carpeta Imagen por defecto
     *  Ordena los archivos del buscador y filtra por png
     * @param QFileDialog&
     *  Ventana de Dialogo Abrir Imagen
     * @param QFileDialog::AcceptMode
     */
    void inicializarVentanaAbrirImagen(QFileDialog&, QFileDialog::AcceptMode);

    void inicializarVentanaAplicacionDeteccion();
    void inicializarVentanaAplicacionCorreccion();


    /**
     * @brief
     * Metodo que abre un fichero deseado mediante asistente de ventana.
     * Filtra por text Files y directorio por defecto. Mis documentos
     * @return  QString
     * Path en la que se encuentra el fichero que se desea abrir
     */
    QString ventanaAbrirFichero();

public:
    /**
     * @brief
     * Contructor de la Clase CAplicacion
     */
    CAplicacion();

    /**
     * @brief
     * Destructor de la Clase CAplicacion
     */
    ~CAplicacion();

    /**
     * @brief
     * Metodo que devuelve la Path Actual de la Imagen del Panel Principal
     * @return
     * QString Path
     */
    QString getPathImagenActual();

    /**
     * @brief
     * Metodo que asigna una nueva Path de la Imagen del Panel Principal
     * @param
     * Nuevo Path
     */
    void setPathImagenActual(QString newPath);

    /**
     * @brief
     * Metodo que devuelve el Panel Principal de la Aplicacion
     * @return
     * CLabel* panel principal
     */
    CLabel* getPanelPrincipal();

    /**
     * @brief
     * Metodo que devuelve el Panel Comparacion de la Aplicacion. Utilizado en la correccion de automatas
     * @return
     * CLabel* panel comparacion
     */
    CLabel* getPanelComparacion();

    /**
     * @brief
     * Metodo que devuelve el Panel Opciones de la Aplicacion
     * @return
     * CLabel* panel opciones
     */
    CPanelOpciones* getPanelOpciones();

    /**
     * @brief
     * Metodo que devuelve el panel de informacion de la Aplicacion
     * @return
     * CLabel* panel informacion
     */
    CLabel* getPanelHistograma();

    /**
     * @brief
     * Metodo que devuelve el layout de la Aplicacion
     * @return
     * layout de la Aplicacion
     */
    QGridLayout* getLayout();

    /**
     * @brief
     * Metodo que devuelve el Menu de la Aplicacion
     * @return
     * Menu Aplicacion
     */
    QMenuBar* getMenuBar();
    /**
     * @brief
     * Metodo que devuelve el submenu Archivo del Menu de la Aplicacion
     * @return
     * Submenu Archivo
     */
    QMenu* getMenuArchivo();
    /**
     * @brief
     * Metodo que devuelve el submenu Editar del Menu de la Aplicacion
     * @return
     * Submenu Editar
     */
    QMenu* getMenuDeteccion();
    /**
     * @brief
     * Metodo que devuelve el submenu Correccion del Menu de la Aplicacion
     * @return
     * Submenu Correccion
     */
    QMenu* getMenuCorreccion();
    /**
     * @brief
     * Metodo que devuelve el submenu Filtro del Menu de la Aplicacion
     * @return
     * Submenu Filtro
     */
    QMenu* getMenuFiltro();

    /**
     * @brief
     * Metodo que devuelve el ToolBar de la Aplicacion
     * @return
     * Toolbar de la Aplicacion
     */
    QToolBar* getToolBar();
    /**
     * @brief
     * Metodo que devuelve el campo CLineEdit, nodo de inicio. Este se introducirá en la ventana
     * @return
     * CLineEdit nodo inicio
     */
    CLineEdit* getNodoInicio();
    /**
     * @brief
     * Metodo que devuelve el campo CLineEdit, nodos finales. Estos se introduciran en la ventana
     * @return
     * CLineEdit nodos finales
     */
    CLineEdit* getNodosFinales();
    /**
     * @brief
     * Metodo que devuelve el campo QComboBox, alfabeto actual, se elige en la ventana si es alfabetico o numerico
     * @return
     * QComboBox opcion alfabeto actual
     */
    QComboBox* getAlfabetoActual();

    /**
     * @brief
     * Metodo que devuelve la Accion Abrir Imagen
     * @return
     * QAction
     */
    QAction* getActionAbrirImagen();
    /**
     * @brief
     * Metodo que devuelve la Accion Abrir Fichero
     * @return
     * QAction
     */
    QAction* getActionAbrirFichero();
    /**
     * @brief
     * Metodo que devuelve la Accion Crear Nuevo Fichero
     * @return
     * QAction
     */
    QAction* getActionCrearNuevoFichero();
    /**
     * @brief
     * Metodo que devuelve la Accion About
     * @return
     * QAction
     */
    QAction* getActionAbout();
    /**
     * @brief
     * Metodo que devuelve la Accion About QT
     * @return
     * QAction
     */
    QAction* getActionAboutQT();
    /**
     * @brief
     * Metodo que devuelve la Accion Salir
     * @return
     * QAction
     */
    QAction* getActionSalir();

    /**
     * @brief
     * Metodo que devuelve la Accion Detectar Lineas
     * @return
     * QAction
     */
    QAction* getActionDetectarLineas();
    /**
     * @brief
     * Metodo que devuelve la Accion DetectarCirculos
     * @return
     * QAction
     */
    QAction* getActionDetectarCirculos();
    /**
     * @brief
     * Metodo que devuelve la Accion Detectar Transiciones
     * @return
     * QAction
     */
    QAction* getActionDetectarTransiciones();
    /**
     * @brief
     * Metodo que devuelve la Accion Codificar Imagen
     * @return
     * QAction
     */
    QAction* getActionCodificarImagen();
    /**
     * @brief
     * Metodo que devuelve la Accion Procesar Imagen
     * @return
     * QAction
     */
    QAction* getActionProcesarImagen();
    /**
     * @brief
     * Metodo que devuelve la Accion Cargar Imagen Original, leida desde get Path Imagen Actual
     * @return
     * QAction
     */
    QAction* getActionCargarImagenOriginal();

    /**
     * @brief
     * Metodo que devuelve la Accion Abrir Fichero Correcto
     * @return
     * QAction
     */
    QAction* getActionAbrirFicheroCorrecto();

    /**
     * @brief
     * Metodo que devuelve la Accion Filtro Gray
     * @return
     * QAction
     */
    QAction* getActionFiltroGray();
    /**
     * @brief
     * Metodo que devuelve la Accion Filtro Gaussiano
     * @return
     * QAction
     */
    QAction* getActionFiltroGaussiano();
    /**
     * @brief
     * Metodo que devuelve la Accion Filtro Mediana
     * @return
     * QAction
     */
    QAction* getActionFiltroMediana();
    /**
     * @brief
     * Metodo que devuelve la Accion Filtro Sobel
     * @return
     * QAction
     */
    QAction* getActionFiltroSobel();
    /**
     * @brief
     * Metodo que devuelve la Accion Filtro Laplaciano
     * @return
     * QAction
     */
    QAction* getActionFiltroLaplaciano();
    /**
     * @brief
     * Metodo que devuelve la Accion Histograma
     * @return
     */
    QAction* getActionHistograma();


    /**
     * @brief
     * Metodo que devuelve el atributo operacionesImagen_
     * @return
     * QAction
     */
    COperacionesImagen* getOperacionesImagen();

    QTextEdit* getTextEditCrearFichero();
    QTimer* getCheckUpdatesTimer();

public slots:

    /**
     * @brief
     * Metodo Slot que Abre una Imagen de fichero y la coloca en el Panel Principal
     */
    void slotAbrirImagen();
    /**
     * @brief
     * Metodo Slot que Abre un Fichero y lo coloca en el Panel Principal
     */
    void slotAbrirFichero();
    /**
     * @brief
     * Metodo Slot que Abre un Fichero y lo coloca en el Panel Principal
     */
    void slotCrearNuevoFichero();
    /**
     * @brief
     * Metodo Slot que Abre un QMessageBox con Informacion Relevante del Proyecto
     */
    void slotAbout();
    /**
     * @brief
     * Metodo Slot que Abre una Ventana de Informacion sobre QT Creator
     */
    void slotAboutQT();
    /**
     * @brief
     * Metodo Slot que Cierra la Aplicacion
     */
    void slotSalir();

    /**
     * @brief
     * Metodo Slot que detecta Lineas en la Imagen de Panel Principal a traves de operacionesImagen_ y coloca la imagen
     * resultante en el Panel Principal de nuevo
     */
    void slotDetectarLineas();
    /**
     * @brief
     * Metodo Slot que detecta Circulos en la Imagen de Panel Principal a traves de operacionesImagen_ y coloca la imagen
     * resultante en el Panel Principal de nuevo
     */
    void slotDetectarCirculos();
    /**
     * @brief
     * Metodo Slot que detecta Transiciones en la Imagen de Panel Principal a traves de operacionesImagen_ y coloca la imagen
     * resultante en el Panel Principal de nuevo
     */
    void slotDetectarTransiciones();
    /**
     * @brief
     * Metodo Slot que intenta codificar la imagen del Panel Principal.
     * Tanto detectarCirculos, detectarLineas y detectarTransiciones, deben haberse ejecutado anteriormente
     * Se abre un asistente para confirmar los datos de la codificacion
     */
    void slotCodificarImagen();
    /**
     * @brief
     * Metodo Slot que automatiza la deteccion de automatas. Detecta Lineas, Circulos, Transiciones y Codifica
     */
    void slotProcesarImagen();
    /**
     * @brief
     * Metodo Slot que Carga la Imagen Original de pathImagenActual_
     */
    void slotCargarImagenOriginal();

    /**
     * @brief
     * Metodo Slot que Abre un Fichero mediante una ventana y lo coloca en el Panel Comparacion
     */
    void slotAbrirFicheroCorrecto();

    /**
     * @brief
     * Metodo Slot que utiliza el FiltroGray sobre la Imagen del panel Principal
     */
    void slotFiltroGray();
    /**
     * @brief
     * Metodo Slot que utiliza el FiltroGaussiano sobre la Imagen del panel Principal
     */
    void slotFiltroGaussiano();
    /**
     * @brief
     * Metodo Slot que utiliza el FiltroMediana sobre la Imagen del panel Principal
     */
    void slotFiltroMediana();
    /**
     * @brief
     * Metodo Slot que utiliza el FiltroSobel sobre la Imagen del panel Principal
     */
    void slotFiltroSobel();
    /**
     * @brief
     * Metodo Slot que utiliza el FiltroLaplaciano sobre la Imagen del panel Principal
     */
    void slotFiltroLaplaciano();
    /**
     * @brief
     * Metodo Slot que calcula slotHistograma sobre la Imagen del panel Principal
     */
    void slotHistograma();

    /**
     * @brief
     * Metodo Slot que calcula de nuevo las detecciones hechas en la imagen si se modifica algun valor del panel Opciones
     */
    void slotCirculosCannyAccumulatorHoughLinesP();
    /**
     * @brief
     * Metodo Slot utilizado en crear nuevo fichero que ofrece informacion, formato fichero automata
     */
    void slotHelp();
    /**
     * @brief
     * Metodo Slot que guarda el Automata creado en el fichero que se especifique
     */
    void slotGuardar();

    void prueba();
};
#endif
