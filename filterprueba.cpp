//filtros basicos de imagen
/*
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Apply the filters
    Mat dst, dst2;
    GaussianBlur( src, dst, Size( 9, 9 ), 0, 0);
    medianBlur( src, dst2, 9);

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " GAUSSIAN BLUR ", WINDOW_AUTOSIZE );
    imshow( " GAUSSIAN BLUR ", dst );
    namedWindow( " MEDIAN BLUR ", WINDOW_AUTOSIZE );
    imshow( " MEDIAN BLUR ", dst2 );

    waitKey();
    return 0;
}

//libro Learning Image Processing with OpenCV

//realce de bordes, se parece a la invertida
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
    // Read the source file
    Mat src;
    src = imread(argv[1]);

    // Apply Sobel and Laplacian
    Mat dst, dst2;
    Sobel(src, dst, -1, 1, 1 );
    Laplacian(src, dst2, -1 );

    // Show the results
    namedWindow( " ORIGINAL ", WINDOW_AUTOSIZE );
    imshow( " ORIGINAL ", src );
    namedWindow( " SOBEL ", WINDOW_AUTOSIZE );
    imshow( " SOBEL ", dst );
    namedWindow( " LAPLACIAN ", WINDOW_AUTOSIZE );
    imshow( " LAPLACIAN ", dst2 );

    waitKey();
    return 0;
}*/
