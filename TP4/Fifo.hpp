#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include <queue>
#include "Mutex.hpp"


// header
template <class T>
class Fifo
{
public:
  class EmptyException;

public:
  Fifo();
  ~Fifo();
  void push(T element);
  T pop();
  T pop (double timeout_ms);

private:
  std::queue<T> elements;
  Mutex mutex;
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