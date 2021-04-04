#include "mutex.h"
#include "../TP1/timespec.h"

Mutex::Mutex()
{
    pthread_mutexattr_t mutexAttribute;
    pthread_mutexattr_init(&mutexAttribute);
    pthread_mutexattr_settype(&mutexAttribute,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&posixId, &mutexAttribute);
    pthread_mutexattr_destroy(&mutexAttribute);
    pthread_cond_init(&posixCondId, nullptr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}

// pthread_mutex_t Mutex::getMutexId()
// {
//     return posixId;
// }

// pthread_cond_t Mutex::getMutexCondId();
// {
//     return posixCondId;
// }

void Mutex::lock()
{
    pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms)
{
    bool result = true;
    if (pthread_mutex_timedlock(&posixId, &timespec_from_ms(timeout_ms)) == ETIMEDOUT)
    {
        result = false;
    }
    return result;
}

bool Mutex::trylock()
{
    bool result = false;
    if(pthread_mutex_trylock(posixId) == 0)
    {
        result = true;
    }
    return result;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixId);
}







Mutex::Monitor::Monitor(Mutex& m) : m_mutex(m) {}



void Mutex::Monitor::wait()
{
    pthread_cond_wait(&m_mutex.posixCondId, &m_mutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    bool result = false;
    if (pthread_cond_timedwait(&m_mutex.posixCondId, &m_mutex.posixId,timespec_from_ms(timeout_ms)) == 0)
    {
        result = true;
    }
    return result;
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(m_mutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(m_mutex.posixCondId);
}





Mutex::Lock::Lock(Mutex& m) : m_mutex(m)
{
    m.lock();
}

Mutex::Lock::Lock(Mutex& m, double timeout_ms) : m_mutex(m)
{
    if (m.lock(timeout_ms))
    {
        throw TimeoutException("Timeout on mutex lock");
    }
}

Mutex::Lock::~Lock()
{
    m_mutex.unlock();
}





Mutex::TryLock::TryLock(Mutex& m) : m_mutex(m)
{
    if(m.trylock())
    {
        throw TimeoutException("Timeout on mutex trylock()");
    }
}

Mutex::TryLock::~TryLock()
{
    m_mutex.unlock();
}

