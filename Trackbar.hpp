#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cstdio>
namespace editor{
    cv::Mat gray, blurred, edge;
///Canny Edge Detection Variables
    int lowerThreshold = 0; //нижний порог
    //const int max_lowThreshold = 100;//максимальное значение
    void CannyThreshold(int, void*);

    int brightness = 50;
    void on_brightness_trackbar(int value, void* userdata);

    int contrast = 50;
    void on_contrast_trackbar(int value, void* userdata);

//Размытие изображения
    int kernel = 3;
    //const int maximum_value = 50; // максимальное значение степени размытия

    void on_blur_trackbar(int, void* userdata);
}