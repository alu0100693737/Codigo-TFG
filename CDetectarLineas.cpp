#include "CDetectarLineas.h"

CDetectarLineas::CDetectarLineas() {

}

Mat CDetectarLineas::iniciarDeteccion(Mat imagen, int houghprobabilistico) {
    //Deteccion de lineas
    lineasEncontradas = detectarLineas(imagen, houghprobabilistico);
    //cout << "Acabo de pescarla" << endl;
    //Dibujamos lineas sobre la imagen original
    for( size_t i = 0; i < getLineasDetectadas().size(); i++ ) {
        // Mat imagenaux = imagen;
        Vec4i l = getLineasDetectadas().at(i);
        line( imagen, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
        //cout << "linea numero " << i << endl;
        //cout << " inicio " << l[0] << " , " << l[1] << " " << l[2] << " , " << l[3] << endl;
        //imshow("HOLA", imagen);


        //waitKey(0);
    }
    return imagen;
}

vector<Vec4i> CDetectarLineas::detectarLineas(const Mat& src_gray, int houghprobabilistico) {
    Mat edges;

    // Deteccion de bordes
    Canny( src_gray, edges, 50, 200, 3 );

    //Deteccion de lineas
    return HoughProbabilistico(edges, 0, 0, houghprobabilistico);
}

vector<Vec4i> CDetectarLineas::HoughProbabilistico(Mat edges, int, void*, int houghprobabilistico) {
    Mat probabilistic_hough;
    vector<Vec4i> p_lines;
    cvtColor(edges, probabilistic_hough, COLOR_GRAY2BGR );

    /// Usamos la transformada de Hough probabilistica
    HoughLinesP( edges, p_lines, 1, CV_PI/180, houghprobabilistico, 30, 10 ); //70 cambiado a 80, longitudes mas largas
    //p_lines guarda xstart y start x end y end
    /*for(int i = 0; i < p_lines.size(); i++) {
        cout << "Linea " << i << " con datos " << p_lines.at(i) << endl;
    }*/
    cout << "Lineas detectadas inicialmente: " << p_lines.size() << endl;

    //filtramos las lineas, duplicaciones
    filtrarLineas(p_lines);

    //imshow("probabilistic", probabilistic_hough);
    return p_lines; //datos de la deteccion de lineas
}

vector<Vec4i> CDetectarLineas::filtrarLineas(vector<Vec4i>& lineas) {

    //for(int i = 0; i < lineas.size(); i++)
    //    cout << "Linea " << i << " " << lineas.at(i) << endl;
    for(int i = 0; i < lineas.size() - 1; i++) {
        for(int j = i + 1; j < lineas.size(); j++) {
            //if(i != j) {
            //0 x1 1 y1 2 x2 3 y2

            //continuacion de lineas en X
            if(distanciaEuclidea(lineas[i][2], lineas[j][0]) < DISTANCIAPIXELPRINCIPAL) {
                if(distanciaEuclidea(lineas[i][3], lineas[j][1]) < DISTANCIAPIXELSECUNDARIO) {
                    //cout << "cuidado" << endl;
                    cout << "Unificando lineas en X" << endl;
                    lineas.push_back(Vec4i(lineas[i][0], lineas[i][1], lineas[j][2], lineas[j][3]));
                    lineas.erase(lineas.begin() + (j));
                    lineas.erase(lineas.begin() + (i));
                    j = i + 1; //i avanza solo al eliminar 2 e introducir 1. Inicializamos j
                }
                //continuacion de lineas en Y
            } else if(distanciaEuclidea(lineas[i][3], lineas[j][1]) < DISTANCIAPIXELPRINCIPAL) {
                if(distanciaEuclidea(lineas[i][2], lineas[j][0]) < DISTANCIAPIXELSECUNDARIO) {
                    cout << "Unificando lineas en Y" << endl;
                    lineas.push_back(Vec4i(lineas[i][0], lineas[i][1], lineas[j][2], lineas[j][3]));
                    lineas.erase(lineas.begin() + (j));
                    lineas.erase(lineas.begin() + (i));
                    j = i + 1; //i avanza solo al eliminar 2 e introducir 1. Inicializamos j
                }
                //Lineas superpuestas completamente, falta las que son sublineas de una mayor
            } else if(distanciaEuclidea(lineas[i][1], lineas[j][1]) < DISTANCIAPIXELPRINCIPAL) { //Lineas superpuestas
                if(distanciaEuclidea(lineas[i][3], lineas[j][3]) < DISTANCIAPIXELPRINCIPAL) {
                    if(distanciaEuclidea(lineas[i][0], lineas[j][0]) < DISTANCIAPIXELSECUNDARIO) {
                        if(distanciaEuclidea(lineas[i][2], lineas[j][2]) < DISTANCIAPIXELSECUNDARIO) {
                            //cout << lineas[i] << " y " << lineas[j] << endl;
                            //cout << "lineas superpuestas " << i << " " << j << endl;
                            //cout << "Lineas candidatas " << lineas[i][0] << " , " << lineas[j][0] << endl;
                            int izquierda = min(lineas[i][0], lineas[j][0]);
                            //cout << "Izquierda vale " << izquierda << endl;
                            //cout << "Lineas candidatas " << lineas[i][2] << " , " << lineas[j][2] << endl;
                            int derecha = max(lineas[i][2], lineas[j][2]);
                            //cout << "derecha vale " << derecha << endl;
                            lineas.push_back(Vec4i(izquierda, lineas[i][1], derecha, lineas[i][3]));
                            //cout << "Nuevo nodo: " << lineas.at(lineas.size() - 1) << endl;
                            lineas.erase(lineas.begin() + (j));
                            lineas.erase(lineas.begin() + (i));
                            j = i + 1;
                        }
                    }
                }
            }

        }
    }
    cout << "Hay " << lineas.size() << " lineas despues de filtrar las lineas" << endl;
    return lineas;
}

//distancia euclidea entre dos componentes pixels (x's || y's)
int CDetectarLineas::distanciaEuclidea(int a, int b, bool mostrar) {
    if(mostrar == true) {
        cout << a << " , " << b;
        cout << " resultado " << sqrt(pow(a - b, 2)) << endl;
    }
    return sqrt(pow(a - b, 2));
}

int CDetectarLineas::distanciaEuclidea(int a, int b) {
    return sqrt(pow(a - b, 2));
}

vector<Vec4i> CDetectarLineas::getLineasDetectadas() {
    return lineasEncontradas;
}
