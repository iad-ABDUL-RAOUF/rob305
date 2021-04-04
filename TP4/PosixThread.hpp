#include <pthread.h>
#include <exception>
#include <iostream>
#include <string>
#include "Chrono.h"

class PosixThread
{
public:
  class Exception;

public:
  PosixThread();
  PosixThread(pthread_t posixId);
  ~PosixThread();
  void start(void* (*threadFunc) (void*), void* threadArg);
  void join();
  bool join(double timeout_ms);
  bool setScheduling(int schedPolicy, int priority);
  bool getScheduling(int *p_schedPolicy = nullptr, int *p_priority = nullptr);

protected:
  /* data */
  bool isActive;

private:
  /* data */
  pthread_t posixId_;
  pthread_attr_t posixAttr_;
};


class PosixThread::Exception : public std::exception
{
public:
  Exception(const std::string& error="") noexcept : error_(error) {};
  //Exception(const char* error) noexcept : error_(error) {};
  virtual ~Exception() noexcept {};
  virtual const char* what() const noexcept {return error_.c_str();}
private:
  std::string error_;
};



class Thread : public PosixThread
{
public:
  Thread() : PosixThread() {};
  ~Thread() {};
  void start();
  void sleep_ms(double delay_ms);
  double startTime_ms();
  double stopTime_ms();
  double exectTime_ms();

protected:
  virtual void run();

private:
  static void* call_run(void* v_thread);
  
private:
  Chrono chrono;
};