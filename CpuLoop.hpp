#ifndef CpuLoop_hpp_INCLUDED
#define CpuLoop_hpp_INCLUDED

#include "Calibrator.hpp"

class CpuLoop : public Looper
{
public:
  CpuLoop(Calibrator& calibrator);
  ~CpuLoop();
  void runTime(double duration_ms);

private:
  Calibrator& calibrator_;
};

#endif
