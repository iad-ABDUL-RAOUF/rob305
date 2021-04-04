#include "Timer.hpp"

class CountDown : public PeriodicTimer
{
  public:
    CountDown(unsigned int initCount);
    unsigned int count() const {return count_;}

  private :
    void callback() override;
  
  private :
    unsigned int count_;
};