#ifndef __PRINT_H__
#define __PRINT_H__

#include "vector.h"
#include "player.h"
#include "cards.h"
#include "round.h"
#include "shapes.h"

/* TODO description */
void PrintPlayerHand(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak);


/* TODO description */
void PrintChooseThreeCards(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, size_t _numOfCards, int* _ans);


/* TODO description */
void PrintChooseCard (Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, size_t _numOfCards, int* _ans);


/* TODO description */
void PrintTable(Player** _playersArr, int* _table);


/* TODO description */
void PrintNumOfTrick(int _numOfTrick);


/* TODO description */
void PrintTaker(Player** _playersArr, int _taker);


/* TODO description */
void PrintScore(Player** _playersArr, int* _points);


/* TODO description */
void PrintAskForName(char* _name);

#endif 
