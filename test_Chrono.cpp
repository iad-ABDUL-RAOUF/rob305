#include "Chrono.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char* argv[])
{
  unsigned int waitTime_s = 1;
  if (argc > 1)
  {
    waitTime_s = std::atoi(argv[1]);
  }
  std::cout << "Waiting for " << waitTime_s << " seconds" << std::flush;
  Chrono chrono;
  sleep(waitTime_s);
  chrono.stop();
  std::cout <<"done. Chrono time = " << chrono.lap() << " milliseconds." << std::endl;
  return 0;
}
