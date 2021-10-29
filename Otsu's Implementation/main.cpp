#include<iostream>
#include<string>
#include<vector>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int calculateThreshold(Mat image) {
    vector<int> histogram(256, 0);
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            int pixel = image.at<uchar>(r, c);
            histogram[pixel]++;
        }
    }

    int size = image.rows * image.cols;
    long long sum = 0;
    for (int i = 0; i <= 255; i++)
        sum += i * histogram[i];
    int w1, w2;
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
                image.at<uchar>(r, c) = 0;
            else
                image.at<uchar>(r, c) = 255;
        }
    }
    return image;
}

int main() {
    Mat image = imread(" IMAGE PATH ", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Image not found!" << endl;
        cin.get();
        return -1;
    }

    String windowName = "Original image";
    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, image);
    waitKey(0);
    destroyWindow(windowName);
    int T = calculateThreshold(image);
    Mat segmentedImage = applyBinarization(image, T);
    windowName = "Segmented image";
    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, segmentedImage);
    waitKey(0);
    destroyWindow(windowName);
    return 0;
}
