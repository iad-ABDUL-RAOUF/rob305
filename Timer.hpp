/**
 * Timer.h
 * Object-orinted implementation of a Posif timer
 */

#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>

class Timer
{
public:
  Timer();
  virtual ~Timer();
  virtual void start(double duration_ms); // virtual non indiqué dans l uml mais plus coherent ici
  void stop();

protected:
  virtual void callback() = 0;

private:
  static void call_callback(int, siginfo_t* si, void*);

protected:
    timer_t tid_;

private:
  struct sigaction sa_; 
  struct sigevent sev_;
  void* p_data_;
};


class PeriodicTimer : public Timer
{
public :
  void start(double duration_ms) override;
};


#endif

/*
Timer t;
t.stop();
en C : Timer::stop(&t);   &this si on est dans la classe
Timer::call_callback(i,t,d) (pas de &t car static et donc la signature respectera bien cele attendue par le timer posix)
*/