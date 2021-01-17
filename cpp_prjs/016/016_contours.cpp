#include <iostream>
#include <string>
#include <vector>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include "..\lib\show_image.hpp"


int main(){
    std::string img_path = ".\\images\\Contour.png";
    cv::Mat img = cv::imread(img_path);
    cv::Mat img_copy = img.clone(), img_gray;

    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    showImage("Grayscale", img_gray);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img_gray, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    std::cout << "Number of contours found: " << contours.size() << std::endl;

    cv::drawContours(img, contours, -1, cv::Scalar(0, 255, 0), 6);
    showImage("Contours", img);

    // find external contours
    cv::findContours(img_gray, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::cout << "Number of external contours found: " << contours.size() << std::endl;

    img = img_copy.clone();
    cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 0), 6);
    showImage("External Contours", img);

    // mark a specific contour
    cv::drawContours(img, contours, 0, cv::Scalar(0, 0, 255), 6);
    showImage("First Contour Found", img);

    // center of mass and centroid
    // find all the contours
    cv::findContours(img_gray, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(img, contours, -1, cv::Scalar(0, 255, 0), 3);

    cv::Moments M;
    int x, y;
    for(size_t i = 0; i < contours.size(); i++){
        // find moments of the contours
        // and calculate the conter of mass
        M = cv::moments(contours[i]);
        x = int(M.m10/double(M.m00));
        y = int(M.m01/double(M.m00));
        // mark the center
        cv::circle(img, cv::Point(x, y), 10, cv::Scalar(255, 0, 0), -1);
        // mark the contour number
        cv::putText(img, std::to_string(i + 1), cv::Point(x + 40, y + 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        // calculate area and perimeter of contours
        double area = cv::contourArea(contours[i]);
        double perimeter = cv::arcLength(contours[i], true);
        std::cout << "Are of contour " << i + 1 << " = " << area << ". Perimeter of contour " << i + 1 << " = " << perimeter << "." << std::endl;
        // draw bbox
        cv::Rect rect = cv::boundingRect(contours[i]);
        cv::rectangle(img, rect, cv::Scalar(255, 0, 255), 2);
        // draw rotated bbox
        cv::RotatedRect rot_rect = cv::minAreaRect(contours[i]);
        cv::Point2f rect_points[4];
        cv::Mat box_points_2f, box_points_cov;

        cv::boxPoints(rot_rect, box_points_2f);
        box_points_2f.assignTo(box_points_cov, CV_32S);
        cv::polylines(img, box_points_cov, true, cv::Scalar(255, 255, 0), 2);
    }

    showImage("Centroids", img);



    return 0;
}