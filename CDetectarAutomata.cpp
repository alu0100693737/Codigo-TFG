#include "CDetectarAutomata.h"

CDetectarAutomata::CDetectarAutomata() {
}

Mat CDetectarAutomata::iniciarDeteccion(Mat imagen) {
    Mat src_gray;
    cvtColor(imagen, src_gray, COLOR_BGR2GRAY );
    //Reducción de ruido
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    return detectarCirculos(src_gray, imagen, CANNYTHRESHOLD, ACCUMULATORTHRESHOLD); //canny entre 26 y 118, acumulator 45
}

Mat CDetectarAutomata::detectarCirculos(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold) {
    // resultados de la deteccion de circulos
    std::vector<Vec3f> circles; // posicion (x y) y radio
    //Aplicamos la transformada de Hought para la deteccion de circulos
    //Recordar, metodo HOUGH_Gradient, el unico que esta implementado actualmente
    //1, misma resolucion
    //src_gray.rows/8 distancia minima entre los circulos
    //cannyThreshold umbral mas alto
    //umbral de acumulacion. Los circulos que corresponden a los mayores valores del acumuladorr se devolveran primero
    HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold);

    // Dibujamos sobre la imagen los circulos detectados, punto radio y circunferencia
    Mat display = src_display.clone();
    for( size_t i = 0; i < circles.size(); i++ ) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //x y
        int radius = cvRound(circles[i][2]);
        //punto central
        circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    return display;
}
