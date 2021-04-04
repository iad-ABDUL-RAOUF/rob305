#ifndef timespec_h_INCLUDED
#define timespec_h_INCLUDED

#include <time.h>
#include <math.h>

double timespec_to_ms(const timespec& time_ts);
/**
 * \brief converter from timespec to milliseconds
 * \param time_ts timespec to convert
 * \return number of milliseconds 
*/
timespec timespec_from_ms(double time_ms);
/**
 * \brief converter from milliseconds to timespec
 * \param time_ms number of milliseconds to convert
 * \return corresponding timespec
*/

timespec timespec_now();
/**
 * \brief creating a timespec with current time
*/
timespec timespec_negate(const timespec& time_ts);
/**
 * \brief negate a timespec
 * \param time_ts timespec to negate
 * \return negative timespec
*/

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief adding two timespecs
 * \param time1_ts timespec to add
 * \param time2_ts timespec to add
 * \return added timespecs
*/
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief substracting two timespecs
 * \param time1_ts timespec to be substracted
 * \param time2_ts timespec to substract
 * \return substracted timespecs
*/

timespec timespec_wait(const timespec& delay_ts);
/**
 * \brief putting calling task to sleep
 * \param delay_ts timespec to wait
 * \return remaining time that needs to be waited
*/

timespec  operator- (const timespec& time_ts);
/**
 * \brief operator to negate a timespec
 * \param time_ts timespec to negate
 * \return negative timespec
*/
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief operator to add two timespecs
 * \param time1_ts timespec to add
 * \param time2_ts timespec to add
 * \return added timespecs
*/
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief operator to substract two timespecs
 * \param time1_ts timespec to be substracted
 * \param time2_ts timespec to substract
 * \return substracted timespecs
*/
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);
/**
 * \brief operator to add a timespec to another
 * \param time1_ts added timespec
 * \param time2_ts timespec to add
 * \return added timespec
*/
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);
/**
 * \brief operator to substract a timespec to another
 * \param time1_ts timespec to be substracted
 * \param time2_ts timespec to substract
 * \return substracted timespec
*/
bool operator== (const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief operator to check if to timespecs are equal
 * \param time1_ts timespec to be compared
 * \param time2_ts timespec to be compared
 * \return resulting bool
*/
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief operator to check if to timespecs are not equal
 * \param time1_ts timespec to be compared
 * \param time2_ts timespec to be compared
 * \return resulting bool
*/
bool operator< (const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief operator to check if a timespec is lower than another
 * \param time1_ts timespec to be compared
 * \param time2_ts timespec to be compared
 * \return resulting bool
*/
bool operator> (const timespec& time1_ts, const timespec& time2_ts);
/**
 * \brief operator to check if a timespec is greater than another
 * \param time1_ts timespec to be compared
 * \param time2_ts timespec to be compared
 * \return resulting bool
*/

#endif