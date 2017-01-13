#include "manipulation.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

int Manipulation::drawLine(cv::Mat &in,cv::Mat &out,int x1,int y1,int x2, int y2)
{
	pt1 = cv::Point(x1, y1);
	pt2 = cv::Point(x2, y2);
	lineThickness = 1;
	lineType = 8;
	lineShift = 0;
	lineColor = cv::Scalar(255, 255, 255); //r,g,b

	//However, this does work with a CV_8U (8-bit unsigned) image, as opposed to CV_32F (32-bit float) image that I have here. (For CV_8U, you must pass cv::Scalar(255) instead of cv::Scalar(1.0) into the line function to compare) 

	cv::line(out, pt1, pt2, lineColor, lineThickness, lineType, lineShift);

}



