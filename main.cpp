#include <iostream>
#include "Trackbar.hpp"
#include <filesystem>
using namespace std;
using namespace cv;
namespace fs = std::filesystem; // Чтобы не писать `std::filesystem` каждый раз
int main()
{
    cv::Mat imgOriginal;        // input image
    std::string directory_name = "/Users/sonya/Desktop/Git/2_Project/pics/";
    std::string extension = ".png";

    std::cout<<"Варианты файлов: ";
    try // Может быть исключение, например, если папки не существует
    {
        for (auto &p : fs::directory_iterator(directory_name)) // Для всех файлов в папке
        {
            if (!fs::is_regular_file(p.status()))
                continue; // Пропускаем, если это не простой файл, а папка или что-то другое

            std::string name(p.path().filename());
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
    createTrackbar("Min Threshold", "Edge Detection", &lowerThreshold, max_lowThreshold, Bar::CannyThreshold);
    Bar::CannyThreshold(0,nullptr);
    imshow("Original",imgOriginal);
    imshow("Edge Detection",edge);

    ///Negative
    cv::Mat img_neg;
    img_neg = cv::Scalar(255,255,255) - imgOriginal; ///Вычисляем негатив
    cv::imshow("Negative", img_neg);

    ///Яркость и контрастность

   // cv::Mat image = imgOriginal;

    namedWindow("Bright");
    namedWindow("Contrast");

    createTrackbar("Brightness", "Bright", &brightness, 100, Bar::on_brightness_trackbar, &imgOriginal);
    createTrackbar("Contrast", "Contrast", &contrast, 100, Bar::on_contrast_trackbar, &imgOriginal);

    Bar::on_contrast_trackbar(0, nullptr);
    Bar::on_brightness_trackbar(0, nullptr);

    imshow("Contrast", imgOriginal);
    imshow("Bright", imgOriginal);

    ///RGB в отдельныъ окнах
    cv::Mat rgbchannel[3];

    // разделение изображения
    cv::split(imgOriginal, rgbchannel);

    cv::namedWindow("Blue",WINDOW_AUTOSIZE);
    cv::imshow("Red", rgbchannel[0]);

    cv::namedWindow("Green",WINDOW_AUTOSIZE);
    cv::imshow("Green", rgbchannel[1]);

    cv::namedWindow("Red",WINDOW_AUTOSIZE);
    cv::imshow("Blue", rgbchannel[2]);

    ///Blur
    namedWindow("Blur", WINDOW_NORMAL);
    createTrackbar("Kernel size", "Blur", &kernel, maximum_value, Bar::on_blur_trackbar, &imgOriginal);
    imshow("Blur", imgOriginal);

    waitKey(0);
return 0;
}