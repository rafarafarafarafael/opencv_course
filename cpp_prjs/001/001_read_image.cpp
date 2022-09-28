#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "..\lib\img_type.hpp" // external utility function
#include "..\lib\show_image.hpp" // external utility function

int main(){
    std::string imagePath = ".\\images\\boy.jpg";
    cv::Mat testImage = cv::imread(imagePath);

    const std::string winname = "test";

    showImage(winname, testImage);

    imagePath = ".\\images\\number_zero.jpg";
    cv::Mat zero = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    std::cout << zero << std::endl;
    std::cout << "Data type: " << type2str(zero.type()) << std::endl;
    std::cout << "Image dimensions: " << zero.size();
    
    return 0;
}