#include <iostream>
#include <opencv2/opencv.hpp>
/****************************************************/
#include "Ehancement.hpp"


int main(int argc, const char * argv[]) {
    
    cv::Mat src = cv::imread("./imgs/original.bmp",cv::IMREAD_COLOR);
    
    cv::Mat dst1,dst2,dst3,dst4;
    Enhancer en;
    
    en.EnhancementForColor(src, dst1, 0);
    en.EnhancementForColor(src, dst2, 1, 1.5);
    en.EnhancementForColor(src, dst3, 2, 1, 1.1);
    en.EnhancementForColor(src, dst4, 3);
    
    cv::imshow("original",src);
    cv::imshow("result negative",dst1);
    cv::imshow("refult logarithmic",dst2);
    cv::imshow("result gamma",dst3);
    cv::imshow("result histequalize",dst4);
    
    cv::imwrite("./imgs/negative.bmp",dst1);
    cv::imwrite("./imgs/logarithmic.bmp",dst2);
    cv::imwrite("./imgs/gamma.bmp",dst3);
    cv::imwrite("./imgs/histequalize.bmp",dst4);
    
    cv::waitKey(0);
    cv::destroyAllWindows();
    
}
