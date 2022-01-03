#ifndef __ADTD_ERR_H__
#define __ADTD_ERR_H__
typedef enum
{
    /* General ADT Errors */
    ERR_OK = 0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    
    /* For Hearts */
    ERR_WRONG_INPUT,
    ERR_FULL_HAND,
    ERR_EMPTY_HAND,
    ERR_FULL_DECK,
    ERR_EMPTY_DECK,
    
    YES = 100,
	NO,
	COMPUTER,
	HUMAN,

	MAGIC = 263974,
	
	NUM_OF_PLEYRS = 4,
	FORGIVENESS = 5,  /* the number of times a user can enter an incorrect index when choosing a card */
	NUM_OF_HUMAN_PLEYRS = 1,
	END_SCORE = 100,
	MAX_CHARS_FOR_NAME = 15
} ADTErr;

#endif 
