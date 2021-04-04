#include "Calibrator.hpp"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples)
: nSamples(nSamples), nSamplesDone(0)
{
  PeriodicTimer::start(samplingPeriod_ms);
  looper.runLoop();
  
  // contruct samples time vector
  std::vector<double> times;
  for (unsigned int i=1;i<=nSamples; i++)
  {
    times.push_back(samplingPeriod_ms*i);
  }
  // do linear regression
  double ySum = 0;
  double xxSum = 0;
  double xSum = 0;
  double xySum = 0;
  for (unsigned int i=0;i<nSamples; i++)
  {
    ySum += samples[i]; //ySum
    xSum += times[i]; //xSum
    xxSum += times[i]*times[i];
    xySum += times[i]*samples[i];
  }
  a = (nSamples*xySum - xSum*ySum)/(nSamples*xxSum - xSum*xSum);
  b = (xxSum*ySum - xSum*xySum)/(nSamples*xxSum - xSum*xSum);
}

void Calibrator::callback()
{
  nSamplesDone++;
  if (nSamplesDone<nSamples)
  {
    samples.push_back(looper.getSample());
  }
  else
  {
    samples.push_back(looper.stopLoop());
  }
}