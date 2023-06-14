#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat img, gray, blurred, edge;
//Laplacian Operator Variables
int kernel_size =3;
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