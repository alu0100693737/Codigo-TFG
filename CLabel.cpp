#include "CLabel.h"

CLabel::CLabel() : QLabel() {
    setAutoFillBackground(true);
    setStyleSheet("background: red");
    setText("Prueba Label propia");

}

CLabel::CLabel(QString text) : QLabel() {
    setText(text);
    setStyleSheet("background: blue");

}
