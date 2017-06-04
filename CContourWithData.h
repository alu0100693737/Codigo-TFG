////////////////////////////////////////////////////////////////////////////
//      CContourWithData.h - Declaración de la clase CContourWithData     //
//                                                                        //
//               Autor: Iván García Campos                                //
//                                                                        //
//            Proyecto de Trabajo Fin de Grado.                           //
//                                                                        //
//               Fecha: 05/06/2017                                        //
////////////////////////////////////////////////////////////////////////////

#ifndef CONTOURWITHDATA_H
#define CONTOURWITHDATA_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include <iostream>
#define MIN_CONTOUR_AREA 100
using namespace std;
using namespace cv;

class CContourWithData {
public:

    std::vector<cv::Point> ptContour;           // Contorno
    cv::Rect dimensionContorno;                      // Rectangulo
    float fltArea;                              // Area del contorno

    CContourWithData();
    CContourWithData(const CContourWithData& copy);

    //Identifica si el contorno cubre el area minima
    bool checkIfContourIsValid();
    void mostrarContorno();
};

//Ordena los contornos por posicion coordenadas
static bool sortByBoundingRectXPosition(const CContourWithData& cwdLeft, const CContourWithData& cwdRight) {      // this function allows us to sort
    return(cwdLeft.dimensionContorno.x < cwdRight.dimensionContorno.x);                                                   // the contours from left to right
}


#endif // CONTOURWITHDATA_H
