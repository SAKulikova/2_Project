// canny_img.cpp
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Detector_edge.hpp"
#include "opencv2/imgproc/imgproc.hpp" //Новые функции обработки изображений, написанные на C++.
//#include "opencv2/video/photo.hpp" //Алгоритмы обработки и восстановления фотографий.
#include "opencv2/highgui/highgui.hpp" //Новые написанные на C++ функции вывода изображений, ползунков, взаимодействия с помощью мыши, ввода-вывода.
#include <filesystem>
using namespace std;
using namespace cv;
namespace fs = std::filesystem; // Чтобы не писать `std::filesystem` каждый раз
int main()
{
    std::string directory_name = "/Users/polina/Desktop/С++/2_Project/cmake-build-debug";
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
            bool match = !name.compare(name.size() - extension.size(), extension.size(), extension);
            if (!match)
                continue;

            // Тут делаем с путем то, что нужно
            std::cout << name << " ";
        }
        std::cout<<std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Error: " << e.what() << '\n';
    }
    //img = imread("animal.jpeg",-1);

    cv::Mat imgOriginal;        // input image
    cv::Mat imgGrayscale;        // grayscale of input image
    cv::Mat imgBlurred;            // intermediate blured image
    cv::Mat imgCanny;            // Canny edge image


    std::cout << "Введите название изображения : ";
    std::string img_addr;
    std::cin >> img_addr;

    std::cout << "Поиск изображения " + img_addr << std::endl;
    imgOriginal = cv::imread(img_addr);            // open image

    if (imgOriginal.empty())
    {                                    // if unable to open image
        std::cout << "error: изображение не найдено.\n";        // show error message on command line
        return(0);                                                // and exit program
    }
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
    cv::Mat img_neg, img_rgb;
    img_neg = cv::Scalar(255,255,255)-imgOriginal; ///Вычисляем негатив
    cv::imshow("Negative", img_neg);

    waitKey(0);
return 0;
}