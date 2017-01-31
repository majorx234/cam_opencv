#ifndef IMAGE_MANIPULATION_MODEL_H_
#define IMAGE_MANIPULATION_MODEL_H_

#include "opencv2/opencv.hpp"
#include "cam.h"
#include "filter.h"
#include <thread>
#include "manipulation_parameter.h"
#include <atomic>
#include <mutex>


class ImageManipulationModel
{
public:
  ImageManipulationModel();
  ~ImageManipulationModel();

  int getImage(cv::Mat& manipulatedImage);
  int setImage(cv::Mat& inputImage);
  
  void getParameter(ManipulationParameter &new_params);
  void setParameter(ManipulationParameter new_params);

  // setFilter(); // theFuture.exe

  void stop();



private:
  int imageManipulationLoopFunction();

  ManipulationParameter params;
  cv::Mat image;

  Filter myFilter;
  Cam myCam;
  std::thread ImageGrapManipulationThread;
  std::atomic_int abbrechen;

  std::mutex imageMutex;
  // std::condition_variable imageCv;
  std::atomic_int imageWritten;
  std::mutex ParameterMutex;
};

#endif // IMAGE_MANIPULATION_MODEL_H_
