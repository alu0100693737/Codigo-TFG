#ifndef CDETECTARAUTOMATA_H
#define CDETECTARAUTOMATA_H
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

#define CANNYTHRESHOLD 60
#define ACCUMULATORTHRESHOLD 42
//Para la deteccion, canny entre 26, 118 y acummulador 45
class CDetectarAutomata {
private:
    //Circulos
    vector<Vec3f> detectarCirculos(const Mat& imagen_gray, int cannyThreshold, int accumulatorThreshold);

    //Lineas
    vector<Vec4i> detectarLineas(const Mat& src_gray);
    vector<Vec4i> HoughProbabilistico(Mat, int, void*);
    vector<Vec4i> filtrarLineas(vector<Vec4i>& lineas);

    int distanciaEuclidea(int a, int b);
public:
    CDetectarAutomata();

    Mat iniciarDeteccion(Mat imagen);
};

#endif // CDETECTARAUTOMATA_H

