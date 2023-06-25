#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
//Размытие изображения
Mat imgOriginal;
int kernel_size = 3;
const int maximum_value = 50; // максимальное значение степени размытия
Mat img_blurred;
void on_trackbar(int, void*)
{
    if (imgOriginal.empty()) std::cout<<"ERROR!!!"<<std::endl;
    if (kernel_size % 2 == 0) // действительная степень нечетна
    {
        kernel_size--;
    }
    if (kernel_size <= 1) // ограничения размера kernel
    {
        kernel_size = 3;
    }

    blur(imgOriginal, img_blurred, Size(kernel_size, kernel_size)); // применяем размытие

    imshow("Blur image", img_blurred); // показываем результат
}
/*
int main(int argc, char** argv)
{
    imgOriginal = imread("/Users/sonya/Downloads/124.jpeg", IMREAD_COLOR);

    namedWindow(window_name, WINDOW_NORMAL);
    //resizeWindow(window_name, 640, 480);

    createTrackbar("Kernel size", window_name, &kernel_size, maximum_value, on_trackbar); // создаем трекбар

    on_trackbar(kernel_size, 0); // заполняем окно изображением и применяем размытие

    waitKey(0);

    return 0;
}*/
