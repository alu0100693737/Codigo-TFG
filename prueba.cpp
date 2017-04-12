/*
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/ml.h>
#include <iostream>
#include "COperacionesImagen.h"
#include<vector>


//--Clasificación
#define NCLASE1 11//8
#define NCLASE2 13//9
#define NENTRE (NCLASE1+NCLASE2)

using namespace cv;
using namespace std;

static Ptr<ml::TrainData>
//Convertir los datos de una matriz al tipo TrainData
prepare_train_data(const Mat& data, const Mat& responses, int ntrain_samples)
{
	Mat sample_idx = Mat::zeros(1, data.rows, CV_8U);
	Mat train_samples = sample_idx.colRange(0, ntrain_samples);
	train_samples.setTo(Scalar::all(1));

	int nvars = data.cols;
	Mat var_type(nvars + 1, 1, CV_8U);
	var_type.setTo(Scalar::all(ml::VAR_ORDERED));
	var_type.at<uchar>(nvars) = ml::VAR_CATEGORICAL;

	return ml::TrainData::create(data, ml::ROW_SAMPLE, responses,
		noArray(), sample_idx, noArray(), var_type);
}

int main() {
	

	//Histograma
	/// Load image
    String imageName("/home/ivan/TFG/grafoReal1.png"); // by default
    Mat a = imread(imageName);
    COperacionesImagen* p = new COperacionesImagen();
    imshow("Ejemplos", p->calcularHistograma(a));
    waitKey(0);
    cout << "UES" << endl;
}

	//Deteccion clasificador de bayes

	Mat imagen, imagen_bin, imagen_color;
	vector<vector<Point> > contours;

	int i = 0, clase, k = 0;
	double perimetro, area;
	char *nombre_clases[2] = { "Circulo", "Linea" };

	// 1) entrenamiento
	//char *imagenes[2] = { "circulos.jpg", "lineas1.jpg" };
	char *imagenes[2] = { "Clase1.jpg", "Clase2.jpg" };
	for (int i = 0; i < 2; i++) {
		Mat aux = imread(imagenes[i]);
		imshow("Ejemplos", aux);
	}

	//Creacion del clasificador de Bayes
	Ptr<ml::NormalBayesClassifier> bayes = ml::NormalBayesClassifier::create();

	// creación de imatrices para almacenar la imformación
	Mat train_data(NENTRE, 2, CV_32FC1);
	Mat response_data(NENTRE, 1, CV_32FC1);
	Mat test_data(NENTRE, 2, CV_32FC1);
	Mat	test_data_2(1, 2, CV_32FC1);

	cout << "Ejemplos para el entrenamiento" << endl << endl;

	for (clase = 0; clase < 2; ++clase) {
		imagen = imread(imagenes[clase]);
		if (!imagen.data) {
			cout << "Error al cargar la imagen" << endl;
			return 1;
		}
		imagen_bin = Mat(imagen.size(), CV_8UC1, 1);
		cvtColor(imagen, imagen, CV_BGR2GRAY);
		threshold(imagen, imagen_bin, 128, 255, CV_THRESH_BINARY);

		namedWindow("Ventana", 1);
		imshow("Ventana", imagen_bin);

		findContours(imagen_bin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		cout << "El numero total de " << nombre_clases[clase] << "s es " << contours.size() << endl;
		for (int i = 0; i < contours.size(); i++) {
			Scalar color1(255, 0, 0);
			drawContours(imagen_bin, contours, i, color1, 2, 8, CV_RETR_LIST, 0, Point());
		}

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

	int ntrain_samples = (int)(NENTRE);
	Ptr<ml::TrainData> tdata = prepare_train_data(train_data, response_data, ntrain_samples);
	bayes->train(tdata);

	
	// 2) prueba
	//imagen = imread("grafo1.jpg", 1);
	imagen = imread("clasif.jpg", 1);
	imagen_bin = Mat(imagen.size(), 8, 1);
	cvtColor(imagen, imagen, CV_BGR2GRAY);
	threshold(imagen, imagen_bin, 128, 255, CV_THRESH_BINARY);

	imagen_color = Mat(imagen.size(), CV_8UC1, 3);
	cvtColor(imagen, imagen_color, CV_GRAY2BGR);
	imshow("Pepe", imagen_color);

	findContours(imagen_bin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	cout << endl << "El numero total de piezas a clasificar es: " << contours.size() << endl;

	Mat clasif(contours.size(), 1, CV_32FC1);
	for (size_t idx = 0; idx < contours.size(); idx++) {
		area = contourArea(contours[idx], false);
		perimetro = arcLength(contours[idx], 1);

		test_data_2.at<float>(0, 0) = perimetro;
		test_data_2.at<float>(0, 1) = area;

		clasif.at<float>(idx) = bayes->predict(test_data_2);

		cvtColor(imagen, imagen_color, CV_GRAY2BGR);
		Scalar color_rojo(0, 0, 255);
		drawContours(imagen_color, contours, idx, color_rojo, 2);
		imshow("Ventana", imagen_color);
		cout << "La pieza resaltada es un " << nombre_clases[(int)clasif.at<float>(idx)] << endl;
		waitKey(0);
	}

	return 0;
}
//CANNY HoughLines y HoughCircles
*
* @function calcHist_Demo.cpp
* @brief Demo code to use the function calcHist
* @author

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "COperacionesImagen.h"

using namespace std;
using namespace cv;


* @function main
*
int main(int argc, char** argv) {

	Mat src;

	/// Load image
	String imageName("grafo.jpg"); // by default

	//COperacionesImagen* p = new COperacionesImagen(imageName);
	//char* imagenes[2] = { "circulo.jpg", "linea1.jpg" };

    //p->calcularHistograma();

	src = imread(imageName, 0);
	cout << "YESS" << endl;

	//Canny
	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3); //Deteccion bordes imagen
	cvtColor(dst, cdst, CV_GRAY2BGR); //Deteccion de los bordes de la imagen
	vector<Vec4i> lines; //Vector para almacenar las lineas detectadas

						 //Deteccion de las lineas de la imagen Hough probabilistico
						 //Cuidado con el ultimo parametro maxLineGap. Estudiar en profundidad
	HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 20);

	//Pintar las lineas de la imagen
	for (size_t i = 0; i < lines.size(); i++) {
		line(cdst, Point(lines[i][0], lines[i][1]),
			Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
	}

	//Detect circles with HoughCircles
	vector<Vec3f> circles;
	//Aplicacion de la Transformada de Hough para localizar circulos
	HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1, src.rows / 8, 100, 75, 0, 0);
	//Dibujo de los circulos localizados
	for (size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//centro del circulo
		circle(cdst, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		//borde del circulo
		circle(cdst, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	imshow("source1", src);
	cout << "El numero de lines encontradas es: " << lines.size() << endl;
	cout << "El numero de circulos encontrados es: " << circles.size() << endl;

	imshow("detected lines", cdst);

	waitKey(0);
	
	return 0;
}*/

	
