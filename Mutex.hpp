class Mutex
{
public:
  class Lock;

public:
  Mutex()

private:
  void lock();
  void unlock();

private:
  pthread_mutex_t posixId;
};




class Mutex::Lock
{
public:
  Lock(Mutex& mutex);
  ~Lock();

private:
  Mutex& m_mutex;
}