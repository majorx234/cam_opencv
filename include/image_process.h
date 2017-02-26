#ifndef IMAGE_PROCESS_H_
#define IMAGE_PROCESS_H_

#include "opencv2/opencv.hpp"

class image_process
{
public:
	image_process() = default;
	virtual ~image_process() =default;
	virtual int apply_image_process(const cv::Mat &in,cv::Mat &out)
  {};

};



#endif