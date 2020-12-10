#include <iostream>
#include <string>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>

// global variables visible to callback functions
cv::Point pt0, pt1;
cv::Mat source;

void drawRect(int action, int x, int y, int flags, void *user_data){
    if(action == cv::EVENT_LBUTTONDOWN){
        pt0 = cv::Point(x, y);
        cv::circle(source, pt0, 1, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    } else if (action == cv::EVENT_LBUTTONUP){
        pt1 = cv::Point(x, y);
        cv::rectangle(source, cv::Rect(pt0, pt1), cv::Scalar(128, 128, 0), 2, cv::LINE_AA);
        cv::imshow("Window", source);
    }
}

int main(){

    return 0;
}