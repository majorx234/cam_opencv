#ifndef FILTER_H_
#define FILTER_H_

#include "opencv2/opencv.hpp"

class filter
{
public:
  int kantenFilter(cv::Mat &in,cv::Mat &out);
  int medianBlurFilter(cv::Mat &in,cv::Mat &out);
  int rangeFilter(cv::Mat &in,cv::Mat &out);
};




#endif // FILTER_H_