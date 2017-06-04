///////////////////////////////////////////////////////////////
//          CLabel.h - Declaración de la clase CLabel        //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CLABEL_H
#define CLABEL_H
#include <QLabel>
#include <iostream>
using namespace std;

class CLabel : public QLabel {
private:
    QImage imagen_;
public:
    CLabel();
    CLabel(QString text, bool);
    QImage getImagen();
    void setImagen(const QImage);
};

#endif // CLABEL_H
