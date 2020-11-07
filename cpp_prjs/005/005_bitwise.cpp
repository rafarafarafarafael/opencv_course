#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

void showImage(const std::string & win, cv::Mat & img){
    cv::namedWindow(win);
    cv::imshow(win, img);
    cv::waitKey();
    cv::destroyAllWindows();
}