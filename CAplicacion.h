#include <QtWidgets>
#include "CLabel.h"
#include "COperacionesImagen.h"

class CAplicacion: public QMainWindow {
  Q_OBJECT
private:

    QString pathImagenActual_;

    CLabel* panelPrincipal_;
    CLabel* panelOpciones_;
    CLabel* panelHistograma_;

    QMenuBar* menu_;
    QMenu* menuArchivo_;
    QMenu* menuEditar_;
    QAction* actionAbrirImagen_;
    QAction* actionAbout_;
    QAction* actionSalir_;
    QAction* actionDetectarAutomata_;
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
    QAction* getActionAbrirImagen();
    QAction* getActionAbout();
    QAction* getActionSalir();
    QAction* getActionDetectarAutomata();

    COperacionesImagen* getOperacionesImagen();

public slots:
    void slotAbrirImagen();
    void slotAbout();
    void slotSalir();

    void slotDetectarAutomata();
};
