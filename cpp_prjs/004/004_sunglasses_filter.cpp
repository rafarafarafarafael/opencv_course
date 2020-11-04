#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

void showImage(const std::string & win, cv::Mat & img){
    cv::namedWindow(win);
    cv::imshow(win, img);
    cv::waitKey();
    cv::destroyAllWindows();
}

int main(){
    const std::string face_img_path = ".\\images\\musk.jpg";
    const std::string sunglass_img_path = ".\\images\\sunglass.png";
    cv::Mat musk = cv::imread(face_img_path, cv::IMREAD_UNCHANGED);
    cv::Mat sunglass = cv::imread(sunglass_img_path, cv::IMREAD_UNCHANGED);

    std::cout << "Musk info: " << musk.size().width << "X" << musk.size().height << ", " << musk.channels() << "." << std::endl;
    std::cout << "Sunglasses info: " << sunglass.size().width << "X" << sunglass.size().height << ", " << sunglass.channels() << "." << std::endl;

    showImage("Elon Musk", musk);
    // showImage("Sunglasses", sunglass);

    // split the image channels for the sunglasses

    return 0;
}