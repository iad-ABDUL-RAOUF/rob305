#ifndef Calibrator_hpp_INCLUDED
#define Calibrator_hpp_INCLUDED

#include "Looper.hpp"
#include "Timer.hpp"
#include <vector>

class Calibrator : public PeriodicTimer
/**
 * \class Calibrator
 * \brief measures the a and b parameters from the linear equation ax+b to convert execution time in number of loops done
 */
{
public:
  Calibrator(double samplingPeriod_ms, unsigned int nSamples);
  /**
   * \brief constructor of an instance of the class Calibrator
   * \param samplingPeriod_ms duration of each tests
   * \param nSamples number of tests to be done
   */
  double nLoops(double duration_ms) const { return a * duration_ms + b; }
  /**
     * \brief converts a duration into number of loops done in the same amount of time
     * \param duration_ms duration to be converted, in milliseconds
     */

protected:
  void callback() override;
  /**
     * \brief callback function, that stores the number of loops done during each period of the timer
     */

private:
  Looper looper;               /** looper that is calibrated */
  double a;                    /** a param from the linear equation ax+b */
  double b;                    /** b param from the linear equation ax+b */
  std::vector<double> samples; /** storage for the result of each test */
  unsigned int nSamples;       /** number of tests to be done */
  unsigned int nSamplesDone;   /** number of tests that are already done */
};

#endif