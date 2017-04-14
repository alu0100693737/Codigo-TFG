#pragma once
#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "CFiltrosImagenes.h"
#include "CDetectarAutomata.h"
#include <QImage>

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
    CDetectarAutomata* detector_;
public:
    COperacionesImagen();
	~COperacionesImagen();
    Mat calcularHistograma(Mat imagen);
    QImage Mat2QImage(Mat const& src);
    Mat QImage2Mat(QImage const & src);

    CFiltrosImagenes* aplicarFiltro();// get filtros_
    CDetectarAutomata* detectarAutomata(); //get funciones deteccion
    /*
	//reconocerPatrones
	static Ptr<ml::TrainData> prepararDatosEntrenamiento(const Mat& data, const Mat& responses, int ntrain_samples);
	void entrenamiento(char* imagenes[2]);
    //void clasificacion(string imagen);*/
};
