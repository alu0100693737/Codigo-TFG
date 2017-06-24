///////////////////////////////////////////////////////////////
// CPushButton.h - Implementacion de la clase CPushButton    //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#include "CPushButton.h"

CPushButton::CPushButton(QString text, bool s) : QPushButton(text){
    if( s)
        setStyleSheet("background-color: rgb(233, 233, 233);"
                  "color: black; border-width: 1px;"
                  "border-top: 1px solid white;"
                  "border-left: 1px solid white;"
                  "border-right: 1px solid grey;"
                  "border-bottom: 1px solid grey;"
                  "border-style: solid; "
                  "border-radius: 5;"
                  "padding: 3px;"
                  "padding-left: 5px;"
                  "padding-right: 5px;"
                  "font: 16px;"
                  "font-weight: bold;");
    else {
        setStyleSheet("background-color: rgb(233, 233, 233);"
                  "color: black; border-width: 1px;"
                  "border-top: 1px solid white;"
                  "border-left: 1px solid white;"
                  "border-right: 1px solid grey;"
                  "border-bottom: 1px solid grey;"
                  "border-style: solid; "
                  "border-radius: 5;"
                  "padding: 5px;"
                  "padding-left: 8px;"
                  "padding-right: 8px;"
                  "font: 12px;"
                  "font-weight: bold;");
    }
}
