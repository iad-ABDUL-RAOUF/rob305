#ifndef CpuLoop_hpp_INCLUDED
#define CpuLoop_hpp_INCLUDED

#include "Calibrator.hpp"

class CpuLoop : public Looper
/** 
 * \class CpuLoop
 * \brief calibrates the looper, and then runs loops to last the right execution time
 */
{
public:
  CpuLoop(Calibrator& calibrator);
  /**
   * \brief constructor of an instance of the class CpuLoop
   * \param calibrator calibrator that implements the converter between execution time and number of loops
   */
  ~CpuLoop();
  /**
   * \brief destructor of an instance of the class CpuLoop
   */
  void runTime(double duration_ms);
  /**
   * \brief runs the right amounts of loops to last the duration
   * \param duration_ms duration of the execution time needed, in milliseconds
   */

private:
  Calibrator& calibrator_; /** calibrator that implements the converter between execution time and number of loops */
};

#endif
