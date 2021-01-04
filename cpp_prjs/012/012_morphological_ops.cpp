#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    const std::string img_dilate_path = ".\\images\\dilation_example.jpg";
    auto img_dilate = cv::imread(img_dilate_path);

    showImage("Original", img_dilate);

    int k_size = 7;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(k_size, k_size));
    // showImage("Kernel", kernel);

    // dialation with large kernel and single iteration
    cv::Mat img_di_single = img_dilate.clone();
    cv::dilate(img_dilate, img_di_single, kernel);
    showImage("Dialated Large Kernel", img_di_single);

    // dialation with small kernel and multiple iterations
    cv::Mat img_di_multi = img_dilate.clone();
    k_size = 3;
    kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(k_size, k_size));
    cv::dilate(img_di_multi, img_di_multi, kernel, cv::Point(-1, -1), 3);
    showImage("Dialated Small Kernel", img_di_multi);

    // erosion operation
    const std::string img_erode_path = ".\\images\\erosion_example.jpg";
    cv::Mat img_erode = cv::imread(img_erode_path);
    auto img_er_single = img_erode.clone();

    k_size = 5;
    kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(k_size, k_size));
    cv::erode(img_erode, img_er_single, kernel);
    showImage("Eroded Image", img_er_single);
    
    return 0;
}