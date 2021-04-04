#include <time.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>


int main(void)
{
  timespec debut, fin, duree;
  clock_gettime(CLOCK_REALTIME, &debut);
  sleep(5);
  clock_gettime(CLOCK_REALTIME, &fin);
  duree.tv_sec = fin.tv_sec - debut.tv_sec;
  duree.tv_nsec = fin.tv_nsec - debut.tv_nsec;
if (duree.tv_nsec < 0)
{
  duree.tv_nsec -= 1;
  duree.tv_nsec += 1000000000;
}

  std::cout << "Secondes: " << debut.tv_sec << ", nanosec: " << debut.tv_nsec << std::endl;
  std::cout << "Secondes Float: " << (duree.tv_sec + ((double) duree.tv_nsec)/1e9) << std::endl;
  return EXIT_SUCCESS;
}