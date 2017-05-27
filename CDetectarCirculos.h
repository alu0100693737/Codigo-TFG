#ifndef CDETECTARCIRCULOS_H
#define CDETECTARCIRCULOS_H
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

//Para la deteccion, canny entre 26, 118 y acummulador 45
class CDetectarCirculo {
private:

    vector<Vec3f> circles;

    vector<Vec3f> detectarCirculos(const Mat& imagen_gray, int cannyThreshold, int accumulatorThreshold);

    //filtra circulos con dimensiones extrañas
    vector<Vec3f> filtrarCirculos(vector<Vec3f> circulos);

public:
    CDetectarCirculo();

    Mat iniciarDeteccion(Mat imagen, int cannythreshold, int accumulatorthreshold);

    vector<Vec3f> getCirculosDetectados();
};

#endif // CDETECTARAUTOMATA_H

