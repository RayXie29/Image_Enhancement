#include <iostream>
#include "Enhancement.hpp"
#include <opencv2/opencv.hpp>



void Enhancer::Negative(cv::Mat &src,cv::Mat &dst)
{
    if(src.channels() != 1) { return ;}
    dst = 255 - src;
}

void Enhancer::Logarithmic(cv::Mat &src,cv::Mat &dst,float c)
{
    if(src.channels() != 1) { return ;}
    dst = cv::Mat(src.size(),CV_8UC1);
    for(int i=0;i<src.rows;++i)
    {
        uchar *sptr = src.ptr<uchar>(i);
        uchar *dptr = dst.ptr<uchar>(i);
        for(int j=0;j<src.cols;++j)
        {
            
            dptr[j] = cv::saturate_cast<uchar>(c * 255 * log2(1+sptr[j]/255.0));
        }
    }
}

void Enhancer::gammaCorrection(cv::Mat &src, cv::Mat &dst,float c, float gamma)
{
    if(src.channels() != 1) { return ;}
    dst = cv::Mat(src.size(),CV_8UC1);
    for(int i=0;i<src.rows;++i)
    {
        uchar *sptr = src.ptr<uchar>(i);
        uchar *dptr = dst.ptr<uchar>(i);
        for(int j=0;j<src.cols;++j)
        {
            dptr[j] = cv::saturate_cast<uchar>(c * pow(double(sptr[j]),gamma))  ;
        }
    }
}


void Enhancer::CDF(cv::Mat &Hist,std::vector<float> &CDfunction)
{
    int size = Hist.rows;
    int i =0 , j=0;
    float *Hptr = Hist.ptr<float>(0);
    for(i=0;i<size;++i)
    {
        for(j=0;j<=i;++j) { CDfunction[i]+= Hptr[j];  }
    }
}

void Enhancer::HistEqualize(cv::Mat &Src,cv::Mat &Dst)
{
    Dst = cv::Mat(Src.size(),CV_8UC1);
    int histSize = 256;
    float range[] = { 0,255 };
    const float *HistRange = { range };
    
    cv::Mat SrcHist;

    cv::calcHist(&Src,1,0,cv::Mat(),SrcHist,1,&histSize,&HistRange);
    SrcHist /= (Src.cols*Src.rows);
    SrcHist *= 255;
    
    std::vector<float> CDFunction(SrcHist.rows);
    CDF(SrcHist,CDFunction);
    
    int i,j;
    for(i=0;i<Src.rows;++i)
    {
        uchar *sptr = Src.ptr<uchar>(i);
        uchar *dptr = Dst.ptr<uchar>(i);
        for(j=0;j<Src.cols;++j)
        {
            dptr[j] = cv::saturate_cast<uchar>(CDFunction[int(sptr[j])]);
        }
    }
    
    
    double minVal = 255, maxVal = 0;
    cv::minMaxLoc(Dst, &minVal, &maxVal);
    
    if(minVal > 10 || maxVal <245)
    {
        double oldRange = (maxVal - minVal);
        Dst = (((Dst-minVal)*255)/oldRange);
    }
}

void Enhancer::EnhancementForColor(cv::Mat &Src,cv::Mat &Dst,int flag,float c,float gamma)
{
    if(Src.type() != CV_8UC3) { return ;}
    Dst = Src.clone();
    
    cv::Mat yuvDst;
    cv::cvtColor(Dst, yuvDst, cv::COLOR_BGR2YUV);
    std::vector<cv::Mat> yuvVec(3);
    cv::split(yuvDst,yuvVec);
    
    cv::Mat temp;
    
    switch (flag)
    {
        case 0: Negative(yuvVec[0], temp); break;
        case 1: Logarithmic(yuvVec[0], temp,c); break;
        case 2: gammaCorrection(yuvVec[0], temp,c,gamma); break;
        case 3: HistEqualize(yuvVec[0], temp); break;
        default: HistEqualize(yuvVec[0], temp); break;
    }
    
    
    yuvVec[0] = temp;
    
    cv::merge(yuvVec, yuvDst);
    cv::cvtColor(yuvDst, Dst, cv::COLOR_YUV2BGR);
}
