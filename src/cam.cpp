#include "cam.h"
#include <stdio.h>

Cam::Cam(int cam_nr)
{


  cap = cv::VideoCapture(cam_nr);
  printf("cam erstellt\n");

}

Cam::~Cam()
{
  printf("cam zerstörrt\n");
}

int Cam::getFrame(cv::Mat &image)
{
  cap >> image;
  return 0;
}

void Cam::test()
{
  printf("cam da\n");
}