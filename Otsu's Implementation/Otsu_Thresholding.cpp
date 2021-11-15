//including libraries

#include<iostream>
#include<string>
#include<vector>
#include<opencv2/opencv.hpp>

using namespace std;  
using namespace cv;

//function to plot histogram 

void plotHistogram(vector<int> histogram) {
    int image_w = 512 * 2;
    int image_h = 800;
    int binW = image_w / 256;
    int pad = 60;
    Mat image(image_h + 2 * pad, image_w + 2 * pad, CV_8UC1, Scalar(255));
    float maxFreq = *max_element(histogram.begin(), histogram.end());
    vector<int> height(256, 0);
    for (int i = 0; i <= 255; i++)
        height[i] = (histogram[i] / maxFreq) * image_h;

    // draw bins
    int thickness = 2;
    for (int i = 0; i <= 255; i++) {
        int x1, y1, x2, y2;
        x1 = x2 = binW * i + pad;
        y1 = image_h + pad;
        y2 = y1 - height[i];
        line(image, Point(x1, y1), Point(x2, y2), Scalar(0), thickness);
    }

    //declaring window for histogram
    String windowName2 = "Histogram";
    namedWindow(windowName2, WINDOW_NORMAL);
    imshow(windowName2, image);
}


//Function to calculate threshold value of the greyscale image 
int calculateThreshold(Mat image) {
    vector<int> histogram(256);
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            int pixel = image.at<uchar>(r, c);
            histogram[pixel]++;
        }
    }

    plotHistogram(histogram);

    int size = image.rows * image.cols;
    long long sum = 0;
    for (int i = 0; i <= 255; i++)
        sum += i * histogram[i];
    long double w1, w2;
    w1 = w2 = 0;
    long double currSum = 0;
    int T = 0;
    long double varMax = 0;

    for (int t = 0; t <= 255; t++) {
        w1 += histogram[t];
        if (w1 == 0)
            continue;
        else if (w2 == size)
            break;

        w2 = size - w1;
        currSum += t * histogram[t];
        long double u1, u2;
        u1 = currSum / w1;
        u2 = (sum - currSum) / w2;

        long double var = w1 * w2 * (u1 - u2) * (u1 - u2);
        if (var > varMax) {
            varMax = var;
            T = t;
        }
    }
    return T;
}


Mat applyBinarization(Mat image, int T) {
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            int pixel = image.at<uchar>(r, c);
            if (pixel <= T)
                image.at<uchar>(r,c) = 0; //Foreground(BLACK)
            else
                image.at<uchar>(r, c) = 255;//Background(WHITE)
        }
    }
    return image;
}

int main() {
    Mat image = imread("C:/Users/DELL/Downloads/finalimage.jpg", IMREAD_GRAYSCALE); //Stores pixel values of the image in matrix form.
    if (image.empty()) {
        cout << "Image not found!" << endl;
       // cin.get(); //terminates when whitespace is found.
        return -1;
    }

    String windowName = "Original image";
    String windowName1 = "Segmented image";
    String windowName2 = "Histogram";

    namedWindow(windowName);// Creates a window that will be used to store the image.
    imshow(windowName, image);//Display the window that contains the image along with its name
    int T = calculateThreshold(image);
    cout << "Threshold value of the image is:" << T;
    Mat segmentedImage = applyBinarization(image, T);
    namedWindow(windowName1);
    imshow(windowName1, segmentedImage);
    waitKey(0);
    destroyWindow(windowName);
    destroyWindow(windowName1);
    destroyWindow(windowName2);
    return 0;
}
