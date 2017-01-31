#ifndef CAM_H_
#define CAM_H_

#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"


class Cam
{
private:
  cv::VideoCapture cap;


public: 
  explicit Cam(int cam_nr);
  ~Cam(); 
  int getFrame(cv::Mat &image);
  void test();

};
#endif // CAM_H_