#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "..\lib\show_image.hpp" // external utility function

int main(){
    cv::Mat img = cv::imread(".\\images\\truth.png", cv::IMREAD_GRAYSCALE);
    showImage("Original", img);

    // threshold image
    cv::Mat img_thresh;
    cv::threshold(img, img_thresh, 127, 255, cv::THRESH_BINARY);

    // find connected components
    cv::Mat img_labels;
    int num_components = cv::connectedComponents(img_thresh, img_labels);
    cv::Mat img_labels_copy = img_labels.clone();

    // find min and max values
    cv::Point min_loc, max_loc;
    double min_val, max_val;
    cv::minMaxLoc(img_labels, &min_val, &max_val, &min_loc, &max_loc);

    //normalize image so min = 0 and max = 255
    img_labels = 255 * (img_labels - min_val)/(max_val-min_val);

    //convert image to 8-bits
    img_labels.convertTo(img_labels, CV_8U);
    showImage("Labels", img_labels);

    // show labels isolated
    cv::namedWindow("Labels");
    cv::imshow("Labels", img_labels==1);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // create a color map for the labels
    img_labels = img_labels_copy.clone();
    double min_val2, max_val2;
    cv::minMaxLoc(img_labels, &min_val2, &max_val2, &min_loc, &max_loc);
    img_labels = 255 * (img_labels - min_val2)/(max_val2 - min_val2);
    img_labels.convertTo(img_labels, CV_8U);
    cv::Mat img_colormap;
    cv::applyColorMap(img_labels, img_colormap, cv::COLORMAP_JET);
    showImage("Color Map", img_colormap);    

    return 0;
}