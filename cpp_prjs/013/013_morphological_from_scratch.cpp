#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <time.h>
#include "..\lib\show_image.hpp" // external utility function


int main(){
    cv::Mat demoImage = cv::Mat::zeros(cv::Size(10,10),CV_8U);

    std::cout << demoImage;

    showImage("Demo Image", demoImage);

    demoImage.at<uchar>(0,1) = 1;
    demoImage.at<uchar>(9,0) = 1;
    demoImage.at<uchar>(8,9) = 1;
    demoImage.at<uchar>(2,2) = 1;
    demoImage(cv::Range(5,8),cv::Range(5,8)).setTo(1);

    std::cout << demoImage;

    showImage("Demo Image", demoImage);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));

    std::cout << element;

    showImage("Demo Image", element);

    int ksize = element.size().height;

    int height, width;
    height = demoImage.size().height;
    width  = demoImage.size().width;

    cv::Mat dilatedCrossKernel;
    cv::dilate(demoImage, dilatedCrossKernel, element);
    std::cout << dilatedCrossKernel;

    showImage("Demo Image", dilatedCrossKernel);

    int border = ksize/2;
    cv::Mat paddedDemoImage = cv::Mat::zeros(cv::Size(height + border*2, width + border*2), CV_8UC1);
    cv::copyMakeBorder(demoImage,paddedDemoImage,border,border,border,border,cv::BORDER_CONSTANT,0);

    cv::Mat paddedDilatedImage = paddedDemoImage.clone();
    cv::Mat mask;
    cv::Mat resizedFrame;

    double minVal, maxVal;

    // Create a VideoWriter object
    // Use frame size as 50x50
    ///
    /// YOUR CODE HERE
    cv::Size frame_size = cv::Size(50, 50);
    double frame_rate = 10.0;
    cv::VideoWriter dilationScratch;
    int fourcc = cv::VideoWriter::fourcc('H','2','6','4');
    dilationScratch.open("dilationScratch.avi", fourcc, frame_rate, frame_size);
    ///

    for (int h_i = border; h_i < height + border; h_i++){
        for (int w_i = border; w_i < width + border; w_i++){
            ///
            /// YOUR CODE HERE
            cv::Rect roi = cv::Rect(w_i - (element.size().width - 1)/2, h_i - (element.size().height - 1)/2, element.size().width, element.size().height);
            cv::Mat slice = paddedDemoImage(roi); 
            cv::Mat bit_and = slice.clone();
            bitwise_and(slice, element, bit_and);
            minMaxLoc(bit_and, &minVal, &maxVal);
            if(maxVal){
                paddedDilatedImage.at<uchar>(h_i, w_i) = maxVal;
            }
            ///
            // Resize output to 50x50 before writing it to the video
            ///
            /// YOUR CODE HERE
            cv::Mat resizedPaddedDilatedImage;
            resize(paddedDilatedImage * 255, resizedPaddedDilatedImage, frame_size, 1.0, 1.0, cv::INTER_NEAREST);
            ///
            // Convert resizedFrame to BGR before writing
            ///
            /// YOUR CODE HERE
            cv::Mat resizedPaddedDilatedImageChannels[3], resizedPaddedDilatedImageBGR;
            for(int i = 0; i < 3; i++){
                resizedPaddedDilatedImageChannels[i] = resizedPaddedDilatedImage;
            }
            merge(resizedPaddedDilatedImageChannels, 3, resizedPaddedDilatedImageBGR);
            dilationScratch.write(resizedPaddedDilatedImageBGR);
            ///
        }
    }

    // Release the VideoWriter object
    ///
    /// YOUR CODE HERE
    dilationScratch.release();
    ///


    // Display final image (cropped)
    ///
    /// YOUR CODE HERE

    showImage("Demo Image", paddedDilatedImage);
    ///

    cv::Mat ErodedCrossKernel;
    cv::erode(demoImage, ErodedCrossKernel, element);
    std::cout << ErodedCrossKernel;

    showImage("Demo Image", ErodedCrossKernel);

    border = ksize/2;
    paddedDemoImage = cv::Mat::zeros(cv::Size(height + border*2, width + border*2),CV_8UC1);
    cv::copyMakeBorder(demoImage,paddedDemoImage,border,border,border,border,cv::BORDER_CONSTANT,0);

    cv::Mat paddedErodedImage = paddedDemoImage.clone();

    // Create a VideoWriter object
    // Use frame size as 50x50
    ///
    /// YOUR CODE HERE
    cv::VideoWriter erosionScratch;
    erosionScratch.open("erosionScratch.avi", fourcc, frame_rate, frame_size);
    ///

    for (int h_i = border; h_i < height + border; h_i++){
        for (int w_i = border; w_i < width + border; w_i++){
            ///
            /// YOUR CODE HERE
            cv::Rect roi = cv::Rect(w_i - (element.size().width - 1)/2, h_i - (element.size().height - 1)/2, element.size().width, element.size().height);
            cv::Mat slice = paddedDemoImage(roi);
            minMaxLoc(slice, &minVal, &maxVal);
            if(paddedDemoImage.at<uchar>(h_i, w_i) > minVal){
                paddedErodedImage.at<uchar>(h_i, w_i) = minVal;
            }
            ///
            // Resize output to 50x50 before writing it to the video
            ///
            /// YOUR CODE HERE
            cv::Mat resizedPaddedErodedImage;
            resize(paddedErodedImage * 255, resizedPaddedErodedImage, frame_size, 1.0, 1.0, cv::INTER_NEAREST);
            ///
            // Convert resizedFrame to BGR before writing
            ///
            /// YOUR CODE HERE
            cv::Mat resizedPaddedErodedImageChannels[3], resizedPaddedErodedImageBGR;
            for(int i = 0; i < 3; i++){
                resizedPaddedErodedImageChannels[i] = resizedPaddedErodedImage;
            }
            merge(resizedPaddedErodedImageChannels, 3, resizedPaddedErodedImageBGR);
            erosionScratch.write(resizedPaddedErodedImageBGR);
            ///
        }
    }

    // Release the VideoWriter object
    ///
    /// YOUR CODE HERE
    erosionScratch.release();
    ///

    // Display final image (cropped)
    ///
    /// YOUR CODE HERE
    paddedErodedImage *= 255;
    showImage("Demo Image", paddedErodedImage);
    ///
    return 0;
}