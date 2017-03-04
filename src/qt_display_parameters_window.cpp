#include "qt_display_parameters_window.h"
#include "cvmat2qimage.h"
#include <QCoreApplication>

QtDisplayParametersWindow::QtDisplayParametersWindow(QWidget *parent) : QMainWindow(parent),
                                                                        pixmapItem(NULL),
                                                                        bildReadingRequest(false)
{

  closeButton = new QPushButton("close");
  newFrameButton = new QPushButton("new frame");
  parameterBox = new QDoubleSpinBox();
  parameterBox->setValue(0.0);
  newParameter = new QPushButton("newParameter");

  scene = new QGraphicsScene();
  scene_view = new QGraphicsView(scene);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(closeButton,0,1);
  mainLayout->addWidget(newFrameButton,0,2);
  mainLayout->addWidget(parameterBox,1,1);
  mainLayout->addWidget(newParameter,1,2);
  mainLayout->addWidget(scene_view,2,1);

  QWidget *window = new QWidget(this);
  window->setLayout(mainLayout);


  setCentralWidget(window);
  //setLayout(mainLayout);
  setWindowTitle("layouts");
  screenRefreshTimer = new QTimer(this);
  screenRefreshTimer->setInterval(50);
  screenRefreshTimer->setSingleShot(false);
  connect(closeButton, SIGNAL(clicked()),this, SLOT(on_closebutton_clicked()) );
  //connect(newFrameButton, SIGNAL(clicked()),this, SLOT(pullNewFrameLockFree()) );
  //connect(screenRefreshTimer, SIGNAL(timeout()),this, SLOT(pullNewFrameLockFree()) );
  connect(newFrameButton, SIGNAL(clicked()),this, SLOT(pullNewFrame()) );
  connect(screenRefreshTimer, SIGNAL(timeout()),this, SLOT(pullNewFrame()) );
 
  
  connect(newParameter,SIGNAL(clicked()),this,SLOT(on_new_parameter_clicked()));
  //connect(parameterBox,SIGNAL(editingFinished()),this,SLOT(on_new_parameter_clicked()));
  screenRefreshTimer->start();
}
QtDisplayParametersWindow::~QtDisplayParametersWindow()
{

}

void QtDisplayParametersWindow::on_closebutton_clicked()  
{
  QCoreApplication::quit();
}

void QtDisplayParametersWindow::pullNewFrame()
{ //lesen
  printf("test wait\n");
  
  {

    std::unique_lock<std::mutex> bildReadingRequestLock(bildReadingRequestMutex);
    bildReadingRequest = true;
    bildReadingRequestCV.wait(bildReadingRequestLock);

  }

  std::unique_lock<std::mutex> lock(bildMutex);
  QPixmap pixmap( QPixmap::fromImage(bild));
  if(!pixmapItem)
  {
    pixmapItem  = scene->addPixmap(pixmap);
  }
  else
  {
    pixmapItem->setPixmap(pixmap);
  }
  printf("image putted in scene\n");
  bildReadingRequest = false;
  bildReadingRequestCV.notify_one();

}

void QtDisplayParametersWindow::on_new_parameter_clicked()  
{
  parameter = parameterBox->value();
}

double QtDisplayParametersWindow::getParameter()
{
  return parameter;
}

void QtDisplayParametersWindow::setBild(QImage &newBild)
{
  static int bild_count;
  {
    //
    printf("mutex??\n");
    if(bildReadingRequest)
    {  
      std::unique_lock<std::mutex> lock(bildReadingRequestMutex);
      bildReadingRequestCV.notify_one();  
      printf("write wait\n");
      bildReadingRequestCV.wait(lock);
      printf("writer go\n");
    }  
  }
  {
    std::unique_lock<std::mutex> lock(bildMutex);    
    bild = newBild;
    bildReadingRequestCV.notify_one();  
  }
  bild_count++;
  printf("QtDisplayParametersWindow::setBild(): new image set by Controller %d \n",bild_count);
}

void QtDisplayParametersWindow::pullNewFrameLockFree()
{
  int tmp_read_image = lastImage;
  readImage = tmp_read_image;
  QPixmap pixmap( QPixmap::fromImage(bildLockFree[lastImage]));
  int temp_last_image = lastImage;
  printf("pullNewFrameLockFree: %d\n",temp_last_image);
  if(!pixmapItem)
  {
    pixmapItem  = scene->addPixmap(pixmap);
  }
  else
  {
    pixmapItem->setPixmap(pixmap);
  }
} 
void QtDisplayParametersWindow::setBildLockFree(QImage &newBild)
{
  printf("setBildLockFree start %d\n");
  for(int i = 0;i<3;i++)
  {
    if((i!=lastImage)&&(i!=penultimateImage))
    {
      if(readImage != i)
      {
        bildLockFree[i] = newBild;
        penultimateImage  = lastImage;
        lastImage = i;
      }
      else
      {   
        bildLockFree[penultimateImage] = newBild;
        int tmp = penultimateImage;
        penultimateImage  = lastImage;
        lastImage = tmp;
      }
    
    
      break;
    }
  }
}
void QtDisplayParametersWindow::close()
{
  on_closebutton_clicked(); 
}