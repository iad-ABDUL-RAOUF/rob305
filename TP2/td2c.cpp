#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <pthread.h>
#include "../TP1/timespec.h"

namespace td2c
/** \namespace td2c
 * space that defines the data structure and the incremental function for the TP2c
 */
{
  struct Data
  /**
 * \struct Data
 * data structure to be passed on the thread
 */
  {
    volatile double counter; /** counter to be incremented */
    unsigned int nLoops;     /** number of times the counter will be incremented */
    pthread_mutex_t mutex;   /** mutex to protect the counter */
    bool protect;            /** true if the mutex is activated */
  };

  void incr(Data &data)
  /**
 * \brief implemented in different threads, increments the counter
 * \param data structure with the counter and the number of loops
 */
  {
    if (data.protect)
    {
      for (unsigned int i = 0; i < data.nLoops; i++)
      {
        pthread_mutex_lock(&data.mutex);
        data.counter += 1;
        pthread_mutex_unlock(&data.mutex);
      }
    }
    else
    {
      for (unsigned int i = 0; i < data.nLoops; i++)
      {
        data.counter += 1;
      }
    }
  }
} // namespace td2c

void *call_incr(void *v_data)
/**
 * \brief caller of the incr function by the thread
 * \param v_data data strcture to be passed to the thread
 */
{
  td2c::Data *p_data = (td2c::Data *)v_data;
  td2c::incr(*p_data);
  return v_data;
}

int main(int argc, char *argv[])
{
  int status = 0;
  // load parameters
  if (argc != 5)
  {
    std::cerr << "USAGE: "
              << "<thisExecutable> <nLoops> <nTasks> <protect> <schedPolicy>" << std::endl;
    return 1;
  }
  std::string params;
  for (int i = 1; i < argc; ++i)
  {
    params += argv[i];
    params += " ";
  }
  std::istringstream is(params);
  unsigned int nLoops;
  unsigned int nTasks;
  bool protect;
  std::string schedPolicyInput;
  int schedPolicy = SCHED_OTHER;
  is >> nLoops;
  is >> nTasks;
  is >> protect;
  is >> schedPolicyInput;
  if (std::string(argv[2]) == "SCHED_RR")
  {
    schedPolicy = SCHED_RR;
  }
  else if (std::string(argv[2]) == "SCHED_FIFO")
  {
    schedPolicy = SCHED_FIFO;
  }
  else if (!(std::string(argv[2]) == "SCHED_OTHER"))
  {
    fprintf(stderr, "Unkown scheduling policy : %s\n", argv[4]);
    status = 1;
  }

  std::cout << "nLoops = " << nLoops << ", nTasks = " << nTasks << ", protect = " << protect << ", schedPolicyInput = " << schedPolicyInput << std::endl;

  // init variable
  pthread_mutex_t mutex;
  td2c::Data data;
  data.counter = 0.0;
  data.nLoops = nLoops;
  data.mutex = mutex;
  data.protect = protect;
  pthread_mutex_init(&data.mutex, nullptr);
  // mian thread priority
  sched_param schedParams;
  schedParams.sched_priority = sched_get_priority_max(schedPolicy);
  pthread_setschedparam(pthread_self(), schedPolicy, &schedParams);

  // // init tasks
  // int task attribute
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED); // par defaut (sans ca) la politique est herite du main et alors pthread_attr_setschedpolicy(&attr, schedPolicy) est ignoree
  pthread_attr_setschedpolicy(&attr, schedPolicy);
  // if (std::string(argv[2]) == "SCHED_FIFO") TODO reexecuter pour verifier
  schedParams.sched_priority = 9;
  pthread_attr_setschedparam(&attr, &schedParams);
  // int task
  pthread_t incrementThread[nTasks];

  // perform task and measure elapsed time
  timespec begin_ts = timespec_now();
  for (unsigned int i = 0; i < nTasks; i++)
  {
    pthread_create(&incrementThread[i], &attr, call_incr, &data);
  }

  // wait for end task
  pthread_attr_destroy(&attr);
  for (unsigned int i = 0; i < nTasks; i++)
  {
    pthread_join(incrementThread[i], nullptr);
  }
  timespec end_ts = timespec_now();
  timespec duration = end_ts - begin_ts;
  pthread_mutex_destroy(&data.mutex);

  // display result
  std::cout << "counter = " << data.counter << std::endl;
  std::cout << "time : " << duration.tv_sec << "," << std::setfill('0') << std::setw(9) << duration.tv_nsec << "s" << std::endl;

  return status;
}
