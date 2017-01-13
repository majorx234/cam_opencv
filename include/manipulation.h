#ifndef MANIPULATION_H_
#define MANIPULATION_H_

#include "opencv2/opencv.hpp"

class Manipulation
{
private:
	cv::Point pt1, pt2;
	int lineThickness;
	int lineType;
	int lineShift;
	cv::Scalar lineColor;

public:
	int drawLine(cv::Mat &in,cv::Mat &out,int x1,int y1,int x2, int y2);
};

#endif // MANIPULATION_H_