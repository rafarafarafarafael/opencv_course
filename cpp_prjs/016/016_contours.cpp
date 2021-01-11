#include <iostream>
#include <string>
#include <vector>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include "..\lib\show_image.hpp"


int main(){
    std::string img_path = ".\\images\\Contour.png";
    cv::Mat img = cv::imread(img_path);
    cv::Mat img_copy = img.clone(), img_gray;

    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    showImage("Grayscale", img_gray);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img_gray, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    std::cout << "Number of contours found: " << contours.size() << std::endl;

    cv::drawContours(img, contours, -1, cv::Scalar(0, 255, 0), 6);
    showImage("Contours", img);

    // find external contours
    cv::findContours(img_gray, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::cout << "Number of external contours found: " << contours.size() << std::endl;

    img = img_copy.clone();
    cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 0), 6);
    showImage("External Contours", img);

    // mark a specific contour
    cv::drawContours(img, contours, 0, cv::Scalar(0, 0, 255), 6);
    showImage("First Contour Found", img);

    return 0;
}