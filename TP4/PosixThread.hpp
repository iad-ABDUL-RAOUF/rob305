#ifndef PosixThread_hpp_INCLUDED
#define PosixThread_hpp_INCLUDED

#include <pthread.h>
#include <exception>
#include <iostream>
#include <string>
#include "../TP3/Chrono.h"

class PosixThread
/**
 * \class PosixThread
 * \brief encapsulates the posix thread managment functions
 */
{
public:
  class Exception;
  /**
   * \class Exception
   * \brief Exception called when a posix thread ID doesn't exist
   */

public:
  PosixThread();
  /**
   * \brief constructor of an instance of the PosixThread class
   */
  PosixThread(pthread_t posixId);
  /**
   * \brief constructor of an instance of the PosixThread class referring to an existing thread
   * \param posixId existing posix thread ID to be referred to
   */
  ~PosixThread();
  /**
   * \brief destructor of the PosixThread class
   */
  void start(void *(*threadFunc)(void *), void *threadArg);
  /**
   * \brief launches the posix thread
   * \param threadFunc function executed by the posix thread
   * \param threadArg arguments passed to the function executed by the posix thread
   */
  void join();
  /**
   * \brief implementing the posix join function
   */
  bool join(double timeout_ms);
  /**
   * \brief implementing the posix join function with timeout
   * \param timeout_ms time during which the join function is tried, in milliseconds
   */
  bool setScheduling(int schedPolicy, int priority);
  /**
   * \brief implementing the posix set scheduling function
   * \param schedPolicy policy to be set
   * \param priority priority to be set
   */
  bool getScheduling(int *p_schedPolicy = nullptr, int *p_priority = nullptr);
  /**
   * \brief implements the posix get scheduling functino
   * \param p_schedPolicy storage for the scheduling policy
   * \param p_priority storage for the priority
   */

protected:
  bool isActive; /** true if the thread is running */

private:
  pthread_t posixId_;        /** posix thread ID */
  pthread_attr_t posixAttr_; /** attributes for the posix thread */
};

class PosixThread::Exception : public std::exception
/**
 * \class Exception
 * \brief Exception called when a posix thread ID doesn't exist
 */
{
public:
  Exception(const std::string &error = "") noexcept : error_(error){};
  /**
   * \brief constructor of an instance of the PosixThread::Exception class
   * \param error string message detailing the error
   */
  virtual ~Exception() noexcept {};
  /**
   * \brief destructor of the PosixThread::Exception class
   */
  virtual const char *what() const noexcept { return error_.c_str(); }
  /**
   * \brief details of the error
   * \return string detailing the error
   */

private:
  std::string error_; /** string detailing the error */
};

class Thread : public PosixThread
/**
 * \class Thread
 * \brief implements the posix thread functions, with informations on start and stop time
 */
{
public:
  Thread();
  /**
   * \brief constructor of an instance of the PosixThread::Exception class
   */
  ~Thread();
  /**
   * \brief destructor of an instance of the PosixThread::Exception class
   */
  void start();
  /**
   * \brief starts the posix thread
   */
  void sleep_ms(double delay_ms);
  /**
   * \brief stops the execution of the thread during a delay
   * \param delay_ms duration of the pause in the exection, in milliseconds
   */
  double startTime_ms();
  /**
   * \brief accessor to the start time of the thread
   * \return start time of the thread, in milliseconds
   */
  double stopTime_ms();
  /**
   * \brief accessor to the stop time of the thread, equal to start time if the thread is running
   * \return stop time of the thread, in milliseconds
   */
  double exectTime_ms();
  /**
   * \brief returns the execution time of the thread, null if the thread is running
   * \return execution time of the thread, in milliseconds
   */

protected:
  virtual void run() = 0; 
  /**
   * \brief virtual function that is executed by the thread 
   */

private:
  static void *call_run(void *v_thread); 
  /** 
   * \brief calls the function executed by the thread
   * \param v_thread pointer to the thread, passed to the function executed by the thread
   */

private:
  Chrono chrono; /** stopwatch that measures the start, stop and execution times */
};

#endif