#include "PosixThread.hpp"
#include <pthread.h>
#include <errno.h>
#include "../TP1/timespec.h"
#include <unistd.h>


PosixThread::PosixThread()
: isActive(false)
{
  pthread_attr_init(&posixAttr_);
}

PosixThread::PosixThread(pthread_t posixId)
: isActive(true), posixId_(posixId)
{
  sched_param schedParams;
  int schedPolicy;
  int error = pthread_getschedparam(posixId_, &schedPolicy, &schedParams);
  if (error == ESRCH)
  {
    throw Exception("invalid posix thread id given in constructeur PosixThread");
  }
  //keep coherence between member posixAttr_ and the thread
  pthread_attr_setschedpolicy(&posixAttr_, schedPolicy);
  pthread_attr_setschedparam(&posixAttr_, &schedParams);
  
}

PosixThread::~PosixThread()
{
}

void PosixThread::start(void* (*threadFunc) (void*), void* threadArg)
{
  if (!isActive)
  {
    pthread_create(&posixId_, &posixAttr_, threadFunc, threadArg);
    isActive = true;
  }
}

void PosixThread::join()
{
  pthread_join(posixId_, NULL);
  isActive = false;
}

bool PosixThread::join(double timeout_ms)
{
  timespec timeout_ts = timespec_from_ms(timeout_ms);
  bool isTimedOut = (bool) pthread_timedjoin_np(posixId_, NULL, &timeout_ts);
  if (not isTimedOut)
  {
    isActive = false;
  }
  return isTimedOut;
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
  sched_param schedParams;
  schedParams.sched_priority = priority;
  if (isActive)
  {
    pthread_setschedparam(posixId_, schedPolicy, &schedParams);
    pthread_attr_setschedpolicy(&posixAttr_, schedPolicy);
    pthread_attr_setschedparam(&posixAttr_, &schedParams);
    
  }
  else
  {
    pthread_attr_setinheritsched(&posixAttr_, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&posixAttr_, schedPolicy);
    pthread_attr_setschedparam(&posixAttr_, &schedParams);
  }
  return isActive;
}

bool PosixThread::getScheduling(int *p_schedPolicy, int *p_priority)
{
  sched_param schedParams;
  if (isActive)
  {
    pthread_getschedparam(posixId_, p_schedPolicy, &schedParams);
    *p_priority = schedParams.sched_priority;
  }
  else
  {
    pthread_attr_getschedpolicy(&posixAttr_, p_schedPolicy);
    pthread_attr_getschedparam(&posixAttr_, &schedParams);
    *p_priority = schedParams.sched_priority;
  }
  
  return isActive;
}


// classe Thread
Thread::Thread()
: PosixThread()
{
}

Thread::~Thread()
{
}

void Thread::start()
{
  chrono.restart();
  PosixThread::start(call_run, (void*) this);
}

void Thread::sleep_ms(double delay_ms)
{
  sleep(delay_ms/1000);
}

double Thread::startTime_ms()
{
  return chrono.startTime();
}

double Thread::stopTime_ms()
{
  return chrono.stopTime();
}

double Thread::exectTime_ms()
{
  return chrono.lap();
}

void* Thread::call_run(void* v_thread)
{
  Thread *thread = (Thread*) v_thread;
  thread->run();

  return nullptr;
}
