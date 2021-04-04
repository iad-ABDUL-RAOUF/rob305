#include "Calibrator.hpp"
#include "CpuLoop.hpp"
#include <iostream>


int main(int argc, char *argv[])
{
  // calibrate on 4 samples for 8 secondes
  std::cout << "begin calibration" << std::endl;
  Calibrator calibrator(2000, 4);
  CpuLoop cpuLoop(calibrator);
  std::cout << "end calibration" << std::endl;
  

  // run loop for 15 secondes
  std::cout << "begin runTime" << std::endl;
  cpuLoop.runTime(15000);
  std::cout << "end runTime" << std::endl;
  return 0;
}