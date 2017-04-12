#ifndef CFILTROSIMAGENES_H
#define CFILTROSIMAGENES_H
#include "opencv2/imgcodecs.hpp" //MAT OPENCV
#include "opencv2/imgproc.hpp"    //FILTROS
using namespace cv;

class CFiltrosImagenes {
public:
    CFiltrosImagenes();
    Mat filtroGaussianBlur(Mat original);
    Mat filtroMedianBlur(Mat original);
    Mat filtroSobel(Mat original);
    Mat filtroLaplacian(Mat original);
};

#endif // CFILTROSIMAGENES_H
