#include <QtWidgets>
#include "CLabel.h"
#include "COperacionesImagen.h"

class CAplicacion: public QMainWindow {
  Q_OBJECT
private:
    CLabel* panelPrincipal_;
    CLabel* panelOpciones_;
    CLabel* panelHistograma_;
    COperacionesImagen* operacionesImagen_;

    bool loadFile(const QString &fileName); //Utilizado slot abrirImagen
    //Guarda localizacion elegida, por defecto carpeta imagenes, ordena los archivos y filtra por jpg
    void inicializarVentanaAbrirImagen(QFileDialog&, QFileDialog::AcceptMode);
 public:
    CAplicacion();
    ~CAplicacion();
    CLabel* getPanelPrincipal();
    CLabel* getPanelOpciones();
    CLabel* getPanelHistograma();
    COperacionesImagen* getOperacionesImagen();

public slots:
    void slotAbrirImagen();
    void slotAbout();
    void slotSalir();

    void slotDetectarAutomata();
};
