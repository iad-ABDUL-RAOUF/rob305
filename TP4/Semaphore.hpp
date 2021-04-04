#ifndef Semaphore_hpp_INCLUDED
#define Semaphore_hpp_INCLUDED

#include "Mutex.hpp"

class Semaphore
{
public:
  Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT32_MAX);
  ~Semaphore();
  void give();
  void take();
  bool take(double timeout_ms);

private:
  unsigned int counter;
  unsigned int maxCount;
  Mutex mutex;
};

#endif