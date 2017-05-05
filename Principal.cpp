#include "CAplicacion.h"
#include "CDetectarTransiciones.h"
int main(int argc,char* argv[]) {
  QApplication app(argc,argv);


  CDetectarTransiciones* prueba = new CDetectarTransiciones();
  prueba->ejecutar();

  CAplicacion window;
  window.show();
  cout << "Version: " << CV_MAJOR_VERSION << endl;
  return app.exec();
}

