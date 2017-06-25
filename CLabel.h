///////////////////////////////////////////////////////////////
//          CLabel.h - Declaración de la clase CLabel        //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#ifndef CLABEL_H
#define CLABEL_H
#include <QLabel>
#include <iostream>
#include <QLabel>
#include <QWidget>
#include <Qt>
using namespace std;
/**
 * @brief
 * Clase heredada de 'QLabel' que aplica un estilo determinado a este tipo de container
 */
class CLabel : public QLabel {
    Q_OBJECT
private:
    ///Imagen actual del CLabel si la tuviera
    QImage imagen_;
public:
    /**
     * @brief
     * Constructor por defecto
     * Aplica estilo, alinea centro, color gris y borde
     */
    CLabel();
    CLabel(CLabel*);
    /**
     * @brief
     * Constructor que aplica un estilo con fondo blanco y letra Arial, centrado y texto
     * @param text. Texto
     * @param tipo. False -> Letra 9. True -> Letra 14
     */
    CLabel(QString text, bool tipo);
    /**
     * @brief
     * Metodo que devuelve la imagen del CLabel si la hubiera
     * @return QImage
     */
    QImage getImagen();
    /**
     * @brief
     * Metodo que introduce una imagen en el CLabel
     */
    void setImagen(const QImage);

signals:
    void clicked(QMouseEvent* event);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLABEL_H
