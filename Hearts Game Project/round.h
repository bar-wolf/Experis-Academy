#ifndef __RAUND_H__
#define __RAUND_H__
#include "player.h"
#include "game.h"

typedef struct Round Round; 


/*  Creat Round
description: creat new round
input: 1. array of pointers to Player
       2. array of points
       3. number of round 
       4. number of players 
output: pointer to Raund
error: return NULL           */  
Round* RoundCreat(Player** _playersArr, int* _pointsArr, size_t _numberOfRound, size_t _numberOfPlayers);


/*  Destroy Round 
description: delete the round
input: pointer to Game
output: void
error:                      */  
void RoundDestroy(Round* _round);


/*  Run Round
description: runing hearts round
input: 1. pointer to Round  
output: ERR_OK
error:                      */  
ADTErr RoundRun(Round* _round);

#endif 
