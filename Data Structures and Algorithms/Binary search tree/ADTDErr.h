#ifndef __ADTD_ERR_H__
#define __ADTD_ERR_H__

typedef enum
{
    /* General ADT Errors */
    ERR_OK =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_SAME_DATA_EXISTS,
    ERR_STACK_BBBBB = 30
	
} ADTErr;

#endif 
