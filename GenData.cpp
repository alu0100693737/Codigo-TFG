// GenData.cpp
/*
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>

#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

//variables globales
const int MIN_CONTOUR_AREA = 80;

const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

int main() {

    Mat imgTrainingNumbers;         // imagen de entrada

    //Preprocesamiento
    Mat imgGrayscale;               //
    Mat imgBlurred;                 // declare various images
    Mat imgThresh;                  //
    Mat imgThreshCopy;              //

    vector<vector<Point> > ptContours;        // declare contours vector
    vector<Vec4i> v4iHierarchy;                    // declare contours hierarchy

    Mat matClassificationInts;      // these are our training classifications, note we will have to perform some conversions before writing to file later

                                // these are our training images, due to the data types that the KNN object KNearest requires, we have to declare a single Mat,
                                // then append to it as though it's a vector, also we will have to perform some conversions before writing to file later
    Mat matTrainingImagesAsFlattenedFloats;

    //Caracteres en los que estamos interesados
    vector<int> intValidChars = { '0', '1', '2', 'a', 'b', 'c', 'f'};

    //mostrando codificacion
    //for(int i = 0; i < intValidChars.size(); i++) {
    //    cout << intValidChars.at(i) << endl;
    //}

    //Leemos la imagen de entreno
    imgTrainingNumbers = imread("/home/ivan/Documentos/pruebaNumeros/training.png");          // read in training numbers image

    if (imgTrainingNumbers.empty()) {
        std::cout << "error: image not read from file\n\n";
        return(0);
    }

    cvtColor(imgTrainingNumbers, imgGrayscale, CV_BGR2GRAY);        //Escala de grises

    //Suavizado
    GaussianBlur(imgGrayscale,              // input image
        imgBlurred,                             // output image
        cv::Size(5, 5),                         // smoothing window width and height in pixels
        0);                                     // sigma value, determines how much the image will be blurred, zero makes function choose the sigma value

    //Filtro para cambiar de escala de grises a blancos y negros
    adaptiveThreshold(imgBlurred,
        imgThresh,
        255,                                    // make pixels that pass the threshold full white
        cv::ADAPTIVE_THRESH_GAUSSIAN_C,         // use gaussian rather than mean, seems to give better results
        cv::THRESH_BINARY_INV,                  // invert so foreground will be white, background will be black
        11,                                     // size of a pixel neighborhood used to calculate threshold value
        2);                                     // constant subtracted from the mean or weighted mean

    //Mostramos imagen blanco y negro
    imshow("imgThresh", imgThresh);

    //findContours modifica la imagen, se hace una copia
    imgThreshCopy = imgThresh.clone();

    findContours(imgThreshCopy,
        ptContours,
        v4iHierarchy,
        RETR_EXTERNAL,                      // retrieve the outermost contours only
        CHAIN_APPROX_SIMPLE);               // compress horizontal, vertical, and diagonal segments and leave only their end points

    for (int i = 0; i < ptContours.size(); i++) {                           // for each contour
        if (contourArea(ptContours[i]) > MIN_CONTOUR_AREA) {                // Tamano minimo de area permitido
           Rect boundingRect = cv::boundingRect(ptContours[i]);                // Dibujamos rectangle alrededor del contorno, aplicamos tratamiento y guardamos opcion del usuario

            cv::rectangle(imgTrainingNumbers, boundingRect, cv::Scalar(0, 0, 255), 2);

            //Tratamiento Imagen
            Mat matROI = imgThresh(boundingRect);

            //Mayor consistencia en el reconocimiento y almacenaje
            Mat matROIResized;
            resize(matROI, matROIResized, cv::Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));

            //cv::imshow("matROI", matROI);
            cv::imshow("matROIResized", matROIResized);

            //imagen con rectangulos
            cv::imshow("imgTrainingNumbers", imgTrainingNumbers);

            //si es un caracter valido, se acepta
            int intChar = cv::waitKey(0);           // get key press
            cout << intChar  << endl;
            if (intChar == 27) {        // 27 == esc key
                return(0);
            } else if (std::find(intValidChars.begin(), intValidChars.end(), intChar) != intValidChars.end()) {     // else if the char is in the list of chars we are looking for . . .
                cout << "vale " << intChar << endl;
                matClassificationInts.push_back(intChar);       // append classification char to integer list of chars

                cv::Mat matImageFloat;                          // now add the training image (some conversion is necessary first) . . .
                matROIResized.convertTo(matImageFloat, CV_32FC1);       // convert Mat to float

                cv::Mat matImageFlattenedFloat = matImageFloat.reshape(1, 1);       // flatten

                matTrainingImagesAsFlattenedFloats.push_back(matImageFlattenedFloat);       // add to Mat as though it was a vector, this is necessary due to the                                                                                // data types that KNearest.train accepts
            }
        }
    }

    cout << "training complete\n\n";

    // se guarda la clasificacion creada

    FileStorage fsClassifications("/home/ivan/Documentos/pruebaNumeros/classifications.xml", cv::FileStorage::WRITE);           // open the classifications file

    if (fsClassifications.isOpened() == false) {                                                        // if the file was not opened successfully
        std::cout << "error, unable to open training classifications file, exiting program\n\n";        // show error message
        return(0);                                                                                      // and exit program
    }

    fsClassifications << "classifications" << matClassificationInts;        // write classifications into classifications section of classifications file
    fsClassifications.release();

    // se guardan las imagenes del entrenamiento

    FileStorage fsTrainingImages("/home/ivan/Documentos/pruebaNumeros/images.xml", cv::FileStorage::WRITE);

    if (fsTrainingImages.isOpened() == false) {
        cout << "error, unable to open training images file, exiting program\n\n";
        return(0);
    }

    fsTrainingImages << "images" << matTrainingImagesAsFlattenedFloats;         // write training images into images section of images file
    fsTrainingImages.release();

    return(0);
}*/
