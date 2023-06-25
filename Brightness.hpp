#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*int brightnessValue = 50; // начальное значение яркости

void onTrackbar(int, void*)
{
    cv::Mat imgOriginal;
    cv::Mat image = imgOriginal;
    // обработчик события изменения положения трекбара
    // получаем новое значение яркости
    int newValue = brightnessValue - 50; // приводим из диапазона [0, 100] к [-50, 50]
    // загружаем изображение

    // увеличиваем яркость изображения
    Mat img_bright = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            for (int c = 0; c < image.channels(); c++)
            {
                img_bright.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(image.at<Vec3b>(y, x)[c] + newValue);
            }
        }
    }
    // выводим изображение на экран
    imshow("Bright", img_bright);
}*/
/*Mat image, img_bright;;
int brightness = 10;
int max_brightness = 100;
void on_brightness_change(int , void* ) {
    float alpha = (float) (brightness - 50) / 50;
    cv::addWeighted(image, 1.0, Mat::zeros(image.size(), image.type()), 0, 50*alpha, img_bright);
    imshow("Bright", img_bright);
}*/
/*
int alpha = 1; /**< Simple contrast control */
int beta = 100;  /**< Simple brightness control */
/*
Mat image;
//std::cout<< image.size()<<" "<<image.type()<<std::endl;
Mat new_image = Mat::zeros( image.size(), image.type() );
//std::cout<<image.size()<<" "<<image.type()<<std::endl;
void onTrackbar(int, void*) {
    std::cout<<"rows: "<<image.rows<<" cols: "<<image.cols<<" channels: "<<image.channels()<<std::endl;
// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for (int y = 0; y < image.rows; y++) {
        std::cout<<"y:"<<y<<std::endl;
        for (int x = 0; x < image.cols; x++) {
            std::cout<<"x:"<<x<<std::endl;
            for (int c = 0; c < image.channels(); c++) {
                std::cout<<"c:"<<c<<std::endl;
                new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
                std::cout<<new_image.at<Vec3b>(y, x)[c]<<std::endl;
            };
        };
    };
    imshow("Bright", new_image);
};*/

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



