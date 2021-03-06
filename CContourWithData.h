////////////////////////////////////////////////////////////////////////////
//      CContourWithData.h - Declaración de la clase CContourWithData     //
//                                                                        //
//               Autor: Iván García Campos                                //
//                                                                        //
//            Proyecto de Trabajo Fin de Grado.                           //
//                                                                        //
//               Fecha: 05/06/2017                                        //
////////////////////////////////////////////////////////////////////////////

#ifndef CCONTOURWITHDATA_H
#define CCONTOURWITHDATA_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include <iostream>
#define MIN_CONTOUR_AREA 100
using namespace std;
using namespace cv;

/**
 * @brief
 * Clase que guarda contornos encontrados con su contorno, dimension y Area
 */
class CContourWithData {
public:
    /// Contorno Detectado
    std::vector<cv::Point> ptContour;
    /// Rectangulo alrededor del Contorno
    cv::Rect dimensionContorno;
    /// Area del Contorno detectado
    float fltArea;

    /**
     * @brief
     * Constructor sin parametros. Vacio
     */
    CContourWithData();
    /**
     * @brief
     * Constructor copia
     * @param copy
     */
    CContourWithData(const CContourWithData& copy);

    /**
     * @brief
     * Identifica si el contorno cubre el area minima MIN_CONTOUR_AREA
     */
    bool checkIfContourIsValid();
    /**
     * @brief
     * Muestra los datos de la clase por Std
     */
    void mostrarContorno();
};

/**
 * @brief
 * Metodo estatico que ordena los contornos por posiciones coordenadas
 * Utilizado en CDetectarTransiciones
 * @param cwdLeft
 * @param cwdRight
 * @return Bool si param1 es menor que param2
 */
static bool sortByBoundingRectXPosition(const CContourWithData& cwdLeft, const CContourWithData& cwdRight) {      // this function allows us to sort
    return(cwdLeft.dimensionContorno.x < cwdRight.dimensionContorno.x);                                                   // the contours from left to right
}

#endif
