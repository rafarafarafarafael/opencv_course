#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <typeinfo>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/fast_math.hpp>

int main(){
    double scale = 2.0;
    cv::CascadeClassifier faceCascade;
    faceCascade.load("C:\\opencv-4.6.0\\build\\etc\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");

    cv::VideoCapture capture(0);
    if(!capture.isOpened()){
        return -1;
    }

    cv::Mat camFeed;
    const std::string winName = "webcam";
    cv::namedWindow(winName);

    while(true){
        capture >> camFeed;

        cv::Mat camFeedGray;
        cv::cvtColor(camFeed, camFeedGray, cv::COLOR_BGR2GRAY);
        cv::resize(camFeedGray, camFeedGray, cv::Size(camFeedGray.size().width / scale, camFeedGray.size().height / scale));

        std::vector<cv::Rect> faces;
        std::vector<int> numFound;
        faceCascade.detectMultiScale(camFeedGray, faces, numFound, 1.1, 3, 0, cv::Size(15, 15));

        /* draw rectangles on the eyes
        for(cv::Rect area : faces){
            cv::Scalar color = cv::Scalar(64, 255, 64);
            cv::rectangle(camFeed, cv::Point(cvRound(area.x * scale), cvRound(area.y * scale)),
                        cv::Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)),
                        color);
        }*/

        // find leftmost upper corner for placing the glasses image
        //std::cout << typeid(faces.size()).name() << std::endl;
        int numEyes = faces.size();
        if(numEyes > 0){
            std::cout << "found an eye!" << std::endl;
            for(int num: numFound){
                std::cout << num << ", ";
            }
            std::cout << "." << std::endl;
        }


        cv::imshow(winName, camFeed);

        if(cv::waitKey(1) >= 0){
            break;
        }
    }

    return 0;
}