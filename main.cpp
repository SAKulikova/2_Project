#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Trackbar.hpp"
#include <filesystem>
namespace fs = std::filesystem; // Чтобы не писать `std::filesystem` каждый раз

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
    //cv::Mat gray, blurred, edge;
    cvtColor(imgOriginal, editor::gray, cv::COLOR_BGR2GRAY);//преобразование изображения в оттенки серого
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Edge Detection", cv::WINDOW_AUTOSIZE);
    //int lowerThreshold = 0; //нижний порог
    const int max_lowThreshold = 100;//максимальное значение
    ///Canny Edge Detector
    cv::createTrackbar("Min Threshold", "Edge Detection", &editor::lowerThreshold, max_lowThreshold, editor::CannyThreshold);
    editor::CannyThreshold(0,nullptr);
    imshow("Original",imgOriginal);
    imshow("Edge Detection",editor::edge);

    ///Negative
    cv::Mat img_neg;
    img_neg = cv::Scalar(255,255,255) - imgOriginal; ///Вычисляем негатив
    cv::imshow("Negative", img_neg);

    ///Яркость и контрастность

    cv::Mat img = imgOriginal; ///???

    cv::namedWindow("Bright");
    cv::namedWindow("Contrast");

    //int brightness = 50;
    createTrackbar("Brightness", "Bright", &editor::brightness, 100, editor::on_brightness_trackbar, &imgOriginal);
    //int contrast = 50;
    createTrackbar("Contrast", "Contrast", &editor::contrast, 100, editor::on_contrast_trackbar, &imgOriginal);

    imshow("Contrast", img);
    imshow("Bright", img);

        ///RGB в отдельныъ окнах
    // 3 канала b, g, r
    cv::Mat rgbchannel[3];

    // разделение изображения
    cv::split(imgOriginal, rgbchannel);

    cv::namedWindow("Blue",cv::WINDOW_AUTOSIZE);
    cv::imshow("Red", rgbchannel[0]);

    cv::namedWindow("Green",cv::WINDOW_AUTOSIZE);
    cv::imshow("Green", rgbchannel[1]);

    cv::namedWindow("Red",cv::WINDOW_AUTOSIZE);
    cv::imshow("Blue", rgbchannel[2]);

    ///Blur
    namedWindow("Blur", cv::WINDOW_NORMAL);
    cv::Mat image;
    //int kernel = 3;
    const int maximum_value = 50;
    createTrackbar("Kernel size", "Blur", &editor::kernel, maximum_value, editor::on_blur_trackbar, &imgOriginal); // создаем трекбар
    imshow("Blur", image);

    cv::waitKey(0);
return 0;
}