#include "PosixThread.hpp"
#include "Semaphore.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// TokenProducer produce token for semaphore
class TokenProducer : public Thread
{
public:
  TokenProducer(Semaphore& semaphore,double delay_ms = 0);
  ~TokenProducer();
  void run() override;

private:
  Semaphore& semaphore;
  double delay_ms;
};

TokenProducer::TokenProducer(Semaphore& semaphore, double delay_ms) 
: Thread(), semaphore(semaphore), delay_ms(delay_ms)
{
}

TokenProducer::~TokenProducer()
{
}

void TokenProducer::run()
{
  // Token production take delay_ms milliseconds to be completed
  sleep_ms(delay_ms);
  semaphore.give();
}


// TokenConsumer consume token from semaphore
class TokenConsumer : public Thread
{
public:
  TokenConsumer(Semaphore& semaphore);
  ~TokenConsumer();
  void run() override;

private:
  Semaphore& semaphore;
};

TokenConsumer::TokenConsumer(Semaphore& semaphore) 
: Thread(), semaphore(semaphore)
{
}

TokenConsumer::~TokenConsumer()
{
}

void TokenConsumer::run()
{
  semaphore.take();
}


int main(int argc, char* argv[])
{
  //read parameters
  if (argc != 3)
  {
    std::cerr << "USAGE: " << "<nCons> <nProd>" << std::endl;
    return 1;
  }
  std::string params;
  for (int i=1; i < argc; ++i)
  {
    params += argv[i];
    params += " ";
  }
  std::istringstream is(params);
  unsigned int nCons;
  unsigned int nProd;
  is >> nCons;
  is >> nProd;
  // init variables
  Semaphore semaphore;
  std::vector<TokenProducer> tokenProducer;
  std::vector<TokenConsumer> tokenConsumer;
  for (unsigned int i = 0; i < nCons; i++) {
    tokenConsumer.push_back(TokenConsumer(semaphore));
  }
  for (unsigned int i = 0; i < nProd; i++) {
    tokenProducer.push_back(TokenProducer(semaphore));
  }
  // start threads
  for (unsigned int i = 0; i < nCons; i++) {
    tokenConsumer[i].start();
  }
  for (unsigned int i = 0; i < nProd; i++) {
    tokenProducer[i].start();
  }
  // wait for end of threads
  for (unsigned int i = 0; i < nCons; i++) {
    tokenConsumer[i].join();
  }
  for (unsigned int i = 0; i < nProd; i++) {
    tokenProducer[i].join();
  }
  return 0;
}