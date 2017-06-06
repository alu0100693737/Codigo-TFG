////////////////////////////////////////////////////////////////////////////
//      CDetectarCirculos.h - Declaración de la clase CDetectarCirculos   //
//                                                                        //
//               Autor: Iván García Campos                                //
//                                                                        //
//            Proyecto de Trabajo Fin de Grado.                           //
//                                                                        //
//               Fecha: 05/06/2017                                        //
////////////////////////////////////////////////////////////////////////////

#ifndef CDETECTARCIRCULOS_H
#define CDETECTARCIRCULOS_H
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include <iostream>
#include <cmath>
#include <QtWidgets>
#include <QMessageBox>
#include <QInputDialog>
using namespace std;
using namespace cv;

/**
 * @brief
 * Clase para la deteccion de Circulos
 * Valores por defecto para la deteccion, canny entre 26, 118 y acummulador 45
 */
class CDetectarCirculo {
private:
    /**
     * @brief
     * Vector Vec3f de circulos encontrados
     * Estructura pos(x, y) y radio
     */
    vector<Vec3f> circles;

    /**
     * @brief
     * Metodo que detecta Circulos en una imagen
     * @param imagen_gray. Imagen en escala de grises
     * @param cannyThreshold. Primera Variable deteccion de Circulos
     * @param accumulatorThreshold. Segunda Variable deteccion de Circulos
     * @return Circulos encontrados
    */
    vector<Vec3f> detectarCirculos(const Mat& imagen_gray, int cannyThreshold, int accumulatorThreshold);

    /**
     * @brief
     * Metodo que filtra circulos con dimensiones extrañas, demasiado grandes
     * @param circulos. Conjunto de circulos
     * @return. Circulos Filtrados
     */
    vector<Vec3f> filtrarCirculos(vector<Vec3f> circulos);

public:
    /**
     * @brief
     * Constructor Vacio
     */
    CDetectarCirculo();

    /**
     * @brief
     * Metodo que inicia la deteccion de Circulos
     * @param imagen. Imagen
     * @param cannythreshold. Primera Variable deteccion de Circulos
     * @param accumulatorthreshold. Segunda Variable deteccion de Circulos.
     * @return Imagen resultado de la deteccion
     */
    Mat iniciarDeteccion(Mat imagen, int cannythreshold, int accumulatorthreshold);

    /**
     * @brief
     * Metodo que devuelve el conjunto de circulos detectados en la imagen
     * @return
     */
    vector<Vec3f> getCirculosDetectados();
};

#endif // CDETECTARAUTOMATA_H

