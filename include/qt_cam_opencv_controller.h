#ifndef QT_CAM_OPENCV_CONTROLLER_H
#define QT_CAM_OPENCV_CONTROLLER_H

#include <atomic>
#include <mutex>
#include <thread>

class QtCamOpenCvController
{
public:
  explicit QtCamOpenCvController(int &new_argc, char **new_argv);
  ~QtCamOpenCvController();

  
  void close();
  int isClosed();
private:
  int QtCamOpenCvControllerFunction();

  int &argc; 
  char ** argv;
    
  std::thread QtCamOpenCvControllerThread;
  std::atomic_int abbrechen;
  std::atomic_int closed;
  

};
#endif //QT_CAM_OPENCV_CONTROLLER_H

