#include "CFiltrosImagenes.h"

CFiltrosImagenes::CFiltrosImagenes(){}

//Difumina imagen usando filtro Gaussiano, usado deteccion de circulos. Reduccion de ruido, Mas rapido que median (convolucion)
Mat CFiltrosImagenes::filtroGaussianBlur(Mat original) {
    Mat dst;
    GaussianBlur(original, dst, Size( 9, 9 ), 0, 0);
    return dst;
}

//Difumina imagen usando filtro de la mediana. Reduccion de ruido, preserva mejor los bordes
Mat CFiltrosImagenes::filtroMedianBlur(Mat original) {
    Mat dst;
    medianBlur(original, dst, 9);
    return dst;
}
//Busca mejorar la deteccion de bordes buscando los cambios de intensidad de gris a partir de la primesa, segunda, tercera o mezcla de derivadas de la imagen
Mat CFiltrosImagenes::filtroSobel(Mat original) {
    Mat dst;
    Sobel(original, dst, -1, 1, 1);
    return dst;
}

//Destaca las regiones de cambio de intensidad rapida. Usa la segunda derivada espacial de una imagen
Mat CFiltrosImagenes::filtroLaplacian(Mat original) {
    Mat dst;
    Laplacian(original, dst, -1);
    return dst;
}

void CFiltrosImagenes::pruebaFiltros() {
    String imageName("/home/ivan/TFG/grafoReal1.png"); // by default
    Mat aux = imread(imageName);

    imshow("Gaussian", filtroGaussianBlur(aux));
    imshow("Median", filtroMedianBlur(aux));
    imshow("Sobel", filtroSobel(aux));
    imshow("Laplacian", filtroLaplacian(aux));
}


