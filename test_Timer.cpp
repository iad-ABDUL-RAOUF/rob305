#include "CountDown.hpp"

int main (int argc, char *argv[])
{
  CountDown countDown(15); // CountDown countDown(...); ou : CountDown* countDown = new CountDown(...);
  countDown.start(1000);
  while (countDown.count() > 0)
  {
    /* wait. Meilleure pratique : rempalcer while par mutex avec wait*/
  }
  countDown.stop();
  return 0;
}