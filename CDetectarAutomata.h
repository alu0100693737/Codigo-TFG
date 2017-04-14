#ifndef CDETECTARAUTOMATA_H
#define CDETECTARAUTOMATA_H
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define CANNYTHRESHOLD 100
#define ACCUMULATORTHRESHOLD 45
//Para la deteccion, canny entre 26, 118 y acummulador 45
class CDetectarAutomata {
private:
    Mat detectarCirculos(const Mat& imagen_gray, const Mat& imagen, int cannyThreshold, int accumulatorThreshold);
    Mat detectarLineas();
public:
    CDetectarAutomata();
    Mat iniciarDeteccion(Mat imagen);
};

#endif // CDETECTARAUTOMATA_H

