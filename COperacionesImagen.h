#pragma once
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "CFiltrosImagenes.h"

//#include "opencv/ml.h"
//reconocimiento de patrones
/*#define NCLASE1 3
#define NCLASE2 4
#define NCLASE3 13
#define NENTRE (NCLASE1 + NCLASE2 + NCLASE3)
*/

using namespace cv;
using namespace std;

class COperacionesImagen {
private:
    CFiltrosImagenes* filtros_;
public:
    COperacionesImagen();
	~COperacionesImagen();
    Mat calcularHistograma(Mat imagen);
    CFiltrosImagenes* aplicarFiltro();// get filtros_
    /*
	//reconocerPatrones
	static Ptr<ml::TrainData> prepararDatosEntrenamiento(const Mat& data, const Mat& responses, int ntrain_samples);
	void entrenamiento(char* imagenes[2]);
    //void clasificacion(string imagen);*/
};
