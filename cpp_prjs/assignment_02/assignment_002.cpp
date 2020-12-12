#include <iostream>
#include <string>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>

// global variables visible to callback functions
cv::Point pt0, pt1;
cv::Mat source;
const std::string win_name = "Window";

// callback function
void drawRect(int action, int x, int y, int flags, void *user_data){
    if(action == cv::EVENT_LBUTTONDOWN){
        pt0 = cv::Point(x, y);
        cv::circle(source, pt0, 2, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    } else if (action == cv::EVENT_LBUTTONUP){
        pt1 = cv::Point(x, y);
        cv::rectangle(source, cv::Rect(pt0, pt1), cv::Scalar(255, 255, 0), 2, cv::LINE_AA);
        cv::Mat crop = source(cv::Range(pt0.y, pt1.y), cv::Range(pt0.x, pt1.x));
        cv::imwrite(".\\images\\assignment_02_cropped_image.jpg", crop);
        cv::imshow(win_name, source);
    }
}

int main(){
    // program variables
    const std::string img_path = ".\\images\\boy.jpg";
    source = cv::imread(img_path);
    int k = 0;

    // create named window and set callback
    cv::namedWindow(win_name);
    cv::setMouseCallback(win_name, drawRect);

    while(k != 27){// end loop and program if user hits ESC
        cv::imshow(win_name, source);
        k = cv::waitKey(20);
    }

    return 0;
}