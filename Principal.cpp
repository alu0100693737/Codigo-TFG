///////////////////////////////////////////////////////////////
//          Principal.cpp - Programa principal               //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#include "CAplicacion.h"
int main(int argc,char* argv[]) {
    QApplication app(argc,argv);

    CAplicacion window;
    window.show();
    cout << "Version: " << CV_MAJOR_VERSION << endl;
    return app.exec();
}


