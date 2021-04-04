#include "Mutex.hpp"

Mutex::Lock::Lock()(Mutex& mutex) : m_mutex(mutex)
{
  mutex.lock();
}

Mutex::Lock::~Lock()
{
  m_mutex.unlock();
}