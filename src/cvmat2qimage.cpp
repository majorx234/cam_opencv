#include "cvmat2qimage.h"
QImage  cvmat2qimage( const cv::Mat &inMat )
{
  switch ( inMat.type() )
  {
    // 8-bit, 4 channel
  case CV_8UC4:
    {
      QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

      return image;
    }

    // 8-bit, 3 channel
  case CV_8UC3:
    {
      QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

      return image.rgbSwapped();
    }

    // 8-bit, 1 channel
  case CV_8UC1:
    {
      static QVector<QRgb>  sColorTable;

      // only create our color table once
      if ( sColorTable.isEmpty() )
      {
        for ( int i = 0; i < 256; ++i )
          sColorTable.push_back( qRgb( i, i, i ) );
      }

      QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

      image.setColorTable( sColorTable );

      return image;
    }

  default:
    break;
  }

  return QImage();
}

/**
 A Mapping of Type to Numbers in OpenCV

        C1  C2  C3  C4
CV_8U   0   8   16  24
CV_8S   1   9   17  25
CV_16U  2   10  18  26
CV_16S  3   11  19  27
CV_32S  4   12  20  28
CV_32F  5   13  21  29
CV_64F  6   14  22  30
*/
std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}