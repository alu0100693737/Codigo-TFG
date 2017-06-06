/////////////////////////////////////////////////////////////////////
//   CCheckBox.h - Declaración    de la clase CCheckBox            //
//                                                                 //
//               Autor: Iván García Campos                         //
//                                                                 //
//            Proyecto de Trabajo Fin de Grado.                    //
//                                                                 //
//               Fecha: 05/06/2017                                 //
/////////////////////////////////////////////////////////////////////

#ifndef CCHECKBOX_H
#define CCHECKBOX_H
#include <QCheckBox>

/**
 * @brief
 * Clase heredada de 'QCheckBox' que aplica un estilo determinado a este tipo de container
*/
class CCheckBox : public QCheckBox {
public:
    /**
     * @brief
     * Constructor con estilo centrado y fondo blanco
     */
    CCheckBox();

    /**
      * @brief
      * Destructor
     */
    ~CCheckBox();
};

#endif // CCHECKBOX_H
