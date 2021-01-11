#include <iostream>
#include <string>
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

    return 0;
}