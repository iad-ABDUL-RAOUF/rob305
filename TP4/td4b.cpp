#include "PosixThread.hpp"
#include "Mutex.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ThreadIncr : public Thread
/**
 * \class ThreadIncr
 * \brief implementation of a thread, that increments a counter
 */
{
public:
  ThreadIncr(unsigned int nLoops, volatile double *pCounter, Mutex &mutex);
  /**
   * \brief constructor of an instance of the ThreadIncr class
   * \param nLoops number of times the counter is incremented
   * \param pCounter counter to be incremented
   * \param mutex mutex to protect the counter
   */
  ~ThreadIncr();
  /**
   * \brief desctructor of the ThreadIncr class
   */
  void run() override;
  /**
   * \brief function executed by the thread : increments the counter
   */

private:
  unsigned int m_nLoops;       /** number of times the counter will be incremented */
  volatile double *m_pCounter; /** counter to be incremented */
  Mutex &mutex;                /** mutex to protect the counter */
};

ThreadIncr::ThreadIncr(unsigned int nLoops, volatile double *pCounter, Mutex &mutex)
    : Thread(), m_nLoops(nLoops), m_pCounter(pCounter), mutex(mutex)
{
}

ThreadIncr::~ThreadIncr()
{
}

void ThreadIncr::run()
{
  for (unsigned int i = 0; i < m_nLoops; i++)
  {
    {
      Mutex::Lock lock(mutex);
      *m_pCounter += 1;
    }
  }
}

int main(int argc, char *argv[])
{
  //read parameters
  if (argc != 3)
  {
    std::cerr << "USAGE: "
              << "<nLoops> <nTasks>" << std::endl;
    return 1;
  }
  std::string params;
  for (int i = 1; i < argc; ++i)
  {
    params += argv[i];
    params += " ";
  }
  std::istringstream is(params);
  unsigned int nLoops;
  unsigned int nTasks;
  is >> nLoops;
  is >> nTasks;

  // init variables
  volatile double counter = 0;
  Mutex mutex;
  std::vector<ThreadIncr> threadIncr;
  for (unsigned int i = 0; i < nTasks; i++)
  {
    threadIncr.push_back(ThreadIncr(nLoops, &counter, mutex));
  }

  // start thread
  for (unsigned int i = 0; i < nTasks; i++)
  {
    threadIncr[i].start();
  }

  // wait for end of thread
  for (unsigned int i = 0; i < nTasks; i++)
  {
    threadIncr[i].join();
  }
  
  // display result
  std::cout << "counter = " << counter << std::endl;
  return 0;
}