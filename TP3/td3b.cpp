#include "CountDown.hpp"

int main ()
{
  CountDown countDown(15); 
  countDown.start(1000);
  while (countDown.count() > 0)
  {
    // wait. 
  }
  countDown.stop();
  return 0;
}