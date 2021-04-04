#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "timespec.h"


void incr(unsigned int nLoops, double* pCounter)
/**
 * \brief increments a counter n times
 * \param nLoops number of times the counter is incremented
 * \param pCounter counter to be incremented
 */
{
  for (unsigned int i = 0; i < nLoops; i++)
  {
    *pCounter += 1;
  }
}

int main(int argc, char* argv[])
{
  // load parameters
  if (argc < 2)
  {
    std::cerr << "USAGE: "<< argv[1] << "<myarg1>" << std::endl;
    return 1;
  }
  std::istringstream is(argv[1]);
  unsigned int nLoops;
  is >> nLoops;
  // init variable
  double counter = 0.0;
  // perform task
  timespec begin_ts = timespec_now();
  incr(nLoops, &counter);
  timespec end_ts = timespec_now();
  timespec duration = end_ts-begin_ts;
  // display output
  std::cout << counter << std::endl;
  std::cout << "time : " << duration.tv_sec << ","<< std::setfill ('0') << std::setw (9) << duration.tv_nsec << "s" << std::endl;
}

