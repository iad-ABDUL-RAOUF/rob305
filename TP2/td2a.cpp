#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <pthread.h>
#include "../TP1/timespec.h"


namespace td2a
/** \namespace td2a
 * space that defines the data structure and the incremental function for the TP2a
 */
{
struct Data
/**
 * \struct Data
 * daat structure to be passed on the thread
 */
{
  volatile double counter; /** counter to be incremented */
  unsigned int nLoops; /** number of times the counter will be incremented */
};

void incr(Data &data)
/**
 * \brief implemented in different threads, increments the counter
 * \param data structure with the counter and the number of loops
 */
{
  for (unsigned int i = 0; i < data.nLoops; i++)
  {
    data.counter += 1;
  }
}
} // namespace td2a



void* call_incr(void* v_data)
/**
 * \brief caller of the incr function by the thread
 * \param v_data data strcture to be passed to the thread
 */
{
  td2a::Data* p_data = (td2a::Data*) v_data;
  td2a::incr(*p_data);
  return v_data;
}

int main(int argc, char* argv[])
{
  int status = 0;
  // load parameters
  if (argc != 3)
  {
    std::cerr << "USAGE: " << "<thisExecutable> <nLoops> <nTasks> " << std::endl;
    return 1;
  }
  std::string params;
  for (int i=1; i < argc; ++i)
  {
    params += argv[i];
    params += " ";
  }
  std::istringstream is(params);
  unsigned int nLoops;
  unsigned int nTasks;
  is >> nLoops;
  is >> nTasks;

  std::cout << "nLoops = " << nLoops << ", nTasks = " << nTasks  << std::endl;

  // init variable
  td2a::Data data = {counter : 0.0, nLoops : nLoops};


  // init tasks
  pthread_t incrementThread[nTasks];

  // perform task and measure elapsed time
  timespec begin_ts = timespec_now();
  for (unsigned int i = 0; i < nTasks; i++)
  {
    pthread_create(&incrementThread[i], nullptr, call_incr, &data);
  }

  // wait for end task
  for (unsigned int i = 0; i < nTasks; i++)
  {
    pthread_join(incrementThread[i], nullptr);
  }
  timespec end_ts = timespec_now();
  timespec duration = end_ts-begin_ts;

  // display result 
  std::cout << "counter = " << data.counter << std::endl;
  std::cout << "time : " << duration.tv_sec << ","<< std::setfill ('0') << std::setw (9) << duration.tv_nsec << "s" << std::endl;

  return status;
}


