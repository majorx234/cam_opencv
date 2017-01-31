#ifndef CVMAT2QIMAGE_H
#define CVMAT2QIMAGE_H

#include <QImage>
#include "opencv2/opencv.hpp"

QImage  cvmat2qimage( const cv::Mat &inMat );
std::string type2str(int type); 


#endif //CVMAT2QIMAGE_H 