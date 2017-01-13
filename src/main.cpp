#include <stdio.h>
#include <csignal>
#include "cam.h"
#include "filter.h"
#include "manipulation.h"
#include "opencv2/opencv.hpp"



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


int main() {

  signal(SIGINT, signalHandler1);  
  signal(SIGUSR1, signalHandler2);  


  Cam mycam(0);

  Filter myfilter;

  Manipulation willItWork;

  cv::Mat image,blurred,edges,cutted,cutted2;
  cv::namedWindow("bild1",1);
  cv::namedWindow("bild2",1);
  cv::namedWindow("bild3",1);


  while(abbrechen == 0)
  {

    mycam.getFrame(image);
    myfilter.medianBlurFilter(image,blurred);
    //willItWork.drawLine(image, blurred, 20, 40, 200, 400);
    myfilter.rangeFilter(blurred,edges);
    myfilter.cutFilter1(edges,cutted,15,20,0,20);
    myfilter.normalize(cutted,cutted2);
    cv::imshow("bild1", image);
    cv::imshow("bild2", edges);
    cv::imshow("bild3", cutted2);
    cv::waitKey(20);
  }
  printf("test1\n");
  return 0;
}
