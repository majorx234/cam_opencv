#ifndef CAM_H_
#define CAM_H_

#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"


class cam
{
private:
  cv::VideoCapture cap;


public: 
  cam(int cam_nr);
  ~cam(); 
  int getFrame(cv::Mat &image);
  void test();

};
#endif // CAM_H_