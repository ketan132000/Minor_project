#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    //read the image data, in the file in the mentioned location, in grayscale and store it in 'inputimage'
    Mat inputimage = imread("C:\\Users\\Gjay3\\Desktop\\Minor_project_final\\Test_image.jpg", 0);

    //Window name declaration
    string window1 = "Original image";
    string window2 = "Sobel Edge Detector";
    string window3 = "X-Deivative";
    string window4 = "Y-Derivative";

    //Sobel variable declaration
    int ddepth = CV_16S; //to avoid overflow
    Mat D_x_image, D_y_image;
    Mat abs_D_x_image, abs_D_y_image;
    Mat SobelOP;

    //check whether the image is loaded or not
    if (inputimage.empty())
    {
        cout << "Error : Image cannot be loaded..!!";
        system("pause"); //wait for a key press
        return -1;
    }

    //Creating windows with corresponding names
    namedWindow(window1); //create a window with the name "Unprocessed image"
    namedWindow(window2); //create a window with the name "Sobel Edge Detector"
    namedWindow(window3); //create a window with the name "X-derivative"
    namedWindow(window4); //create a window with the name "Y-derivative"

    //SOBEL EDGE DETECTION

    Sobel(inputimage, D_x_image, ddepth, 1, 0, 3); //computing the horizontal derivative
    Sobel(inputimage, D_y_image, ddepth, 0, 1, 3); //computing the vertical derivative

    convertScaleAbs(D_x_image, abs_D_x_image); //converting back to CV_8U
    convertScaleAbs(D_y_image, abs_D_y_image);

    addWeighted(abs_D_x_image, 0.5, abs_D_y_image, 0.5,0, SobelOP); //merging the horizontal and vertical derivatives into a single image

    //Displaying the edge map in different windows
    imshow(window2, SobelOP);
    imshow(window1, inputimage);
    imshow(window3, abs_D_x_image);
    imshow(window4, abs_D_y_image);

    waitKey(0); //wait infinite time for a keypress
    return 0;

    //destroy the window
    destroyWindow(window1);
    destroyWindow(window2);
    destroyWindow(window3);
    destroyWindow(window4);
}
