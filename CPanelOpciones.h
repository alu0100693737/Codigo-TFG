///////////////////////////////////////////////////////////////
// CPanelOpciones.h - Declaración de la clase CPanelOpciones //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CPANELOPCIONES_H
#define CPANELOPCIONES_H
#include <iostream>
#include <QWidget>
#include <QScrollBar>
#include <QGridLayout>
#include "CLabel.h"
#include "CPushButton.h"

#define CANNYTHRESHOLD 30
#define ACCUMULATORTHRESHOLD 42
#define HOUGHLINESP 80

using namespace std;
/**
 * @brief
 * Clase que almacena un panel con las variables de la Detección de circulos y lineas
*/
class CPanelOpciones : public QWidget {
private:

    QGridLayout* layout_;

    /// QScrollBar variable cannyThresHold por defecto a 30. Utilizada en la deteccion de circulos
    QScrollBar* cannyThresHold_;
    /// QScrollBar variable accumulatorThresHold por defecto a 42. Utilizada en la deteccion de circulos
    QScrollBar* accumulatorThresHold_;
    /// QScrollBar variable houghLinesP por defecto 80. Utilizada en la deteccion de lineas
    QScrollBar* hougLinesP_;

    CLabel* lCannyThresHold_;
    CLabel* lAccumulatorThresHold_;
    CLabel* lHoughLinesP_;

    /// CLabel variable cannyThresHold
    CLabel* valorCannyThresHold_;
    /// CLabel variable accumulatorThresHold
    CLabel* valorAccumulatorThresHold_;
    /// CLabel variable houghLinesP
    CLabel* valorHoughLinesP_;

    CPushButton* simplificarAutomata_;
    CPushButton* corregirFichero_;

public:
    /**
     * @brief
     * Constructor de la clase
     */
    CPanelOpciones();

    void iniciarVistaDeteccion();
    void iniciarVistaCorreccion();

    QGridLayout* getLayout();
    /**
     * @brief
     * Metodo que retorna el QScrollBar de la Variable CannyThresHold
     * @return QScrollBar
     */
    QScrollBar* getCannyThresHold();
    /**
     * @brief
     * Metodo que retorna el QScrollBar de la Variable AccumulatorThresHold
     * @return QScrollBar
     */
    QScrollBar* getAccumulatorThresHold();
    /**
     * @brief
     * Metodo que retorna el QScrollBar de la Variable houghLinesP
     * @return
     */
    QScrollBar* getHoughLinesP();

    CLabel* getLCannyThresHold();
    CLabel* getLAccumulatorThresHold();
    CLabel* getLHoughLinesP();
    /**
     * @brief
     * Metodo que retorna el CLabel de la Variable CannyThresHold
     * @return CLabel
     */
    CLabel* getValorCannyThresHold();
    /**
     * @brief
     * Metodo que retorna el CLabel de la Variable AccumulatorThresHold
     * @return CLabel
     */
    CLabel* getValorAccumulatorThresHold();
    /**
     * @brief
     * Metodo que retorna el CLabel de la Variable HoughLinesP
     * @return
     */
    CLabel* getValorHoughLinesP();

    CPushButton* getSimplificarFichero();
    CPushButton* getCorregirFichero();
};

#endif // CPANELOPCIONES_H
