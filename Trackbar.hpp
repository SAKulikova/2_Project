#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat gray, blurred, edge;
int lowerThreshold = 0;
int max_lowThreshold = 100;
int brightness = 50;
int contrast = 50;
int kernel = 3;
const int maximum_value = 50;

namespace Bar {
    void CannyThreshold(int, void *);

    void on_brightness_trackbar(int value, void *userdata);

    void on_contrast_trackbar(int value, void *userdata);

    void on_blur_trackbar(int, void *userdata);
}