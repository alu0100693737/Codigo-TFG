#include "CLabel.h"

CLabel::CLabel() : QLabel() {
    setStyleSheet("background-color : rgba( 160, 160, 160, 255); border: 10px solid black");
    setText("Prueba Label propia");
    setAlignment(Qt::AlignCenter);
}

CLabel::CLabel(QString text) : QLabel() {
    setText(text);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("background-color : rgba( 160, 160, 160, 255); border: 5px solid black");
}

QImage CLabel::getImagen() {
    return imagen_;
}

void CLabel::setImagen(const QImage imagenNueva) {
    imagen_ = imagenNueva;
    setScaledContents(true);
    setPixmap(QPixmap::fromImage(getImagen()));
}
