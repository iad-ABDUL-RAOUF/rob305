#include "Fifo.hpp"
#include "PosixThread.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// IntProducer produce int pushed into fifo
class IntProducer : public Thread
/**
 * \class IntProducer
 * \brief pushes ints into a Fifo
 */
{
public:
  IntProducer(Fifo<unsigned int> &fifo, unsigned int maxn, double delay_ms = 0);
  /**
   * \brief constructor of an instance of the intProducer class
   * \param fifo Fifo to push ints into
   * \param maxn maximum int to push into the fifo
   * \param delay_ms delay between each push, in milliseconds
   */
  ~IntProducer();
  /**
   * \brief destructor of the IntProducer class
   */
  void run() override;
  /**
   * \brief pushes ints into the fifo
   */

private:
  Fifo<unsigned int> &fifo; /** Fifo to push ints into */
  unsigned int maxn;        /** maximum int to push into the fifo */
  unsigned int n;           /** last int pushed */
  double delay_ms;          /** delay between each push, in milliseconds */
};

IntProducer::IntProducer(Fifo<unsigned int> &fifo, unsigned int maxn, double delay_ms)
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
/**
 * \class IntConsumer
 * \brief pops ints from the Fifo
 */
{
public:
  IntConsumer(Fifo<unsigned int> &fifo, unsigned int maxn);
  /**
   * \brief constructor of an instance of the IntConsumer class
   * \param fifo Fifo to pop ints from
   * \param maxn maximum int to pop
   */
  ~IntConsumer();
  /**
   * \brief destructor of IntConsumer class
   */
  void run() override;
  /**
   * \brief pops the ints from 0 to maxn, in the ascendant order
   */
  unsigned int nextn() { return nextn_; };
  /**
   * \brief returns next int to be popped from the Fifo
   */

private:
  Fifo<unsigned int> &fifo; /** Fifo to pop ints from */
  unsigned int maxn;        /** maximum int to pop */
  unsigned int nextn_;      /** next int to be popped from the Fifo*/
};

IntConsumer::IntConsumer(Fifo<unsigned int> &fifo, unsigned int maxn)
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

int main(int argc, char *argv[])
{
  //read parameters
  if (argc != 4)
  {
    std::cerr << "USAGE: "
              << "<nCons> <n> <delay_ms>" << std::endl;
    return 1;
  }
  std::string params;
  for (int i = 1; i < argc; ++i)
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
  Fifo<unsigned int> fifo;
  std::vector<IntProducer> intProducer;
  std::vector<IntConsumer> intConsumer;
  for (unsigned int i = 0; i < nCons; i++)
  {
    intConsumer.push_back(IntConsumer(fifo, n));
    intProducer.push_back(IntProducer(fifo, n, delay_ms));
  }

  // start threads
  for (unsigned int i = 0; i < nCons; i++)
  {
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
  for (unsigned int i = 0; i < nCons; i++)
  {
    intConsumer[i].join();
    intProducer[i].join();
  }

  for (unsigned int i = 0; i < nCons; i++)
  {
    std::cout << "ntConsumer[" << i << "].nextn() = " << intConsumer[i].nextn() << std::endl;
  }
  return 0;
}