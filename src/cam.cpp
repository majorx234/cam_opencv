#include "cam.h"
#include <stdio.h>

cam::cam(int cam_nr)
{


  cap = cv::VideoCapture(cam_nr);
  printf("cam erstellt\n");

}

cam::~cam()
{
  printf("cam zerstörrt\n");
}

int cam::getFrame(cv::Mat &image)
{
  cap >> image;
  return 0;
}

void cam::test()
{
  printf("cam da\n");
}