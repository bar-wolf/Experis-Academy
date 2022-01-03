#include <stdlib.h> /* malloc & free */
#include "ADTDErr.h"
#include "player.h"
#include "round.h"
#include "shapes.h"
#include "deck.h"
#include "print.h"
#include "strategy.h"

#define NUM_OF_DECKS 1
#define PASSIBLE 100
#define NUT_PASSIBLE 101
#define I_START 217
#define POINTS_OF_PEAK_Q 13

#define PASS_RIGHT 0
#define PASS_LEFT 1
#define PASS_OPPOSITE 2
#define NO_PASS 3
#define WHERE_TO_PASS _round->m_numberOfRound % 4

struct Round 
{
    Player**   m_playersArr;
    int*       m_pointsArr;
    int        m_isHeartsPossible;
    int        m_trickCount;   
    size_t     m_numberOfRound;
    size_t     m_numberOfPlayers; 
    int        m_magic;    
};

/************* helping round run ***************/
ADTErr SpreadTheDeck (Player** _playersArr, Deck* _deck, size_t _numOfPlayers);

ADTErr ThreeCardsPass(Round* _round);
/* helping three cards pass */
ADTErr CreatArraysForThreeCards(int** _cardsPlayer0, int** _cardsPlayer1, int** _cardsPlayer2, int** _cardsPlayer3);
void GetThreeCards(Round* _round, int* _cardsPlayer0, int* _cardsPlayer1, int* _cardsPlayer2, int* _cardsPlayer3);
void GiveThreeCards(Round* _round, int* _cardsPlayer0, int* _cardsPlayer1, int* _cardsPlayer2, int* _cardsPlayer3); 

ADTErr PlayTheTricks(Round* _round);
/* helping play the tricks */
ADTErr PlayFirstTrick(Round* _round, int* _table);
ADTErr PlayAfterTheFirstPlayer(Round* _round, int _howPlay, int* _table);
void ClearTable(Round* _round, int* _table);
void CountPoints(Round* _round, int* _table);
ADTErr PlayNormalTrick (Round* _round, int* _table);
int DecideWhoTakes(int* _table, Shape _leadShape);

/* general */
Shape FindCardShape(Card _card);


/************************ Round Creat ************************/
Round* RoundCreat(Player** _playersArr, int* _pointsArr, size_t _numberOfRound, size_t _numberOfPlayers)
{
    Round* myRound;
    
    if (_playersArr == NULL || _pointsArr == NULL)
    {
        return NULL;
    }
    
    myRound = (Round*)malloc(sizeof(Round));
    if (myRound == NULL)
    {
        return NULL;
    }
    
    myRound->m_magic = MAGIC;
    myRound->m_playersArr = _playersArr;
    myRound->m_pointsArr = _pointsArr;
    myRound->m_isHeartsPossible = NUT_PASSIBLE; 
    myRound->m_trickCount = 0;
    myRound->m_numberOfRound = _numberOfRound;    
    myRound->m_numberOfPlayers = _numberOfPlayers;

    return myRound;
}


/************************ Round Destroy ************************/
void RoundDestroy(Round* _round)
{
    if (_round == NULL || _round->m_magic != MAGIC)
    {
        return;
    }
    
    _round->m_magic = 0;
    free(_round);
}


/************************ Round Run ************************/
ADTErr RoundRun(Round* _round)
{
    Deck* myDeck;    
    
    if (_round == NULL)
    {
        return ERR_NOT_INITIALIZED;    
    }
    
    myDeck = DeckCreate(NUM_OF_DECKS);
    if (myDeck == NULL)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
/*TODO    DeckShuffle(myDeck); */
    
    SpreadTheDeck(_round->m_playersArr, myDeck, _round->m_numberOfPlayers);
    
/*TODO    SortPlayersHand */

    ThreeCardsPass(_round);
    _round->m_trickCount += 1;
    
/*TODO    SortPlayerHand */
    
    PlayTheTricks(_round);
    
    PrintScore(_round->m_playersArr, _round->m_pointsArr); 
    
    DeckDestroy(myDeck);
    
    RoundDestroy(_round);
    
    return ERR_OK;
}


/************* helping round run ***************/

/*** Play The Tricks ***/
ADTErr PlayTheTricks(Round* _round)
{
    int* table;
    
    table = (int*)malloc(sizeof(int) * (_round->m_numberOfPlayers + 1));
    if (table == NULL)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
    ClearTable(_round, table);    
    
    PlayFirstTrick(_round, table);            
    _round->m_trickCount += 1;
    
      
    for (;_round->m_trickCount <= NUM_OF_CARDS_AT_SHAPE;)
    {
        PrintNumOfTrick(_round->m_trickCount); /* print */
        PlayNormalTrick(_round, table);
        _round->m_trickCount += 1;
    }
   
    free(table);
    return ERR_OK;
}


/*** Helping Play The Tricks ***/

