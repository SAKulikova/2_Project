#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
Mat gray, blurred, edge;
///Canny Edge Detection Variables
int lowerThreshold = 0; //нижний порог
int max_lowThreshold = 100;//максимальное значение
void CannyThreshold(int, void*){
    GaussianBlur(gray, blurred, cv::Size (3,3),3 );
    Canny(blurred,edge,lowerThreshold,50);
    imshow("Edge Detection", edge);
}