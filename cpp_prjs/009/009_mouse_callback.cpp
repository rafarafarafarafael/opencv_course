#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

cv::Point center, circumference;
cv::Mat source;

void showImage(const std::string & win, cv::Mat & img){
    cv::namedWindow(win);
    cv::imshow(win, img);
    cv::waitKey();
    cv::destroyAllWindows();
}

void drawCircle(int action, int x, int y, int flags, void *user_data){
    if(action == cv::EVENT_LBUTTONDOWN){
        // mark the center of the circle
        center = cv::Point(x, y);
        cv::circle(source, center, 1, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
    } else if (action == cv::EVENT_LBUTTONUP) {
        circumference = cv::Point(x, y);
        float radius = sqrt(pow(center.x - circumference.x, 2) + pow(center.y - circumference.y, 2));
        cv::circle(source, center, radius, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
        cv::imshow("Window", source);
    }

}

int main(){
    source = cv::imread(".\\images\\boy.jpg", 1);
    // making a dummy image to help clear source if needed
    cv::Mat dummy = source.clone();
    cv::namedWindow("Window");
    // set the callback function
    cv::setMouseCallback("Window", drawCircle);
    int k = 0;

    // loop until escape key is pressed
    while(k != 27){
        cv::imshow("Window", source);
        cv::putText(source, "choose center and drag. Press ESC to quit or c to clear.", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        k = cv::waitKey(20) & 0xFF;
        if(k == 99){
            dummy.copyTo(source);
        }
    }

    return 0;
}