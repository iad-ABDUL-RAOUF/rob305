#include "CountDown.hpp"
#include <iostream>

CountDown::CountDown(unsigned int initCount)
: PeriodicTimer(), count_(initCount)
{
}

void CountDown::callback()
{
  count_ -= 1;
  std::cout << count_ << std::endl;
}