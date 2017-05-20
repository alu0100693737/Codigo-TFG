#pragma once
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "CFiltrosImagenes.h"
#include "CDetectarAutomata.h"
#include "CDetectarTransiciones.h"
#include <QImage>
#define DISTANCIAPIXELPRINCIPAL 10
#define DISTANCIAPIXELSECUNDARIO 100

using namespace cv;
using namespace std;

class COperacionesImagen {
private:
    CFiltrosImagenes* filtros_;

    CDetectarAutomata* detector_;
    CDetectarTransiciones* transiciones_;

    //utilizado en codificarDeteccion
    bool ventanaConfirmarNodos(int nodos, QString text);

public:
    COperacionesImagen();
	~COperacionesImagen();

    CFiltrosImagenes* aplicarFiltro();// get filtros_

    CDetectarAutomata* detectarAutomata(); //get funciones deteccion
    CDetectarTransiciones* detectarTransiciones();

    void codificarDeteccion();

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
