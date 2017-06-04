///////////////////////////////////////////////////////////////
//          CLineEdit.h - Declaración de la clase CLineEdit  //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CLINEEDIT_H
#define CLINEEDIT_H
#include <QLineEdit>

class CLineEdit : public QLineEdit{
public:
    CLineEdit();
    CLineEdit(QString text);
};

#endif // CLINEEDIT_H
