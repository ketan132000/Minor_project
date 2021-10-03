#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{

    Mat inputimage = imread("C:/Users/DELL/Downloads/Test_Image.png", 0);
    if (inputimage.empty())
    {
        cout << "Image not found";
        exit(0);
    }
    string window1 = "Unprocessed";
    string window2 = "Sobel Edge Detector";
 
    namedWindow(window1);
    namedWindow(window2);


    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S; 
    Mat D_x, D_y;
    Mat abs_D_x, abs_D_y;
    Mat SobelOP;

 
    Sobel(inputimage, D_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT); 
    Sobel(inputimage, D_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT); 
    convertScaleAbs(D_x, abs_D_x); 
    convertScaleAbs(D_y, abs_D_y);

    addWeighted(abs_D_x, 0.5, abs_D_y, 0.5, 0, SobelOP); 


   
    imshow(window1, inputimage);
     imshow(window2, SobelOP);
   
    imwrite("SobelFinal_output.jpg", SobelOP);
 

    waitKey(0); 
    return 0;

    destroyWindow(window1);
    destroyWindow(window2);
}
