#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "..\lib\img_type.hpp" // external utility function
#include "..\lib\show_image.hpp" // external utility function

int main(){
    std::string image_path = ".\\images\\boy.jpg";
    cv::Mat test_image = cv::imread(image_path);

    const std::string win_name = "test";

    showImage(win_name, test_image);

    image_path = ".\\images\\number_zero.jpg";
    cv::Mat zero = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    std::cout << zero << std::endl;
    std::cout << "Data type: " << type2str(zero.type()) << std::endl;
    std::cout << "Image dimensions: " << zero.size();
    
    //pick up one pixel and inspect it
    int pixel_value = zero.at<uchar>(6, 5);
    std::cout << "Pixel value is: " << pixel_value << std::endl;

    //set a new value for the pixel and print the matrix
    zero.at<uchar>(6, 5) = 255;
    std::cout << zero << std::endl;
    showImage(win_name, zero);

    return 0;
}