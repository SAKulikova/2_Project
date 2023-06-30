#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
namespace Bar{
    class Track {
    public:
        static cv::Mat gray, blurred, edge;
        static int lowerThreshold;
        static int max_lowThreshold;
        static int brightness;
        static int contrast;
        static int kernel;
        static const int maximum_value;

        static void CannyThreshold(int, void *);

        static void on_brightness_trackbar(int value, void *userdata);

        static void on_contrast_trackbar(int value, void *userdata);

        static void on_blur_trackbar(int, void *userdata);

        static cv::Mat max_rgb_filter(const cv::Mat& image);
    };

}