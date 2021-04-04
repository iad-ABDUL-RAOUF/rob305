/**
 * Timer.h
 * Object-orinted implementation of a Posif timer
 */

#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>

class Timer
/**
 * \class Timer
 * \brief encapsulates the functionalities of a Posix timer
 */
{
public:
  Timer();
  /**
   * \brief constructor of an instance of the Timer class
   */
  virtual ~Timer();
  /**
   * \brief constructor of an instance of the Timer class
   */
  virtual void start(double duration_ms);
  /**
   * \brief starts the posix timer
   * \param duration_ms duration of the posix timer, in milliseconds
   */
  void stop();
  /**
   * \brief stops the posix timer
   */

protected:
  virtual void callback() = 0;
  /**
   * \brief callback function that is called when the timer ends. Needs to be implemented by a daughter class
   */

private:
  static void call_callback(int, siginfo_t *si, void *);
  /**
   * \brief callback function that is called when a timer ends, calling callback
   * \param si info that is passed to the callback function, pointer to the instance of the timer
   */

protected:
  timer_t tid_; /** timer ID */

private:
  struct sigaction sa_; /** action to be done when the timer ends */
  struct sigevent sev_; /** event associated with the end of the timer */
};

class PeriodicTimer : public Timer
/**
 * \class PeriodicTimer
 * \brief implements a posix timer that restarts when it ends.
 */
{
public:
  void start(double duration_ms) override;
  /**
   * \brief starts the periodic timer
   * \param duration_ms duration of each period of the timer, in milliseconds
   */
};

#endif
