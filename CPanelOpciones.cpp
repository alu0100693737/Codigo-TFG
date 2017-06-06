/////////////////////////////////////////////////////////////////
//CPanelOpciones.h - Implementacion de la clase CPanelOpciones //
//                                                             //
//               Autor: Iván García Campos                     //
//                                                             //
//            Proyecto de Trabajo Fin de Grado.                //
//                                                             //
//               Fecha: 05/06/2017                             //
/////////////////////////////////////////////////////////////////

#include "CPanelOpciones.h"

CPanelOpciones::CPanelOpciones() {

    ///Se carga el Layout del panel
    QGridLayout *layout = new QGridLayout();

    ///Se inicializan los QScrollBar
    cannyThresHold_ = new QScrollBar(Qt::Horizontal);
    accumulatorThresHold_ = new QScrollBar(Qt::Horizontal);
    hougLinesP_ = new QScrollBar(Qt::Horizontal);

    ///Aplicamos estilo fondo 'verde', rango de valores y valor por defecto a los QScrollBar

    getCannyThresHold()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getCannyThresHold()->setRange(10, 150);
    getCannyThresHold()->setValue(30);

    getAccumulatorThresHold()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getAccumulatorThresHold()->setRange(10, 150);
    getAccumulatorThresHold()->setValue(42);

    getHoughLinesP()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getHoughLinesP()->setRange(10, 150);
    getHoughLinesP()->setValue(80);

    ///Se inicializan los CLabel con los valores de los QScrollBar
    valorCannyThresHold_ = new CLabel(QString::number(getCannyThresHold()->value()), false);
    valorAccumulatorThresHold_ = new CLabel(QString::number(getAccumulatorThresHold()->value()), false);
    valorHoughLinesP_ = new CLabel(QString::number(getHoughLinesP()->value()), false);

    ///Agregamos a la ventana los datos
    layout->addWidget(new CLabel(QString("CannyThresHold"), false),  0, 0, 1, 4);
    layout->addWidget(getCannyThresHold(), 1, 0, 1, 3);
    layout->addWidget(getValorCannyThresHold(), 1, 3, 1, 1);

    layout->addWidget(new CLabel(QString("AcummulatorThresHold"), false),  2, 0, 1, 4);
    layout->addWidget(getAccumulatorThresHold(), 3, 0, 1, 3);
    layout->addWidget(getValorAccumulatorThresHold(), 3, 3, 1, 1);

    layout->addWidget(new CLabel(QString("HoughLinesP"), false),  4, 0, 1, 4);
    layout->addWidget(getHoughLinesP(), 5, 0, 1, 3);
    layout->addWidget(getValorHoughLinesP(), 5, 3, 1, 1);

    setLayout(layout);
}

QScrollBar* CPanelOpciones::getCannyThresHold() {
    return cannyThresHold_;
}

QScrollBar* CPanelOpciones::getAccumulatorThresHold() {
    return accumulatorThresHold_;
}

QScrollBar* CPanelOpciones::getHoughLinesP() {
    return hougLinesP_;
}

CLabel* CPanelOpciones::getValorCannyThresHold() {
    return valorCannyThresHold_;
}

CLabel* CPanelOpciones::getValorAccumulatorThresHold() {
    return valorAccumulatorThresHold_;
}

CLabel* CPanelOpciones::getValorHoughLinesP() {
    return valorHoughLinesP_;
}
