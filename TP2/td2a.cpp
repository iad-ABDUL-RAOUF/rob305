#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <pthread.h>
#include "../TP1/timespec.h"


namespace td2a
{
struct Data
{
  /* data */
  volatile double counter;
  unsigned int nLoops;
  pthread_mutex_t mutex;
  bool protect;
};

void incr(Data &data)
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
} // namespace td2a



void* call_incr(void* v_data)
{
  td2a::Data* p_data = (td2a::Data*) v_data;
  td2a::incr(*p_data);
  return v_data;
}

int main(int argc, char* argv[])
{
  int status = 0;
  // load parameters
  if (argc != 5)
  {
    std::cerr << "USAGE: " << "<thisExecutable> <nLoops> <nTasks> <protect> <schedPolicy>" << std::endl;
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
  td2a::Data data = {counter : 0.0, nLoops : nLoops};
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
  timespec duration = end_ts-begin_ts;
  pthread_mutex_destroy(&data.mutex);

  // display result 
  std::cout << "counter = " << data.counter << std::endl;
  std::cout << "time : " << duration.tv_sec << ","<< std::setfill ('0') << std::setw (9) << duration.tv_nsec << "s" << std::endl;

  return status;
}



/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
  int status = 0;
  
  // Lecture d'un entier depuis les argv
  int nLoops;
  nLoops = atoi(argv[1]);

  // Autre passibilite
  sscanf(argv[1], "%d", &nLoops);

  // Input de l'utilisateur
  for (char answer[32]='c'; answer != 's'; scanf("%c", &answer))
  {
    printf("Enter command: ");
    fflush(stdout);
  }

  int schedPolicy = SCHED_OTHER;
  if (strcmp(argv[2], "SCHED_RR") == 0)
  {
    schedPolicy = SCHED_RR;
  }
  else if (strcmp(argv[2], "SCHED_FIFO") == 0)
  {
    schedPolicy = SCHED_FIFO;
  }
  else if (strcmp(argv[2], "SCHED_OTHER") == 0)
  {
    fprintf(stderr, "Unkown scheduling policy : %s\n", argv[2]);
    status = 1;
  }

  // en C++
  if (std::string(argv[2]) == "SCHED_RR")
  {
    schedPolicy = SCHED_RR;
  }
  else if (std::string(argv[2]) == "SCHED_FIFO")
  {
    schedPolicy = SCHED_FIFO;
  }
  if (std::string(argv[2]) == "SCHED_OTHER")
  {
    fprintf(stderr, "Unkown scheduling policy : %s\n", argv[2]);
    status = 1;
  }

  return status;
}
*/

/*
#include <vector>
std::vector<pthread_t> incrementThread(nTasks);
*/