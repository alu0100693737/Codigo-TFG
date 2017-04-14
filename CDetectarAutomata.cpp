#include "CDetectarAutomata.h"

CDetectarAutomata::CDetectarAutomata() {
}

Mat CDetectarAutomata::iniciarDeteccion(Mat imagen) {
    //Escala de grises
    Mat src_gray;
    cvtColor(imagen, src_gray, COLOR_BGR2GRAY );

    //Deteccion de lineas
    vector<Vec4i> lineasEncontradas = detectarLineas(imagen);

    //Reducción de ruido para la deteccion de circulos
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
    vector<Vec3f> circles = detectarCirculos(src_gray, CANNYTHRESHOLD, ACCUMULATORTHRESHOLD); //canny entre 26 y 118, acumulator 45

    //Dibujamos circulos sobre la imagen original
    for( size_t i = 0; i < circles.size(); i++ ) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //x y
        int radius = cvRound(circles[i][2]);
        //punto central
        circle( imagen, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( imagen, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    //Dibujamos lineas sobre la imagen original
    for( size_t i = 0; i < lineasEncontradas.size(); i++ ) {
         Vec4i l = lineasEncontradas[i];
         line( imagen, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
    }
    return imagen;
}

vector<Vec3f> CDetectarAutomata::detectarCirculos(const Mat& src_gray, int cannyThreshold, int accumulatorThreshold) {
    // resultados de la deteccion de circulos
    vector<Vec3f> circles; // posicion (x y) y radio

    /*
     * Aplicamos la transformada de Hought para la deteccion de circulos
     * Recordar, metodo HOUGH_Gradient, el unico que esta implementado actualmente
     * 1, misma resolucion
     * src_gray.rows/8 distancia minima entre los circulos
     * cannyThreshold umbral mas alto
     * umbral de acumulacion. Los circulos que corresponden a los mayores valores del acumuladorr se devolveran primero
    */
    HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold);

    //circles contiene los circulos detectados, punto radio y circunferencia
    return circles;
}


vector<Vec4i> CDetectarAutomata::detectarLineas(const Mat& src_gray) {
    Mat edges;
    /// Deteccion de bordes
    Canny( src_gray, edges, 50, 200, 3 );
    return HoughProbabilistico(edges, 0, 0);
}

vector<Vec4i> CDetectarAutomata::HoughProbabilistico(Mat edges, int, void*) {
  Mat probabilistic_hough;
  vector<Vec4i> p_lines;
  cvtColor(edges, probabilistic_hough, COLOR_GRAY2BGR );

  /// Usamos la transformada de Hough probabilistica
  HoughLinesP( edges, p_lines, 1, CV_PI/180, 70, 30, 10 ); //70

  //imshow("probabilistic", probabilistic_hough);
  return p_lines; //datos de la deteccion de lineas
}
