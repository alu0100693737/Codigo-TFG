#include <QtWidgets>
#include "CLabel.h"
class CAplicacion: public QMainWindow {
  Q_OBJECT
private:

  public:
  CAplicacion();
  ~CAplicacion();

  void prueba();
public slots:
  void slotAbout();
};
