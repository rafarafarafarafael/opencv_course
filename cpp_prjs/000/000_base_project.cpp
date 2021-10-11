#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main(){
    std::string imagePath = ".\\images\\boy.jpg";
    cv::Mat testImage = cv::imread(imagePath);

    const std::string winname = "test";

    cv::namedWindow(winname);
    cv::imshow(winname, testImage);
    cv::waitKey();

    return 0;
}