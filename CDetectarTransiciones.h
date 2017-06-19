////////////////////////////////////////////////////////////////////////////
//CDetectarTransiciones.h - Declaración de la clase CDetectarTransiciones //
//                                                                        //
//               Autor: Iván García Campos                                //
//                                                                        //
//            Proyecto de Trabajo Fin de Grado.                           //
//                                                                        //
//               Fecha: 05/06/2017                                        //
////////////////////////////////////////////////////////////////////////////

#ifndef CDETECTARTRANSICIONES_H
#define CDETECTARTRANSICIONES_H

#include "CContourWithData.h"

#include<iostream>
#include<sstream>
using namespace std;
using namespace cv;

const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

/**
 * @brief
 * Clase para la dereccion de Transiciones a partir de images.xml y classification.xml
 * Ambos sacados de GenerarClasificador. Proceso de Aprendizaje
 */
class CDetectarTransiciones {
private:
    /// Imagen actual a detectar Transiciones
    Mat imagenTransicionActual_;

    /// Vector con los contornos encontrados,
    vector<CContourWithData> contornosEncontrados_;
    /// Vector con las letras encontradas, emparejado con contorno
    vector<char> letrasEncontradas_;
public:
    /**
     * @brief
     * Constructor Vacio
     */
    CDetectarTransiciones();

    /**
     * @brief
     * Metodo que busca las transiciones en una imagen
     * @param image Imagen a detectar
     * @return Imagen resultado de la deteccion
     */
    bool ejecutar(Mat image, int opcion);

    /**
     * @brief
     * Metodo que devuelve la imagen actual
     * @return Mat
     */
    Mat getImagenTransicionActual();
    /**
     * @brief
     * Metodo que asigna una imagen nueva a la imagen a detectar
     * @param image. Nueva imagen
     */
    void setImagenTransicionActual(Mat image);

    /**
     * @brief
     * Metodo que devuelve los contornos encontrados en la imagen
     * @return vector<CContourWithData>
     */
    vector<CContourWithData>& getContornosEncontrados();
    /**
     * @brief
     * Metodo que devuelve las letras encontradas en la imagen. Emparejado con los contornos
     * @return vector<CContourWithData>
     */
    vector<char>& getLetrasEncontradas();
};

#endif // CDETECTARTRANSICIONES_H
