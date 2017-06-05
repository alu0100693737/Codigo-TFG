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

class COperacionesImagen {
private:
    CFiltrosImagenes* filtros_;

    CDetectarCirculo* circulos_;
    CDetectarLineas* lineas_;
    CDetectarTransiciones* transiciones_;

    //utilizado en codificarDeteccion
    bool ventanaConfirmarNodos(int nodos);
    CAsistenteCodificacion* asistente_;

public:
    COperacionesImagen();
	~COperacionesImagen();

    CFiltrosImagenes* aplicarFiltro();// get filtros_

    CDetectarCirculo* detectarCirculos(); //get funciones deteccion
    CDetectarLineas* detectarLineas();
    CDetectarTransiciones* detectarTransiciones();

    CAsistenteCodificacion* getAsistente();

    void codificarDeteccion(string nodoInicial, string nodosFinales);
    bool contain(vector<Point> aux, Point a);

    Mat calcularHistograma(Mat imagen);
    QImage Mat2QImage(Mat const& src);
    Mat QImage2Mat(QImage const & src);

    Point puntoMedio(Point a, Point b);
    /*
	//reconocerPatrones
	static Ptr<ml::TrainData> prepararDatosEntrenamiento(const Mat& data, const Mat& responses, int ntrain_samples);
	void entrenamiento(char* imagenes[2]);
    //void clasificacion(string imagen);*/
};

#endif
