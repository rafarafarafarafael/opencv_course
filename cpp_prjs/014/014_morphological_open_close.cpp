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
    //std::cout << element <<std::endl;

    // morphological opening
    // method 1: erosion step followed by dilation
    cv::Mat img_eroded = img_opening.clone();
    cv::erode(img_opening, img_eroded, element, cv::Point(-1, -1), 1);
    showImage("Eroded", img_eroded);

    cv::Mat img_eroded_dilated = img_eroded.clone();
    cv::dilate(img_eroded, img_eroded_dilated, element, cv::Point(-1, -1), 1);
    showImage("Eroded + Dilated = Open", img_eroded_dilated);

    // method 2: morphologyEX function
    int opening_size = 3;
    element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2 * opening_size + 1, 2 * opening_size + 1), cv::Point(opening_size, opening_size));
    cv::Mat img_morph_opening;
    cv::morphologyEx(img_opening, img_morph_opening, cv::MORPH_OPEN, element, cv::Point(-1, -1), 3);
    showImage("Morph Opening", img_morph_opening);

    return 0;
}