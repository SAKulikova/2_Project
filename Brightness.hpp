#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
void on_brightness_trackbar(int value, void* userdata)
{
    Mat* image = static_cast<Mat*>(userdata);
    Mat adjusted;
    image->convertTo(adjusted, -1, 1, value - 50);
    imshow("Bright", adjusted);
}

void on_contrast_trackbar(int value, void* userdata)
{
    Mat* image = static_cast<Mat*>(userdata);
    double alpha = value / 50.0; // значения ползунка в диапазоне от 0 до 100
    Mat adjusted;
    image->convertTo(adjusted, -1, alpha, 0);
    imshow("Contrast", adjusted);
}



