#ifndef Looper_hpp_INCLUDED
#define Looper_hpp_INCLUDED

class Looper
{

public:
  Looper();
  double runLoop(double nLoops=__DBL_MAX__);
  double getSample() const {return iLoop;}
  double stopLoop() {doStop = true; return iLoop;}

private:
  bool doStop;
  double iLoop;
};

#endif