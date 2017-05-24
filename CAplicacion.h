#include <QtWidgets>
#include "CLabel.h"
#include "COperacionesImagen.h"

class CAplicacion: public QMainWindow {
  Q_OBJECT
private:

    QImage imagenPanelPrincipal;

    QString pathImagenActual_;

    CLabel* panelPrincipal_;
    CLabel* panelOpciones_;
    CLabel* panelHistograma_;

    QMenuBar* menu_;
    QMenu* menuArchivo_;
    QMenu* menuEditar_;
    QMenu* menuFiltro_;
    QAction* actionAbrirImagen_;
    QAction* actionAbout_;
    QAction* actionSalir_;
    QAction* actionDetectarAutomata_;
    QAction* actionDetectarTransiciones_;
    QAction* actionCodificarImagen_;
    QAction* actionCargarImagenOriginal_;
    QAction* actionFiltroGray_;
    QAction* actionFiltroGaussiano_;
    QAction* actionFiltroMediana_;
    QAction* actionFiltroSobel_;
    QAction* actionFiltroLaplaciano_;
    QAction* actionHistograma_;

    QToolBar* toolbar_;

    QLineEdit* nodo_inicio;
    QLineEdit* nodos_finales;
    QComboBox* alfabeto_; //0 -> alfabeto a, b, c   1 -> Alfabeto numerico

    COperacionesImagen* operacionesImagen_;

    //Abrir Imagen
    bool loadFile(const QString &fileName); //Utilizado slot abrirImagen
    //Guarda localizacion elegida, por defecto carpeta imagenes, ordena los archivos y filtra por jpg
    void inicializarVentanaAbrirImagen(QFileDialog&, QFileDialog::AcceptMode);
 public:
    CAplicacion();
    ~CAplicacion();

    QString getPathImagenActual();
    void setPathImagenActual(QString newPath);

    CLabel* getPanelPrincipal();
    CLabel* getPanelOpciones();
    CLabel* getPanelHistograma();

    QMenuBar* getMenuBar();
    QMenu* getMenuArchivo();
    QMenu* getMenuEditar();
    QMenu* getMenuFiltro();

    QToolBar* getToolBar();
    QLineEdit* getNodoInicio();
    QLineEdit* getNodosFinales();
    QComboBox* getAlfabetoActual();

    QAction* getActionAbrirImagen();
    QAction* getActionAbout();
    QAction* getActionSalir();
    QAction* getActionDetectarAutomata();
    QAction* getActionDetectarTransiciones();
    QAction* getActionCodificarImagen();
    QAction* getActionCargarImagenOriginal();
    QAction* getActionFiltroGray();
    QAction* getActionFiltroGaussiano();
    QAction* getActionFiltroMediana();
    QAction* getActionFiltroSobel();
    QAction* getActionFiltroLaplaciano();
    QAction* getActionHistograma();

    COperacionesImagen* getOperacionesImagen();

public slots:
    void slotAbrirImagen();
    void slotAbout();
    void slotSalir();

    void slotDetectarAutomata();
    void slotDetectarTransiciones();
    void slotCodificarImagen();
    void slotCargarImagenOriginal();

    void slotFiltroGray();
    void slotFiltroGaussiano();
    void slotFiltroMediana();
    void slotFiltroSobel();
    void slotFiltroLaplaciano();
    void slotHistograma();
};
