#include "filter.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <assert.h>
#include <stdio.h>
  
int Filter::kantenFilter(cv::Mat &in,cv::Mat &out)
{
  //cv::Canny( in, out, 50, 150, 3);

}
  
int Filter::medianBlurFilter(cv::Mat &in,cv::Mat &out)
{
  cv::medianBlur(in,out,5);
}
  
int Filter::rangeFilter(cv::Mat &in,cv::Mat &out)
{
	// eingangsbildspiegelung
	flip(in, fliped, 1);
	// rgb2gw
	cvtColor( fliped, fliped, CV_BGR2GRAY );
	// maximum-filter
	erode(fliped, min, cv::Mat::ones(3,3,CV_32F), cv::Point(-1,-1), 1, 1, 1 );
	// minimumfilter
	dilate(fliped, max, cv::Mat::ones(3,3,CV_32F), cv::Point(-1,-1), 1, 1, 1 );
	// der waaaahnsinnig komplex range-filter-prozess
	out = (max - min);

}

int Filter::cutFilter1(const cv::Mat& in, cv::Mat& out, int lowerThresh, int upperThresh,int lowerValue, int upperValue)
{

	assert((in.channels() == 1) && (in.depth() == CV_8U));
	assert((lowerThresh >= 0) && (lowerThresh <= 255) && (upperThresh >= 0) && (upperThresh <= 255));


	
	cv::Size size = in.size();
	//printf("size h %d, w %d  type: %d \n",size.height,size.width,in.type());

	out.create(size, in.type());

	cv::MatConstIterator_<VT1> inIter = in.begin<VT1>(), inIterEnd = in.end<VT1>();
	cv::MatIterator_<VT1> outIter = out.begin<VT1>();
	//VT1 px2;
	for( ; inIter != inIterEnd; ++inIter, ++outIter)
	{
		VT1 px = *inIter;
		*outIter = VT1(cv::saturate_cast<unsigned char>((px[0] <= lowerThresh) ? lowerValue : ((px[0] >= upperThresh) ? upperValue : px[0])));

	}
	//printf("filter end \n");


}

int Filter::normalize(const cv::Mat &in, cv::Mat &out)
{
	cv::Size size = in.size();
	out.create(size, in.type());
	unsigned char max, min;
	double dmin,dmax;
	cv:minMaxLoc(in, &dmin, &dmax);
	min = cv::saturate_cast<unsigned char>(dmin);
	max = cv::saturate_cast<unsigned char>(dmax);
	//printf("dmax: %d dmin: %d \n", max, min);
	out = 255-((in-min) * 255/(max-min));
}



int Filter::colorFilter(cv::Mat &in,cv::Mat &out)
{
	// eingangsbildspiegelung
	flip(in, fliped, 1);
	// aufspaltung in rgb-Kanäle
	split(fliped, bgr);
	// grün
	bgr[1].setTo(0);
	// rot
	bgr[2].setTo(0);
	// blau
	for(int i = 0; i < bgr[0].cols; i++)
		for(int ii = 0; ii < bgr[0].rows; ii++)
	{
		{
			// sigmodialfilter 100+
			bgr[0].at<int>(i,ii) = bgr[0].at<int>(i,ii)*(0.5*(1 - tanh((bgr[0].at<int>(i,ii)-100)/8)));
		}
	}
	// zusammenführung zu farbbild
	merge(bgr, 3, out);
}


int Filter::apply_image_process(const cv::Mat &in, cv::Mat &out)
{
	int error = 0;
  if(image_processes.size() == 0)
  {
 	  out=in;
    return 0;
  } 
  cv::Mat tmp_in = in;
  cv::Mat tmp_out;
  for(std::vector<image_process>::iterator it = image_processes.begin();it != image_processes.end();++it)
  {
  	error = it->apply_image_process(tmp_in,tmp_out);
  	if(error)
  	{
  		return error;
  	}
  	tmp_in = tmp_out;
  }	
  out = tmp_out;
  return error;
} 

int Filter::add_image_process(image_process new_process)
{
  image_processes.push_back(new_process);
  return image_processes.size();
}