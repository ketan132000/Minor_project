#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char **argv)
{
    //read the image data, in the file in the mentioned location, in grayscale and store it in 'inputimage'
    Mat inputimage = imread("C:\\Users\\Jay\\OneDrive\\Pictures\\Saved Pictures\\LordKrishnaPhoto.jpg", 0);

    //Window name declaration
    const char *window1 = "Unprocessed";
    const char *window2 = "Sobel Edge Detector";
    const char *window3 = "Laplace Edge Detector";
    const char *window4 = "Canny Edge Detector";

    //Sobel variable declaration
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S; //to avoid overflow
    Mat D_x, D_y;
    Mat abs_D_x, abs_D_y;
    Mat SobelOP;

    //Laplace variable declaration
    int kernel_size = 3;
    Mat blurred1, outputL, LaplaceOP;

    //Canny variable declaration
    int aperture_size = 3;
    int threshold = 90;
    Mat blurred2, CannyOP;

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
    namedWindow(window3); //create a window with the name "Laplace Edge Detector"
    namedWindow(window4); //create a window with the name "Canny Edge Detector"

    //SOBEL EDGE DETECTION

    Sobel(inputimage, D_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT); //computing the horizontal derivative
    Sobel(inputimage, D_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT); //computing the vertical derivative

    convertScaleAbs(D_x, abs_D_x); //converting back to CV_8U
    convertScaleAbs(D_y, abs_D_y);

    addWeighted(abs_D_x, 0.5, abs_D_y, 0.5, 0, SobelOP); //merging the horizontal and vertical derivatives into a single image

    //LAPLACIAN EDGE DETECTION
    GaussianBlur(inputimage, blurred1, Size(3, 3), 0, 0, BORDER_DEFAULT); //to remove the noise in the image
    Laplacian(blurred1, outputL, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(outputL, LaplaceOP); //convert to a CV_8U image

    //CANNY EDGE DETECTION
    blur(inputimage, blurred2, Size(3, 3)); //to remove the noise in the image
    Canny(blurred2, CannyOP, threshold, threshold / 3, aperture_size, true);

    //Displaying the edge map in different windows
    imshow(window4, CannyOP);
    imshow(window3, LaplaceOP);
    imshow(window2, SobelOP);
    imshow(window1, inputimage);

    //Storing the edge map with corresponding file name
    imwrite("SobelFinal_output.jpg", SobelOP);
    imwrite("LaplaceFinal_output.jpg", LaplaceOP);
    imwrite("CannyFinal_output.jpg", CannyOP);

    waitKey(0); //wait infinite time for a keypress
    return 0;

    //destroy the window
    destroyWindow(window1);
    destroyWindow(window2);
    destroyWindow(window3);
    destroyWindow(window4);
}