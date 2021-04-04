#include "Chrono.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char* argv[])
{
  // Testing class chrono
  
  // init waiting time
  unsigned int waitTime_s = 2;
  if (argc > 1)
  {
    waitTime_s = std::atoi(argv[1]);
  }
  std::cout << "Waiting for " << waitTime_s << " seconds\n" << std::flush;

  //using chrono classs
  Chrono chrono;
  sleep(waitTime_s);
  chrono.restart();
  sleep(waitTime_s);
  chrono.stop();

  //printing results
  std::cout <<"done. Chrono time = " << chrono.lap() << " milliseconds." << std::endl;
  std::cout <<"Start time = "<<chrono.startTime() << " ; Stop time = "<<chrono.stopTime()<<std::endl;

  return 0;
}
