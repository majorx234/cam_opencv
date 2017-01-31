#include <stdio.h>
#include <csignal>
#include "qt_cam_opencv_controller.h"
#include <chrono>

int abbrechen = 0;
void signalHandler1( int signum ) {

   printf("Interrupt Signal: %d\n", signum);
   abbrechen=1;
  // exit(signum);  

}


int main(int argc, char *argv[]) {

  signal(SIGINT, signalHandler1);  

  QtCamOpenCvController controller_obj(argc, argv);
  while(!abbrechen)
  {
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if(controller_obj.isClosed())
      break;
  }
  if(abbrechen)
    controller_obj.close();
  return 0; 
}