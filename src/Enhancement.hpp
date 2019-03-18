#ifndef Enhancement_hpp
#define Enhancement_hpp

#include <opencv2/opencv.hpp>

class Enhancer
{
public:
    void Negative(cv::Mat &src,cv::Mat &dst);
    void Logarithmic(cv::Mat &src,cv::Mat &dst,float c = 1);
    void gammaCorrection(cv::Mat &src,cv::Mat &dst,float c = 1, float gamma = 1);
    void HistEqualize(cv::Mat &Src,cv::Mat &Dst);
private:
    void CDF(cv::Mat &Hist,std::vector<float> &CDfunction);
};

#endif /* Enhancement_hpp */