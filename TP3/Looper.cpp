#include "Looper.hpp"

Looper::Looper()
: doStop(false), iLoop(0.0)
{
}

double Looper::runLoop (double nLoops)
{
  while ((!doStop) and (iLoop < nLoops))
  {
    iLoop++;
  }
  double copyILoop = iLoop;
  iLoop = 0.0;
  doStop = false;
  return copyILoop;
}