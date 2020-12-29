#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    const std::string img_path = ".\\images\\dilation_example.jpg";
    auto img = cv::imread(img_path);

    showImage("Original", img);
    
    return 0;
}