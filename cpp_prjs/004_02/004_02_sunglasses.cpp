#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "../lib/show_image.hpp"


int main(){
    // Load the face image
    std::string face_image_path = "./images/musk.jpg";
    cv::Mat face_image = imread(face_image_path, cv::IMREAD_COLOR);
    showImage("Face image", face_image);

    return 0;
}