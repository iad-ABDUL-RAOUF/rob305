#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <pthread.h>
#include <exception>
#include <string>

class Mutex
/**
 * \class Mutex
 * \brief implements the mutex management posix functions
 */
{
public:
    Mutex();
    /**
     * \brief constructor of an instance of the Mutex class
     */
    ~Mutex();
    /**
     * \brief destructor of an instance of the Mutex class
     */

private:
    void lock();
    /**
     * \brief locks the mutex
     */
    bool lock(double timeout_ms);
    /**
     * \brief tries to lock the mutex for a definite time
     * \param timeout_ms time during which the mutex is tried to be locked, in milliseconds
     */
    bool trylock();
    /**
     * \brief tries to lock the mutex
     */
    void unlock();
    /**
     * \brief unlocks the mutex
     */

public:
    class Lock;
    /**
     * \brief class that implements the lock of the mutex
     */
    class TryLock;
    /**
     * \brief class that implements trying to lock the mutex
     */
    class Monitor;
    /**
     * \brief class that monitors the condition for the mutex
     */

private:
    pthread_mutex_t posixId;    /** ID of the mutex */
    pthread_cond_t posixCondId; /** condition for the mutex */
};

class Mutex::Monitor
/**
 * \class Mutex::Monitor
 * \brief class that monitors the condition for the mutex
 */
{
public:
    class TimeoutException;
    /**
     * \brief exception thrown if the timeout is reached on locking the mutex 
     */

public:
    void wait();
    /**
     * \brief implements the wait for condition mutex posix function
     */
    bool wait(double timeout_ms);
    /**
     * \brief implements the wait for condition mutex posix function with timeout
     */
    void notify();
    /**
     * \brief implements the cond_signal mutex posix function
     */
    void notifyAll();
    /**
     * \brief implements the cond_broadcast mutex posix function
     */

protected:
    Monitor(Mutex &m);
    /**
     * \brief constructor of an instance of the Monitor class
     */

protected:
    Mutex &m_mutex; /** mutex that is monitored */
};

class Mutex::Monitor::TimeoutException : public std::exception
/**
 * \class Mutex::Monitor::TimeoutException
 * \brief exception thrown if the timeout is reached on locking the mutex 
 */
{
public:
    TimeoutException(const std::string &error = "Timeout error") noexcept : m_error(error){};
    /**
   * \brief constructor of an instance of the Mutex::Monitor::TimeoutException class
   * \param error string message detailing the error
   */
    virtual ~TimeoutException() noexcept {};
    /**
   * \brief destructor of the Mutex::Monitor::TimeoutException class
   */
    virtual const char *what() const noexcept
    /**
   * \brief details of the error
   * \return string detailing the error
   */
    {
        return m_error.c_str();
    }

private:
    std::string m_error; /** string detailing the error */
};

class Mutex::Lock : public Mutex::Monitor
/**
 * \class Mutex::Lock
 * \brief class that implements the lock of the mutex
 */
{
public:
    Lock(Mutex &m);
    /**
     * \brief constructor of an instance of the Mutex::Lock class, locks the mutex right away
     * \param m mutex to be locked
     */
    Lock(Mutex &m, double timeout_ms);
    /**
     * \brief constructor of an instance of the Mutex::Lock class, locks the mutex on timeout right away
     * \param m mutex to be locked
     * \param timeout_ms time during which the mutex must be tried to be locked, in milliseconds
     */
    ~Lock();
    /**
     * \brief destructor of the Mutex::Lock class, unlocks the mutex
     */
};

class Mutex::TryLock : public Mutex::Monitor
/**
 * \class Mutex::TryLock
 * \brief class that implements trying to lock the mutex
 */
{
public:
    TryLock(Mutex &m);
    /**
     * \brief constructor of an instance of the Mutex::TryLock class, tries to locks the mutex right away
     * \param m mutex to be locked
     */
    ~TryLock();
    /**
     * \brief destructor of the Mutex::TryLock class, unlocks the mutex
     */
};

#endif