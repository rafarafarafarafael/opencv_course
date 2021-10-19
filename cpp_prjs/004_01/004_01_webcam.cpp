#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main(){
    double scale = 1.0;
    cv::CascadeClassifier faceCascade;
    faceCascade.load("C:\\opencv-4.1.0\\etc\\haarcascades\\haarcascade_frontalface_default.xml");

    cv::VideoCapture capture(0);
    if(!capture.isOpened()){
        return -1;
    }

    cv::Mat camFeed;
    const std::string winName = "webcam";

    while(true){
        capture >> camFeed;

        cv::Mat camFeedGray;
        cv::cvtColor(camFeed, camFeedGray, cv::COLOR_BGR2GRAY);
        cv::resize(camFeedGray, camFeedGray, cv::Size(camFeedGray.size().width / scale, camFeedGray.size().height / scale));


        cv::imshow(winName, camFeedGray);

        if(cv::waitKey(30) >= 0){
            break;
        }
    }

    return 0;
}