#include "Timer.hpp"

class CountDown : public PeriodicTimer
/**
 * \class CountDown
 * \brief implements a periodic timer that decrements a counter
 */
{
public:
  CountDown(unsigned int initCount);
  /**
     * \brief constructor of an instance of the CountDown class
     * \param initCount counter value at the beginning of the countdown
     */
  unsigned int count() const { return count_; }
  /**
     * \brief checks the value of the counter
     */

private:
  void callback() override;
  /**
     * \brief callback function when the timer ends, decrements the counter
     */

private:
  unsigned int count_; /** counter to be decremented */
};