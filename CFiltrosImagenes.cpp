#include "CFiltrosImagenes.h"

CFiltrosImagenes::CFiltrosImagenes(){}

Mat CFiltrosImagenes::filtroGaussianBlur(Mat original) {
    Mat dst;
    GaussianBlur(original, dst, Size( 9, 9 ), 0, 0);
    return dst;
}

Mat CFiltrosImagenes::filtroMedianBlur(Mat original) {
    Mat dst;
    medianBlur(original, dst, 9);
    return dst;
}

Mat CFiltrosImagenes::filtroSobel(Mat original) {
    Mat dst;
    Sobel(original, dst, -1, 1, 1);
    return dst;
}

Mat CFiltrosImagenes::filtroLaplacian(Mat original) {
    Mat dst;
    Laplacian(original, dst, -1);
    return dst;
}
