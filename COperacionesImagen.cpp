#include "COperacionesImagen.h"

COperacionesImagen::COperacionesImagen(string nombre) {
	imagen = imread(nombre, IMREAD_COLOR);

	if (getImagen().empty()) {
		cerr << "Error cargando la imagen" << endl;
	}
}

COperacionesImagen::~COperacionesImagen() {}

Mat COperacionesImagen::getImagen() {
	return imagen;
}

void COperacionesImagen::mostrarImagen(Mat img) {
	namedWindow("Foto original", WINDOW_AUTOSIZE);
	imshow("Foto original", img);
	waitKey(0);
}

void COperacionesImagen::calcularHistograma() {
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(getImagen(), bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
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

	mostrarImagen(getImagen());
	mostrarImagen(histImage); //imagen histograma
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
/*
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
