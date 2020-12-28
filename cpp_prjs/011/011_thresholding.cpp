#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    const std::string win_name = "Window";
    const std::string img_path = ".\\images\\threshold.png";

    cv::Mat img = cv::imread(img_path);
    showImage(win_name, img);

    int thresh = 100;
    int thresh_max = 200;

    auto thresh1 = img.clone();
    cv::threshold(img, thresh1, thresh, thresh_max, cv::THRESH_BINARY);
    showImage(win_name, thresh1);

    return 0;
}