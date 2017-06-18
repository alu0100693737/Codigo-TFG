///////////////////////////////////////////////////////////////
//       CLabel.h - Implementación de la clase CLabel        //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#include "CLabel.h"

CLabel::CLabel() : QLabel() {
        setStyleSheet("background-color : rgba( 160, 160, 160, 255); border: 10px solid black");
        setText("Prueba Label propia");
        setAlignment(Qt::AlignCenter);
}

CLabel::CLabel(QString text, bool style) : QLabel() {
    setText(text);
    setAlignment(Qt::AlignAbsolute);
    if(style == true) {
        setStyleSheet("background-color: white; border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; padding: 6px;");

        QFont f( "Arial", 14, QFont::Bold);
        setFont(f);
    } else {
        QFont f( "Arial", 9, QFont::Bold);
        setFont(f);
        setStyleSheet("background-color : white;");
    }
}

QImage CLabel::getImagen() {
    return imagen_;
}

void CLabel::setImagen(const QImage imagenNueva) {
    imagen_ = imagenNueva;
    setScaledContents(true);
    setPixmap(QPixmap::fromImage(getImagen()));
}

void CLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked(event);
}
