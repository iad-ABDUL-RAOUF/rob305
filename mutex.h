#ifndef MUTEX_H
# define MUTEX_H

#include <pthread.h>

class Mutex
{
public:
    Mutex();
    ~Mutex();

// protected:
//     const pthread_mutex_t getMutexId();
//     const pthread_cond_t getMutexCondId();

private:
    void lock();
    bool lock(double timeout_ms);
    bool trylock();
    void unlock();

public:
    class Lock;
    class TryLock;
    class Monitor;

private:
    pthread_mutex_t posixId;
    pthread_cond_t posixCondId;
}


class Mutex::Monitor
{
public:
    void wait();
    bool wait(double timeout_ms);
    void notify();
    void notifyAll();

protected:
    Monitor(Mutex& m);

public:
    class TimeoutException;

private:
    Mutex& m_mutex;
};

class Mutex::Monitor::TimeoutException : public std::exception
{
public:
    TimeoutException(const std::string& error="Timeout error") noexcept : m_error(error) {};
    virtual ~TimeoutException() noexcept {};
    virtual const char* what() const noexcept
    {
        return m_error.c_str();
    }

private:
    std::string m_error;
};


class Mutex::Lock : public Mutex::Monitor
{
public:
    Lock(Mutex& m);
    Lock(Mutex& m, double timeout_ms) throw TimeoutException;
    ~Lock()

private:
    Mutex& m_mutex;
}

class Mutex::TryLock : public Mutex::Monitor
{
public:
    TryLock(Mutex& m) throw TimeoutException;
    ~TryLock();

private:
    Mutex& m_mutex;
}

#endif