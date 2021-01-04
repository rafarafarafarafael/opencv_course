#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    const std::string img_path = ".\\images\\";
    cv::Mat img_opening = cv::imread(img_path + "opening.png", cv::IMREAD_GRAYSCALE);
    cv::Mat img_closing = cv::imread(img_path + "closing.png", cv::IMREAD_GRAYSCALE);

    showImage("Original Opening", img_opening);
    showImage("Original Closing", img_closing);

    int kernel_size = 10;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2 * kernel_size + 1, 2 * kernel_size + 1), cv::Point(kernel_size, kernel_size));
    showImage("Kernel", element);

    cv::Mat img_eroded = img_opening.clone();
    cv::erode(img_opening, img_eroded, element, cv::Point(-1, -1), 1);
    showImage("Eroded", img_eroded);

    return 0;
}