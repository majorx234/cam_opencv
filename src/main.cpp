#include <stdio.h>
#include <csignal>
#include "cam.h"
#include "filter.h"
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


  cam mycam(1);

  filter myfilter;

  cv::Mat image,blurred,edges;
  cv::namedWindow("bild1",1);
  cv::namedWindow("bild2",1);
  cv::namedWindow("bild3",1);


  while(abbrechen == 0)
  {

    mycam.getFrame(image);
    myfilter.medianBlurFilter(image,blurred);
    myfilter.kantenFilter(blurred,edges);
    cv::imshow("bild1", image);
    cv::imshow("bild2", blurred);
    cv::imshow("bild3", edges);
    cv::waitKey(20);
  }
  printf("test1\n");
  return 0;
}