#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    const std::string win_name = "Window";
    const std::string img_path = ".\\images\\boy.jpg";

    cv::Mat img = cv::imread(img_path);

    showImage(win_name, img);

    return 0;
}