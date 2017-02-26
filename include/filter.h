#ifndef FILTER_H_
#define FILTER_H_

#include "opencv2/opencv.hpp"
#include "image_process.h"

typedef cv::Vec<unsigned char,1> VT1;
typedef cv::Vec<unsigned char,3> VT3;

class Filter
{
private:
	cv::Mat min;
	cv::Mat max;
	cv::Mat bgr[3];
	cv::Mat fliped;

  std::vector<image_process> image_processes;
public:
  int kantenFilter(cv::Mat &in,cv::Mat &out);
  int medianBlurFilter(cv::Mat &in,cv::Mat &out);
  int rangeFilter(cv::Mat &in,cv::Mat &out);
  int colorFilter(cv::Mat &in, cv::Mat &out);
  int cutFilter1(const cv::Mat &in, cv::Mat &out, int lowerThresh, int upperThresh,int lowerValue, int upperValue);
  int normalize(const cv::Mat &in, cv::Mat &out);
  
  int apply_image_process(const cv::Mat &in, cv::Mat &out);
  
  int add_image_process(image_process new_process);
};




#endif // FILTER_H_