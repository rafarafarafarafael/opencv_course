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
    // loading images
    const std::string face_img_path = ".\\images\\musk.jpg";
    const std::string sunglass_img_path = ".\\images\\sunglass.png";
    cv::Mat musk = cv::imread(face_img_path, cv::IMREAD_UNCHANGED);
    cv::Mat sunglass = cv::imread(sunglass_img_path, cv::IMREAD_UNCHANGED);

    // split the sunglass into channels
    cv::Mat sunglass_RGB_channels[3], sunglass_RGBA_channels[4], sunglass_RGB, sunglass_mask;
    cv::split(sunglass, sunglass_RGBA_channels);
    for(int i = 0; i < 3; i++){
        sunglass_RGB_channels[i] = sunglass_RGBA_channels[3]; // putting the alpha channel in the all three channels of sunglass_RGB_channels
    }
    cv::merge(sunglass_RGB_channels, 3, sunglass_mask); // no need to convert to normalized values as in the arithmetic version

    for(int i = 0; i < 3; i++){
        sunglass_RGB_channels[i] = sunglass_RGBA_channels[i]; // putting the color channels in the all three channels of sunglass_RGB_channels
    }
    cv::merge(sunglass_RGB_channels, 3, sunglass_RGB);

    cv::Rect roi = cv::Rect(150, 130, 270, 117);
    cv::Mat eyes_roi = musk(roi);
    cv::Mat sunglass_RGB_scaled = sunglass_RGB.clone();
    cv::Mat sunglass_mask_scaled = sunglass_mask.clone();
    cv::resize(sunglass_RGB, sunglass_RGB_scaled, roi.size(), 1.0, 1.0, cv::INTER_LINEAR);
    cv::resize(sunglass_mask, sunglass_mask_scaled, roi.size(), 1.0, 1.0, cv::INTER_LINEAR);

    // showImage("Sunglass scaled", sunglass_RGB_scaled);

    cv::Mat sunglass_mask_scaled_not = sunglass_mask_scaled.clone();
    cv::bitwise_not(sunglass_mask_scaled, sunglass_mask_scaled_not);

    // create masked versions of the images
    cv::Mat eyes_roi_masked = eyes_roi.clone();
    cv::Mat sunglass_RGB_scaled_masked = sunglass_RGB_scaled.clone();
    cv::bitwise_and(eyes_roi, sunglass_mask_scaled_not, eyes_roi_masked);
    cv::bitwise_and(sunglass_RGB_scaled, sunglass_mask_scaled, sunglass_RGB_scaled_masked);
    showImage("Eyes masked", eyes_roi_masked);
    showImage("Sunglass masked", sunglass_RGB_scaled_masked);

    // and composite them
    cv::Mat eyes_roi_with_glasses = eyes_roi.clone();
    cv::bitwise_or(eyes_roi_masked, sunglass_RGB_scaled_masked, eyes_roi_with_glasses);
    cv::Mat eyes_roi_plus_glasses = eyes_roi_masked.clone();
    eyes_roi_plus_glasses += sunglass_RGB_scaled_masked;

    showImage("Eyes with glasses", eyes_roi_with_glasses);
    showImage("Eyes plus glasses", eyes_roi_plus_glasses);

    // replace section with new ROI
    cv::Mat musk_with_glasses = musk.clone();
    eyes_roi_with_glasses.copyTo(musk_with_glasses(roi));

    showImage("Elon with glasses", musk_with_glasses);

    return 0;
}