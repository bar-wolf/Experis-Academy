#ifndef __DECK_H__
#define __DECK_H__

#include "cards.h"

typedef struct Deck Deck;
 
 
/*  Creat Deck
description: creat a deck
input: number of cards decks (can't be zero) 
output: void
error: return NULL               */  
Deck* DeckCreate(size_t _numOfDecks);


/*  Destroy Deck
description: destroy the deck
input: pointer to Deck
output: void
error:                           */  
void DeckDestroy(Deck* _deck);


/*  Shuffle Deck       
description: shuffle a deck
input: pointer to Deck
output: ERR_OK
error: ERR_EMPTY_DECK            */  
ADTErr DeckShuffle(Deck* _deck);


/*  Get Card From Deck
description: tack a card from the deck
input: 1. pointer to Deck
       2. pointer to Card (to get beck the card)
output: ERR_OK
error: ERR_EMPTY_DECK, ERR_NOT_INITIALIZED, ERR_UNDERFLOW (caming frome vector)            */  
ADTErr GetCardFromDeck(Deck* _deck, Card* _card);


/*  Give Card To Deck  
description: give a card to the deck
input: 1. pointer to Deck
       2. Card 
output: ERR_OK
error: ERR_FULL_DECK            */  
ADTErr GiveCardToDeck(Deck* _deck, Card _card);

#endif
