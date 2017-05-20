#ifndef CDETECTARTRANSICIONES_H
#define CDETECTARTRANSICIONES_H

#include "CContourWithData.h"

#include<iostream>
#include<sstream>
using namespace std;
using namespace cv;

const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

class CDetectarTransiciones {
private:
    Mat imagenTransicionActual_;

    //datos parejos por posicion
    vector<ContourWithData> contornosEncontrados_;
    vector<char> letrasEncontradas_;
public:
    CDetectarTransiciones();
    bool ejecutar(Mat image);
    Mat getImagenTransicionActual();
    void setImagenTransicionActual(Mat image);

    //Contorno, area y letra correspondiente
    vector<ContourWithData>& getContornosEncontrados();
    vector<char>& getLetrasEncontradas();
};

#endif // CDETECTARTRANSICIONES_H
