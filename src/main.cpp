#include <iostream>
#include <opencv2/opencv.hpp>
/****************************************************/
#include "Ehancement.hpp"


int main(int argc, const char * argv[]) {
    
    cv::Mat src = cv::imread("./imgs/original.bmp",cv::IMREAD_GRAYSCALE);
    
    cv::Mat dst,dst1,dst2,dst3;
    Enhancer en;
    
    en.Negative(src, dst);
    en.Logarithmic(src, dst1,1);
    en.gammaCorrection(src, dst2,1,1.05);
    en.HistEqualize(src, dst3);
    
    cv::imshow("original",src);
    cv::imshow("result negative",dst);
    cv::imshow("refult logarithmic",dst1);
    cv::imshow("result gamma",dst2);
    cv::imshow("result histequalize",dst3);
    
    cv::imwrite("./imgs/negative.bmp",dst);
    cv::imwrite("./imgs/logarithmic.bmp",dst1);
    cv::imwrite("./imgs/gamma.bmp",dst2);
    cv::imwrite("./imgs/histequalize.bmp",dst3);
    
    cv::waitKey(0);
    cv::destroyAllWindows();
    
}
