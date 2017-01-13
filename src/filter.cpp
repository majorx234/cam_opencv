#include "filter.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
  
int filter::kantenFilter(cv::Mat &in,cv::Mat &out){
  cv::Canny( in, out, 50, 150, 3);
}
  
int filter::medianBlurFilter(cv::Mat &in,cv::Mat &out){
  cv::medianBlur(in,out,5);
}
  
int filter::rangeFilter(cv::Mat &in,cv::Mat &out){

}
