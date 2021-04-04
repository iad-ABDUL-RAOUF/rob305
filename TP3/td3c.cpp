#include "Calibrator.hpp"
#include "CpuLoop.hpp"
#include <iostream>
#include "Chrono.h"


int main()
{
  // calibrate on 4 samples for 8 secondes
  std::cout << "begin calibration" << std::endl;
  Calibrator calibrator(2000, 4);
  CpuLoop cpuLoop(calibrator);
  std::cout << "end calibration" << std::endl;
  

  // run loop for 15 secondes
  double duration_ms = 3000 ;
  std::cout << "begin runTime "<<duration_ms<<" milliseconds" << std::endl;
  Chrono chrono;
  cpuLoop.runTime(duration_ms);
  chrono.stop();
  std::cout << "end runTime, lasted "<<chrono.lap() << " milliseconds" << std::endl;

  return 0;
}