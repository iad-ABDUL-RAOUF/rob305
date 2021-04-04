#include "mutex.h"
#include <time.h>
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
    bool isTimedOut = false;
    timespec timeout_ts = timespec_from_ms(timeout_ms) + timespec_now();
    if (pthread_mutex_timedlock(&posixId, &timeout_ts) == ETIMEDOUT)
    {
        isTimedOut = true;
    }
    return isTimedOut;
}

bool Mutex::trylock()
{
    bool fail = false;
    if(pthread_mutex_trylock(&posixId) != 0)
    {
        fail = true;
    }
    return fail;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixId);
}


// Monitor
Mutex::Monitor::Monitor(Mutex& m) : m_mutex(m) {}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&m_mutex.posixCondId, &m_mutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    bool isTimedOut = false;
    timespec timeout_ts = timespec_from_ms(timeout_ms) + timespec_now();
    if (pthread_cond_timedwait(&m_mutex.posixCondId, &m_mutex.posixId, &timeout_ts) == ETIMEDOUT)
    {
        isTimedOut = true;
    }
    return isTimedOut;
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&m_mutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&m_mutex.posixCondId);
}


// Lock
Mutex::Lock::Lock(Mutex& m) : Monitor(m)
{
    m_mutex.lock();
}

Mutex::Lock::Lock(Mutex& m, double timeout_ms) : Monitor(m)
{
    if (m_mutex.lock(timeout_ms))
    {
        throw TimeoutException("Timeout on mutex lock");
    }
}

Mutex::Lock::~Lock()
{
    m_mutex.unlock();
}


// Try lock
Mutex::TryLock::TryLock(Mutex& m) : Monitor(m)
{
    if(m_mutex.trylock())
    {
        throw TimeoutException("Fail on mutex trylock()");
    }
}

Mutex::TryLock::~TryLock()
{
    m_mutex.unlock();
}

