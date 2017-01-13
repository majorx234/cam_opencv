#ifndef FILTER_H_
#define FILTER_H_

#include "opencv2/opencv.hpp"

typedef cv::Vec<unsigned char,1> VT1;
typedef cv::Vec<unsigned char,3> VT3;

class Filter
{
private:
	cv::Mat min;
	cv::Mat max;
	cv::Mat bgr[3];
	cv::Mat fliped;
public:
  int kantenFilter(cv::Mat &in,cv::Mat &out);
  int medianBlurFilter(cv::Mat &in,cv::Mat &out);
  int rangeFilter(cv::Mat &in,cv::Mat &out);
  int colorFilter(cv::Mat &in, cv::Mat &out);
  int cutFilter1(const cv::Mat &in, cv::Mat &out, int lowerThresh, int upperThresh,int lowerValue, int upperValue);
  int normalize(const cv::Mat &in, cv::Mat &out);
};




#endif // FILTER_H_