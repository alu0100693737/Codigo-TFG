#include "CLabel.h"

CLabel::CLabel() : QLabel() {

        setStyleSheet("background-color : rgba( 160, 160, 160, 255); border: 10px solid black");
        setText("Prueba Label propia");
        setAlignment(Qt::AlignCenter);
}

CLabel::CLabel(QString text, bool style) : QLabel() {
    QFont f( "Arial", 10, QFont::Bold);
    setFont(f);
    setText(text);
    setAlignment(Qt::AlignCenter);
    if(style == true)
        setStyleSheet("background-color : rgba( 160, 160, 160, 255); border: 5px solid black");
    else {
        setStyleSheet("border: 5px solid black");
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
