#include "CountDown.hpp"

int main ()
{
  //init countdown timer
  CountDown countDown(15); 

  //starts countdown, the counter is decreased every second
  countDown.start(1000);

  //waiting for countdown to reach the null value
  while (countDown.count() > 0)
  {
    // wait. 
  }

  //stopping countdown
  countDown.stop();

  return 0;
}