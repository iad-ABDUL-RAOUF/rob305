#include "timespec.h"

double timespec_to_ms(const timespec& time_ts)
{
  //blabla
  double time_ms = 0.0;
  time_ms = time_ts.tv_sec*1000 + time_ts.tv_nsec/1e6;
  return time_ms;
}

timespec timespec_from_ms(double time_ms)
{
  //blalba
  timespec time_ts;
  time_ts.tv_sec = (long) floor(time_ms/1000); //TODO assert its ok for negative values
  time_ts.tv_nsec = (long) ((time_ms - time_ts.tv_sec*1000)*1e6); 
  return time_ts;
}

timespec timespec_now()
{
  timespec now_ts;
  clock_gettime(CLOCK_REALTIME, &now_ts);
  return now_ts;
}

timespec timespec_negate(const timespec& time_ts)
{
  timespec negTime_ts;
  negTime_ts.tv_sec = -time_ts.tv_sec;
  negTime_ts.tv_nsec = -time_ts.tv_nsec;
  if (negTime_ts.tv_nsec < 0)
  {
    negTime_ts.tv_sec -= 1;
    negTime_ts.tv_nsec +=1000000000;
  }
  return negTime_ts;
}


timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
  timespec time3_ts;
  time3_ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
  time3_ts.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
  if (time3_ts.tv_nsec >= 1000000000)
  {
    time3_ts.tv_sec +=1;
    time3_ts.tv_nsec -= 1000000000;
  }
  return time3_ts;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
  timespec time3_ts;
  time3_ts.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
  time3_ts.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
  if (time3_ts.tv_nsec < 0)
  {
    time3_ts.tv_sec -=1;
    time3_ts.tv_nsec += 1000000000;
  }
  return time3_ts;
}


timespec timespec_wait(const timespec& delay_ts)
{
  timespec remain_ts{0, 0};
  int interrupted = nanosleep(&delay_ts, &remain_ts);
  while (interrupted == -1)
  {
    interrupted = nanosleep(&remain_ts, &remain_ts);
  }
  return remain_ts;
}


timespec  operator- (const timespec& time_ts)
{
  timespec negTime_ts;
  negTime_ts = timespec_negate(time_ts);
  return negTime_ts;
}



timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
  timespec addTime_ts;
  addTime_ts = timespec_add(time1_ts, time2_ts);
  return addTime_ts;
}



timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
  timespec subTime_ts;
  subTime_ts = timespec_subtract(time1_ts, time2_ts);
  return subTime_ts;
}


timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
  time_ts = timespec_add(time_ts, delay_ts);
  return time_ts;
}


timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
  time_ts = timespec_subtract(time_ts, delay_ts);
  return time_ts;
}


bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
  return ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec));
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
  return ((time1_ts.tv_sec != time2_ts.tv_sec) || (time1_ts.tv_nsec != time2_ts.tv_nsec));
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
  if (time2_ts.tv_sec > time1_ts.tv_sec)
  {
      return true;
  }
  if (time2_ts.tv_sec == time1_ts.tv_sec)
  {
    return time2_ts.tv_nsec > time1_ts.tv_nsec;
  }
  return false;
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
  {
  if (time1_ts.tv_sec > time2_ts.tv_sec)
  {
      return true;
  }
  if (time1_ts.tv_sec == time2_ts.tv_sec)
  {
    return time1_ts.tv_nsec > time2_ts.tv_nsec;
  }
  return false;
}
}




















