#include "PosixThread.hpp"
#include "mutex.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ThreadIncr : public Thread
{
public:
  ThreadIncr(unsigned int nLoops, volatile double* pCounter, Mutex& mutex);
  ~ThreadIncr();
  void run() override;

private:
  unsigned int m_nLoops;
  volatile double* m_pCounter;
  Mutex& mutex;

};

ThreadIncr::ThreadIncr(unsigned int nLoops, volatile double* pCounter, Mutex& mutex) 
: Thread(), m_nLoops(nLoops), m_pCounter(pCounter), mutex(mutex)
{
}

ThreadIncr::~ThreadIncr()
{
}

void ThreadIncr::run()
{
  for (unsigned int i = 0; i<m_nLoops; i++)
  {
    {
      Mutex::Lock lock(mutex);
      *m_pCounter += 1;
    }
    
  }
}


int main(int argc, char* argv[])
{
  //read parameters
  if (argc != 3)
  {
    std::cerr << "USAGE: " << "<nLoops> <nTasks>" << std::endl;
    return 1;
  }
  std::string params;
  for (int i=1; i < argc; ++i)
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
  volatile double counter = 0 ;
  Mutex mutex;
  std::vector<ThreadIncr> threadIncr;
  // ThreadIncr* threadIncr = (ThreadIncr*)malloc(sizeof(ThreadIncr) * nTasks);
  for (unsigned int i = 0; i < nTasks; i++) {
    threadIncr.push_back(ThreadIncr(nLoops, &counter, mutex));
  }
  // start thread
  for (unsigned int i = 0; i < nTasks; i++) {
    threadIncr[i].start();
  }
  // wait for end of thread
  for (unsigned int i = 0; i < nTasks; i++) {
    threadIncr[i].join();
  }
  // display result
  std::cout<<"counter = "<<counter<<std::endl;
  return 0;
}