#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    const std::string win_name = "Original";
    const std::string img_path = ".\\images\\threshold.png";

    cv::Mat img = cv::imread(img_path);
    showImage(win_name, img);

    int thresh = 100;
    int thresh_max = 150;

    // basic binary threshold
    auto dst_bin = img.clone();
    cv::threshold(img, dst_bin, thresh, thresh_max, cv::THRESH_BINARY);
    showImage("Binary Threshold", dst_bin);

    // inverse binary threshold
    auto dst_inv_bin = img.clone();
    cv::threshold(img, dst_inv_bin, thresh, thresh_max, cv::THRESH_BINARY_INV);
    showImage("Inverse Binary Threshold", dst_inv_bin);

    // truncate threshold
    auto dst_trunc = img.clone();
    cv::threshold(img, dst_trunc, thresh, thresh_max, cv::THRESH_TRUNC);
    showImage("Truncate Threshold", dst_trunc);

    // threshold to zero
    auto dst_to_zero = img.clone();
    cv::threshold(img, dst_to_zero, thresh, thresh_max, cv::THRESH_TOZERO);
    showImage("Threshold To Zero", dst_to_zero);

    // inverted threshold to zero
    auto dst_inv_to_zero = img.clone();
    cv::threshold(img, dst_inv_to_zero, thresh, thresh_max, cv::THRESH_TOZERO_INV);
    showImage("Inverse Threshold To Zero", dst_inv_to_zero);

    return 0;
}