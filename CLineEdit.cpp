#include "CLineEdit.h"

CLineEdit::CLineEdit() {
    setAlignment(Qt::AlignCenter);
    setStyleSheet("background-color: white;");
}

CLineEdit::CLineEdit(QString text) : QLineEdit(text){
    setAlignment(Qt::AlignCenter);
    setStyleSheet("background-color: white;");
}
