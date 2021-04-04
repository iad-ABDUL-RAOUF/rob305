#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "timespec.h"


void incr(unsigned int nLoops, double* pCounter)
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
  // init varaible
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


/*
  for (int i=1; i < argc; ++i)
  {
    params += argv[i];
    params += " ";
  }

  std::istringstream is(params);
*/

/*
en C
#include <stdio.h>
int main(int argc, char* argv[])
{
  if (argc blablabla)
  {
    printf("")
  }

  unsigned param;
  sscanf(argv[1], "%d", &param);

  // ou des truc du genre atoi
  return 0;
}



*/

//#include <cstdlib>
// std::atoi(argv[1])