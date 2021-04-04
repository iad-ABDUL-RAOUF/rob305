#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "timespec.h"
#include <climits>
#include <signal.h>

namespace td1d
{
unsigned int incr(unsigned int nLoops, double* pCounter, volatile bool *pStop)
/**
 * \brief increments a counter n times or until a stop signal is sent
 * \param nLoops number of times the counter is incremented
 * \param pCounter counter to be incremented
 * \param pStop boolean that stops the incrementation if true
 * \return final number of loops
 */
{
  unsigned int i = 0;
  while ((i < nLoops) && (!*pStop))
  {
    *pCounter += 1;
    i++;
  }
  return i;
}

void callBack(int /*sig*/, siginfo_t* si, void* /*unused*/)
/**
 * \brief callback function when the timer ends, stops the incrementation fo a counter
 */
{
  volatile bool *pstop = (volatile bool*) si-> si_value.sival_ptr;
  *pstop = true;
}

void calib (float *affine_param)
/**
 * \brief calibrating the incr function
 * \param affine_param storage of the calibrated parameters
 */
{
  unsigned int nLoops = UINT_MAX;
  float iLoop[2];
  volatile bool stop = false;
  double counter = 0.0;
  // init action, event and timer
  // init action
  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = td1d::callBack;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGRTMIN, &sa, nullptr);
  //init event
  struct sigevent sev;
  sev.sigev_notify= SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMIN;
  sev.sigev_value.sival_ptr = (void*) &stop;
  // init timer
  timer_t tid;
  timer_create(CLOCK_REALTIME, &sev, &tid);
  itimerspec its;
  // first measure
  its.it_value.tv_sec = 4;
  its.it_value.tv_nsec = 0;
  its.it_interval.tv_sec = 0;
  its.it_interval.tv_nsec = 0;
  timer_settime(tid, 0, &its, nullptr);
  iLoop[0] = (float) incr(nLoops, &counter, &stop);
  stop = false;
  // second measure
  its.it_value.tv_sec = 6;
  its.it_value.tv_nsec = 0;
  its.it_interval.tv_sec = 0;
  its.it_interval.tv_nsec = 0;
  timer_settime(tid, 0, &its, nullptr);
  iLoop[1] = (float) incr(nLoops, &counter, &stop);
  stop = false;
  std::cout << "iLoop[0] = " << iLoop[0] << ", iLoop[1] = " << iLoop[1] << std::endl;
  // compute affine calibration
  affine_param[0] = (iLoop[1] - iLoop[0])/(float) 2;
  affine_param[1] = iLoop[0] - 4*affine_param[0];
  std::cout << "a : " << affine_param[0] << ", b : " << affine_param[1] << std::endl;
}
} // namespace td1d


int main(int argc, char* argv[])
{  
  // Testing incr function

  // init varaible
  unsigned int nLoops = UINT_MAX;
  unsigned int iLoop = 0;
  volatile bool stop = false;
  double counter = 0.0;
  // init action, event and timer
  // init action
  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = td1d::callBack;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGRTMIN, &sa, nullptr);
  //init event
  struct sigevent sev;
  sev.sigev_notify= SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMIN;
  sev.sigev_value.sival_ptr = (void*) &stop;
  // init timer
  timer_t tid;
  timer_create(CLOCK_REALTIME, &sev, &tid);
  itimerspec its;
  its.it_value.tv_sec = 1;
  its.it_value.tv_nsec = 0;
  its.it_interval.tv_sec = 0;
  its.it_interval.tv_nsec = 0;
  // perform task
  timespec begin_ts = timespec_now();
  timer_settime(tid, 0, &its, nullptr);
  iLoop = td1d::incr(nLoops, &counter, &stop);
  timespec end_ts = timespec_now();
  timespec duration = end_ts-begin_ts;
  
  // display output
  std::cout << "counter = " << counter << std::endl;
  std::cout << "iLoop = " << iLoop << std::endl;
  std::cout << "time : " << duration.tv_sec << ","<< std::setfill ('0') << std::setw (9) << duration.tv_nsec << "s" << std::endl;
  std::cout << "perform calibration " << std::endl;
  
  
  // Calibrating

  float affine_param[2]; // a, b
  td1d::calib(affine_param);


  // Verifying calibration

  nLoops = 1000000000;
  stop = false;
  
  begin_ts = timespec_now();
  iLoop = td1d::incr(nLoops, &counter, &stop);
  end_ts = timespec_now();
  duration = end_ts-begin_ts;

  float expectedTime_ms = 1000 * (nLoops - affine_param[1]) / affine_param[0];
  timespec expectedTime_ts = timespec_from_ms(expectedTime_ms);
  timespec diff = duration - expectedTime_ts;

  std::cout << "time : " << duration.tv_sec << ","<< std::setfill ('0') << std::setw (9) << duration.tv_nsec << "s" << std::endl;
  std::cout << "expected time : " << expectedTime_ts.tv_sec << ","<< std::setfill ('0') << std::setw (9) << expectedTime_ts.tv_nsec << "s" << std::endl;
  std::cout << "diff time : " << diff.tv_sec << ","<< std::setfill ('0') << std::setw (9) << diff.tv_nsec << "s" << std::endl;

  // delete because in C++ you always have to delete stuff...
  timer_delete(tid);
}