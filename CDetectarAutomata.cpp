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

    cout << "Hay " << circles.size() << " circulos en la imagen"<< endl;
    //Dibujamos circulos sobre la imagen original
    for( size_t i = 0; i < circles.size(); i++ ) {

        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //x y
        int radius = cvRound(circles[i][2]);
        cout << "Circulo num " << i << " con centro (" << center.x << ", " << center.y << " y radio " << radius << endl;
        //punto central
        circle( imagen, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( imagen, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    //Dibujamos lineas sobre la imagen original
    for( size_t i = 0; i < lineasEncontradas.size(); i++ ) {
        Vec4i l = lineasEncontradas[i];
        line( imagen, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        cout << "linea numero " << i << endl;
       cout << " inicio " << l[0] << " , " << l[1] << " " << l[2] << " , " << l[3] << endl;
        imshow("HOLA", imagen);
        waitKey(0);


    }

    imshow("HOLA", imagen);
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
    //p_lines guarda xstart y start x end y end
    for(int i = 0; i < p_lines.size(); i++) {
        cout << "Linea " << i << " con datos " << p_lines.at(i) << endl;
    }
    cout << "Lineas " << p_lines.size() << endl;
    filtrarLineas(p_lines);
    //imshow("probabilistic", probabilistic_hough);
    return p_lines; //datos de la deteccion de lineas
}

vector<Vec4i> CDetectarAutomata::filtrarLineas(vector<Vec4i>& lineas) {
    vector<Vec4i> lineasFinales;
    vector<int> candidatos;
    candidatos.push_back(0);
    lineasFinales.push_back(lineas.at(0));
    int contador = lineas.size();
    cout << "Hay estas lineas al principio " << contador << endl;
    for(int k = 0; k < 4; k++) {
    for(int i = 0; i < lineas.size() - 1; i++) {
        if(distanciaEuclidea(lineas[i][k], lineas[i + 1][k]) < 10) {
                cout << "cuidado" << endl;
                lineas.erase(lineas.begin() + (i + 1));
                cout << "Lineas ahora tiene " << lineas.size() << " elementos" << endl;


                contador--;
            }
        if(distanciaEuclidea(lineas[i][k + 1], lineas[i +1][k + 1]) < 10) {
            cout << "cuidado" << endl;
            lineas.erase(lineas.begin() + (i + 1));
            cout << "Lineas ahora tiene " << lineas.size() << " elementos" << endl;
            contador--;
        }

    } k += 1;
    }
    cout << "Realmente hay " << contador << " lineas" << endl;
    return lineas;
}

int CDetectarAutomata::distanciaEuclidea(int a, int b) {
    cout << a << " , " << b;
    cout << " resultado " << sqrt(pow(a - b, 2)) << endl;
    return sqrt(pow(a - b, 2));
}

