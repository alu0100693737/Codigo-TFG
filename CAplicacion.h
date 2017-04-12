#include <QtWidgets>
#include "CLabel.h"
class CAplicacion: public QMainWindow {
  Q_OBJECT
private:
    CLabel* panelPrincipal_;
    CLabel* panelOpciones_;
    CLabel* panelHistograma_;
 public:
    CAplicacion();
    ~CAplicacion();
    CLabel* getPanelPrincipal();
    CLabel* getPanelOpciones();
    CLabel* getPanelHistograma();

    void prueba();
public slots:
    void slotAbout();
};
