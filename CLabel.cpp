#include "CLabel.h"

CLabel::CLabel() : QLabel() {
    setStyleSheet("background-color : rgba( 160, 160, 160, 255); border: 10px solid black");
    setText("Prueba Label propia");
    setAlignment(Qt::AlignCenter);
}

CLabel::CLabel(QString text, bool imagen) : QLabel() {
    setText(text);
    setAlignment(Qt::AlignCenter);
    if(imagen) {
        QImage image;
        image.load("/home/ivan/Documentos/TFG/grafo.jpg");

        setScaledContents(true);
        //int w = this->width();
        //int h = this->height();
        // set a scaled pixmap to a w x h window keeping its aspect ratio
        //setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
        setPixmap(QPixmap::fromImage(image));
        //setPicture("grafo.jpg");
         }
}
