#ifndef QT_IMAGE_VIEW_H
#define QT_IMAGE_VIEW_H

#include <QImage>
#include <QApplication>
#include "qt_display_parameters_window.h"
#include <thread>
#include "manipulation_parameter.h"

class QtImageView
{

public:
  explicit QtImageView(int &new_argc, char **new_argv);
  ~QtImageView();

  int setImage(QImage &bild);
  int getParameter(ManipulationParameter &params);
  int isClosed();
  void stop();

private:
  int qtImageLoopFunction();

  int &argc; 
  char **argv;

  
  QtDisplayParametersWindow* myWindow;
  std::thread qtImageViewThread;
  std::atomic_int closed;


};

#endif //QT_IMAGE_VIEW_H