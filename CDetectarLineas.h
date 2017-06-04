////////////////////////////////////////////////////////////////////////////
//          CDetectarLineas.h - Declaración de la clase CDetectarLineas   //
//                                                                        //
//               Autor: Iván García Campos                                //
//                                                                        //
//            Proyecto de Trabajo Fin de Grado.                           //
//                                                                        //
//               Fecha: 05/06/2017                                        //
////////////////////////////////////////////////////////////////////////////

#ifndef CDETECTARLINEAS_H
#define CDETECTARLINEAS_H
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
#define DISTANCIAPIXELPRINCIPAL 10
#define DISTANCIAPIXELSECUNDARIO 30

class CDetectarLineas {
private:
    vector<Vec4i> lineasEncontradas;

    //Lineas
    vector<Vec4i> detectarLineas(const Mat& src_gray, int houghprobabilistico);
    vector<Vec4i> HoughProbabilistico(Mat, int, void*, int houghprobabilistico);

    //filtra linea por cercania y por duplicidad de principio a fin
    vector<Vec4i> filtrarLineas(vector<Vec4i>& lineas);
public:
    CDetectarLineas();
    Mat iniciarDeteccion(Mat imagen, int houghprobabilistico);

    vector<Vec4i> getLineasDetectadas();


    int distanciaEuclidea(int a, int b);
    int distanciaEuclidea(int a, int b, bool mostrar);
    int distanciaEuclidea(Point a, Point b);
};

#endif // CDETECTARLINEAS_H
