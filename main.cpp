// canny_img.cpp
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include "Detector_edge.hpp"
#include "opencv2/imgproc/imgproc.hpp" //Новые функции обработки изображений, написанные на C++.
//#include "opencv2/video/photo.hpp" //Алгоритмы обработки и восстановления фотографий.
#include "opencv2/highgui/highgui.hpp" //Новые написанные на C++ функции вывода изображений, ползунков, взаимодействия с помощью мыши, ввода-вывода.
#include <filesystem>
#include <vector>
using namespace std;
using namespace cv;
namespace fs = std::filesystem; // Чтобы не писать `std::filesystem` каждый раз

double alpha = 1.0; //< Simple contrast control
int beta = 0; //< Simple brightness control
int brightnessValue = 50; // начальное значение яркости

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
}


int main()
{
    cv::Mat imgOriginal;        // input image

    std::string directory_name = "/Users/polina/Desktop/С++/2_Project/cmake-build-debug/";
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
            // В С++20 можно будет просто `bool match = name.ends_with(extension);`
            bool match = name.ends_with(extension);
            //bool match = !name.compare(name.size() - extension.size(), extension.size(), extension);
            if (!match)
                continue;

            // Тут делаем с путем то, что нужно
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
    //img = imread("animal.jpeg",-1);

    cv::Mat imgGrayscale;        // grayscale of input image
    cv::Mat imgBlurred;            // intermediate blured image
    cv::Mat imgCanny;            // Canny edge image

    cvtColor(imgOriginal, gray, COLOR_BGR2GRAY);//преобразование изображения в оттенки серого
    cv::namedWindow("Original", WINDOW_AUTOSIZE);
    //cv::namedWindow("Gray", WINDOW_AUTOSIZE);
    //cv::namedWindow("Blurred", WINDOW_AUTOSIZE);
    cv::namedWindow("Edge Detection", WINDOW_AUTOSIZE);
    ///Canny Edge Detector
    createTrackbar("Min Threshold", "Edge Detection", &lowerThreshold, max_lowThreshold, CannyThreshold);
    CannyThreshold(0,0);
    ///laplactian Edge Detector
    //laplacianDectection();
    imshow("Original",imgOriginal);
    //imshow("Gray",gray);
   // imshow("Blurred",blurred);
    imshow("Edge Detection",edge);

    ///Negative
    cv::Mat img_neg;
    img_neg = cv::Scalar(255,255,255) - imgOriginal; ///Вычисляем негатив
    cv::imshow("Negative", img_neg);

    ///Яркость
    cv::Mat img_bright;
    cv::namedWindow("Bright", WINDOW_AUTOSIZE);
    //img_bright = imgOriginal + 40;

    int min_bright = 0;
    int max_bright = 100;
    /*void Bright_Threshold(){
        for( int i = 0; i < imgOriginal.rows; i++ ) {
            for( int j = 0; j < imgOriginal.cols; j++ ) {
                for( int z = 0; z < imgOriginal.channels(); z++ ) {
                    img_bright.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*imgOriginal.at<Vec3b>(y,x)[c] + beta );
                }
            }
        }
        imshow("Bright", img_bright)
    }*/
    //Bright_Threshold(0, 0);
    //cv::Mat imgOriginal

    double alpha = 1.0; //< Simple contrast control
    int beta = 0; //< Simple brightness control
    /*void Bright_Threshold(){
        for( int i = 0; i < imgOriginal.rows; i++ ) {
            for( int j = 0; j < imgOriginal.cols; j++ ) {
                for( int z = 0; z < imgOriginal.channels(); z++ ) {
                    img_bright.at<Vec3b>(j,i)[z] = saturate_cast<uchar>( alpha*imgOriginal.at<Vec3b>(j,i)[z] + beta );
                }
            }
        }
        imshow("Bright", img_bright);
    }*/

    cv::createTrackbar("Brightness", "Bright", &brightnessValue, 100,
                       onTrackbar);
    cv::imshow("Bright", img_bright);

    ///RGB в отдельныъ окнах
    cv::Mat sum_rgb;  // variable image of datatype Matrix
   // cv::imshow("Display Image", imgOriginal);

    // three channel to store b, g, r
    cv::Mat rgbchannel[3];

    // split image
    cv::split(imgOriginal, rgbchannel);

    // plot individual component
    //cv::namedWindow("Blue",WINDOW_AUTOSIZE);
    //cv::imshow("Red", rgbchannel[0]);

    //cv::namedWindow("Green",WINDOW_AUTOSIZE);
    //cv::imshow("Green", rgbchannel[1]);

    //cv::namedWindow("Red",WINDOW_AUTOSIZE);
    //cv::imshow("Blue", rgbchannel[2]);

    // merge : (input, num_of_channel, output)
    cv::merge(rgbchannel, 3, sum_rgb);
    //cv::imshow("Merged", sum_rgb);

    waitKey(0);
return 0;
}