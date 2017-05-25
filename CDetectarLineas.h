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
#define DISTANCIAPIXELSECUNDARIO 100

class CDetectarLineas {
private:
    vector<Vec4i> lineasEncontradas;

    //Lineas
    vector<Vec4i> detectarLineas(const Mat& src_gray);
    vector<Vec4i> HoughProbabilistico(Mat, int, void*);

    //filtra linea por cercania y por duplicidad de principio a fin
    vector<Vec4i> filtrarLineas(vector<Vec4i>& lineas);
public:
    CDetectarLineas();
    Mat iniciarDeteccion(Mat imagen);

    vector<Vec4i> getLineasDetectadas();


    int distanciaEuclidea(int a, int b);
    int distanciaEuclidea(int a, int b, bool mostrar);
    int distanciaEuclidea(Point a, Point b);
};

#endif // CDETECTARLINEAS_H
