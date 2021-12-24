#include <iostream>
#include <stack>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void grow(Mat& src,Mat& dest,Mat& mask,Point seed, int threshold);

// parameters
const int threshold = 200;
const uchar max_region_num = 100;
const double min_region_area_factor = 0.01;
const Point PointShift2D[8] =
{
    Point(1, 0),
    Point(1, -1),
    Point(0, -1),
    Point(-1, -1),
    Point(-1, 0),
    Point(-1, 1),
    Point(0, 1),
    Point(1, 1)
};


int main() {
    // read source image
    Mat src = imread("C:\\Users\\Gjay3\\Desktop\\Minor_project_final\\Test_image.jpg");
    assert(!src.empty());
    if (src.cols > 500 || src.rows > 500) {
        resize(src, src,Size(0, 0), 0.5, 0.5); // resize for speed
    }
    namedWindow("Original Image");
    imshow("Original Image", src);

    // ready for seed grow
    int min_region_area = int(min_region_area_factor * src.cols * src.rows);  // small region will be ignored
    namedWindow("Output Image");

    // "dest" records all regions using different padding number
    // 0 - undetermined, 255 - ignored, other number - determined
    uchar padding = 1;  // use which number to pad in "dest"
    Mat dest = Mat::zeros(src.rows, src.cols, CV_8UC1);

    // "mask" records current region, always use "1" for padding
    Mat mask = Mat::zeros(src.rows, src.cols, CV_8UC1);

    // 4. traversal the whole image, apply "seed grow" in undetermined pixels
    for (int x = 0; x < src.cols; ++x) {
        for (int y = 0; y < src.rows; ++y) {
            if (dest.at<uchar>(Point(x, y)) == 0) {
                grow(src, dest, mask, Point(x, y), 200);
                int mask_area = (int)sum(mask).val[0];  // calculate area of the region that we get in "seed grow"
                if (mask_area > min_region_area) {
                    dest = dest + mask * padding;   // record new region to "dest"
                    imshow("Output Image", mask * 255);
                    waitKey();
                    if (++padding > max_region_num) { printf("run out of max_region_num..."); return -1; }
                }
                else {
                    dest = dest + mask * 255;   // record as "ignored"
                }
                mask = mask - mask;     // zero mask, ready for next "seed grow"
            }
        }
    }
    return 0;
}

void grow(Mat& src,Mat& dest,Mat& mask,Point seed, int threshold) {
    /* apply "seed grow" in a given seed
     * Params:
     *   src: source image
     *   dest: a matrix records which pixels are determined/undtermined/ignored
     *   mask: a matrix records the region found in current "seed grow"
     */
    stack<Point> point_stack;
    point_stack.push(seed);

    while (!point_stack.empty()) {
        Point center = point_stack.top();
        mask.at<uchar>(center) = 1;
        point_stack.pop();

        for (int i = 0; i < 8; ++i) {
            Point estimating_point = center + PointShift2D[i];
            if (estimating_point.x < 0
                || estimating_point.x > src.cols - 1
                || estimating_point.y < 0
                || estimating_point.y > src.rows - 1) {
                // estimating_point should not out of the range in image
                continue;
            }
            else {
                //                uchar delta = (uchar)abs(src.at<uchar>(center) - src.at<uchar>(estimating_point));
                                // delta = (R-R')^2 + (G-G')^2 + (B-B')^2
                int delta = int(pow(src.at<Vec3b>(center)[0] - src.at<Vec3b>(estimating_point)[0], 2)
                    + pow(src.at<Vec3b>(center)[1] - src.at<Vec3b>(estimating_point)[1], 2)
                    + pow(src.at<Vec3b>(center)[2] - src.at<Vec3b>(estimating_point)[2], 2));
                if (dest.at<uchar>(estimating_point) == 0
                    && mask.at<uchar>(estimating_point) == 0
                    && delta < threshold) {
                    mask.at<uchar>(estimating_point) = 1;
                    point_stack.push(estimating_point);
                }
            }
        }
    }
}