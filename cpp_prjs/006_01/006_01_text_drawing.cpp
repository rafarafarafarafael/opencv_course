#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "..\lib\show_image.hpp"

int main(){
    const std::string img_path = ".\\images\\boy.jpg";
    cv::Mat img = cv::imread(img_path);

    showImage("Boy", img);

    // drawing text onto the image
    const cv::Scalar PURPLE = cv::Scalar(255, 0, 128);
    const std::string msg = "I am stydying";
    int font = cv::FONT_HERSHEY_COMPLEX;
    int pixThick = 1;
    const int pixHeight = 30; // desired pixel height of the text
    int baseLine = 0; // will contain the height in pixels from bottom of text to the baseline
    double fontScale = cv::getFontScaleFromHeight(font, pixHeight, pixThick); // getting font scale based on pixel height
    cv::Size textSize = cv::getTextSize(msg, font, fontScale, pixThick, &baseLine); // getting total text size
    cv::Point orig = cv::Point((img.size().width - textSize.width)/2, ((img.size().height - textSize.height)/2) - baseLine); // finding text position centered on image

    cv::putText(img, msg, orig, font, fontScale, PURPLE, pixThick, cv::LINE_AA);
    showImage("And text...", img);

    return 0;
}