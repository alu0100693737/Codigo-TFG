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

/**
 * @brief
 * Clase con diferentes filtros para aplicar sobre imagenes
 */
class CFiltrosImagenes {
public:
    /**
     * @brief
     * Constructor Vacio
     */
    CFiltrosImagenes();
    /**
     * @brief
     * Metodo que aplica el filtro Gaussiano a una imagen
     * @param original. Imagen a aplicar el filtro
     * @return Mat Imagen modificada
     */
    Mat filtroGaussianBlur(Mat original);
    /**
     * @brief
     * Metodo que aplica el filtro de la Mediana a una imagen
     * @param original. Imagen a aplicar el filtro
     * @return Mat Imagen modificada
     */
    Mat filtroMedianBlur(Mat original);
    /**
     * @brief
     * Metodo que aplica el filtro Sobel a una imagen
     * @param original. Imagen a aplicar el filtro
     * @return Mat Imagen modificada
     */
    Mat filtroSobel(Mat original);
    /**
     * @brief
     * Metodo que aplica el filtro Laplaciano a una imagen
     * @param original. Imagen a aplicar el filtro
     * @return Mat Imagen modificada
     */
    Mat filtroLaplacian(Mat original);

    /**
     * @brief
     * Metodo para la prueba de filtros sobre una imagen
     */
    void pruebaFiltros();
};

#endif // CFILTROSIMAGENES_H
