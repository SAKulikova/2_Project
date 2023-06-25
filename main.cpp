#include <opencv2/imgproc.hpp>//Новые функции обработки изображений, написанные на C++.
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>//Новые написанные на C++ функции вывода изображений, ползунков, взаимодействия с помощью мыши, ввода-вывода.
//#include <stdio.h>
#include "Detector_edge.hpp"
#include "Brightness.hpp"
#include <filesystem>
#include <vector>
#include "Blur.hpp"
using namespace std;
using namespace cv;
namespace fs = std::filesystem; // Чтобы не писать `std::filesystem` каждый раз

int main()
{
    cv::Mat imgOriginal;        // input image
    std::string directory_name = "/Users/sonya/Desktop/Git/2_Project/cmake-build-debug/pics/";
    std::string extension = ".png";
    std::cout<<"Варианты файлов: ";
    try // Может быть исключение, например, если папки не существует
    {
        for (auto &p : fs::directory_iterator(directory_name)) // Для всех файлов в папке
        {
            if (!fs::is_regular_file(p.status()))
                continue; // Пропускаем, если это не простой файл, а папка или что-то другое

            std::string name(p.path().filename());

            // Проверяем, что имя заканчивается нужным расширением
            bool match = name.ends_with(extension);
            if (!match)
                continue;
            std::cout << name << " ";
        }
        std::cout<<std::endl;
        std::cout << "Введите название изображения : ";
        std::string img_addr;
        std::cin >> img_addr;

        std::cout << "Поиск изображения " + img_addr << std::endl;
        imgOriginal = cv::imread(directory_name + img_addr);            // open image

        if (imgOriginal.empty())
        {                                    // if unable to open image
            std::cout << "error: изображение пустое.\n";        // show error message on command line
            return(0);                                                // and exit program
        }
    }
    catch (std::exception &e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    cv::Mat imgGrayscale;        // grayscale of input image
    cv::Mat imgBlurred;            // intermediate blured image
    cv::Mat imgCanny;            // Canny edge image

    cvtColor(imgOriginal, gray, COLOR_BGR2GRAY);//преобразование изображения в оттенки серого
    cv::namedWindow("Original", WINDOW_AUTOSIZE);
    cv::namedWindow("Edge Detection", WINDOW_AUTOSIZE);
    ///Canny Edge Detector
    createTrackbar("Min Threshold", "Edge Detection", &lowerThreshold, max_lowThreshold, CannyThreshold);
    CannyThreshold(0,nullptr);
    imshow("Original",imgOriginal);
    imshow("Edge Detection",edge);

    ///Negative
    cv::Mat img_neg;
    img_neg = cv::Scalar(255,255,255) - imgOriginal; ///Вычисляем негатив
    cv::imshow("Negative", img_neg);

    ///Яркость и контрастность
    cv::Mat image = imgOriginal;
    namedWindow("Bright");
    namedWindow("Contrast");

    int brightness = 50;
    createTrackbar("Brightness", "Bright", &brightness, 100, on_brightness_trackbar, &imgOriginal);

    int contrast = 50;
    createTrackbar("Contrast", "Contrast", &contrast, 100, on_contrast_trackbar, &imgOriginal);

    imshow("Contrast", image);
    imshow("Bright", image);

        ///RGB в отдельных окнах
    // three channel to store b, g, r
    cv::Mat rgbchannel[3];

    // split image
    cv::split(imgOriginal, rgbchannel);

    // plot individual component
    cv::namedWindow("Blue",WINDOW_AUTOSIZE);
    cv::imshow("Red", rgbchannel[0]);

    cv::namedWindow("Green",WINDOW_AUTOSIZE);
    cv::imshow("Green", rgbchannel[1]);

    cv::namedWindow("Red",WINDOW_AUTOSIZE);
    cv::imshow("Blue", rgbchannel[2]);


    waitKey(0);
return 0;
}