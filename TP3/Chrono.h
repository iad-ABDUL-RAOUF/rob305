#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

#include <time.h>

class Chrono
/**
 * \class Chrono
 * \brief implements the functionalities of a stopwatch
 */
{
public:
  Chrono();
  /**
   * \brief constructor of an instance of the Chrono class, starts the clockwatch right away.
   */
  void stop();
  /**
   * \brief stops the clockwatch
   */
  void restart();
  /**
   * \brief restarts the clockwatch
   */
  bool isActive() const;
  /**
   * \brief tells if the clockwatch is running
   * \return true if the clockwatch is running
   */
  double startTime() const;
  /**
   * \brief tells the starting time of the clockwatch, in milliseconds
   */
  double stopTime() const;
  /**
   * \brief tells the stopping time of the clockwatch, in milliseconds, equals to starting time if the clockwatch is running
   */
  double lap() const;
  /**
   * \brief tells the elapsed time between the starting and the stopping time.
   */

private:
  timespec startTime_; /** starting time of the clockwatch */
  timespec stopTime_;  /** stopping time of the clockwatch, equal to the starting time if the clockwatch is running */
};

#endif