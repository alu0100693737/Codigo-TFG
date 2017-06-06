//////////////////////////////////////////////////////////////////////
//COperacionesImagen.h - Declaración de la clase COperacionesImagen //
//                                                                  //
//               Autor: Iván García Campos                          //
//                                                                  //
//            Proyecto de Trabajo Fin de Grado.                     //
//                                                                  //
//               Fecha: 05/06/2017                                  //
//////////////////////////////////////////////////////////////////////

#ifndef COPERACIONESIMAGEN_H
#define COPERACIONESIMAGEN_H
#pragma once
#include <iostream>
#include <fstream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "CFiltrosImagenes.h"
#include "CDetectarCirculos.h"
#include "CDetectarLineas.h"
#include "CDetectarTransiciones.h"
#include "CAsistenteCodificacion.h"
#include <QImage>

#define DISTANCIAPIXELSECUNDARIO 100
#define CONTORNOMEDIOLETRA 30

using namespace cv;
using namespace std;

/**
 * @brief
 * Clase que contiene CFiltrosImagenes, CDetectarCirculo, CDetectarLineas, CDetectarTransiciones
 * y CAsistenteCodificacion
 * Encargada de unificar todas las operaciones sobre imagenes
 */
class COperacionesImagen {
private:
    /**
     * @brief
     * Atributo de la clase CFiltrosImagenes para aplicar filtros a la imagen
     */
    CFiltrosImagenes* filtros_;

    /**
     * @brief
     * Atributo de la clase CDetectarCirculos para la deteccion de circulos en la imagen
     */
    CDetectarCirculo* circulos_;
    /**
     * @brief
     * Atributo de la clase CDetectarLineas para la deteccion de lineas en la imagen
     */
    CDetectarLineas* lineas_;
    /**
     * @brief
     * Atributo de la clase CDetectarTransiciones para la deteccion de transiciones en la imagen
     */
    CDetectarTransiciones* transiciones_;

    /**
     * @brief
     * Metodo para confirmar el numero de nodos cuando se quiera codificar o procesar la imagen.
     * Utilizado en codificarDeteccion
     * @param nodos. Num de nodos
     * @return
     */
    bool ventanaConfirmarNodos(int nodos);

    /**
     * @brief
     * Atributo de la clase CAsistenteCodificacion para la confirmacion del automata detectado en la imagen
     */
    CAsistenteCodificacion* asistente_;

public:
    /**
     * @brief
     * Constructor. Inicializa valores
     */
    COperacionesImagen();

    /**
      * @brief
      * Destructor Vacio
      */
    ~COperacionesImagen();

    /**
     * @brief
     * Metodo que devuelve el atributo filtros
     * @return CFiltrosImagenes
     */
    CFiltrosImagenes* aplicarFiltro();// get filtros_

    /**
     * @brief
     * Metodo que devuelve el atributo circulos
     * @return
     */
    CDetectarCirculo* detectarCirculos();
    /**
     * @brief
     * Metodo que devuelve el atributo lineas
     * @return
     */
    CDetectarLineas* detectarLineas();
    /**
     * @brief
     * Metodo que devuelve el atributo transiciones
     * @return
     */
    CDetectarTransiciones* detectarTransiciones();

    /**
     * @brief
     * Metodo que devuelve el atributo asistente
     * @return
     */
    CAsistenteCodificacion* getAsistente();

    /**
     * @brief
     * Metodo que codifica la deteccion del automata de la imagen
     * @param nodoInicial
     * @param nodosFinales
     */
    void codificarDeteccion(string nodoInicial, string nodosFinales);

    /**
     * @brief
     * Metodo que determina si un tenerminado punto se encuentra en un vector de
     * puntos
     * @param aux. Vector de puntos
     * @param a. Punto
     * @return bool
     */
    bool contain(vector<Point> aux, Point a);

    /**
     * @brief
     * Metodo que calcula el histograma de una determinada imagen
     * @param imagen. Imagen
     * @return Mat Imagen del histograma
     */
    Mat calcularHistograma(Mat imagen);
    /**
     * @brief
     * Metodo que transforma una imagen en formato Mat a QImage
     * @param src Mat Imagen
     * @return QImage Imagen
     */
    QImage Mat2QImage(Mat const& src);
    /**
     * @brief
     * Metodo que transforma  una imagen en formato QImage a formato Mat
     * @param src QImage imagen
     * @return Mat Imagen
     */
    Mat QImage2Mat(QImage const & src);

    /**
     * @brief
     * Metodo que devuelve el punto medio entre dos puntos
     * Utilizado en la codificacion
     * @param a. Punto a
     * @param b. Punto b
     * @return Punto medio
     */
    Point puntoMedio(Point a, Point b);
    /*
    //reconocerPatrones
    static Ptr<ml::TrainData> prepararDatosEntrenamiento(const Mat& data, const Mat& responses, int ntrain_samples);
    void entrenamiento(char* imagenes[2]);
    //void clasificacion(string imagen);*/
};

#endif
