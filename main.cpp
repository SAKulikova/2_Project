// canny_img.cpp
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Detector_edge.hpp"
#include "opencv2/imgproc/imgproc.hpp" //Новые функции обработки изображений, написанные на C++.
//#include "opencv2/video/photo.hpp" //Алгоритмы обработки и восстановления фотографий.
#include "opencv2/highgui/highgui.hpp" //Новые написанные на C++ функции вывода изображений, ползунков, взаимодействия с помощью мыши, ввода-вывода.
using namespace std;
using namespace cv;
int main()
{
    img = imread("/Users/sonya/Downloads/lena.png",-1);
    if (img.empty())
    {
        cout<<"Could not open or find the image!"<<std::endl;
        return -1;
    }
    cvtColor(img, gray, COLOR_BGR2GRAY);//преобразование изображения в оттенки серого
    cv::namedWindow("Original", WINDOW_AUTOSIZE);
    //cv::namedWindow("Gray", WINDOW_AUTOSIZE);
    //cv::namedWindow("Blurred", WINDOW_AUTOSIZE);
    cv::namedWindow("Edge Detection", WINDOW_AUTOSIZE);
    ///Canny Edge Detector
    createTrackbar("Min Threshold", "Edge Detection", &lowerThreshold, max_lowThreshold, CannyThreshold);
    CannyThreshold(0,0);
    ///laplactian Edge Detector
    //laplacianDectection();
    imshow("Original",img);
    //imshow("Gray",gray);
   // imshow("Blurred",blurred);
    imshow("Edge Detection",edge);
    waitKey(0);
return 0;
}
