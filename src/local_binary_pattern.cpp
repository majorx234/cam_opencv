#include "local_binary_pattern.h"
#include <bitset>

bool isUniform(uchar in)
{
  unsigned char bitfield = in ^ (in << 1 | in >> 7);
  if (std::bitset<8>(bitfield).count() <=2)
    return true;
  return false;
}

local_binary_pattern::local_binary_pattern() : startBit(0), clockWise(true), threshold(0), uniformize(true)
{} 
local_binary_pattern::~local_binary_pattern()
{}

int local_binary_pattern::apply_image_process(const cv::Mat &in, cv::Mat &out)
{
 
  CV_Assert((in.type() == CV_8UC1));
  printf("local_binary_pattern::apply_image_process(): start\n");
  //pointermask
  const uchar *p[9] ;

  int  bin_pat_midle;
  
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
    
    for (int col = 0; col < in.cols - 1; ++col)
    {
      unsigned char bin_pat = 0;
      bin_pat_midle = *++p[8];
      bin_pat |= (bin_pat_midle + threshold < *++p[0]) ? 0  : 128;
      bin_pat |= (bin_pat_midle + threshold < *++p[1]) ? 0  : 64;
      bin_pat |= (bin_pat_midle + threshold < *++p[2]) ? 0  : 32;
      bin_pat |= (bin_pat_midle + threshold < *++p[3]) ? 0  : 16;
      bin_pat |= (bin_pat_midle + threshold < *++p[4]) ? 0  : 8;
      bin_pat |= (bin_pat_midle + threshold < *++p[5]) ? 0  : 4;
      bin_pat |= (bin_pat_midle + threshold < *++p[6]) ? 0  : 2;
      bin_pat |= (bin_pat_midle + threshold < *++p[7]) ? 0  : 1;
      uchar out_grey_value;

      out_grey_value = bin_pat;
      if (uniformize)
        if(!isUniform(bin_pat)) out_grey_value = 0;

      out.at<uchar>(cv::Point(col+1,row)) = out_grey_value;
    }

  }
  return 0;
}

void local_binary_pattern::set_parameter(int startBit_,
    bool clockWise_,
    bool uniformize_,
    int threshold_)
{
  startBit = startBit_;
  clockWise = clockWise_;
  uniformize = uniformize_;
  threshold = threshold_;
}

