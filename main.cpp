#include <iostream>
#include "Trackbar.hpp"
#include <filesystem>
namespace fs = std::filesystem; // Чтобы не писать `std::filesystem` каждый раз

int main()
{
    cv::Mat imgOriginal;        // input image
    std::string directory_name = "/Users/polina/Documents/Git/2-semestr/2_Project/pics/";
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
    cvtColor(imgOriginal, Bar::Track::gray, cv::COLOR_BGR2GRAY);//преобразование изображения в оттенки серого
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Edge Detection", cv::WINDOW_AUTOSIZE);
    imshow("Original",imgOriginal);
    ///Canny Edge Detector
    cv::createTrackbar("Min Threshold", "Edge Detection", &Bar::Track::lowerThreshold, Bar::Track::max_lowThreshold, Bar::Track::CannyThreshold);
    Bar::Track::CannyThreshold(0,nullptr);
    imshow("Edge Detection",Bar::Track::edge);

    ///Negative
    cv::Mat img_neg;
    img_neg = cv::Scalar(255,255,255) - imgOriginal; ///Вычисляем негатив
    cv::imshow("Negative", img_neg);

    ///Яркость и контрастность
    cv::Mat image1 = imgOriginal;
    cv::Mat image2 = imgOriginal;

    cv::namedWindow("Bright");
    cv::namedWindow("Contrast");

    createTrackbar("Brightness", "Bright", &Bar::Track::brightness, 100, Bar::Track::on_brightness_trackbar, &image1);
    createTrackbar("Contrast", "Contrast", &Bar::Track::contrast, 100, Bar::Track::on_contrast_trackbar, &image2);

    Bar::Track::on_contrast_trackbar(0, &image1);
    Bar::Track::on_brightness_trackbar(0, &image2);

    imshow("Contrast", imgOriginal);
    imshow("Bright", imgOriginal);

    ///Blur
    cv::namedWindow("Blur", cv::WINDOW_NORMAL);
    createTrackbar("Kernel size", "Blur", &Bar::Track::kernel, Bar::Track::maximum_value, Bar::Track::on_blur_trackbar, &imgOriginal);
    cv::imshow("Blur", imgOriginal);

    ///RGB filter
    cv::namedWindow("RGB", cv::WINDOW_AUTOSIZE);
    cv::Mat filtered_image = Bar::Track::max_rgb_filter(imgOriginal);
    cv::imshow("RGB", filtered_image);

    cv::waitKey(0);
    return 0;
}