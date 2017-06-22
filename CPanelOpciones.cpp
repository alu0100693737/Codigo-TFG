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
    layout_ = new QGridLayout();
    setFixedHeight(140);
    //verde
    setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black");

    ///Agregamos a la ventana los datos
    setLayout(layout_);
    iniciarVistaDeteccion();
}

void CPanelOpciones::iniciarVistaDeteccion() {
    ///Se inicializan los QScrollBar
    cannyThresHold_ = new QScrollBar(Qt::Horizontal);
    accumulatorThresHold_ = new QScrollBar(Qt::Horizontal);
    hougLinesP_ = new QScrollBar(Qt::Horizontal);

    ///Aplicamos estilo fondo 'verde', rango de valores y valor por defecto a los QScrollBar

    getCannyThresHold()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getCannyThresHold()->setRange(10, 150);
    getCannyThresHold()->setValue(CANNYTHRESHOLD);

    getAccumulatorThresHold()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getAccumulatorThresHold()->setRange(10, 150);
    getAccumulatorThresHold()->setValue(ACCUMULATORTHRESHOLD);

    getHoughLinesP()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getHoughLinesP()->setRange(10, 150);
    getHoughLinesP()->setValue(HOUGHLINESP);

    lCannyThresHold_ = new CLabel(QString("CannyThresHold"), false);
    lAccumulatorThresHold_ = new CLabel(QString("AccumulatorThresHold"), false);
    lHoughLinesP_ = new CLabel(QString("HoughLinesP"), false);

    ///Se inicializan los CLabel con los valores de los QScrollBar
    valorCannyThresHold_ = new CLabel(QString::number(getCannyThresHold()->value()), false);
    valorAccumulatorThresHold_ = new CLabel(QString::number(getAccumulatorThresHold()->value()), false);
    valorHoughLinesP_ = new CLabel(QString::number(getHoughLinesP()->value()), false);

    // simplificarAutomata_ = new CPushButton("Simplificar Automata", true);
    // corregirFichero_ = new CPushButton("Corregir Fichero", true);

    if(!getLayout()->isEmpty()) {
        getLayout()->removeWidget(getAnalizarCadena());
        getLayout()->removeWidget(getSimplificarFichero());
        getLayout()->removeWidget(getCorregirFichero());
        delete getAnalizarCadena();
        delete getSimplificarFichero();
        delete getCorregirFichero();
    }

    getLayout()->addWidget(getLCannyThresHold(),  0, 0, 1, 4);
    getLayout()->addWidget(getCannyThresHold(), 1, 0, 1, 3);
    getLayout()->addWidget(getValorCannyThresHold(), 1, 3, 1, 1);

    getLayout()->addWidget(getLAccumulatorThresHold(),  2, 0, 1, 4);
    getLayout()->addWidget(getAccumulatorThresHold(), 3, 0, 1, 3);
    getLayout()->addWidget(getValorAccumulatorThresHold(), 3, 3, 1, 1);

    getLayout()->addWidget(getLHoughLinesP(),  4, 0, 1, 4);
    getLayout()->addWidget(getHoughLinesP(), 5, 0, 1, 3);
    getLayout()->addWidget(getValorHoughLinesP(), 5, 3, 1, 1);
}

void CPanelOpciones::iniciarVistaCorreccion() {

    getLayout()->removeWidget(getCannyThresHold());
    getLayout()->removeWidget(getValorCannyThresHold());
    getLayout()->removeWidget(getLCannyThresHold());
    getLayout()->removeWidget(getAccumulatorThresHold());
    getLayout()->removeWidget(getValorAccumulatorThresHold());
    getLayout()->removeWidget(getLAccumulatorThresHold());
    getLayout()->removeWidget(getValorHoughLinesP());
    getLayout()->removeWidget(getHoughLinesP());
    getLayout()->removeWidget(getLHoughLinesP());

    delete getLCannyThresHold();
    delete getCannyThresHold();
    delete getValorCannyThresHold();
    delete getLAccumulatorThresHold();
    delete getAccumulatorThresHold();
    delete getValorAccumulatorThresHold();
    delete getLHoughLinesP();
    delete getHoughLinesP();
    delete getValorHoughLinesP();

    /// Valores para la codificacion 2 Botones
    analizarCadena_ = new CPushButton("Analizar Cadena", true);
    simplificarAutomata_ = new CPushButton("Simplificar Automata", true);
    corregirFichero_ = new CPushButton("Corregir Fichero", true);

    getLayout()->addWidget(getAnalizarCadena(), 0, 0, 2, 4);
    getLayout()->addWidget(getSimplificarFichero(),  2, 0, 2, 4);
    getLayout()->addWidget(getCorregirFichero(), 4, 0, 2, 4);
    getAnalizarCadena()->setEnabled(false);
    getSimplificarFichero()->setEnabled(false);
    getCorregirFichero()->setEnabled(false);
}

QGridLayout* CPanelOpciones::getLayout() {
    return layout_;
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

CLabel* CPanelOpciones::getLCannyThresHold() {
    return lCannyThresHold_;
}

CLabel* CPanelOpciones::getLAccumulatorThresHold() {
    return lAccumulatorThresHold_;
}

CLabel* CPanelOpciones::getLHoughLinesP() {
    return lHoughLinesP_;
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

CPushButton* CPanelOpciones::getAnalizarCadena() {
    return analizarCadena_;
}

CPushButton* CPanelOpciones::getSimplificarFichero() {
    return simplificarAutomata_;
}

CPushButton* CPanelOpciones::getCorregirFichero() {
    return corregirFichero_;
}
