///////////////////////////////////////////////////////////////
//    CPushButton.h - Declaración de la clase CPushButton    //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H
#include <QPushButton>
#include <iostream>
using namespace std;

/**
 * @brief
 * Clase heredada de 'QPushButton' que aplica un estilo determinado a este tipo de container
*/
class CPushButton : public QPushButton {
public:
    /**
     * @brief
     * Constructor que aplica el estilo
     * @param text. Texto del Button
     */
    CPushButton(QString text);
};
#endif // CPUSHBUTTON_H
