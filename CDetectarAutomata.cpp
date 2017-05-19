#include "CDetectarAutomata.h"

CDetectarAutomata::CDetectarAutomata() {
}

Mat CDetectarAutomata::iniciarDeteccion(Mat imagen) {
    //Escala de grises
    Mat src_gray;
    cvtColor(imagen, src_gray, COLOR_BGR2GRAY );

    //Deteccion de lineas
    lineasEncontradas = detectarLineas(imagen);

    //Reducción de ruido para la deteccion de circulos
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
    circles = detectarCirculos(src_gray, CANNYTHRESHOLD, ACCUMULATORTHRESHOLD); //canny entre 26 y 118, acumulator 45

    cout << "Hay " << getCirculosDetectados().size() << " circulos en la imagen"<< endl;
    //Dibujamos circulos sobre la imagen original
    for( size_t i = 0; i < getCirculosDetectados().size(); i++ ) {

        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); //x y
        int radius = cvRound(circles[i][2]);
        cout << "Circulo num " << i << " con centro (" << center.x << ", " << center.y << " y radio " << radius << endl;
        //punto central
        circle( imagen, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //circunferencia
        circle( imagen, center, radius, Scalar(0,0,255), 3, 8, 0 );
        stringstream ss;
        ss << i;
        string text = ss.str();


        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;
        int thickness = 2;
        cv::putText(imagen, text, Point(center.x - radius/2, center.y + radius/2), fontFace, fontScale, Scalar::all(255), thickness,8);
    }
   // Mat imagenaux = imagen;
    //Dibujamos lineas sobre la imagen original
    for( size_t i = 0; i < getLineasDetectadas().size(); i++ ) {
        // Mat imagenaux = imagen;
        Vec4i l = getLineasDetectadas().at(i);
        line( imagen, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        cout << "linea numero " << i << endl;
        cout << " inicio " << l[0] << " , " << l[1] << " " << l[2] << " , " << l[3] << endl;
        imshow("HOLA", imagen);

        waitKey(0);

    }

    //imshow("HOLA", imagen);
    return imagen;
}

vector<Vec3f> CDetectarAutomata::detectarCirculos(const Mat& src_gray, int cannyThreshold, int accumulatorThreshold) {
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

    //circles contiene los circulos detectados, punto radio y circunferencia
    return circl;
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
    HoughLinesP( edges, p_lines, 1, CV_PI/180, 80, 30, 10 ); //70 cambiado a 80, longitudes mas largas
    //p_lines guarda xstart y start x end y end
    for(int i = 0; i < p_lines.size(); i++) {
        cout << "Linea " << i << " con datos " << p_lines.at(i) << endl;
    }
    cout << "Lineas " << p_lines.size() << endl;
    //filtrarLineas(p_lines);
    //imshow("probabilistic", probabilistic_hough);
    return p_lines; //datos de la deteccion de lineas
}

vector<Vec4i> CDetectarAutomata::filtrarLineas(vector<Vec4i>& lineas) {
    vector<Vec4i> lineasFinales;
    vector<int> candidatos;
    candidatos.push_back(0);
    lineasFinales.push_back(lineas.at(0));
   cout << "Hay " << lineas.size() << " lineas al principio" << endl;
    //for(int k = 0; k < 4; k++) {
    for(int i = 0; i < lineas.size() - 1; i++) {
        for(int j = i; j < lineas.size(); j++) {
            if(i != j) {
            //0 x1 1 y1 2 x2 3 y2
            //continuacion de lineas
            if(distanciaEuclidea(lineas[i][2], lineas[j][0]) < 20) {
                if(distanciaEuclidea(lineas[i][3], lineas[j][1]) < 35) {
                    //cout << "cuidado" << endl;
                    lineas.erase(lineas.begin() + (j));
                    j--;
                    //cout << "Lineas ahora tiene " << lineas.size() << " elementos" << endl;

                    //break;
                }
            } else if(distanciaEuclidea(lineas[i][3], lineas[j][1]) < 20) {
                if(distanciaEuclidea(lineas[i][2], lineas[j][0]) < 35) {
                    //cout << "cuidado" << endl;
                    lineas.erase(lineas.begin() + (j));
                    j--;
                    //cout << "Lineas ahora tiene " << lineas.size() << " elementos" << endl;

                }
            } else if(distanciaEuclidea(lineas[i][1], lineas[j][1]) < 10) {
                if(distanciaEuclidea(lineas[i][3], lineas[j][3]) < 10) {
                    cout << "Cuidaoo " <<  lineas[i] << " y " << lineas[j] << endl;
                    if(distanciaEuclidea(lineas[i][0], lineas[j][0]) < 30) {
                        if(distanciaEuclidea(lineas[i][2], lineas[j][2]) < 30) {
                    cout << lineas[i] << " y " << lineas[j] << endl;
                    cout << "lineas superpuestas " << i << " " << j << endl;
                    /*cout << "Lineas candidatas " << lineas[i][0] << " , " << lineas[j][0] << endl;
                    */int izquierda = min(lineas[i][0], lineas[j][0]);
                    cout << "Izquierda vale " << izquierda << endl;
                    //cout << "Lineas candidatas " << lineas[i][2] << " , " << lineas[j][2] << endl;
                    int derecha = max(lineas[i][2], lineas[j][2]);
                    cout << "derecha vale " << derecha << endl;
                    lineas.push_back(Vec4i(izquierda, lineas[i][1], derecha, lineas[i][3]));
                    cout << "EPALE " << lineas.at(lineas.size() - 1) << endl;
                    lineas.erase(lineas.begin() + (j));
                    lineas.erase(lineas.begin() + (i));
                    j--; i--;

}}
                }
            }
        }
        }
    }
    cout << "Realmente hay " << lineas.size() << " lineas" << endl;
    return lineas;
}

//distancia euclidea entre dos componentes pixels (x's || y's)
int CDetectarAutomata::distanciaEuclidea(int a, int b) {
    //cout << a << " , " << b;
    //cout << " resultado " << sqrt(pow(a - b, 2)) << endl;
    return sqrt(pow(a - b, 2));
}

//distancia euclidea entre dos puntos
int CDetectarAutomata::distanciaEuclidea(Point a, Point b) {
    //cout << a << " , " << b;
    //cout << " resultado " << sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) << endl;
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<Vec3f> CDetectarAutomata::getCirculosDetectados() {
    return circles;
}

vector<Vec4i> CDetectarAutomata::getLineasDetectadas() {
    return lineasEncontradas;
}

void CDetectarAutomata::codificarDeteccion() {

    //Si se ha hecho la deteccion
    if(!getCirculosDetectados().empty() && !getLineasDetectadas().empty()) {
        //Confirmamos el numero de nodos
        QString text;
        int aux = getCirculosDetectados().size();
        if (ventanaConfirmarNodos(aux, text)) {
            cout << "Miramos las lineas" << endl;

            cout << " el numero de circulos detectados es " << getCirculosDetectados().size() << endl;
            cout << " el numero de lineas detectadas es " << getLineasDetectadas().size() << endl;
            for(int i = 0; i < getLineasDetectadas().size(); i++) {
                //cout << " linea num " << i << " con coordenadas " << getLineasDetectadas().at(i) << endl;
                for(int j = 0; j < getCirculosDetectados().size(); j++) {
                    if(distanciaEuclidea(getLineasDetectadas()[i][0], getCirculosDetectados()[j][0]) < (100 + getCirculosDetectados()[j][2])) {
                        if(distanciaEuclidea(getLineasDetectadas()[i][1], getCirculosDetectados()[j][1]) < (100 + getCirculosDetectados()[j][2])) {
                            //cout << "Encontrada una cercania de salida entre linea" << i << " y circulo " << j << endl;
                            for(int k = 0; k < getCirculosDetectados().size(); k++) {
                                if (k!=j) {
                                    if(distanciaEuclidea(getLineasDetectadas()[i][2], getCirculosDetectados()[k][0]) < (100 + getCirculosDetectados()[k][2])) {
                                                        if(distanciaEuclidea(getLineasDetectadas()[i][3], getCirculosDetectados()[k][1]) < (100 + getCirculosDetectados()[k][2])) {
                                                            cout << " hay una transicion entre circulos " << j << " y " << k << endl;
                                                            //cout << "Encontrada una cercania de entrada entre linea" << i << " y circulo " << k << endl;
                                                         }
                                                    }
                                }

                            }

                        }
                    } /*else if(distanciaEuclidea(getLineasDetectadas()[i][2], getCirculosDetectados()[j][0]) < 60) {
                    if(distanciaEuclidea(getLineasDetectadas()[i][3], getCirculosDetectados()[j][1]) < 60) {
                        cout << "Encontrada una cercania de entrada entre linea" << i << " y circulo " << j << endl;
                     }
                }*/
                }
                        cout << getLineasDetectadas()[i][0] << endl;



            }




            /*QMessageBox::information (0, "The Age",
                                      QString("The age is %1").arg(QString::number(age)));
        */} else {
            cout << "Num de nodos no coincidente" << endl;
        }

    } else
        cout << " ERROR, no se ha detectado la imagen previamente" << endl;
}

bool CDetectarAutomata::ventanaConfirmarNodos(int nodos, QString text) {
    text = QString::number(nodos);
    //cout << text.toStdString() << endl;
    bool ok;

    text = QInputDialog::getText(0, "Codificacion",
                                 "El autómata tiene los siguientes nodos:", QLineEdit::Normal,
                                 text, &ok);
    if(text.isEmpty())
        return false;
    return ok;

}


