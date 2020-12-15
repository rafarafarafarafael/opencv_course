#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// global variables
int max_scale_up = 100;
int scale_factor = 1;
int scale_type = 1;
int max_type = 1;
const std::string window_name = "Resize Image";
const std::string trackbar_value = "Scale";
const std::string trackbar_type = "Type: \n 0: Scale Up \n 1: Scale Down";

// image to be used, for some reason I couldn't declare this variable as local to main()
cv::Mat img = cv::imread(".\\images\\truth.png");

// callback definition
void scaleImage(int, void*);

int main(){
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    // trackbar creation and callback assignment
    cv::createTrackbar(trackbar_value, window_name, &scale_factor, max_scale_up, scaleImage);
    cv::createTrackbar(trackbar_type, window_name, &scale_type, max_type, scaleImage);

    // not sure why this one... guess to initialize image size (?)
    scaleImage(100, 0);

    while(true){
        // loop until ESC pressed
        int c = cv::waitKey(20);
        if(static_cast<char>(c) == 27){
            break;
        }
    }

    return 0;
}

// callback implementation
void scaleImage(int, void*){
    // scale factor declared and initialized
    double scale_factor_double = 1.0;

    if(scale_type == 1){
        scale_factor_double += scale_factor/100.0; // scale up
    } else {
        scale_factor_double -= scale_factor/100.0; // scale down
    }

    // clamp scale in extreme cases
    if(scale_factor_double == 0){
        if(scale_type == 1){
            scale_factor_double = 1.0;
        } else {
            scale_factor_double = 0.01;
        }
    }
    
    // creating scaled up version and display
    cv::Mat scaled_image;
    cv::resize(img, scaled_image, cv::Size(), scale_factor_double, scale_factor_double, cv::INTER_LINEAR);
    cv::imshow(window_name, scaled_image);
}