/* Play Normal Trick */
ADTErr PlayNormalTrick (Round* _round, int* _table)
{    
    Card myCard;
    int i;
    
    for (i = 0; i < _round->m_numberOfPlayers; i += 1)
    {
        if (_table[i] == I_START)
        {
            break;
        }
    }
    
    ClearTable(_round, _table);
    
    GetCardFromPlayer(_round->m_playersArr[i], &myCard, _table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
    
    _table[i] = myCard;

    _table[_round->m_numberOfPlayers] = FindCardShape(myCard);     
      
    return PlayAfterTheFirstPlayer(_round, i, _table);
}

/* Count Points */
void CountPoints(Round* _round, int* _table)
{
    int i;
    Card myCard;
    int numOfTaker;
    Shape leadShape = (Shape)_table[_round->m_numberOfPlayers]; 
    
    numOfTaker = DecideWhoTakes (_table, leadShape);
    PrintTaker(_round->m_playersArr ,numOfTaker);   /* print */    
    for (i = 0; i < _round->m_numberOfPlayers; i += 1)
    {
        myCard = _table[i];
        if (HEART == FindCardShape(myCard))
        {
            _round->m_pointsArr[numOfTaker] += 1;             
        }
        
        if (myCard == PEAK_Q)
        {
            _round->m_pointsArr[numOfTaker] += POINTS_OF_PEAK_Q;    
        }
    }
    _table[numOfTaker] = I_START; 
}

/* Decide Who Takes */
int DecideWhoTakes(int* _table, Shape _leadShape)
{
    int i;
    Card myCard;
    Shape myShape;
    int numOfTaker;
    Card highCard = CLAV_2;
    
    for (i = 0; i < NUM_OF_PLEYRS; i += 1)
    {
        myCard = _table[i];
        myShape = FindCardShape(myCard);
        if (myShape == _leadShape && myCard >= highCard)
        {
            highCard = myCard;
            numOfTaker = i;
        }
    }
    
    return numOfTaker;
}

/* Find Card Shape */
Shape FindCardShape(Card _card)
{
    if (CLAV_SHAPE(_card))
    {
        return CLAV;    
    }
    
    if (DIAMOND_SHAPE(_card))
    {
        return DIAMOND;    
    }     

    if (HEART_SHAPE(_card))
    {
        return HEART;    
    }     

    if (PEAK_SHAPE(_card))
    {
        return PEAK;    
    }     
}

/* Play First Trick */
ADTErr PlayFirstTrick(Round* _round, int* _table)
{
    Card myCard;
    int i;
    
    PrintNumOfTrick(_round->m_trickCount);
    
    for(i = 0; i < _round->m_numberOfPlayers; i += 1)
    {    
        if (YES == DoesPlayerHaveTheCard(_round->m_playersArr[i], CLAV_2))
        {
            break;                
        }
    }
    
    /* no one have CLAV_2 */
    if (i == _round->m_numberOfPlayers)
    {
        return ERR_GENERAL; /* TODO return */ 
    }
    
    GetCardFromPlayer(_round->m_playersArr[i], &myCard, _table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
    
    _table[i] = myCard;
    _table[NUM_OF_PLEYRS] = CLAV;
    
    return PlayAfterTheFirstPlayer(_round, i, _table);
}

/* Play After The First Player */
ADTErr PlayAfterTheFirstPlayer(Round* _round, int _howPlay, int* _table)
{
    int i;
    Card myCard;
    
    PrintTable(_round->m_playersArr, _table);
    
    for (i = 0; i < _round->m_numberOfPlayers - 1; i += 1)
    {
        _howPlay = (_howPlay + 1) % _round->m_numberOfPlayers;
        
        GetCardFromPlayer(_round->m_playersArr[_howPlay], &myCard, _table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
        
        _table[_howPlay] = myCard;
        
        PrintTable(_round->m_playersArr, _table);  
    }
    
    CountPoints(_round, _table);
    
    return ERR_OK;
}

/* Clear Table */
void ClearTable(Round* _round, int* _table)
{
    int i;
    for (i = 0; i < _round->m_numberOfPlayers + 1; i += 1)
    {
        _table[i] = NO_CARD;
    }
}

/***  Three Cards Pass ***/
ADTErr ThreeCardsPass(Round* _round)
{
    int* cardsPlayer0; 
    int* cardsPlayer1;
    int* cardsPlayer2;
    int* cardsPlayer3;
    
    if (ERR_OK != CreatArraysForThreeCards(&cardsPlayer0, &cardsPlayer1, &cardsPlayer2, &cardsPlayer3))
    {
        return ERR_ALLOCATION_FAILED;
    }

    if (WHERE_TO_PASS == NO_PASS)
    {
        return ERR_OK;
    }
    
    GetThreeCards(_round, cardsPlayer0, cardsPlayer1, cardsPlayer2, cardsPlayer3);
    
    GiveThreeCards(_round, cardsPlayer0, cardsPlayer1, cardsPlayer2, cardsPlayer3); 

    free(cardsPlayer0);
    free(cardsPlayer1);
    free(cardsPlayer2);
    free(cardsPlayer3);
    
    return ERR_OK;
}


/*** Helping Three Cards Pass ***/

/* Creat Arrays For Three Cards */
ADTErr CreatArraysForThreeCards(int** _cardsPlayer0, int** _cardsPlayer1, int** _cardsPlayer2, int** _cardsPlayer3)
{
    *_cardsPlayer0 = (int*)malloc(sizeof(int) * 4);
    if (*_cardsPlayer0 == NULL)
    {
        return ERR_ALLOCATION_FAILED;
    }
    
    *_cardsPlayer1 = (int*)malloc(sizeof(int) * 4);
    if (*_cardsPlayer1 == NULL)
    {
        free(*_cardsPlayer0);
        return ERR_ALLOCATION_FAILED;
    }

    *_cardsPlayer2 = (int*)malloc(sizeof(int) * 4);
    if (*_cardsPlayer2 == NULL)
    {
        free(*_cardsPlayer0);
        free(*_cardsPlayer1);
        return ERR_ALLOCATION_FAILED;
    }

    *_cardsPlayer3 = (int*)malloc(sizeof(int) * 4);
    if (*_cardsPlayer3 == NULL)
    {
        free(*_cardsPlayer0);
        free(*_cardsPlayer1);
        free(*_cardsPlayer2);
        return ERR_ALLOCATION_FAILED;
    }

    return ERR_OK;
}

/* Give Three Cards */
void GiveThreeCards(Round* _round, int* _cardsPlayer0, int* _cardsPlayer1, int* _cardsPlayer2, int* _cardsPlayer3)
{
    int i;
    
    if (WHERE_TO_PASS == PASS_RIGHT)
    {
        for(i = 0; i < 3; i += 1)
        {
            GivePlayerCard(_round->m_playersArr[1], _cardsPlayer0[i]);
            GivePlayerCard(_round->m_playersArr[2], _cardsPlayer1[i]);
            GivePlayerCard(_round->m_playersArr[3], _cardsPlayer2[i]);
            GivePlayerCard(_round->m_playersArr[0], _cardsPlayer3[i]);
        }
    }
    
    if (WHERE_TO_PASS == PASS_LEFT)
    {
        for(i = 0; i < 3; i += 1)
        {
            GivePlayerCard(_round->m_playersArr[3], _cardsPlayer0[i]);
            GivePlayerCard(_round->m_playersArr[0], _cardsPlayer1[i]);
            GivePlayerCard(_round->m_playersArr[1], _cardsPlayer2[i]);
            GivePlayerCard(_round->m_playersArr[2], _cardsPlayer3[i]);
        }
    } 
    
    if (WHERE_TO_PASS == PASS_OPPOSITE)
    {  
        for(i = 0; i < 3; i += 1)
        {
            GivePlayerCard(_round->m_playersArr[2], _cardsPlayer0[i]);
            GivePlayerCard(_round->m_playersArr[3], _cardsPlayer1[i]);
            GivePlayerCard(_round->m_playersArr[0], _cardsPlayer2[i]);
            GivePlayerCard(_round->m_playersArr[1], _cardsPlayer3[i]);
        }
    }          
}


/*** Get Three Cards ***/
void GetThreeCards(Round* _round, int* _cardsPlayer0, int* _cardsPlayer1, int* _cardsPlayer2, int* _cardsPlayer3)
{
    Card myCard;
    int* table; 
    int i;
       
    for (i = 0; i < 3; i += 1)
    {
        GetCardFromPlayer(_round->m_playersArr[0], &myCard, table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
        _cardsPlayer0[i] = myCard;

        GetCardFromPlayer(_round->m_playersArr[1], &myCard, table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
        _cardsPlayer1[i] = myCard;

        GetCardFromPlayer(_round->m_playersArr[2], &myCard, table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
        _cardsPlayer2[i] = myCard;

        GetCardFromPlayer(_round->m_playersArr[3], &myCard, table, _round->m_trickCount, _round->m_isHeartsPossible, GetCardStrategy);
        _cardsPlayer3[i] = myCard;                          
    }    
}

/* Spread The Deck */
ADTErr SpreadTheDeck (Player** _playersArr, Deck* _deck, size_t _numOfPlayers)
{
    int ans;
    int i;
    Card myCard;
    for (i = 0; i < NUM_OF_CARDS; i += 1)
    {
        ans = GetCardFromDeck(_deck, &myCard);
        if (ERR_OK == ans)
        {
            GivePlayerCard(_playersArr[i % _numOfPlayers] , myCard);    
        }
        else
        {
            return ans;
        } 
    }
    return ERR_OK;
}















