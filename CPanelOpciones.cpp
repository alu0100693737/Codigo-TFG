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

    getCannyThresHold()->setStyleSheet("background-color: rgba(126, 156, 232 ,  0.9);");
    getCannyThresHold()->setRange(10, 150);
    getCannyThresHold()->setValue(CANNYTHRESHOLD);

    getAccumulatorThresHold()->setStyleSheet("background-color: rgba(126, 156, 232 ,  0.9);");
    getAccumulatorThresHold()->setRange(10, 150);
    getAccumulatorThresHold()->setValue(ACCUMULATORTHRESHOLD);

    getHoughLinesP()->setStyleSheet("background-color: rgba(126, 156, 232,  0.9);");
    getHoughLinesP()->setRange(10, 150);
    getHoughLinesP()->setValue(HOUGHLINESP);

    lCannyThresHold_ = new CLabel(QString("CannyThresHold"), false);
    lAccumulatorThresHold_ = new CLabel(QString("AccumulatorThresHold"), false);
    lHoughLinesP_ = new CLabel(QString("HoughLinesP"), false);

    ///Se inicializan los CLabel con los valores de los QScrollBar
    valorCannyThresHold_ = new CLabel(QString::number(getCannyThresHold()->value()), false);
    valorAccumulatorThresHold_ = new CLabel(QString::number(getAccumulatorThresHold()->value()), false);
    valorHoughLinesP_ = new CLabel(QString::number(getHoughLinesP()->value()), false);
    setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black");
    // simplificarAutomata_ = new CPushButton("Simplificar Automata", true);
    // corregirFichero_ = new CPushButton("Corregir Fichero", true);

    if(!getLayout()->isEmpty()) {
        getLayout()->removeWidget(getCargarImagenCorregir());
        getLayout()->removeWidget(getCargarImagenReferencia());
        getLayout()->removeWidget(getCargarFicheroCorregir());
        getLayout()->removeWidget(getCargarFicheroReferencia());
    //    getLayout()->removeWidget(getAnalizarCadena());
        //getLayout()->removeWidget(getSimplificarFicheroCorregir());
       // getLayout()->removeWidget(getSimplificarFicheroReferencia());
        //getLayout()->removeWidget(getCorregirFichero());

        delete getCargarImagenCorregir();
        delete getCargarImagenReferencia();
        delete getCargarFicheroCorregir();
        delete getCargarFicheroReferencia();
        //delete getAnalizarCadena();
        //delete getSimplificarFicheroCorregir();
        //delete getSimplificarFicheroReferencia();
        //delete getCorregirFichero();
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
    setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1 px solid black");
}

void CPanelOpciones::iniciarVistaCorreccion(int valor) { //opciones
if(valor == 0)  {
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
        cargarImagenCorregir_ = new CPushButton("Cargar imagen para \nsu corrección", true);
        cargarImagenReferencia_ = new CPushButton("Cargar imagen de \nreferencia", true);

        cargarFicheroCorregir_ = new CPushButton("Cargar fichero para \nsu corrección", true);
        cargarFicheroReferencia_ = new CPushButton("Cargar fichero de \nreferencia", true);
        getLayout()->addWidget(new CLabel("Panel 1", false), 0, 0, 1, 2);
        getLayout()->addWidget(new CLabel("Panel 2", false), 0, 2, 1, 2);
        getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 2, 2);
        getLayout()->addWidget(getCargarFicheroCorregir(), 3, 0, 2, 2);
        getLayout()->addWidget(getCargarImagenReferencia(), 1, 2, 2, 2);
        getLayout()->addWidget(getCargarFicheroReferencia(), 3, 2, 2, 2);
}
    else if (valor == 2) {
        cout << "HOLA" << endl;
        simplificarAutomataReferencia_ = new CPushButton("Simplificar autómata de referencia", true);
        getLayout()->removeWidget(getCargarImagenReferencia());
        getLayout()->removeWidget((getCargarFicheroReferencia()));
        delete getCargarImagenReferencia();
        delete getCargarFicheroReferencia();

        cargarImagenReferencia_ = new CPushButton("Cargar Imagen de referencia", true);
        cargarFicheroReferencia_ = new CPushButton("Cargar fichero de referencia", true);

        getLayout()->addWidget(new CLabel("Panel 1", false), 0, 0, 1, 2);
        getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 2, 2);
        getLayout()->addWidget(getCargarFicheroCorregir(), 3, 0, 2, 2);

        getLayout()->addWidget(new CLabel("Panel 2", false), 0, 2, 1, 2);
        getLayout()->addWidget(getCargarImagenReferencia(), 1, 2, 1, 2);
        getLayout()->addWidget(getCargarFicheroReferencia(), 2, 2, 1, 2);
        getLayout()->addWidget(getSimplificarFicheroReferencia(), 3, 2, 1, 2);
    }
        /*analizarCadena_ = new CPushButton("Analizar Cadena Sobre Autómata a corregir", true);
    simplificarAutomataCorregir_ = new CPushButton("Simplificar Autómata a Corregir", true);
    corregirFichero_ = new CPushButton("Corregir Fichero", true);

    getLayout()->addWidget(getAnalizarCadena(), 0, 0, 2, 4);
    getLayout()->addWidget(getSimplificarFicheroCorregir(),  2, 0, 2, 4);
    getLayout()->addWidget(getCorregirFichero(), 4, 0, 2, 4);
}
    getAnalizarCadena()->setEnabled(false);
    getSimplificarFicheroCorregir()->setEnabled(false);
    getCorregirFichero()->setEnabled(false);*/

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

CPushButton* CPanelOpciones::getCargarImagenCorregir() {
    return cargarImagenCorregir_;
}

CPushButton* CPanelOpciones::getCargarFicheroCorregir() {
    return cargarFicheroCorregir_;
}

CPushButton* CPanelOpciones::getCargarImagenReferencia() {
    return cargarImagenReferencia_;
}

CPushButton* CPanelOpciones::getCargarFicheroReferencia() {
    return cargarFicheroReferencia_;
}

CPushButton* CPanelOpciones::getAnalizarCadena() {
    return analizarCadena_;
}

CPushButton* CPanelOpciones::getSimplificarFicheroCorregir() {
    return simplificarAutomataCorregir_;
}

CPushButton* CPanelOpciones::getSimplificarFicheroReferencia() {
    return simplificarAutomataReferencia_;
}

CPushButton* CPanelOpciones::getCorregirFichero() {
    return corregirFichero_;
}

void CPanelOpciones::slotAnalizarCadena() {
    cout << "Analizando cadena " << endl;
}

void CPanelOpciones::slotSimplificarFichero() {
    cout << "Simplificando fichero " << endl;
}

void CPanelOpciones::slotCorregirFichero() {
    cout << "Corrigiendo fichero " << endl;
}

