#include "CWidgetOpciones.h"
#include "CLabel.h"

CWidgetOpciones::CWidgetOpciones() : QWidget() {
    setStyleSheet( "QWidget{ background-color : rgba( 160, 160, 160, 255); border-radius : 7px;  }" );
    CLabel *label = new CLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label->setText("Random String");
    layout->addWidget(label);
    setLayout(layout);
}


