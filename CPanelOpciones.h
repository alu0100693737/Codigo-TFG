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
#include <QWidget>
#include <QScrollBar>
#include <QGridLayout>
#include "CLabel.h"

/**
 * @brief
 * Clase que almacena un panel con las variables de la Detección de circulos y lineas
*/
class CPanelOpciones : public QWidget {
private:
    /// QScrollBar variable cannyThresHold por defecto a 30. Utilizada en la deteccion de circulos
    QScrollBar* cannyThresHold_;
    /// QScrollBar variable accumulatorThresHold por defecto a 42. Utilizada en la deteccion de circulos
    QScrollBar* accumulatorThresHold_;
    /// QScrollBar variable houghLinesP por defecto 80. Utilizada en la deteccion de lineas
    QScrollBar* hougLinesP_;

    /// CLabel variable cannyThresHold
    CLabel* valorCannyThresHold_;
    /// CLabel variable accumulatorThresHold
    CLabel* valorAccumulatorThresHold_;
    /// CLabel variable houghLinesP
    CLabel* valorHoughLinesP_;

public:
    /**
     * @brief
     * Constructor de la clase
     */
    CPanelOpciones();
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
};

#endif // CPANELOPCIONES_H
