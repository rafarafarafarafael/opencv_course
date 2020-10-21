#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

void showImage(const std::string & win, cv::Mat & img){
    cv::namedWindow(win);
    cv::imshow(win, img);
    cv::waitKey();
    cv::destroyAllWindows();
}

int main(){
    const std::string img_path = ".\\images\\boy.jpg";
    cv::Mat img = cv::imread(img_path);
    showImage("Original Image", img);

    double scaling_factor = 1.0/255;
    double shift = 0;

    cv::Mat img_normalized = img.clone();
    // converting image to 32 bit/channel float
    img_normalized.convertTo(img_normalized, CV_32FC3, scaling_factor, shift);
    showImage("Normalized", img_normalized);

    // converitng back to uint
    cv::Mat img_uint = img_normalized.clone();
    img_uint.convertTo(img_uint, CV_8UC3, 1.0/scaling_factor, -shift/scaling_factor);
    showImage("UINT image", img_uint);

    // manipulating contrast of an image
    double contrast_percent = 30.0;
    cv::Mat img_contrast_high = img.clone();
    img_contrast_high.convertTo(img_contrast_high, CV_64F, scaling_factor, shift); // remember the scaling factor and shift in the conversion function
    img_contrast_high = img_contrast_high * (1 + contrast_percent/100.0);
    showImage("High Contrast", img_contrast_high);

    // manipulating brightness of an image
    cv::Scalar brightness_factor = cv::Scalar(50.0, 50.0, 50.0);
    cv::Mat brightness_matrix = cv::Mat(img.size().height, img.size().width, CV_8UC3, brightness_factor);
    cv::Mat img_brightness_high = img.clone();
    cv::add(img_brightness_high, brightness_factor, img_brightness_high);
    // show the channel splitting option as well

    showImage("Brighter Image", img_brightness_high);
    
    return 0;
}