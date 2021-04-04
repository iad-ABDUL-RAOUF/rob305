#include "Semaphore.hpp"
#include <iostream>

Semaphore::Semaphore(unsigned int initCount, unsigned int maxCount)
: counter(initCount), maxCount(maxCount)
{
}

 Semaphore::~Semaphore()
{
}

void Semaphore::give()
{
  {
    Mutex::Lock lock(mutex);
    if (counter < maxCount)
    {
      counter++;
    }
    lock.notify();
    // std::cout << "in give counter = " << counter << std::endl;
  }
  
}

void Semaphore::take()
{
  {
    Mutex::Lock lock(mutex);
    if (counter == 0)
    {
      lock.wait();
    }
    counter--;
    // std::cout << "in take counter = " << counter << std::endl;
  }
  
}

bool Semaphore::take(double timeout_ms)
{
  bool isTimedOut = false;
  {
    Mutex::Lock lock(mutex, timeout_ms);
    if (counter == 0)
    {
      isTimedOut = lock.wait(timeout_ms);
    }
    if (not isTimedOut)
    {
      counter--;
    }
  }
  return isTimedOut;
}