#include "Trackbar.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
namespace editor {
    void CannyThreshold(int, void *) {
        //cv::Mat gray, blurred, edge;
        GaussianBlur(gray, blurred, cv::Size(3, 3), 3);
        Canny(blurred, edge, lowerThreshold, 50);
        imshow("Edge Detection", edge);
    }

    void on_brightness_trackbar(int value, void *userdata) {
        cv::Mat *img = auto(static_cast<cv::Mat *>(userdata));
        cv::Mat adjusted;
        img->convertTo(adjusted, -1, 1, value - 50);
        imshow("Bright", adjusted);
    }

    void on_contrast_trackbar(int value, void *userdata) {
        cv::Mat *image = auto(static_cast<cv::Mat *>(userdata));
        double alpha = value / 50.0; // значения ползунка в диапазоне от 0 до 100
        cv::Mat adjusted;
        image->convertTo(adjusted, -1, alpha, 0);
        imshow("Contrast", adjusted);
    }

    void on_blur_trackbar(int, void *userdata) {
        cv::Mat *image = auto(static_cast<cv::Mat *>(userdata));

        if (kernel % 2 == 0) // действительная степень нечетна
        {
            kernel--;
        }
        if (kernel <= 1) // ограничения размера kernel
        {
            kernel = 3;
        }
        cv::Mat img_blurred;
        blur(*image, img_blurred, cv::Size(kernel, kernel)); // применяем размытие
        imshow("Blur", img_blurred); // показываем результат
    }
}