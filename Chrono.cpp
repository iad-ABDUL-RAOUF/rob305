#include "Chrono.h"
#include "timespec.h"



Chrono::Chrono()
{
  restart();
}

void Chrono::stop()
{
  stopTime_ = timespec_now();
}

void Chrono::restart()
{
  startTime_ = timespec_now();
  stopTime_ = startTime_;
}

bool Chrono::isActive() const
{
  return startTime_ == stopTime_;
}

double Chrono::startTime() const
{
  return timespec_to_ms(startTime_);
}

double Chrono::stopTime() const
{
  return timespec_to_ms(stopTime_);
}

double Chrono::lap() const
{
  timespec duration;
  if (isActive())
  {
    duration = timespec_now() - startTime_;
  }
  else
  {
    duration = stopTime_ - startTime_;
  }
  return timespec_to_ms(duration);

  // return timespec_to_ms( (isActive() ? timespec_now() : stopTime_) - startTime_)
}