#include <stdlib.h>  /* malloc & free */
#include <string.h>  /* strcpy */
#include "vector.h"
#include "player.h"
#include "cards.h"
#include "shapes.h"
#include "print.h"
#include "strategy.h"
#include "ADTDErr.h"


struct Player
{
    char*    m_name;
    int      m_id;   
    int      m_humenOrComputer;
    Vector*  m_clav;
    Vector*  m_diamond;
    Vector*  m_heart;
    Vector*  m_peak;
    int      m_magic;   
};

/************* helping to create ****************/
ADTErr CreatTheCardsVectors(Player* _playr);

/********** helping to get card from player *************/
ADTErr OneOfThreeCardsFromHuman(Player* _player, Card* _card);
void GetTheCardFromTheShapVector(Vector* _vec, size_t _Index, Card* _card);
ADTErr GetCardFromHuman(Player* _player, Card* _card);

/******** helping does player have the card ************/
ADTErr DoesTheCardInTheShapeVector(Vector* _vec, Card _card);


/**************** Creat Player *******************/
Player* PlayerCreate(char* _name, int _id, int _humenOrComputer)
{
    Player* myPlayer; 
    
    if (_humenOrComputer != HUMAN && _humenOrComputer != COMPUTER)
    {
        return NULL;
    }
    
    myPlayer = (Player*)malloc(sizeof(Player));
    if (NULL == myPlayer)
    {
        return NULL;
    } 
    
    myPlayer->m_magic = MAGIC;
    
    myPlayer->m_clav = NULL;
    myPlayer->m_diamond = NULL;
    myPlayer->m_heart = NULL;
    myPlayer->m_peak = NULL;
    
    if (ERR_OK != CreatTheCardsVectors(myPlayer))
    {
        PlayerDestroy(myPlayer);
        return NULL;    
    }
    
    myPlayer->m_name = (char*)malloc(sizeof(char) * strlen(_name));
    if (myPlayer->m_name == NULL)
    {
        PlayerDestroy(myPlayer);
        return NULL;
    }
    
    strcpy(myPlayer->m_name, _name);
    myPlayer->m_id = _id;   
    myPlayer->m_humenOrComputer = _humenOrComputer;
    
    return myPlayer;      
}


/**************** Destroy Plear *******************/
void PlayerDestroy(Player* _playr)
{
    if (_playr == NULL || _playr->m_magic != MAGIC)
    {
        return;
    }
    
    _playr->m_magic = 0;
    
    VectorDestroy(_playr->m_clav);
    VectorDestroy(_playr->m_diamond);
    VectorDestroy(_playr->m_heart);
    VectorDestroy(_playr->m_peak);

    if (_playr->m_name != NULL)
    {
        free(_playr->m_name);
    }
        
    free(_playr);
}


