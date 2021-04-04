#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

#include <time.h>

class Chrono
{
public:
  
  Chrono();
  void stop();
  void restart();
  bool isActive() const; 
  double startTime() const; // accesseur // milliseconde
  double stopTime() const; // milliseconde
  double lap() const; // milliseconde

private:
  timespec startTime_; //struct non necessaire en C++. ca vient du C
  timespec stopTime_;
  
};

#endif