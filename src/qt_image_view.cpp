#include "qt_image_view.h"

QtImageView::QtImageView(int &new_argc, char **new_argv) :  argc(new_argc), 
                                                            argv(new_argv), 
                                                            closed(0),
                                                            qtImageViewThread(&QtImageView::qtImageLoopFunction,this)
{
}

QtImageView::~QtImageView()
{
  myWindow->close();
  qtImageViewThread.join();
}

int QtImageView::setImage(QImage &bild)
{
  printf("QtImageView::setImage: call sezBildLockFree()\n");
  if(myWindow)
    myWindow->setBildLockFree(bild);
  return 0;
}

int QtImageView::getParameter(ManipulationParameter &params)
{
  //dummy werte kein frontend 
  params.lowerThresh = 15;
  params.upperThresh = 20;
  params.lowerValue  = 0;
  params.upperValue  = 20;
  return 0; 
}
int QtImageView::qtImageLoopFunction()
{
  QApplication app(argc, argv);
  
  myWindow = new QtDisplayParametersWindow(NULL);
  myWindow->show();
  
  app.exec(); //qt program loop

  if(myWindow)
    delete myWindow;
  closed = 1;
  return 0;
}
int QtImageView::isClosed()
{
  if(closed)
    return 1;
  return 0;
}

void QtImageView::stop()
{
  myWindow->close();
}