/**************** Get Player Name *****************/
ADTErr GetPlayerName(Player* _player, char** _name)
{
    if (_player == NULL || _name == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    *_name = _player->m_name;
    return ERR_OK;    
}


/**************** Give Plear Card *****************/
ADTErr GivePlayerCard(Player* _playr, Card _card)
{
    int ans;
    
    if (_playr == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if (_card >= NUM_OF_CARDS || _card < CLAV_2)
    {
        return ERR_WRONG_INPUT;
    }
    
    /* adding to the vectors */  
    if (CLAV_SHAPE(_card))
    {
        return VectorAdd(_playr->m_clav, _card);
    }
    
    if (DIAMOND_SHAPE(_card))
    {
        return VectorAdd(_playr->m_diamond, _card);
    }
    
    if (HEART_SHAPE(_card))
    {
        return VectorAdd(_playr->m_heart, _card);
    }

    if (PEAK_SHAPE(_card))
    {
        return VectorAdd(_playr->m_peak, _card);
    }    
}


/************* Print Player Cards ****************/
ADTErr PrintPlayerCards(Player* _playr)
{
    if (_playr == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    PrintPlayerHand(_playr->m_clav, _playr->m_diamond, _playr->m_heart, _playr->m_peak);
    
    return ERR_OK;  
}


/************ Does Player Have The Card **********/
ADTErr DoesPlayerHaveTheCard(Player* _player, Card _card)
{
    
    if (_player == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if (CLAV_SHAPE(_card))
    {
        if (YES == DoesTheCardInTheShapeVector(_player->m_clav, _card))
        {
            return YES;
        }
    }
    
    if (DIAMOND_SHAPE(_card))
    {
        if (YES == DoesTheCardInTheShapeVector(_player->m_diamond, _card))
        {
            return YES;
        }    
    }
    
    if (HEART_SHAPE(_card)) 
    {
        if (YES == DoesTheCardInTheShapeVector(_player->m_heart, _card))
        {
            return YES;
        } 
    }

    if (PEAK_SHAPE(_card))
    {
        if (YES == DoesTheCardInTheShapeVector(_player->m_peak, _card))
        {
            return YES;
        }
    }
    
    return NO;
}


/************** Get Card From Player ******** maove down*****/
ADTErr GetCardFromPlayer(Player* _player, Card* _card, int* _table, int _trickNumber, int _isHeartsPossible, Strategy _strategy)
{
    int ans;
    
    if (_player == NULL || _card == NULL || _table == NULL || _strategy == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if(_trickNumber == 0)
    {
        if (_player->m_humenOrComputer == COMPUTER)
        {
            return (*_strategy)(_player->m_clav, _player->m_diamond, _player->m_heart, _player->m_peak, _trickNumber, _isHeartsPossible, _table, _card);         
        }
    
        if (_player->m_humenOrComputer == HUMAN)
        {
            return OneOfThreeCardsFromHuman(_player, _card);
        }
    }
    
    if(_trickNumber == 1 && _table[NUM_OF_PLEYRS] == NO_CARD)
    {
        GetTheCardFromTheShapVector(_player->m_clav, CLAV_2 % NUM_OF_CARDS_AT_SHAPE, _card);
        return ERR_OK;
    }
    
    if (_player->m_humenOrComputer != HUMAN)
    {
        return (*_strategy)(_player->m_clav, _player->m_diamond, _player->m_heart, _player->m_peak, _trickNumber, _isHeartsPossible, _table, _card);          
    }
    
    else
    {
        return GetCardFromHuman(_player, _card);  
    }
}


/************* helping to create ****************/
/* Creat The Cards Vectors*/
ADTErr CreatTheCardsVectors(Player* _playr)
{
    Vector* vecClav;
    Vector* vecDiamond;
    Vector* vecHeart;
    Vector* vecPeak;
    
    vecClav = VectorCreate(NUM_OF_CARDS_AT_SHAPE, NUM_OF_CARDS_AT_SHAPE);        
    _playr->m_clav = vecClav;       
             
    vecDiamond = VectorCreate(NUM_OF_CARDS_AT_SHAPE, NUM_OF_CARDS_AT_SHAPE);        
    _playr->m_diamond = vecDiamond;       

    vecHeart = VectorCreate(NUM_OF_CARDS_AT_SHAPE, NUM_OF_CARDS_AT_SHAPE);        
    _playr->m_heart = vecHeart;       

    vecPeak = VectorCreate(NUM_OF_CARDS_AT_SHAPE, NUM_OF_CARDS_AT_SHAPE);        
    _playr->m_peak = vecPeak;
    
    if (vecClav == NULL || vecDiamond == NULL || vecHeart == NULL || vecClav == NULL)
    {
         return ERR_ALLOCATION_FAILED;
    }       
    
    return ERR_OK;
}


/************* helping to get card from player ****************/
/* One Of Three Cards From Human*/
ADTErr OneOfThreeCardsFromHuman(Player* _player, Card* _card)
{
    int ans;
    size_t playerCardsNumber = 0;
    
    size_t clavCardsNumber = 0;
    size_t diamondCardsNumber = 0;
    size_t heartCardsNumber = 0;
    size_t peakCardsNumber = 0;
    
    VectorItemsNum(_player->m_clav, &clavCardsNumber);
    VectorItemsNum(_player->m_diamond, &diamondCardsNumber);
    VectorItemsNum(_player->m_heart, &heartCardsNumber);
    VectorItemsNum(_player->m_peak, &peakCardsNumber);
    
    playerCardsNumber = clavCardsNumber + diamondCardsNumber + heartCardsNumber + peakCardsNumber;     
        
    PrintChooseThreeCards(_player->m_clav, _player->m_diamond, _player->m_heart, _player->m_peak, playerCardsNumber, &ans);
    
    if (ans < clavCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_clav, ans, _card);
        return ERR_OK;
    }
    
    ans -= clavCardsNumber;
    if (ans < diamondCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_diamond, ans, _card);
        return ERR_OK;
    }
    
    ans -= diamondCardsNumber;
    if (ans < peakCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_peak, ans, _card);
        return ERR_OK;
    }
    
    ans -= peakCardsNumber;
    if (ans < heartCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_heart, ans, _card);
        return ERR_OK;
    }    
}

/* Get The Card From The Shap Vector */
void GetTheCardFromTheShapVector(Vector* _vec, size_t _Index, Card* _card)
{

    int justToSend;
    size_t vecSize;
    int temp;
    
    VectorItemsNum(_vec, &vecSize);
    VectorGet(_vec, _Index, (int*)_card);
    
    if (vecSize == 1)
    {
        VectorDelete(_vec, (int*)_card);
    }
    
    /* sheft left */
    for (; _Index < vecSize - 1; _Index += 1)
    {
        VectorGet(_vec, _Index + 1, &temp);
        VectorSet(_vec, _Index, temp);     
    }
    
    VectorDelete(_vec, &justToSend);
}

/* Get Card From Human*/
ADTErr GetCardFromHuman(Player* _player, Card* _card)
{
    int ans;
    size_t playerCardsNumber = 0;
    
    size_t clavCardsNumber = 0;
    size_t diamondCardsNumber = 0;
    size_t heartCardsNumber = 0;
    size_t peakCardsNumber = 0;
    
    VectorItemsNum(_player->m_clav, &clavCardsNumber);
    VectorItemsNum(_player->m_diamond, &diamondCardsNumber);
    VectorItemsNum(_player->m_heart, &heartCardsNumber);
    VectorItemsNum(_player->m_peak, &peakCardsNumber);
    
    playerCardsNumber = clavCardsNumber + diamondCardsNumber + heartCardsNumber + peakCardsNumber;     
        
    PrintChooseCard(_player->m_clav, _player->m_diamond, _player->m_heart, _player->m_peak, playerCardsNumber, &ans);
    
    if (ans < clavCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_clav, ans, _card);
        return ERR_OK;
    }
    
    ans -= clavCardsNumber;
    if (ans < diamondCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_diamond, ans, _card);
        return ERR_OK;
    }
    
    ans -= diamondCardsNumber;
    if (ans < peakCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_peak, ans, _card);
        return ERR_OK;
    }
    
    ans -= peakCardsNumber;
    if (ans < heartCardsNumber)
    {
        GetTheCardFromTheShapVector(_player->m_heart, ans, _card);
        return ERR_OK;
    }      
} 

/************* Helping Does Player Have The Card ****************/
/* Does The Card In The Shape Vector */
ADTErr DoesTheCardInTheShapeVector(Vector* _vec, Card _card)
{
    int i;
    size_t numOfCards;
    int tempCard;

    VectorItemsNum(_vec, &numOfCards);
    for (i = 0; i < numOfCards; i += 1)             
    {
        VectorGet(_vec, i, &tempCard);
        if (tempCard == _card)
        {
            return YES;        
        }    
    }
    return NO;
}

