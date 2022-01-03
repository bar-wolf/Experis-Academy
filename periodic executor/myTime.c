#define _XOPEN_SOURCE 600 

#include <stdio.h>
#include <time.h>
#include "myTime.h"

#define SEC_TO_MILLISEC(x) (x)*1000
#define NANOSEC_TO_MILLISEC(x) (x)*0.000001
#define MILLISEC_TO_MACROSEC(x) (x)*1000

typedef struct timespec timespec;



size_t GetTime(__clockid_t _clockID)
{ 
    timespec time;
    size_t sec;                                                           
    size_t nanoSec; 

    if (_clockID != CLOCK_REALTIME_COARSE && _clockID != CLOCK_MONOTONIC && _clockID != CLOCK_REALTIME)
    {
        return -1;
    }

    clock_gettime(_clockID, &time);

    sec = (size_t)time.tv_sec;
    nanoSec = (size_t)time.tv_nsec;

    return (SEC_TO_MILLISEC(sec) + NANOSEC_TO_MILLISEC(nanoSec));
}



int TimeComper(size_t _firstTime, size_t _secndTime)
{
    if (_firstTime < _secndTime)
    {
        return FIRST_SMALLER; 
    }

    return SECND_SMALLER; 
}



void TimeWait(size_t _milliSec)
{
    usleep(MILLISEC_TO_MACROSEC(_milliSec)); 
}