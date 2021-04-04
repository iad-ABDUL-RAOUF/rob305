#include "Fifo.hpp"
#include "PosixThread.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// IntProducer produce int pushed into fifo
class IntProducer : public Thread
{
public:
  IntProducer(Fifo <unsigned int>& fifo, unsigned int maxn, double delay_ms = 0);
  ~IntProducer();
  void run() override;

private:
  Fifo <unsigned int>& fifo;
  unsigned int maxn;
  unsigned int n;
  double delay_ms;
};

IntProducer::IntProducer(Fifo <unsigned int>& fifo, unsigned int maxn, double delay_ms) 
: Thread(), fifo(fifo), maxn(maxn), n(0), delay_ms(delay_ms)
{
}

IntProducer::~IntProducer()
{
}

void IntProducer::run()
{
  while (n <= maxn)
  {
    // take some time to produce
    sleep_ms(delay_ms);
    fifo.push(n);
    n++;
  }
}


// IntConsumer consume int from fifo
class IntConsumer : public Thread
{
public:
  IntConsumer(Fifo <unsigned int>& fifo, unsigned int maxn);
  ~IntConsumer();
  void run() override;
  unsigned int nextn(){return nextn_;}; 

private:
  Fifo <unsigned int>& fifo;
  unsigned int maxn;
  unsigned int nextn_;
};

IntConsumer::IntConsumer(Fifo <unsigned int>& fifo, unsigned int maxn) 
: Thread(), fifo(fifo), maxn(maxn), nextn_(0)
{
}

IntConsumer::~IntConsumer()
{
}

void IntConsumer::run()
{
  unsigned int n;
  while (nextn_ <= maxn)
  {
    n = fifo.pop();
    if (n == nextn_)
    {
      nextn_++;
    }
    else
    {
      // n is not the one expected. It is pushed back une the Fifo for later or for another consumer
      fifo.push(n);
    }
  }
}


int main(int argc, char* argv[])
{
  //read parameters
  if (argc != 4)
  {
    std::cerr << "USAGE: " << "<nCons> <n> <delay_ms>" << std::endl;
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
  unsigned int n;
  double delay_ms;
  is >> nCons;
  is >> n;
  is >> delay_ms;
  // init variables
  Fifo <unsigned int> fifo;
  std::vector<IntProducer> intProducer;
  std::vector<IntConsumer> intConsumer;
  for (unsigned int i = 0; i < nCons; i++) {
    intConsumer.push_back(IntConsumer(fifo, n));
    intProducer.push_back(IntProducer(fifo, n, delay_ms));
  }
  // start threads
  for (unsigned int i = 0; i < nCons; i++) {
    intConsumer[i].start();
    intProducer[i].start();
  }
  // while (true)
  // {
  //   for (unsigned int i = 0; i < nCons; i++)
  //   {
  //     std::cout << "ntConsumer[" << i << "].nextn() = " << intConsumer[i].nextn() << std::endl;
  //   }
  // }

  // wait for end of threads
  for (unsigned int i = 0; i < nCons; i++) {
    intConsumer[i].join();
    intProducer[i].join();
  }

  for (unsigned int i = 0; i < nCons; i++)
  {
    std::cout << "ntConsumer[" << i << "].nextn() = " << intConsumer[i].nextn() << std::endl;
  }
  return 0;
}