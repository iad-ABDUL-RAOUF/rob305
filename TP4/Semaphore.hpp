#ifndef Semaphore_hpp_INCLUDED
#define Semaphore_hpp_INCLUDED

#include "Mutex.hpp"

class Semaphore
/**
 * \class Semaphore
 * \brief token counter that allows a definite number of threads to work at a time
 */
{
public:
  Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT32_MAX);
  /**
   * \brief constructor of an instance of the Semaphore class
   * \param initCount initial counter number
   * \param maxCount maximal number of token
   */
  ~Semaphore();
  /**
   * \brief destructor of an instance of the Semaphore class
   */
  void give();
  /**
   * \brief gives back a token
   */
  void take();
  /**
   * \brief takes a token
   */
  bool take(double timeout_ms);
  /**
   * \brief tries to take a token during a definite time
   * \param timeout_ms time during which the thread tries to take a token, in milliseconds
   */

private:
  unsigned int counter;  /** counter of taken token */
  unsigned int maxCount; /** maximum number of token that can be taken */
  Mutex mutex;           /** mutex to protect the counter */
};

#endif