#ifndef Calibrator_hpp_INCLUDED
#define Calibrator_hpp_INCLUDED

#include "Looper.hpp"
#include "Timer.hpp"
#include <vector>

class Calibrator : public PeriodicTimer
{
  public:
    Calibrator(double samplingPeriod_ms, unsigned int nSamples);
    double nLoops(double duration_ms) const {return a*duration_ms+b;}
  
  protected:
    void callback() override;

  private:
    Looper looper;
    double a; 
    double b;
    std::vector<double> samples;
    unsigned int nSamples;
    unsigned int nSamplesDone;
    
};

#endif