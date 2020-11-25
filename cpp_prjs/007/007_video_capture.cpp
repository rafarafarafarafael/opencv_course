#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

void showImage(const std::string & win, cv::Mat & img){
    cv::namedWindow(win);
    cv::imshow(win, img);
    cv::waitKey();
    cv::destroyAllWindows();
}

int main(){
    cv::VideoCapture cap(0);
    cv::Mat frame;

    if(!cap.isOpened()){
        std::cout << "Error opening video stream or file!" << std::endl;
    }

    int key = -1; // stores the key pressed as the video is displayed 
    while(cap.isOpened()){
        cap >> frame;
        if(frame.empty() || key != -1){
            cv::destroyAllWindows();
            break;
        }
        cv::imshow("Frame", frame);
        key = cv::waitKey(1);
    }
    
    return 0;
}