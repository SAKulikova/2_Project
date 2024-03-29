#include "Trackbar.hpp"
namespace Bar{
    cv::Mat Track::gray, Track::blurred, Track::edge;
    int Track::lowerThreshold = 0;
    int Track::max_lowThreshold = 100;
    int Track::brightness = 50;
    int Track::contrast = 50;
    int Track::kernel = 3;
    const int Track::maximum_value = 50;

    void Track::CannyThreshold(int, void *)
    {
        GaussianBlur(gray, blurred, cv::Size(3, 3), 3);
        Canny(blurred, edge, lowerThreshold, 50);
        imshow("Edge Detection", edge);
    }
    void Track::on_brightness_trackbar(int value, void *userdata)
    {
        cv::Mat *image = static_cast<cv::Mat *>(userdata);
        cv::Mat adjusted;
        image->convertTo(adjusted, -1, 1, value - 50);
        imshow("Bright", adjusted);
    }
    void Track::on_contrast_trackbar(int value, void *userdata) {
        cv::Mat *image = static_cast<cv::Mat *>(userdata);
        double alpha = value / 50.0;
        cv::Mat adjusted;
        image->convertTo(adjusted, -1, alpha, 0);
        imshow("Contrast", adjusted);
    }
    void Track::on_blur_trackbar(int, void *userdata)
    {
        cv::Mat *image = static_cast<cv::Mat *>(userdata);

        if (kernel % 2 == 0)
        {
            kernel--;
        }
        if (kernel <= 1)
        {
            kernel = 3;
        }
        cv::Mat img_blurred;
        blur(*image, img_blurred, cv::Size(kernel, kernel));
        imshow("Blur", img_blurred);
    }

    cv::Mat Track::max_rgb_filter(const cv::Mat& image)
    {
        std::vector<cv::Mat> channels;
        cv::split(image, channels);

        cv::Mat M = cv::max(cv::max(channels[2], channels[1]), channels[0]);

        channels[2].setTo(0, channels[2] < M);
        channels[1].setTo(0, channels[1] < M);
        channels[0].setTo(0, channels[0] < M);

        cv::Mat filtered;
        cv::merge(channels, filtered);
        return filtered;
    }
}