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
 public:
    CAplicacion();
    ~CAplicacion();
    CLabel* getPanelPrincipal();
    CLabel* getPanelOpciones();
    CLabel* getPanelHistograma();
    COperacionesImagen* getOperacionesImagen();

    //bool loadFile(const QString &);
    //static void inicializarVentanaAbrirImagen(QFileDialog, QFileDialog::AcceptMode);
public slots:
    void slotAbrirImagen();
    void slotAbout();
};
