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

    std::cout << "Musk info: " << musk.size().width << "X" << musk.size().height << ", " << musk.channels() << "." << std::endl;
    std::cout << "Sunglasses info: " << sunglass.size().width << "X" << sunglass.size().height << ", " << sunglass.channels() << "." << std::endl;

    showImage("Elon Musk", musk);
    showImage("Sunglasses", sunglass);

    // converting images to 32 bit float
    cv::Mat musk_norm = musk.clone();
    cv::Mat sunglass_norm = sunglass.clone();
    double scale_factor = 1.0/255;
    double shift = 0;
    musk_norm.convertTo(musk_norm, CV_32FC3, scale_factor, shift);
    sunglass_norm.convertTo(sunglass_norm, CV_32FC4, scale_factor, shift);

    double sunglasses_aspect_ratio = (double)sunglass.size().height/(double)sunglass.size().width;

    // find area on face for placement of glasses
    const int roi_width = 270;
    const cv::Rect roi = cv::Rect(130, 150, roi_width * sunglasses_aspect_ratio, roi_width);
    std::cout << roi << std::endl;
    
    std::cout << "ROI origin is: " << roi.x << " x " << roi.y << std::endl;
    std::cout << "ROI size is: " << roi.width << " x " << roi.height << std::endl;
    std::cout << "ROI aspect ratio: " << sunglasses_aspect_ratio << std::endl;

    cv::Mat eyes_roi = musk(cv::Range(roi.x, roi.x + roi.width), cv::Range(roi.y, roi.y + roi.height));
    showImage("Eyes", eyes_roi);

    // create scaled version of the sunglasses image to fit in eyes_roi
    cv::Mat scaled_sunglass;
    cv::resize(sunglass, scaled_sunglass, eyes_roi.size(), 1.0, 1.0, cv::INTER_LINEAR);
    showImage("Scaled Glasses", scaled_sunglass);
    
    // split the image channels for the sunglasses
    cv::Mat sunglass_RGB, sunglass_RGB_channels[3], sunglass_RGBA[4], sunglass_mask, sunglass_mask_channels[3], eye_mask, eye_mask_channels[3];
    cv::split(scaled_sunglass, sunglass_RGBA);

    for(int i = 0; i < 3; i++){
        sunglass_mask_channels[i] = sunglass_RGBA[3];   // create mask rgb
        sunglass_RGB_channels[i] = sunglass_RGBA[i];    //create sunglass rgb
    }
    cv::merge(sunglass_mask_channels, 3, sunglass_mask);
    cv::merge(sunglass_RGB_channels, 3, sunglass_RGB);
    showImage("Mask", sunglass_mask);
    showImage("RGB", sunglass_RGB);

    sunglass_mask /= 255;
    std::cout << sunglass_mask.size() << " : " << eyes_roi.size() << std::endl;

    // create glasses masked by alpha and eye region masked by complement of alpha
    cv::Mat sunglass_masked, eye_masked;
    sunglass_masked = sunglass_RGB.clone();
    eye_masked = eyes_roi.clone();

    for(int i = 0; i < 3; i++){
        eye_mask_channels[i] = 1 - (sunglass_mask_channels[i]/255);
    }
    cv::merge(eye_mask_channels, 3, eye_mask);

    cv::multiply(sunglass_RGB, sunglass_mask, sunglass_masked);
    cv::multiply(eyes_roi, eye_mask, eye_masked);
    showImage("Eyes masked", eye_masked);
    showImage("Glasses masked", sunglass_masked);

    cv::Mat composite;
    cv::add(eye_masked, sunglass_masked, composite);
    
    cv::Mat musk_glasses = musk.clone();
    composite.copyTo(musk_glasses(cv::Range(roi.x, roi.x + roi.width), cv::Range(roi.y, roi.y + roi.height)));
    showImage("Musk with glasses", musk_glasses);

    return 0;
}