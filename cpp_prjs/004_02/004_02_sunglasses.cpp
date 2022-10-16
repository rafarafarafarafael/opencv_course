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
    face_image.convertTo(face_image, CV_32FC3);
    face_image /= 255.0;
    showImage("Face image", face_image);

    // Load sunglasses image
    std::string sunglasses_path = "./images/sunglass.png";
    cv::Mat glass_png = cv::imread(sunglasses_path, cv::IMREAD_UNCHANGED);
    glass_png.convertTo(glass_png, CV_32F);
    glass_png /= 255.0;
    // Resize image to fit over the eye region
    cv::resize(glass_png, glass_png, cv::Size(), 0.5, 0.5);
    showImage("Sunglasses", glass_png);
    std::cout << "image size: " << glass_png.size() << std::endl;
    std::cout << "image channels: " << glass_png.channels() << std::endl;
    int glass_height = glass_png.size().height;
    int glass_width = glass_png.size().width;
    // Separate the color and alpha channels
    cv::Mat glass_rgba_channels[4];
    cv::Mat glass_rgb_channels[3];
    cv::split(glass_png, glass_rgba_channels);
    for(int i = 0; i < 3; i++){
        // Copy RGB channels from RGBA
        glass_rgb_channels[i] = glass_rgba_channels[i];
    }
    cv::Mat glass_rgb, glass_mask;
    // Prepare BGR image
    cv::merge(glass_rgb_channels, 3, glass_rgb);
    // Alpha channel is the 4th channel in image
    glass_mask = glass_rgba_channels[3];
    showImage("Sunglasses RGB", glass_rgb);
    showImage("Sunglasses Mask", glass_mask);

    // Naive glasses placement
    // Make a copy of face image
    cv::Mat face_with_glass_naive = face_image.clone();
    cv::Mat roi_face = face_with_glass_naive(cv::Range(150, 250), cv::Range(140, 440));
    // Replace face ROI with sunglasses
    glass_rgb.copyTo(face_with_glass_naive(cv::Range(150, 150+glass_rgb.size().height), cv::Range(140, 140+glass_rgb.size().width)));
    //showImage("ROI face", roi_face);
    showImage("Face with glasses naive", face_with_glass_naive);

    return 0;
}