///////////////////////////////////////////////////////////////
//          CLineEdit.h - Declaración de la clase CLineEdit  //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CLINEEDIT_H
#define CLINEEDIT_H
#include <QLineEdit>

/**Clase heredada de 'QLineEdit' que aplica un estilo determinado a este tipo de container*/
class CLineEdit : public QLineEdit{
public:
    /**
     * @brief CLineEdit Constructor con estilo centrado y fondo blanco
     */
    CLineEdit();

    /**
     * @brief CLineEdit
     * @param text Texto a introducir en el QLineEdit
     */
    CLineEdit(QString text);

    /**
      * @brief Destructor
      */
    ~CLineEdit();
};

#endif // CLINEEDIT_H
