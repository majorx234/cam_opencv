#include "local_binary_pattern.h"


local_binary_pattern::local_binary_pattern() : startBit(0), clockWise(0)
{} 
local_binary_pattern::~local_binary_pattern()
{}

int local_binary_pattern::apply_image_process(const cv::Mat &in, cv::Mat &out)
{

  CV_Assert((in.type() == CV_8UC1));

  //pointermask
  const uchar *p[9] ;

  int  bin_pat_midle;
  int row = 0;
  int col = 0;
  cv::Size size = in.size();
  out = cv::Mat::zeros(size, CV_8UC1);

  for (int row = 1; row < in.rows - 1; ++row) {
    p[0] = in.ptr(row - 1);
    p[1] = in.ptr(row - 1);
    p[2] = in.ptr(row - 1);
    p[3] = in.ptr(row);
    p[4] = in.ptr(row + 1);
    p[5] = in.ptr(row + 1);
    p[6] = in.ptr(row + 1);
    p[7] = in.ptr(row);
    p[8] = in.ptr(row);

    p[1]++;
    p[8]++;
    p[5]++;

    p[2]++;
    p[3]++;
    p[4]++;

    p[2]++;
    p[3]++;
    p[4]++;
    for (col = 1; col < in.cols - 1; ++col)
    {
      unsigned char bin_pat = 0;
      bin_pat_midle = *p[8]++;
      bin_pat |= (bin_pat_midle + threshold < *p[0]++) ? 0  : 128;
      bin_pat |= (bin_pat_midle + threshold < *p[1]++) ? 0  : 64;
      bin_pat |= (bin_pat_midle + threshold < *p[2]++) ? 0  : 32;
      bin_pat |= (bin_pat_midle + threshold < *p[3]++) ? 0  : 16;
      bin_pat |= (bin_pat_midle + threshold < *p[4]++) ? 0  : 8;
      bin_pat |= (bin_pat_midle + threshold < *p[5]++) ? 0  : 4;
      bin_pat |= (bin_pat_midle + threshold < *p[6]++) ? 0  : 2;
      bin_pat |= (bin_pat_midle + threshold < *p[7]++) ? 0  : 1;
      out.at<uchar>(cv::Point(row,col)) = bin_pat;
    }
  }

}

void local_binary_pattern::set_parameter(int startBit_,
    bool clockWise_)
{
  startBit = startBit_;
  clockWise = clockWise_;
}