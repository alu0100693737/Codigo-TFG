//////////////////////////////////////////////////////////////////////
//CFiltrosImagenes.h - Implementacion de la clase CFiltrosImagenes  //
//                                                                  //
//               Autor: Iván García Campos                          //
//                                                                  //
//            Proyecto de Trabajo Fin de Grado.                     //
//                                                                  //
//               Fecha: 05/06/2017                                  //
//////////////////////////////////////////////////////////////////////

#include "CFiltrosImagenes.h"

CFiltrosImagenes::CFiltrosImagenes(){}

Mat CFiltrosImagenes::filtroGaussianBlur(Mat original) {
    ///Difumina reducciendo el ruido . Rapido pero preserva peor los bordes que el filtro de la Mediana (convolucion)
    Mat dst;
    GaussianBlur(original, dst, Size( 9, 9 ), 0, 0);
    return dst;
}

Mat CFiltrosImagenes::filtroMedianBlur(Mat original) {
    ///Difumina reducciendo el ruido preservando mejor los bordes que el filtro Gaussiano
    Mat dst;
    medianBlur(original, dst, 9);
    return dst;
}

Mat CFiltrosImagenes::filtroSobel(Mat original) {
    ///Busca mejorar la deteccion de bordes buscando cambios en la intensidad de gris a partir de la primera, segunda, tercera o mezcla de derivadas de la imagen
    Mat dst;
    Sobel(original, dst, -1, 1, 1);
    return dst;
}

Mat CFiltrosImagenes::filtroLaplacian(Mat original) {
    ///Destaca las regiones de cambio de intensidad rapida
    Mat dst;
    Laplacian(original, dst, -1);
    return dst;
}

void CFiltrosImagenes::pruebaFiltros() {
    String imageName("/home/ivan/TFG/grafoReal1.png"); // by default
    Mat aux = imread(imageName);

    imshow("Gaussian", filtroGaussianBlur(aux));
    imshow("Median", filtroMedianBlur(aux));
    imshow("Sobel", filtroSobel(aux));
    imshow("Laplacian", filtroLaplacian(aux));
}


