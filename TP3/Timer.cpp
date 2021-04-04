#include "Timer.hpp"
#include "timespec.h"
#include <iostream>


Timer::Timer()
{
  sa_.sa_flags = SA_SIGINFO;
  sa_.sa_sigaction = call_callback;
  sigemptyset(&sa_.sa_mask);
  sigaction(SIGRTMIN, &sa_, nullptr);

  sev_.sigev_notify = SIGEV_SIGNAL;
  sev_.sigev_signo = SIGRTMIN;
  sev_.sigev_value.sival_ptr = (void*) this;
  
  timer_create(CLOCK_REALTIME, &sev_, &tid_);
}

Timer::~Timer()
{
  timer_delete(tid_);
}

void Timer::start(double duration_ms)
{
  itimerspec its;
  timespec duration_ts = timespec_from_ms(duration_ms);
  // launch timer one time
  its.it_value = duration_ts;
  its.it_interval.tv_sec = 0;
  its.it_interval.tv_nsec = 0;
  timer_settime(tid_, 0, &its, nullptr);
}

void Timer::stop()
{
  itimerspec its;
  its.it_value.tv_sec = 0;
  its.it_value.tv_nsec = 0;
  its.it_interval.tv_sec = 0;
  its.it_value.tv_nsec = 0;
  timer_settime(tid_, 0, &its, nullptr);
}

void Timer::call_callback(int, siginfo_t* si, void*)
{
  Timer* timer = (Timer*) si-> si_value.sival_ptr;
  timer->callback();
}


// PeriodicTimer

void PeriodicTimer::start (double duration_ms)
{
  itimerspec its;
  timespec duration_ts = timespec_from_ms(duration_ms);
  // launch timer periodic time
  its.it_value = duration_ts;
  its.it_interval = duration_ts;
  timer_settime(tid_, 0, &its, nullptr);
}

