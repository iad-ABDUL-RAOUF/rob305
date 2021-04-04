#include "CpuLoop.hpp"

CpuLoop::CpuLoop(Calibrator& calibrator)
: calibrator_(calibrator)
{
}

 CpuLoop::~CpuLoop()
{
}

void CpuLoop::runTime (double duration_ms)
{
  runLoop(calibrator_.nLoops(duration_ms));
}