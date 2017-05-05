#ifndef CONTOURWITHDATA_H
#define CONTOURWITHDATA_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
const int MIN_CONTOUR_AREA = 100;
using namespace cv;

class ContourWithData {
public:

    std::vector<cv::Point> ptContour;           // Contorno
    cv::Rect boundingRect;                      // Rectangulo
    float fltArea;                              // Area del contorno

    ContourWithData();
    //Identifica si el contorno cubre el area minima
    bool checkIfContourIsValid();
};

//Ordena los contornos por posicion coordenadas
static bool sortByBoundingRectXPosition(const ContourWithData& cwdLeft, const ContourWithData& cwdRight) {      // this function allows us to sort
    return(cwdLeft.boundingRect.x < cwdRight.boundingRect.x);                                                   // the contours from left to right
}


#endif // CONTOURWITHDATA_H
