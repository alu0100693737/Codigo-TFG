#include "COperacionesImagen.h"

COperacionesImagen::COperacionesImagen() {
    filtros_ = new CFiltrosImagenes();
    circulos_ = new CDetectarCirculo();
    lineas_   =  new CDetectarLineas();
    transiciones_ = new CDetectarTransiciones();
}

COperacionesImagen::~COperacionesImagen() {}

Mat COperacionesImagen::calcularHistograma(Mat imagen) {
    //Separa la imagen en Azul, Verde y Rojo ( B, G y R )
    vector<Mat> bgr_planes;
    split(imagen, bgr_planes);

    /// Establish the number of bins
    int histSize = 256;

    /// Rango de colores ( for B,G,R) )
    float range[] = { 0, 256 };
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    //Calcula el histograma para los 3 canales de color
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Formato del Histograma
    int hist_w = 256; int hist_h = 128;
    int bin_w = cvRound((double)hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    //Normaliza el histograma [0, histImage.rows ]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    //Dibuja la linea correspondiente para cada canal de color
    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
             Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
             Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
             Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
             Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
             Scalar(0, 0, 255), 2, 8, 0);
    }
    return histImage;
}

//Se hace una copia de Mat
//stackoverflow.com/questions/17127762/cvmat-to-qimage-and-back
QImage COperacionesImagen::Mat2QImage(cv::Mat const& src) {
    Mat temp;
    cvtColor(src, temp,CV_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

Mat COperacionesImagen::QImage2Mat(QImage const& src) {
    Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cvtColor(tmp, result,CV_BGR2RGB);
    return result;
}

Point COperacionesImagen::puntoMedio(Point a, Point b) {
    //cout << "Los puntos son " << a.x << ", " << a.y << "  " << b.x << ", " << b.y << endl;
    Point aux((a.x + b.x)/ 2, (a.y + b.y)/2);
    //cout << aux;
    return aux;
}

CFiltrosImagenes* COperacionesImagen::aplicarFiltro() {
    return filtros_;
}

CDetectarCirculo* COperacionesImagen::detectarCirculos() {
    return circulos_;
}

CDetectarLineas* COperacionesImagen::detectarLineas() {
    return lineas_;
}

CDetectarTransiciones* COperacionesImagen::detectarTransiciones() {
    return transiciones_;
}

void COperacionesImagen::codificarDeteccion(string nodoInicial, string nodosFinales) {
    vector<Point> transitions;

    vector<Point> auxpuntosMedios;
    //Si se ha hecho la deteccion
    if(!detectarCirculos()->getCirculosDetectados().empty() && !detectarLineas()->getLineasDetectadas().empty() && !detectarTransiciones()->getContornosEncontrados().empty() && !detectarTransiciones()->getLetrasEncontradas().empty()) {
        cout << " CIRCULOS Y LINEAS " << endl;

        //Confirmamos el numero de nodos

        int aux = detectarCirculos()->getCirculosDetectados().size();
        if (ventanaConfirmarNodos(aux)) { //numero de nodos confirmados, miramos ahora las lineas
            //cout << " el numero de lineas detectadas es " << getLineasDetectadas().size() << endl;
            //calculamos punto medio entre los circulos que tienen una transicion para descubrir posteriornente su letra correspondiente
            for(int i = 0; i < detectarLineas()->getLineasDetectadas().size(); i++)
                //cout << " linea num " << i << " con coordenadas " << getLineasDetectadas().at(i) << endl;
                for(int j = 0; j < detectarCirculos()->getCirculosDetectados().size(); j++)
                    if(detectarLineas()->distanciaEuclidea(detectarLineas()->getLineasDetectadas()[i][0], detectarCirculos()->getCirculosDetectados()[j][0]) < (100 + detectarCirculos()->getCirculosDetectados()[j][2]))
                        if(detectarLineas()->distanciaEuclidea(detectarLineas()->getLineasDetectadas()[i][1], detectarCirculos()->getCirculosDetectados()[j][1]) < (100 + detectarCirculos()->getCirculosDetectados()[j][2]))
                            //cout << "Encontrada una cercania de salida entre linea" << i << " y circulo " << j << endl;
                            for(int k = 0; k < detectarCirculos()->getCirculosDetectados().size(); k++)
                                if (k != j)
                                    if(detectarLineas()->distanciaEuclidea(detectarLineas()->getLineasDetectadas()[i][2], detectarCirculos()->getCirculosDetectados()[k][0]) < (100 + detectarCirculos()->getCirculosDetectados()[k][2]))
                                        if(detectarLineas()->distanciaEuclidea(detectarLineas()->getLineasDetectadas()[i][3], detectarCirculos()->getCirculosDetectados()[k][1]) < (100 + detectarCirculos()->getCirculosDetectados()[k][2])) {
                                            if(!contain(transitions, Point(j, k))) {
                                                transitions.push_back(Point(j,k));
                                                cout << " hay una transicion entre circulos " << j << " y " << k << endl;
                                                auxpuntosMedios.push_back(
                                                            puntoMedio(
                                                                Point(detectarCirculos()->getCirculosDetectados()[j][0], detectarCirculos()->getCirculosDetectados()[j][1]),
                                                        Point(detectarCirculos()->getCirculosDetectados()[k][0], detectarCirculos()->getCirculosDetectados()[k][1])
                                                        )
                                                        );
                                            }
                                            //calculamos punto medio entre los circulos que tienen una transicion para descubrir posteriornente su letra correspondiente
                                            //cout << "Encontrada una cercania de entrada entre linea" << i << " y circulo " << k << endl;
                                        }
        } else
            cout << "Num de nodos no coincidente" << endl;


        //Para las transiciones que hemos encontrado, hacemos la busqueda de letras o
        //numeros. en el punto medio de la linea por cercania
        //TENIENDO LAS LETRAS, POSICION VALOR Y PUNTO MEDIO ENTRE LAS TRANSICIONES, FALTA ASIGNAR
        if(transitions.size()) {

            ofstream fs("/home/ivan/Documentos/Codigo-TFG/codificaciones/codificacion.txt");

            // Enviamos una cadena al fichero de salida:
            fs << detectarCirculos()->getCirculosDetectados().size() << endl;
            fs << nodoInicial << endl;
            fs << nodosFinales << endl;

            // Cerrar el fichero,
            // para luego poder abrirlo para lectura:

            for(int i = 0; i < transitions.size(); i++) {
                //cout << "Punto medio " << transitions.at(i) << " " << auxpuntosMedios.at(i) << endl;
                for(int k = 0; k < detectarTransiciones()->getContornosEncontrados().size(); k++) {
                    if(detectarLineas()->distanciaEuclidea(auxpuntosMedios[i].x, detectarTransiciones()->getContornosEncontrados()[k].dimensionContorno.x) < 70) {
                        if(detectarLineas()->distanciaEuclidea(auxpuntosMedios[i].y, detectarTransiciones()->getContornosEncontrados()[k].dimensionContorno.y) < 60) {
                            cout << "Transicion numero " << i << " " << transitions.at(i) << endl;
                            cout << "Punto medio " << transitions.at(i) << " " << auxpuntosMedios.at(i) << endl;
                            cout << "Entornos encontrados " << detectarTransiciones()->getContornosEncontrados()[k].dimensionContorno.x  << "  " << detectarTransiciones()->getContornosEncontrados()[k].dimensionContorno.y << endl;
                            cout << "Letra: " << detectarTransiciones()->getLetrasEncontradas()[k] << endl;

                            fs << transitions.at(i).x << " " << transitions.at(i).y << " " << detectarTransiciones()->getLetrasEncontradas()[k] << endl;
                            detectarTransiciones()->getContornosEncontrados().erase(detectarTransiciones()->getContornosEncontrados().begin() + k);
                            detectarTransiciones()->getLetrasEncontradas().erase(detectarTransiciones()->getLetrasEncontradas().begin() + k);
                            k--;
                            break;
                        } else {
                            cout << "Punto medio " << transitions.at(i) << " " << auxpuntosMedios.at(i) << endl;
                            cout << "fallo" << endl;
                        }
                    }
                }
            }

            //calculamos transiciones al mismo nodo
            cout << "Quedan " << detectarTransiciones()->getContornosEncontrados().size() << " Transiciones por mirar" << endl;
            for(int i = 0; i < detectarTransiciones()->getContornosEncontrados().size(); i++) {
                cout << "Contorno " << i << " " << detectarTransiciones()->getContornosEncontrados()[i].dimensionContorno << endl;
            }

            for(int i = 0; i < detectarTransiciones()->getContornosEncontrados().size(); i++) {
                for(int j = 0; j < detectarCirculos()->getCirculosDetectados().size(); j++) {
                    if(detectarLineas()->distanciaEuclidea(detectarTransiciones()->getContornosEncontrados()[i].dimensionContorno.x, detectarCirculos()->getCirculosDetectados()[j][0]) < 30)
                        if((detectarLineas()->distanciaEuclidea(detectarTransiciones()->getContornosEncontrados()[i].dimensionContorno.y, detectarCirculos()->getCirculosDetectados()[j][1]) < 140) && (detectarLineas()->distanciaEuclidea(detectarTransiciones()->getContornosEncontrados()[i].dimensionContorno.y, detectarCirculos()->getCirculosDetectados()[j][1] > 20))) {
                            cout << " contorno " << detectarTransiciones()->getContornosEncontrados()[i].dimensionContorno << endl;
                            cout << "Transicion a si mismo del nodo " << j << " con letra " << detectarTransiciones()->getLetrasEncontradas()[i] << endl;
                            fs << j << " " << j << " " << detectarTransiciones()->getLetrasEncontradas()[i] << endl;
                            detectarTransiciones()->getContornosEncontrados().erase(detectarTransiciones()->getContornosEncontrados().begin() + i);
                            detectarTransiciones()->getLetrasEncontradas().erase(detectarTransiciones()->getLetrasEncontradas().begin() + i);
                            i--;
                            break;
                        }
                }
            }


            //calculamos transiciones cuando no se detecta la linea
            //cambiar los puntos medios, calcular todos los posibles NO SE PUEDE OCUPA MUCHA MEMORIA
            /*for(int i = 0; i < detectarTransiciones()->getContornosEncontrados().size(); i++) {
                for(int j = 0; j < detectarCirculos()->getCirculosDetectados().size(); j++) {
                    if(detectarLineas()->distanciaEuclidea(auxpuntosMedios[j].x, detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno.x) < 80) {
                        if(detectarLineas()->distanciaEuclidea(auxpuntosMedios[j].y, detectarTransiciones()->getContornosEncontrados().at(i).dimensionContorno.y) < 80) {
                            fs << j << " " << j << " " << detectarTransiciones()->getLetrasEncontradas()[i] << endl;
                            detectarTransiciones()->getContornosEncontrados().erase(detectarTransiciones()->getContornosEncontrados().begin() + i);
                            detectarTransiciones()->getLetrasEncontradas().erase(detectarTransiciones()->getLetrasEncontradas().begin() + i);
                            cout << "·Cuidado" << endl;
                    }
                }}}*/
            fs.close();


        } else {
            cout << "ERROR, hubo un problema con la deteccion de transiciones entre circulos y lineas" << endl;
        }

    } else
        cout << " ERROR, no se ha detectado la imagen previamente" << endl;
}

bool COperacionesImagen::ventanaConfirmarNodos(int nodos) {
    QString text = QString::number(nodos);
    //cout << text.toStdString() << endl;
    bool ok;

    text = QInputDialog::getText(0, "Codificacion",
                                 "El autómata tiene los siguientes nodos:", QLineEdit::Normal,
                                 text, &ok);
    if(text.isEmpty())
        return false;
    return ok;
}

//devuelve si un punto esta dentoro del vector
bool COperacionesImagen::contain(vector<Point> aux, Point a) {
    bool contiene = false;
    for(int i = 0; i < aux.size(); i++) {
        if(aux[i] == a) {
            contiene = true;
            break;
        }
    }
    return contiene;
}

/*
Ptr<ml::TrainData> COperacionesImagen::prepararDatosEntrenamiento(const Mat& data, const Mat& responses, int ntrain_samples) {
    Mat sample_idx = Mat::zeros(1, data.rows, CV_8U);
    Mat train_samples = sample_idx.colRange(0, ntrain_samples);
    train_samples.setTo(Scalar::all(1));
    int nvars = data.cols;
    Mat var_type(nvars + 1, 1, CV_8U);
    var_type.setTo(Scalar::all(ml::VAR_ORDERED));
    var_type.at<uchar>(nvars) = ml::VAR_CATEGORICAL;

    return ml::TrainData::create(data, ml::ROW_SAMPLE, responses, noArray(), sample_idx, noArray(), var_type);
}

//3 imagenes para el entrenamiento
void COperacionesImagen::entrenamiento(char* imagenes[2]) {
    char* nombre_clases[2] = { "Circulo", "Linea" };
    vector<vector<Point>> contours;  //mirar contornos encontrados
    double area, perimetro; //area y perimetro de los contornos encontrados
    Mat imagen, imagen_bin; //imagen original y procesada
    Mat train_data(NENTRE, 2, CV_32FC1);
    Mat response_data(NENTRE, 2, CV_32FC1);
    Mat test_data(1, 2, CV_32FC1);
    Mat test_data_2(1, 2, CV_32FC1);
    Mat clasif(1, 1, CV_32FC1);
    int k = 0; int Nc = 0;

    //Clasificador de Bayes
    Ptr<ml::NormalBayesClassifier> bayes = ml::NormalBayesClassifier::create();


    cout << "Ejemplos para el entrenamiento " << endl;
    //cargamos y buscamos contornos
    for (int clase = 0; clase < 3; ++clase) {
        imagen = imread(imagenes[clase]);
        if (!imagen.data) {
            cerr << "Error al cargar la imagen numero: " << clase << endl;
        }

        imagen_bin = Mat(imagen.size(), CV_8UC1, 1);
        cvtColor(imagen, imagen, CV_BGR2GRAY);
        threshold(imagen, imagen_bin, 128, 255, CV_THRESH_BINARY);
        mostrarImagen(imagen_bin);

        findContours(imagen_bin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
        Nc = contours.size();
        cout << "El numero total de " << imagenes[clase] << " es " << Nc << endl;

        for (size_t idx = 0; idx < contours.size(); idx++) {
            area = contourArea(contours[idx], false);
            perimetro = arcLength(contours[idx], 1);
            train_data.at<float>(k, 0) = perimetro;
            train_data.at<float>(k, 1) = area;
            response_data.at<float>(k) = clase;
            k++;
        }
        cvWaitKey(0);
    }

    int ntrain_samples = (int)(Nc * 0.9);
    Ptr<ml::TrainData> tdata = prepararDatosEntrenamiento(train_data, response_data, ntrain_samples);

    bayes->train(tdata);
    //prueba
    cout << "Llegue hasta aqui" << endl;
    imagen = imread("grafo1.jpg");
    imagen_bin = Mat(imagen.size(), 8, 1);

    cvtColor(imagen, imagen, CV_BGR2GRAY);
    threshold(imagen, imagen_bin, 128, 255, CV_THRESH_BINARY);
    Mat imagen_color = Mat(imagen.size(), CV_8UC1, 3);

    cvtColor(imagen, imagen_color, CV_GRAY2BGR);
    imshow("Ventana", imagen_color);
    findContours(imagen_bin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    Nc = contours.size();
    cout << endl << "El numero total de piezas a clasificar es : " << Nc << endl;

    for (size_t idx = 0; idx < contours.size(); idx++) {
        area = contourArea(contours[idx], false);
        perimetro = arcLength(contours[idx], false);
        test_data_2.at<float>(0, 0) = perimetro;
        test_data_2.at<float>(0, 1) = area;
        //prediccion
        clasif.at<float>(idx) = bayes->predict(test_data_2);
        cvtColor(imagen, imagen_color, CV_GRAY2BGR);
        Scalar color_rojo(0, 0, 255);
        drawContours(imagen_color, contours, idx, color_rojo, 2);
        imshow("ventana", imagen_color);
        cout << "La pieza resaltada es un " << nombre_clases[(int)clasif.at<float>(idx)] << endl;
        waitKey(0);
    }
}  

void COperacionesImagen::clasificacion(string img) {
    Mat image3n = imread("img");
    Mat imagen_bin = Mat(imagen.size(), 8, 1);

    cvtColor(imagen, imagen, CV_BGR2GRAY);
    threshold(imagen, imagen_bin, 128, 255, CV_THRESH_BINARY);
    Mat imagen_color = Mat(imagen.size(), CV_8UC1, 3);

    cvtColor(imagen, imagen_color, CV_GRAY2BGR);
    imshow("Ventana", imagen_color);
    findContours(imagen_bin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
}*/
