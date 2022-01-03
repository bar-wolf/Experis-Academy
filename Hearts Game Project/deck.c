#include <stdlib.h> /* malloc & free */ 
#include "ADTDErr.h"
#include "deck.h"
#include "vector.h"
#include "cards.h"
#include "shapes.h"

struct Deck
{
    Vector* m_cards;
    size_t  m_numOfCards;
    int     m_magic; 
}; 


/**************** Deck Game ****************/
Deck* DeckCreate(size_t _numOfDecks)
{
    int i;
    Vector* vec;
    Deck* myDeck; 
    
    if (_numOfDecks == 0)
    {
        return NULL;
    }
    
    myDeck = (Deck*)malloc(sizeof(Deck));
    if (myDeck == NULL)
    {
        return NULL;
    }
    
    /* create the vector */
    vec = VectorCreate(NUM_OF_CARDS * _numOfDecks, NUM_OF_CARDS);
    if (vec == NULL)
    {
        free(myDeck);
        return NULL;
    }
    
    for (i = NUM_OF_CARDS * _numOfDecks - 1; i >= 0; i -= 1)
    {
        VectorAdd(vec, i % NUM_OF_CARDS);
    }
       
    myDeck->m_cards = vec;
    myDeck->m_numOfCards = NUM_OF_CARDS * _numOfDecks;
    myDeck->m_magic = MAGIC;  
   
    return myDeck;
}


/**************** Deck Destroy ****************/
void DeckDestroy(Deck* _deck)
{
    if (_deck == NULL || _deck->m_magic != MAGIC)
    {
        return;
    }
    
    _deck->m_magic = 0;
    VectorDestroy(_deck->m_cards);
    free(_deck);
}


/**************** Deck Shuffle ****************/
ADTErr DeckShuffle(Deck* _deck)
{
    /* TODO */        
}


/************* Get Card From Deck *************/
ADTErr GetCardFromDeck(Deck* _deck, Card* _card)
{
    int ans; 
    if (_deck == NULL || _card == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if (_deck->m_numOfCards == 0)
    {
        return ERR_EMPTY_DECK;
    }

    ans = VectorDelete(_deck->m_cards, (int*)_card);
    if (ans != ERR_OK)
    {
        return ans;
    }
    
    _deck->m_numOfCards -= 1;
    
    return ERR_OK;
}


/************* Give Card To Deck *************/
ADTErr GiveCardToDeck(Deck* _deck, Card _card)
{
    /* No need for a heart game */ 
}





