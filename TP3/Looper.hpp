#ifndef Looper_hpp_INCLUDED
#define Looper_hpp_INCLUDED

class Looper
/**
 * \class Looper
 * \brief run loops
 */
{
public:
  Looper();
  /**
   * \brief constructor of an instance of the class Looper
   */
  ~Looper(){};
  /**
   * \brief destructor of an instance of the class Looper
   */
  double runLoop(double nLoops = __DBL_MAX__);
  /**
   * \brief run the loop times again
   * \param nLoops number of times the loop is to be run
   */
  double getSample() const { return iLoop; }
  /**
   * \brief returns the current number of loops done
   * \return current number of loops done
   */
  double stopLoop()
  /**
   * \brief stops the loop
   * \return number of loops done until the looper was stopped
   */
  {
    doStop = true;
    return iLoop;
  }

private:
  bool doStop;  /** true if the looper has to stop */
  double iLoop; /**current number of loops done */
};

#endif