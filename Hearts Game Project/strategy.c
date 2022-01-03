#include <stdlib.h> /* size_t */
#include "vector.h"
#include "cards.h"
#include "shapes.h"
#include "print.h"

#define DONE 0
#define NOT_DONE 1
 
/********* helping functions ******************/
ADTErr ThreeCardsTrick(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, Card* _card);
ADTErr NormalTrick(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, int _trickNumber, int _isHeartsPossible, int* _table, Card* _card);
/* Helping Normal Trick*/
ADTErr FindCard(Vector* _vec, Card _card, int* _index);
int GetCardByIndex(Vector* _vec, size_t _index, Card* _card);
ADTErr NoShape(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, Card* _card);
/* Helping Three Cards Pass(return DONE/NOT_DONE) */ 
int GoHighPeak(Vector* _cards, Card* _card);
int GoHighHeart(Vector* _cards, Card* _card);
int GoHighDiamOrClav(Vector* _cards, Card* _card);
int GoLowCard(Vector* _cards, Card* _card);


/************** Get Card Strategy *****************/
ADTErr GetCardStrategy(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, int _trickNumber, int _isHeartsPossible, int* _table, Card* _card)
{    
    if (_clav == NULL || _diamond == NULL || _heart == NULL || _peak == NULL || _card == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    if(_trickNumber < 0)
    {
        return ERR_WRONG_INPUT;
    }    
       
    if (_trickNumber == 0)
    {
        return ThreeCardsTrick(_clav, _diamond, _heart, _peak, _card); 
    }
    
    if (_trickNumber > 0 && _trickNumber <= NUM_OF_CARDS_AT_SHAPE)
    {
        if (_table == NULL)
        {
            return ERR_NOT_INITIALIZED;
        }
        return NormalTrick(_clav, _diamond, _heart, _peak, _trickNumber, _isHeartsPossible, _table, _card);     
    }
    
    if (_trickNumber > NUM_OF_CARDS_AT_SHAPE)
    {
        return ERR_WRONG_INPUT;
    }
}


/********* helping functions ******************/

/*** Normal Trick ***/
ADTErr NormalTrick(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, int _trickNumber, int _isHeartsPossible, int* _table, Card* _card)
{
    int index = 0;
    size_t numOfCards;
    
    /* first to play */
    if (_table[NUM_OF_PLEYRS] == NO_CARD)
    {
        if (YES == FindCard(_peak, PEAK_Q, &index))
        {
            if (DONE == GetCardByIndex(_clav, 0, _card))
            {return ERR_OK;}
            
            if (DONE == GetCardByIndex(_diamond, 0, _card))
            {return ERR_OK;}
            
            if (DONE == GetCardByIndex(_peak, 0, _card))
            {return ERR_OK;}
            
            if (DONE == GetCardByIndex(_heart, 0, _card))
            {return ERR_OK;}
        }
        else
        {
            if (DONE == GetCardByIndex(_peak, 0, _card))
            {return ERR_OK;}
            
            if (DONE == GetCardByIndex(_clav, 0, _card))
            {return ERR_OK;}
            
            if (DONE == GetCardByIndex(_diamond, 0, _card))
            {return ERR_OK;}
            
            if (DONE == GetCardByIndex(_heart, 0, _card))
            {return ERR_OK;}
        }  
    }        

    /* not first to play */
    if (_table[NUM_OF_PLEYRS] != NO_CARD)
    {
        /* clav to play */
        if (_table[NUM_OF_PLEYRS] == CLAV)
        {
           VectorItemsNum(_clav, &numOfCards);
           
           if (numOfCards == 0)
           {
               return NoShape(_clav, _diamond, _heart, _peak, _card); 
           }
           else
           {
               GetCardByIndex(_clav, 0, _card);
               return ERR_OK;                      
           }
        } 
        
        /*  to diamond play */
        if (_table[NUM_OF_PLEYRS] == DIAMOND)
        {
           VectorItemsNum(_diamond, &numOfCards);
           
           if (numOfCards == 0)
           {
               return NoShape(_clav, _diamond, _heart, _peak, _card); 
           }
           else
           {
               GetCardByIndex(_diamond, 0, _card);
               return ERR_OK;                      
           }
        }    
        
        /* heart to play */
        if (_table[NUM_OF_PLEYRS] == HEART)
        {
           VectorItemsNum(_heart, &numOfCards);
           
           if (numOfCards == 0)
           {
               return NoShape(_clav, _diamond, _heart, _peak, _card); 
           }
           else
           {
               GetCardByIndex(_heart, 0, _card);
               return ERR_OK;                      
           }
        }    
        
        /* peak to play */
        if (_table[NUM_OF_PLEYRS] == PEAK)
        {
           VectorItemsNum(_peak, &numOfCards);
           
           if (numOfCards == 0)
           {
               return NoShape(_clav, _diamond, _heart, _peak, _card); 
           }
           else
           {
               GetCardByIndex(_peak, 0, _card);
               return ERR_OK;                      
           }
        }        
    }

    return ERR_OK;
}

/* No Shape */
ADTErr NoShape(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, Card* _card)
{
    int index;
    size_t numOfCards;
    
    if (YES == FindCard(_peak, PEAK_Q, &index))
    {
        GetCardByIndex(_peak, index, _card);
        return ERR_OK;           
    }
    
    if (YES == FindCard(_peak, PEAK_K, &index))
    {
        GetCardByIndex(_peak, index, _card);
        return ERR_OK;           
    }
    
    if (YES == FindCard(_peak, PEAK_A, &index))
    {
        GetCardByIndex(_peak, index, _card);
        return ERR_OK;           
    }
    
    VectorItemsNum(_heart, &numOfCards);
    if (numOfCards > 0)
    {
       return VectorDelete(_heart, (int*)_card);
    }
    
    VectorItemsNum(_clav, &numOfCards);
    if (numOfCards > 0)
    {
       return VectorDelete(_clav, (int*)_card);
    }
    
    VectorItemsNum(_diamond, &numOfCards);
    if (numOfCards > 0)
    {
       return VectorDelete(_diamond, (int*)_card);
    }
    
    VectorItemsNum(_peak, &numOfCards);
    if (numOfCards > 0)
    {
       return VectorDelete(_peak, (int*)_card);
    }
}

/* Get Card By Index */
int GetCardByIndex(Vector* _vec, size_t _Index, Card* _card)
{
    size_t numOfCards;
    int justToSend;
    int temp;
    
    VectorItemsNum(_vec, &numOfCards);
    
    if (numOfCards == 0)
    {
        return NOT_DONE;
    }
    
    if (numOfCards == 1)
    {
        VectorDelete(_vec, (int*)_card);
        return DONE; 
    }
    
    if (numOfCards > 1)
    {
        VectorGet(_vec, _Index, (int*)_card);
            
        /* sheft left */
        for (; _Index < numOfCards - 1; _Index += 1)
        {
            VectorGet(_vec, _Index + 1, &temp);
            VectorSet(_vec, _Index, temp);     
        }
    
        VectorDelete(_vec, &justToSend);
        return DONE;   
    }
}

/* Find Card */
ADTErr FindCard(Vector* _vec, Card _card, int* _index)
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
            *_index = i;
            return YES;        
        }    
    }
    return NO;
}

