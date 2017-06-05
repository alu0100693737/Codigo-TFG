///////////////////////////////////////////////////////////////
//       CLineEdit.h - Implementacion de la clase CLineEdit  //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#include "CLineEdit.h"

CLineEdit::CLineEdit() {
    setAlignment(Qt::AlignCenter);
    setStyleSheet("background-color: white;");
}

CLineEdit::CLineEdit(QString text) : QLineEdit(text){
    setAlignment(Qt::AlignCenter);
    setStyleSheet("background-color: white;");
}

CLineEdit::~CLineEdit() {
}
