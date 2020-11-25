#include <iostream>
#include <sstream>
#include <string>
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
    int frame_width, frame_height;
    double frame_rate;

    cv::VideoCapture cap(0);
    cv::Mat frame;

    if(!cap.isOpened()){
        std::cout << "Error opening video stream or file!" << std::endl;
    }

    int key = -1;
    std::string msg = "";
    const int font_face = cv::FONT_HERSHEY_COMPLEX;
    const int font_thickness = 1;
    const int font_height = 12;
    const int font_base_line = 0;
    const double font_scale = cv::getFontScaleFromHeight(font_face, font_height, font_thickness);

    while(key == -1 && cap.isOpened()){
        cap >> frame;
        if(frame.empty() || key != -1){
            cv::destroyAllWindows();
            break;
        }
        frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        frame_rate = cap.get(cv::CAP_PROP_FPS);

        std::stringstream msg_stream;
        msg_stream << "Video size: " << frame_width << "x" << frame_height << "  Frame rate: " << frame_rate;
        msg = msg_stream.str();
        cv::Size msg_size = cv::getTextSize(msg, font_face, font_scale, font_thickness, font_base_line);
        cv::Point msg_orig = cv::Point(10, (frame_height - msg_size.height));
        cv::putText(frame, msg, msg_orig, font_face, font_scale, cv::Scalar(255, 0, 128), font_thickness, cv::LINE_AA);
        
        cv::imshow("Webcam", frame);
        key = cv::waitKey(1);
    }
    
    return 0;
}