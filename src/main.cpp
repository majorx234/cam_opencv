#include <stdio.h>
#include <csignal>
#include "cam.h"
#include "filter.h"
#include "manipulation.h"
#include "opencv2/opencv.hpp"
#include <thread>
#include "cvmat2qimage.h"
#include <QApplication>
#include "qt_display_parameters_window.h"

int threadGetImageSetOut(Cam &mycam, Filter &myfilter, QtDisplayParametersWindow &mein_fenster);
int test_fnct(int a);

int abbrechen = 0;
void signalHandler1( int signum ) {

   printf("Interrupt Signal: %d\n", signum);
   abbrechen=1;
  // exit(signum);  

}
void signalHandler2( int signum ) {
   printf("Interrupt Signal: %d\n", signum);

   // cleanup and close up stuff here  
   // terminate program  

  // exit(signum);  

}


int main(int argc, char *argv[]) {

  signal(SIGINT, signalHandler1);  
  signal(SIGUSR1, signalHandler2);  
  QApplication app(argc, argv);

  Cam mycam(0);

  Filter myfilter;

  //Manipulation willItWork;

  QtDisplayParametersWindow mein_fenster(NULL);
  mein_fenster.show();
  
  
  std::thread t1(&threadGetImageSetOut, std::ref(mycam), std::ref(myfilter), std::ref(mein_fenster));
  //std::thread t2(test_fnct,1);

  printf("test1\n");

  app.exec();
  abbrechen =1;
  t1.join();
  return 0; 
}


int threadGetImageSetOut(Cam &mycam, Filter &myfilter, QtDisplayParametersWindow &mein_fenster)
{
  cv::Mat blurred,edges,cutted,cutted2;
  while(abbrechen == 0)
  {
    cv::Mat src, dst;

    QImage tmp_image;
    mycam.getFrame(src);
   

    myfilter.medianBlurFilter(src,blurred);
    //willItWork.drawLine(image, blurred, 20, 40, 200, 400);
    myfilter.rangeFilter(blurred,edges);
    myfilter.cutFilter1(edges,cutted,15,20,0,20);
    myfilter.normalize(cutted,cutted2);
    tmp_image = cvmat2qimage( cutted2 );
    mein_fenster.setBild(tmp_image);
    //cv::waitKey(20);
  }
  return 0;
}