#ifndef LOCAL_BINARY_PATTERN_H
#define LOCAL_BINARY_PATTERN_H 

#include "image_process.h"

class local_binary_pattern : public image_process
{

  int startBit;
  bool clockWise;
  int  threshold;
  bool uniformize;
public:  
  local_binary_pattern();
  ~local_binary_pattern();	
  int apply_image_process(const cv::Mat &in,cv::Mat &out);
  void set_parameter(int startBit_, 
    bool clockWise_,
    bool uniformize_,
    int threshold);
};


#endif //LOCAL_BINARY_PATTERN_H 