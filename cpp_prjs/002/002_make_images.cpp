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
    // load an image
    std::string orig_file_path = ".\\images\\boy.jpg";
    cv::Mat orig_img = cv::imread(orig_file_path);
    std::cout << "Image size: " << orig_img.size().width << ", " << orig_img.size().height << "." << std::endl;

    showImage("Original", orig_img);

    // create a slice or cropped area of that image
    cv::Mat img_slice = orig_img(cv::Range(40, 200), cv::Range(170, 320));
    showImage("Slice", img_slice);

    cv::Mat another_slice = orig_img(cv::Rect(170, 40, 120, 130)); // using Rect function instead of Range
    showImage("Another Slice", another_slice);

    // create a copy of an image
    cv::Mat orig_copy = orig_img.clone();
    showImage("Copy", orig_copy);

    // create empty matrix
    cv::Mat empty_matrix = cv::Mat(200, 600, CV_8UC3, cv::Scalar(0, 0, 0));
    showImage("Empty", empty_matrix);

    // fill the empty matrix with a color
    cv::Mat yellow_img = empty_matrix.clone();
    yellow_img.setTo(cv::Scalar(0, 255, 255));
    showImage("Yellow", yellow_img);

    // copy cropped image onto another
    int slice_h = img_slice.size().height;
    int slice_w = img_slice.size().width;
    int in_pt_x = 10;
    int in_pt_y = 30;
    img_slice.copyTo(orig_copy(cv::Range(in_pt_y, in_pt_y + slice_h), cv::Range(in_pt_x, in_pt_x + slice_w)));
    showImage("inserted", orig_copy);

    // resize an image
    cv::Mat img_scale_size;
    cv::Mat img_scale_factor;

    double aspect_ratio = (double)orig_img.size().height / (double)orig_img.size().width;
    std::cout << "Aspect ratio: " << aspect_ratio << "." << std::endl;
    int new_width = 250;
    int new_height = new_width * aspect_ratio;
    std::cout << "New size: " << new_width << " X " << new_height << "." << std::endl;

    cv::resize(orig_img, img_scale_size, cv::Size(new_width, new_height), 0.0, 0.0, cv::INTER_LINEAR);
    showImage("Scaled by Size", img_scale_size);

    cv::resize(orig_img, img_scale_factor, cv::Size(), 1.5, 1.5, cv::INTER_LINEAR);
    showImage("Scaled by Factor", img_scale_factor);    

    // mask images using a color range
    cv::Mat red_mask = cv::Mat::zeros(orig_img.size(), orig_img.type());
    cv::inRange(orig_img, cv::Scalar(0, 0, 150), cv::Scalar(100, 100, 255), red_mask);
    showImage("Red Mask", red_mask);

    // write all these images out



    return 0;
}