#ifndef __MY_TIME_H__
#define __MY_TIME_H__

#include <time.h>

enum
{
    FIRST_SMALLER,
    SECND_SMALLER,
    TIME_UPTADE_FAIL,
    TIME_UPTADE_SUCCESS
};


/**
*/
size_t GetTime(__clockid_t _clockID);



/**
 */
int TimeComper(size_t _firstTime, size_t _secndTime);



/**
 */ 
void TimeWait(size_t _milliSec);


#endif  /* __MY_TIME_H__ */ 