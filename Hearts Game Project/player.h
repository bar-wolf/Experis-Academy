#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "ADTDErr.h"
#include "cards.h"
#include "strategy.h"

typedef struct Player Player; 


/*  Creat Plear
description: creat a player
input: 1. name
       2. id namber
       3. humen or computer (computer/humen)
output: pointer to player
error: return NULL          */  
Player* PlayerCreate(char _name[], int _id, int _humenOrComputer);


/*  Destroy Player
description: delete a player
input: pointer to player
output: void
error:                     */  
void PlayerDestroy(Player* _playr);


/*  Give Player Card
description: give a card to a player
input: 1. Card
       2. Player
output: ERR_OK
error:  ERR_FULL_HAND      */  
ADTErr GivePlayerCard(Player* _playr, Card _card);


/* TODO write all function input and error */
/*  Get Card From Human
description: get a card that human player choose
input: pointer to card (to get beck the chosen card)
output: ERR_OK
error:           */ 
ADTErr GetCardFromPlayer(Player* _player, Card* _card, int* _table, int _trickNumber, int _isHeartsPossible, Strategy _strategy);


/*  Does Player Have The Card ?
description: tell if player have specific card
input: 1. Card
       2. Player
output: YES/NO
error:  ERR_EMPTY_HAND     */ 
ADTErr DoesPlayerHaveTheCard(Player* _player, Card _card);


/* TODO  description */ 
ADTErr PrintPlayerCards(Player* _playr);


/* TODO  description */
ADTErr GetPlayerName(Player* _player, char** _name);


#endif







