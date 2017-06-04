//////////////////////////////////////////////////////////////////
//CFiltrosImagenes.h - Declaración de la clase CFiltrosImagenes //
//                                                              //
//               Autor: Iván García Campos                      //
//                                                              //
//            Proyecto de Trabajo Fin de Grado.                 //
//                                                              //
//               Fecha: 05/06/2017                              //
//////////////////////////////////////////////////////////////////

#ifndef CFILTROSIMAGENES_H
#define CFILTROSIMAGENES_H
#include "opencv2/imgcodecs.hpp" //MAT OPENCV
#include "opencv2/imgproc.hpp"    //FILTROS
#include "opencv2/highgui.hpp"    //Prueba de los filtros, imshow
using namespace cv;

class CFiltrosImagenes {
public:
    CFiltrosImagenes();
    Mat filtroGaussianBlur(Mat original);
    Mat filtroMedianBlur(Mat original);
    Mat filtroSobel(Mat original);
    Mat filtroLaplacian(Mat original);

    void pruebaFiltros();
};

#endif // CFILTROSIMAGENES_H
