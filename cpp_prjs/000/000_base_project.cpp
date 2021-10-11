#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    std::string imagePath = ".\\images\\boy.jpg";
    cv::Mat testImage = cv::imread(imagePath);

    const std::string winname = "Image";

    showImage(winname, testImage);  

    return 0;
}