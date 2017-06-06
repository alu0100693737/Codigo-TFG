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
#define DISTANCIAPIXELSECUNDARIOLINEAS 30

/**
 * @brief
 * Clase para la deteccion de Lineas
 * Valor por defecto para la deteccion, houghLinesP 80
 */
class CDetectarLineas {
private:
    /**
     * @brief
     * Vector Vec4i de lineas detectadas
     * Estructura x1y1  x2y2
     */
    vector<Vec4i> lineasEncontradas;

    /**
     * @brief
     * Metodo que detecta Lineas en una imagen
     * @param src_gray. Imagen en escala de grises
     * @param houghprobabilistico. Variable deteccion de lineas. Por defecto 80
     * @return Lineas encontradas
     */
    vector<Vec4i> detectarLineas(const Mat& src_gray, int houghprobabilistico);

    /**
     * @brief
     * Metodo para la deteccion de Lineas
     * @param houghprobabilistico. Valor variable deteccion de lineas
     * @return
     */
    vector<Vec4i> HoughProbabilistico(Mat, int, void*, int houghprobabilistico);

    /**
     * @brief
     * Metodo que filtra lineas extrañas por cercania y duplicidad de principio a fin
     * @param lineas a filtrar
     * @return lineas filtradas
     */
    vector<Vec4i> filtrarLineas(vector<Vec4i>& lineas);
public:
    /**
     * @brief
     * Constructor Vacio
     */
    CDetectarLineas();
    /**
     * @brief
     * Metodo que inicia la deteccion de lineas en la imagen
     * @param imagen
     * @param houghprobabilistico. Valor de la variable para la deteccion de lineas
     * @return Imagen resultado de la deteccion
     */
    Mat iniciarDeteccion(Mat imagen, int houghprobabilistico);

    /**
     * @brief
     * Metodo que devuelve el conjunto de lineas detectadas en la imagen
     * @return vector<Vec4i>
     */
    vector<Vec4i> getLineasDetectadas();


    /**
     * @brief
     * Metodo que devuelve la distancia euclidiana entre dos numeros
     * @param a. Numero a
     * @param b. Numero b
     * @return distancia euclidiana
     */
    int distanciaEuclidea(int a, int b);
    /**
     * @brief
     * Metodo que devuelve la distancia euclidiana entre dos numeros
     * @param a. Numero a
     * @param b. Numero b
     * @param bool mostrar Std resultado
     * @return distancia euclidiana
     */
    int distanciaEuclidea(int a, int b, bool mostrar);
    /**
     * @brief
     * Metodo que devuelve la distancia euclidiana entre dos Puntos
     * @param a. Punto a
     * @param b. Punto b
     * @return distancia euclidiana
     */
    int distanciaEuclidea(Point a, Point b);
};

#endif // CDETECTARLINEAS_H
