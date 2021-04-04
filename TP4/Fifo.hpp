#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include <queue>
#include "Mutex.hpp"

// header
template <class T>
class Fifo
/**
 * \class Fifo
 * \brief implements a FIFO
 */
{
public:
  class EmptyException;
  /**
   * \brief exception thown if a thread tries to pop from an empty fifo
   */

public:
  Fifo();
  /**
   * \brief constructor of an instance of the Fifo class
   */
  ~Fifo();
  /**
   * \brief destructor of an instance of the Fifo class
   */
  void push(T element);
  /**
   * \brief pushes a new element in the Fifo
   */
  T pop();
  /**
   * \brief extracts the last element from the Fifo
   */
  T pop(double timeout_ms);
  /**
   * \brief tries to extracts the last element from the Fifo for a definite duration
   * \param timeout_ms time during which the htread tries to extract the last element from the Fifo
   */

private:
  std::queue<T> elements; /** storage for the elements in the fifo */
  Mutex mutex;            /** mutex to protect the fifo */
};

// implementation
template <class T>
Fifo<T>::Fifo()
{
  mutex = Mutex();
}

template <class T>
Fifo<T>::~Fifo()
{
}

template <class T>
void Fifo<T>::push(T element)
{
  {
    Mutex::Lock lock(mutex);
    elements.push(element);
    lock.notify();
  }
}

template <class T>
T Fifo<T>::pop()
{
  T element;
  {
    Mutex::Lock lock(mutex);
    while (elements.empty())
    {
      lock.wait();
    }
    element = elements.front();
    elements.pop();
  }
  return element;
}

template <class T>
T Fifo<T>::pop(double timeout_ms)
{
  T element;
  {
    Mutex::Lock lock(mutex);
    while (elements.empty())
    {
      if (lock.wait(timeout_ms))
      {
        throw EmptyException("timed out in Fifo pop");
      }
    }
    element = elements.front();
    elements.pop();
  }
  return element;
}

#endif