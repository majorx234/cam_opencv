#include "image_manipulation_model.h"

ImageManipulationModel::ImageManipulationModel() :  myCam(0), 
                                                    myFilter(), 
                                                    abbrechen(0), 
                                                    imageWritten(0), 
                                                    ImageGrapManipulationThread(&ImageManipulationModel::imageManipulationLoopFunction, this)
{
  params.lowerThresh = 15;
  params.upperThresh = 20;
  params.lowerValue  = 0;
  params.upperValue  = 20;
  
}




ImageManipulationModel::~ImageManipulationModel()
{
  abbrechen = 1;
  ImageGrapManipulationThread.join();
  printf("ImageManipulationModel destructor finished");
}


int ImageManipulationModel::imageManipulationLoopFunction()
{
  cv::Mat src, blurred, edges, cutted, cutted2;
  ManipulationParameter myParams;

  while(abbrechen == 0)
  {

    
    myCam.getFrame(src);
   
   
    myFilter.medianBlurFilter(src,blurred);
    getParameter(myParams);   
    //willItWork.drawLine(image, blurred, 20, 40, 200, 400);
    myFilter.rangeFilter(blurred,edges);
    myFilter.cutFilter1(edges,cutted,
      myParams.lowerThresh,
      myParams.upperThresh,
      myParams.lowerValue,
      myParams.upperValue);
    myFilter.normalize(cutted,cutted2);
    setImage(cutted2);
   }

  return 0;
}

int ImageManipulationModel::getImage(cv::Mat& manipulatedImage)
{
  /*
  while(imageWritten==0)
  {
   imageCv.wait(lock)
   if(closed==1)
    { 
      return 0;
    }
  }*/
  if(imageWritten)
  {
    std::unique_lock<std::mutex> lock(imageMutex);
    // image read
    manipulatedImage.release();
    manipulatedImage = image.clone();
    imageWritten = 0;
  }
  else
  {  
    return -1;
  } 
  return 0; 
}

int ImageManipulationModel::setImage(cv::Mat& inputImage)
{
  {
    std::unique_lock<std::mutex> lock(imageMutex);
    //imagewrite
    image.release();
    image = inputImage.clone();
    imageWritten = 1;
  }
  //imageCv.notify_one();
  return 0;
}

void ImageManipulationModel::getParameter(ManipulationParameter &new_params)
{
  std::unique_lock<std::mutex> lock(ParameterMutex);
  new_params.lowerThresh = params.lowerThresh;
  new_params.upperThresh = params.upperThresh;
  new_params.lowerValue  = params.lowerValue;
  new_params.upperValue  = params.upperValue;
}
void ImageManipulationModel::setParameter(ManipulationParameter new_params)
{
  std::unique_lock<std::mutex> lock(ParameterMutex);
  params.lowerThresh = new_params.lowerThresh;
  params.upperThresh = new_params.upperThresh;
  params.lowerValue  = new_params.lowerValue;
  params.upperValue  = new_params.upperValue;
}
void ImageManipulationModel::stop()
{
  abbrechen = 1;

}