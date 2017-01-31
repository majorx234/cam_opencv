#include "qt_cam_opencv_controller.h"
#include "image_manipulation_model.h"
#include "qt_image_view.h"
#include "manipulation_parameter.h"
#include "cvmat2qimage.h"
#include <chrono>

QtCamOpenCvController::QtCamOpenCvController(int &new_argc, char **new_argv) :  abbrechen(0), 
                                                                                closed(0),
                                                                                argc(new_argc), 
                                                                                argv(new_argv),
                                                                                QtCamOpenCvControllerThread(&QtCamOpenCvController::QtCamOpenCvControllerFunction,this) 

{
}

QtCamOpenCvController::~QtCamOpenCvController()
{
  abbrechen = 1;
  printf("Controller closed\n");
  QtCamOpenCvControllerThread.join();
}

void QtCamOpenCvController::close()
{
  printf("Controller->close\n");
  abbrechen = 1;
}

int QtCamOpenCvController::isClosed()
{
  if(closed){
    return 1;
  }
  return 0;
}

int QtCamOpenCvController::QtCamOpenCvControllerFunction()
{
  // init
  ImageManipulationModel cam_filter_obj;
  QtImageView            display_obj( argc, argv);
  ManipulationParameter params;

  //cam_filter_obj.getParameter(params);
  cv::Mat src;
  QImage dst;
  int test = abbrechen;

  while(!abbrechen)
  { 
    display_obj.getParameter(params);
    cam_filter_obj.setParameter(params);
    cam_filter_obj.getImage( src );
    dst = cvmat2qimage( src );
    display_obj.setImage( dst );
    if(display_obj.isClosed())
      abbrechen = 1; 
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  closed = 1;
  return 0;
  //controll
}