#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat gray, blurred, edge;
//Laplacian Operator Variables
int kernel_size = 3;
int ddepth = CV_16S; //глубина оператора лапласа
///Canny Edge Detection Variables
int lowerThreshold = 0; //нижний порог
int max_lowThreshold = 100;//максимальное значение
void laplacianDectection()
{
    //сглаживаем изображение, чтобы уменьшить часть шумов
    GaussianBlur(gray,blurred,cv::Size(3,3),3);
    Laplacian(blurred, edge, ddepth, kernel_size);
    //converting back to CV_8U
    convertScaleAbs(edge, edge);
}
void CannyThreshold(int, void*){
    GaussianBlur(gray, blurred, cv::Size (3,3),3 );
    Canny(blurred,edge,lowerThreshold,50);
    imshow("Edge Detection", edge);
}

int brightness = 50;
void on_brightness_trackbar(int value, void* userdata)
{
    Mat* image = static_cast<Mat*>(userdata);
    Mat adjusted;
    image->convertTo(adjusted, -1, 1, value - 50);
    imshow("Bright", adjusted);
}

int contrast = 50;
void on_contrast_trackbar(int value, void* userdata)
{
    Mat* image = static_cast<Mat*>(userdata);
    double alpha = value / 50.0; // значения ползунка в диапазоне от 0 до 100
    Mat adjusted;
    image->convertTo(adjusted, -1, alpha, 0);
    imshow("Contrast", adjusted);
}

//Размытие изображения
int kernel = 3;
const int maximum_value = 50; // максимальное значение степени размытия

void on_blur_trackbar(int, void* userdata)
{
    Mat* image = static_cast<Mat*>(userdata);

    if (kernel % 2 == 0) // действительная степень нечетна
    {
        kernel--;
    }
    if (kernel <= 1) // ограничения размера kernel
    {
        kernel = 3;
    }
    Mat img_blurred;
    blur(*image, img_blurred, Size(kernel, kernel)); // применяем размытие
    imshow("Blur", img_blurred); // показываем результат
}