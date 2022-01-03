#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h> /* size_t */ 
#include "ADTDErr.h"

typedef struct Game Game;


/*  Creat Game
description: creat a new game
input: 1. number of pleyrs (can't be zero)
       2. number of human player 
       3. end score (can't be zero) 
output: pointer to Game
error: return NULL           */  
Game* GameCreate(size_t _numOfPlayers, size_t _numOfHumanPlayers, int _endScore); 


/*  Run Game
description: runing the game 
input: pointer to Game
output: 
error: ???                  */ 
ADTErr GameRun(Game* _myGame);


/*  Destroy Game
description: destroy the game 
input: pointer to Game
output: void
error:                     */
void GameDestroy(Game* _game);

#endif
