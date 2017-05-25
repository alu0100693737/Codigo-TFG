#include "CDetectarCirculos.h"

CDetectarCirculo::CDetectarCirculo() {
}

Mat CDetectarCirculo::iniciarDeteccion(Mat imagen) {
    //Escala de grises
    Mat src_gray;
    cvtColor(imagen, src_gray, COLOR_BGR2GRAY );

    //Reducción de ruido para la deteccion de circulos
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
    circles = detectarCirculos(src_gray, CANNYTHRESHOLD, ACCUMULATORTHRESHOLD); //canny entre 26 y 118, acumulator 45

    cout << "Hay " << getCirculosDetectados().size() << " circulos en la imagen"<< endl;
    //Dibujamos circulos sobre la imagen original
    for( size_t i = 0; i < getCirculosDetectados().size(); i++ ) {

        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //x y
        int radius = cvRound(circles[i][2]);
        //cout << "Circulo num " << i << " con centro (" << center.x << ", " << center.y << " y radio " << radius << endl;
        //punto central
        circle( imagen, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( imagen, center, radius, Scalar(0,0,255), 3, 8, 0 );

        //Dibujamos el num del circulo en la imagen
        stringstream ss;
        ss << i;
        string text = ss.str();
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        int thickness = 2;
        cv::putText(imagen, text, Point(center.x - radius/2, center.y + radius/2), fontFace, fontScale, Scalar::all(255), thickness,8);
    }

    //imshow("HOLA", imagen);
    return imagen;
}

vector<Vec3f> CDetectarCirculo::detectarCirculos(const Mat& src_gray, int cannyThreshold, int accumulatorThreshold) {
    // resultados de la deteccion de circulos
    vector<Vec3f> circl; // posicion (x y) y radio

    /*
     * Aplicamos la transformada de Hought para la deteccion de circulos
     * Recordar, metodo HOUGH_Gradient, el unico que esta implementado actualmente
     * 1, misma resolucion
     * src_gray.rows/8 distancia minima entre los circulos
     * cannyThreshold umbral mas alto
     * umbral de acumulacion. Los circulos que corresponden a los mayores valores del acumuladorr se devolveran primero
    */
    HoughCircles( src_gray, circl, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold);

    //cout << "circulos es " << circl.size() << endl;
    return filtrarCirculos(circl);
}

vector<Vec3f> CDetectarCirculo::filtrarCirculos(vector<Vec3f> circulos) {
    double radioMedio = 0;
    for(int i = 0; i < circulos.size(); i++) {
        // cout << "Radio actual " << circulos[i][2] << endl;
        radioMedio += circulos[i][2]; //2 Radios
    }
    radioMedio /= circulos.size();


    //cout << "El radio medio es " << radioMedio << " " << (radioMedio * 1.8) << endl;
    cout << "Numero de circulos " << circulos.size() << endl;

    for(int i = 0; i < circulos.size(); i++) {
        if(circulos[i][2] > (radioMedio * 1.8)) {
            circulos.erase(circulos.begin() + i);
            cout << "Warning: Se elimino un circulo concreto, controle el tamaño de ellos uniformemente, puede dar problemas" << endl;
            i--;
        }
    }
    return circulos;
}



//distancia euclidea entre dos puntos
/*
int CDetectarAutomata::distanciaEuclidea(Point a, Point b) {
    //cout << a << " , " << b;
    //cout << " resultado " << sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) << endl;
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
*/
vector<Vec3f> CDetectarCirculo::getCirculosDetectados() {
    return circles;
}


