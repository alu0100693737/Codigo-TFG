#include "CDetectarTransiciones.h"

CDetectarTransiciones::CDetectarTransiciones() {
}


Mat CDetectarTransiciones::getImagenTransicionActual() {
    return imagenTransicionActual_;
}

void CDetectarTransiciones::setImagenTransicionActual(Mat image) {
    if(!image.empty())
        imagenTransicionActual_ = image;
    else
        cout << "error en SetImagenTransicionActual" << endl;
}

vector<ContourWithData>& CDetectarTransiciones::getContornosEncontrados() {
    return contornosEncontrados_;
}

vector<char>& CDetectarTransiciones::getLetrasEncontradas() {
    return letrasEncontradas_;
}

bool CDetectarTransiciones::ejecutar(Mat image) {

    //Leemos la imagen a detectar, el clasificador.xml y image.xml
    if(image.empty()) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    getContornosEncontrados().clear();
    getLetrasEncontradas().clear();


    //Leemos la clasificacion hecha sobre GenerarClasificador
    vector<ContourWithData> allContoursWithData;           // declare empty vectors,
    vector<ContourWithData> validContoursWithData;         // we will fill these shortly

    Mat matClassificationInts;      // we will read the classification numbers into this variable as though it is a vector

    FileStorage fsClassifications("/home/ivan/Documentos/Codigo-TFG/training/classifications.xml", cv::FileStorage::READ);

    if (fsClassifications.isOpened() == false) {
        std::cout << "error, unable to open training classifications file, exiting program\n\n";
        return(0);
    }

    fsClassifications["classifications"] >> matClassificationInts;     //Guardamos en matClassificationInts
    fsClassifications.release();

    //Leemos las imagenes resultantes del entrenamiento

    Mat matTrainingImagesAsFlattenedFloats;         // we will read multiple images into this single image variable as though it is a vector

    FileStorage fsTrainingImages("/home/ivan/Documentos/Codigo-TFG/training/images.xml", cv::FileStorage::READ);

    if (fsTrainingImages.isOpened() == false) {
        std::cout << "error, unable to open training images file, exiting program\n\n";
        return(0);
    }

    fsTrainingImages["images"] >> matTrainingImagesAsFlattenedFloats;           // Guardamos en matTrainingImagesAsFlattenedFloats
    fsTrainingImages.release();


    /*/////////////////////////////////////////////////*/

    cv::Ptr<cv::ml::KNearest>  kNearest(cv::ml::KNearest::create());            // instantiate the KNN object

    // finally we get to the call to train, note that both parameters have to be of type Mat (a single Mat)
    // even though in reality they are multiple images / numbers
    kNearest->train(matTrainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, matClassificationInts);

    // test ///////////////////////////////////////////////////////////////////////////////

    Mat matTestingNumbers = image;
    //cv::imread("/home/ivan/Documentos/Codigo-TFG/images/GrafoconLetras.png");            // read in the test numbers image


    //cv::Laplacian(matTestingNumbers, matTestingNumbers, -1);
    if (matTestingNumbers.empty()) {
        cout << "error: image not read from file\n\n";
        return(0);
    }

    Mat matGrayscale; Mat matBlurred; Mat matThresh; Mat matThreshCopy;

    cvtColor(matTestingNumbers, matGrayscale, CV_BGR2GRAY);         // imagen Escala de Grises
    matBlurred = matGrayscale;

    //Suavizado Gaussiano
    GaussianBlur(matGrayscale,
                 matBlurred,
                 cv::Size(5, 5),            // smoothing window width and height in pixels
                 0);                        // sigma value, determines how much the image will be blurred, zero makes function choose the sigma value


    // filtro de escala de grises a blanco y negro
    adaptiveThreshold(matBlurred,
                      matThresh,
                      255,                                  // make pixels that pass the threshold full white
                      cv::ADAPTIVE_THRESH_GAUSSIAN_C,       // use gaussian rather than mean, seems to give better results
                      cv::THRESH_BINARY_INV,                // invert so foreground will be white, background will be black
                      11,                                   // size of a pixel neighborhood used to calculate threshold value
                      2);                                   // constant subtracted from the mean or weighted mean

    matThreshCopy = matThresh.clone();

    vector<vector<Point> > ptContours;        // declare a vector for the contours
    vector<cv::Vec4i> v4iHierarchy;                    // declare a vector for the hierarchy (we won't use this in this program but this may be helpful for reference)

    cv::findContours(matThreshCopy,             // input image, make sure to use a copy since the function will modify this image in the course of finding contours
                     ptContours,                             // output contours
                     v4iHierarchy,                           // output hierarchy
                     cv::RETR_EXTERNAL,                      // retrieve the outermost contours only
                     cv::CHAIN_APPROX_SIMPLE);               // compress horizontal, vertical, and diagonal segments and leave only their end points

    for (int i = 0; i < ptContours.size(); i++) {               // for each contour
        ContourWithData contourWithData;                                                    // instantiate a contour with data object
        contourWithData.ptContour = ptContours[i];                                          // assign contour to contour with data
        contourWithData.dimensionContorno = cv::boundingRect(contourWithData.ptContour);         // get the bounding rect
        contourWithData.fltArea = cv::contourArea(contourWithData.ptContour);               // calculate the contour area
        allContoursWithData.push_back(contourWithData);                                     // add contour with data object to list of all contours with data
    }

    for (int i = 0; i < allContoursWithData.size(); i++) {
        if (allContoursWithData[i].checkIfContourIsValid()) {                   //Si el contorno supera el area minimo, append
            validContoursWithData.push_back(allContoursWithData[i]);
        }
    }

    // Ordenamos de izquierda a derecha
    std::sort(validContoursWithData.begin(), validContoursWithData.end(), sortByBoundingRectXPosition);


    std::string strFinalString;

    //Detectamos elementos que guardamos en un string y dibujamos rectangulos al contorno
    for (int i = 0; i < validContoursWithData.size(); i++) {            // for each contour
        if(validContoursWithData[i].fltArea > 285) {
            validContoursWithData.erase(validContoursWithData.begin() + i);
            i--;
        } else{
            //cout << "Area " << validContoursWithData[i].fltArea  << endl;
            //cout << validContoursWithData[i].fltArea,// draw a green rect around the current char
            cv::rectangle(matTestingNumbers,                            // draw rectangle on original image
                          validContoursWithData[i].dimensionContorno,        // rect to draw
                          cv::Scalar(0, 255, 0),                        // green
                          2);                                           // thickness

            cv::Mat matROI = matThresh(validContoursWithData[i].dimensionContorno);          // get ROI image of bounding rect

            cv::Mat matROIResized;
            cv::resize(matROI, matROIResized, cv::Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));     // resize image, this will be more consistent for recognition and storage

            cv::Mat matROIFloat;
            matROIResized.convertTo(matROIFloat, CV_32FC1);             // convert Mat to float, necessary for call to find_nearest

            cv::Mat matROIFlattenedFloat = matROIFloat.reshape(1, 1);

            cv::Mat matCurrentChar(0, 0, CV_32F);

            kNearest->findNearest(matROIFlattenedFloat, 1, matCurrentChar);     // finally we can call find_nearest !!!

            float fltCurrentChar = (float)matCurrentChar.at<float>(0, 0);

            //Asignamos contorno y letra a contornosEncontrados
            getContornosEncontrados().push_back(ContourWithData(validContoursWithData[i]));
            getLetrasEncontradas().push_back( char(int(fltCurrentChar)));

            strFinalString = strFinalString + char(int(fltCurrentChar));
            //cv::imshow("matTestingNumbers", matTestingNumbers);
            //cv::waitKey(0);
            cout << "Encontrado " << strFinalString << endl;
            // append current char to full string
        }
    }

    cout << "\n\n" << "numbers read = " << strFinalString << "\n\n";       // show the full string
    cout << "Finalmente hay " << getContornosEncontrados().size() << " posibles contornos, analizaremos uno por uno " << endl;
    for(int i = 0; i < getContornosEncontrados().size(); i++) {
        getContornosEncontrados().at(i).mostrarContorno();
        cout << " Letra " << getLetrasEncontradas().at(i) << endl;
    }
    cout << getLetrasEncontradas().size() << endl;
    //imshow("Transiciones", matTestingNumbers);
    setImagenTransicionActual(matTestingNumbers);

}
