#ifndef CDETECTARAUTOMATA_H
#define CDETECTARAUTOMATA_H
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

#define CANNYTHRESHOLD 60
#define ACCUMULATORTHRESHOLD 42
#define RANGO 50
//Para la deteccion, canny entre 26, 118 y acummulador 45
class CDetectarAutomata {
private:

    vector<Vec3f> circles;
    vector<Vec4i> lineasEncontradas;

    //Metodos
    //Circulos
    vector<Vec3f> detectarCirculos(const Mat& imagen_gray, int cannyThreshold, int accumulatorThreshold);

    //Lineas
    vector<Vec4i> detectarLineas(const Mat& src_gray);
    vector<Vec4i> HoughProbabilistico(Mat, int, void*);
    vector<Vec4i> filtrarLineas(vector<Vec4i>& lineas);

    int distanciaEuclidea(int a, int b);
    int distanciaEuclidea(Point a, Point b);

    bool ventanaConfirmarNodos(int nodos, QString text);

public:
    CDetectarAutomata();

    Mat iniciarDeteccion(Mat imagen);

     void codificarDeteccion();

    vector<Vec3f> getCirculosDetectados();
    vector<Vec4i> getLineasDetectadas();


};

#endif // CDETECTARAUTOMATA_H