/*** Three Cards Pass ***/ 
ADTErr ThreeCardsTrick(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, Card* _card)
{
    if(DONE == GoHighPeak(_peak, _card))
    {return ERR_OK;}

    if(DONE == GoHighHeart(_heart, _card))
    {return ERR_OK;}

    if(DONE == GoHighDiamOrClav(_diamond, _card))
    {return ERR_OK;}

    if(DONE == GoHighDiamOrClav(_clav, _card))
    {return ERR_OK;}

    if(DONE == GoLowCard(_diamond, _card))
    {return ERR_OK;}

    if(DONE == GoLowCard(_clav, _card))
    {return ERR_OK;}

    if(DONE == GoLowCard(_heart, _card))
    {return ERR_OK;}

    if(DONE == GoLowCard(_peak, _card))
    {return ERR_OK;} 
}

/*** Helping Three Cards Pass ***/

/* Go High Peak */
int GoHighPeak(Vector* _cards, Card* _card)
{
    size_t numOfCards;
    VectorItemsNum(_cards, &numOfCards);
    if (numOfCards > 0)
    {
        VectorGet(_cards, numOfCards - 1, (int*)_card);
        if (*_card >= PEAK_Q)
        {
            VectorDelete(_cards, (int*)_card);    
            return DONE;
        }
    }
    return NOT_DONE;
}

/* Go High Heart */
int GoHighHeart(Vector* _cards, Card* _card)
{
    size_t numOfCards;
    VectorItemsNum(_cards, &numOfCards);
    if (numOfCards > 0)
    {
        VectorGet(_cards, numOfCards - 1, (int*)_card);
        if (*_card > HEART_5)
        {
            VectorDelete(_cards, (int*)_card);    
            return DONE;
        }
    }
    return NOT_DONE;
}

/* Go High Diam Or Clav */
int GoHighDiamOrClav(Vector* _cards, Card* _card)
{
    size_t numOfCards;
    VectorItemsNum(_cards, &numOfCards);
    if (numOfCards > 0)
    {
        if (numOfCards < 3)
        {
            VectorGet(_cards, numOfCards - 1, (int*)_card);    
            VectorDelete(_cards, (int*)_card);    
            return DONE;
        }
         
        if (*_card >= DIAMOND_J && *_card <= DIAMOND_A || *_card >= CLAV_J && *_card <= CLAV_A)
        {
            VectorDelete(_cards, (int*)_card);    
            return DONE;
        }
    }
    return NOT_DONE;
}

/* Go Low Card */
int GoLowCard(Vector* _cards, Card* _card)
{
    size_t numOfCards;
    VectorItemsNum(_cards, &numOfCards);
    if (numOfCards > 0)
    {
        VectorDelete(_cards, (int*)_card);    
        return DONE;
    }    
    return NOT_DONE;
}






