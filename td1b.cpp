#include <time.h>
#include <signal.h>
#include "iostream"



/*
sans namespace
void td1b_handler(int sig, siginfo_t* si, void*)
*/


namespace td1b
{
void handler(int /*sig*/, siginfo_t* si, void* /*unused*/)
{
  int* p_counter = (int*) si-> si_value.sival_ptr;
  /*
  int& counter = *((int*) si-> si_value.sival_ptr);
  et ensuite on peut directmeent manipuler counter au lieu de *p_counter
  */
  *p_counter += 1; // ou p_counter[0]
  std::cout << *p_counter << std::endl;
}
}

int main()
{
  volatile int counter = 0;

  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = td1b::handler;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGRTMIN, &sa, nullptr);

  struct sigevent sev;
  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMIN;
  sev.sigev_value.sival_ptr = (void*) &counter;
  
  timer_t tid;
  timer_create(CLOCK_REALTIME, &sev, &tid);

  itimerspec its;

  // launch timer periodically
  its.it_value.tv_sec = 0;
  its.it_value.tv_nsec = 500000000;
  its.it_interval = its.it_value;
  timer_settime(tid, 0, &its, nullptr);

  while (counter < 15)
  {
    // nothing
  }

  // Stop the timer
  its.it_value.tv_sec = 0;
  its.it_value.tv_nsec = 0;
  its.it_interval = its.it_value;
  timer_settime(tid, 0, &its, nullptr);

  // Destroy timer
  timer_delete(tid);
}



