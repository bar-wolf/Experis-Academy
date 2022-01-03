#include <stdio.h>
#include <string.h> /* strcpy */
#include "print.h"
#include "cards.h"
#include "shapes.h"
#include "player.h"
#include "vector.h"
#include "ADTDErr.h"

/* cards suites symbols */
#define HEART "\x1B[31m" "\xE2\x99\xA5" "\x1B[0m" /* RED HEART NORMAL */
#define PEAK "\x1b[90m" "\xE2\x99\xA0" "\x1B[0m" /* GRAY PEAK NORMAL */
#define DIAMOND "\x1B[31m" "\xE2\x99\xA6" "\x1B[0m" /* RED DIAMOND NORMAL */
#define CLUB "\x1b[90m" "\xE2\x99\xA3" "\x1B[0m" /* GRAY CLUB NORMAL */

/********** helping functions ***********************/
void PrintPlayerShapeCards(Vector* _cards);

void PrintClavCard(Card _myCard);
void PrintDiamondCard(Card _myCard);
void PrintHeartCard(Card _myCard);
void PrintPeakCard(Card _myCard);


/************** Print Choose Three Card Pass ***************/
void PrintChooseThreeCards(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, size_t _numOfCards, int* _ans)
{   
    int i;    
    *_ans = _numOfCards;
    
    if (_clav == NULL || _diamond == NULL || _heart == NULL || _peak == NULL || _ans == NULL)
    {
        return;
    }
    
    sleep(1);
    printf("Choose three cards to pass- ");
    
    if (_numOfCards == NUM_OF_CARDS_AT_SHAPE)
    {
        printf("Choose first card:\n\n");
    }
    
    else if(_numOfCards == NUM_OF_CARDS_AT_SHAPE - 1)
    {
        printf("Choose second card:\n\n");
    }
    
    else if(_numOfCards == NUM_OF_CARDS_AT_SHAPE - 2)
    {
        printf("Choose third card:\n\n");    
    }
    
    PrintPlayerHand (_clav, _diamond, _heart, _peak);
    for (i = 0; i < _numOfCards; i += 1)
    {
        printf(" [%d] " ,i);
    }
    
    putchar('\n');
    putchar('\n');
    fflush( stdout );
    
    for(i = 0; (*_ans >= _numOfCards || *_ans < 0) && i < FORGIVENESS; i++)
    {
        scanf("%d", _ans);
    
        if (*_ans >= _numOfCards || *_ans < 0)
        {
            printf("Index does not exist please select again\n");
            fflush( stdout );
        }
    }
    
    printf("***********************************************************\n");
    fflush( stdout );
}


void PrintAskForName(char* _name)
{
    printf("\n\n %s %s Welcome to Game of Hearts %s %s \n\n",HEART,PEAK,DIAMOND,CLUB);
    printf("Please enter your name\n");
    scanf("%s", _name);
    printf("\nOkay let's get started\n\n");
        
}

/************** Print NumOf Trick ***************/
void PrintNumOfTrick(int _numOfTrick)
{
    sleep(1);
    printf("\n   ** Trick number %d **  \n", _numOfTrick);
    fflush( stdout );
}


/*************** Print Taker ******************/
void PrintTaker(Player** _playersArr, int _taker)
{
    char* name;
    GetPlayerName(_playersArr[_taker], &name);
   
    printf(" %s take the cards\n\n", name);
    fflush( stdout );
}


/************ Print Score ***************/
void PrintScore(Player** _playersArr, int* _points)
{
    char* name;
    int i;
    
    sleep(1);
    printf(" ** Table Score **\n");
    
    for (i = 0; i < NUM_OF_PLEYRS; i += 1)
    {       
        GetPlayerName(_playersArr[i], &name);
        printf(" %s: %d\n", name, _points[i]);
    } 
    putchar('\n');
    fflush( stdout );             
}


/************ Print One Card ***************/
void PrintOneCard(Card _myCard)
{
    if (CLAV_SHAPE(_myCard))
    {PrintClavCard((Card)_myCard);}

    else if (DIAMOND_SHAPE(_myCard))
    {PrintDiamondCard((Card)_myCard);}
         
    else if (HEART_SHAPE(_myCard))
    {PrintHeartCard((Card)_myCard);}
            
    else if (PEAK_SHAPE(_myCard))
    {PrintPeakCard((Card)_myCard);} 
}


/************ Print Table ***************/
void PrintTable(Player** _playersArr, int* _table)
{
    int j;
    int i;
    char* name;
    
    if (_playersArr == NULL || _table == NULL)
    {
        return;
    }
    
    for (i = 0; i < NUM_OF_PLEYRS; i += 1)
    {
        if (_playersArr[i] == NULL)
        {
            return;
        }
        
        GetPlayerName(_playersArr[i], &name);
        printf("%s   ", name);
    }
    
    putchar('\n');
    putchar('\n');
    
    for (i = 0; i < NUM_OF_PLEYRS; i += 1)
    {
        if(_table[i] == NO_CARD)
        {   
            printf("        ");  
        }
        else
        {
            printf(" ");
            PrintOneCard(_table[i]);
            printf("  ");
        }
    }
    putchar('\n');
    printf("***********************************************************\n"); 
    fflush( stdout );
    sleep(1);
}


/************** Print Choose Card ***************/
void PrintChooseCard (Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, size_t _numOfCards, int* _ans)
{
    int i;    
    *_ans = _numOfCards;
    
    printf("Choose card to play:\n\n");    
    PrintPlayerHand (_clav, _diamond, _heart, _peak);
    
    for (i = 0; i < _numOfCards; i += 1)
    {
        printf(" [%d] " ,i);
    }
    
    putchar('\n');
    putchar('\n');
    fflush( stdout );
    
    for(i = 0; (*_ans >= _numOfCards || *_ans < 0) && i < FORGIVENESS; i++)
    {
        scanf("%d", _ans);
    
        if (*_ans >= _numOfCards || *_ans < 0)
        {
            sleep(1);
            printf("Index does not exist please select again\n");
            fflush( stdout );
        }
    }
    
    printf("***********************************************************\n");
    fflush( stdout );
}


/************** Print Player Hand ***************/
void PrintPlayerHand(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak)
{
    if (_clav != NULL)
    {PrintPlayerShapeCards(_clav);}
    
    if (_diamond != NULL)
    {PrintPlayerShapeCards(_diamond);}

    if (_peak != NULL)
    {PrintPlayerShapeCards(_peak);}
    
    if (_heart != NULL)
    {PrintPlayerShapeCards(_heart);}
             
    putchar('\n');                 
}

/* print shape cards */
void PrintPlayerShapeCards(Vector* _cards)
{
    int i;
    size_t numOfCards;
    int myCard;
    
    VectorItemsNum(_cards, &numOfCards);
    for (i = 0; i < numOfCards; i += 1)
    {
        VectorGet(_cards, i, &myCard);
        
        if (CLAV_SHAPE(myCard))
        {PrintClavCard((Card)myCard);}

        else if (DIAMOND_SHAPE(myCard))
        {PrintDiamondCard((Card)myCard);}
         
        else if (HEART_SHAPE(myCard))
        {PrintHeartCard((Card)myCard);}
            
        else if (PEAK_SHAPE(myCard))
        {PrintPeakCard((Card)myCard);}
    }    
} 

/* Print Clav Card */
void PrintClavCard(Card _myCard)
{
        _myCard = _myCard % NUM_OF_CARDS_AT_SHAPE;
        
        if (JACK == _myCard)
        {printf(" J%s  ",CLUB);}
        
        else if (QUEEN == _myCard)
        {printf(" Q%s  ",CLUB);}
        
        else if (KING == _myCard)
        {printf(" K%s  ",CLUB);}
            
        else if (ACE == _myCard)
        {printf(" A%s  ",CLUB);}
       
        else
        {printf(" %d%s  ",_myCard + 2 ,CLUB);}
}

/* Print Diamond Card */
void PrintDiamondCard(Card _myCard)
{
        _myCard = _myCard % NUM_OF_CARDS_AT_SHAPE;
        
        if (JACK == _myCard)
        {printf(" J%s  ",DIAMOND);}
        
        else if (QUEEN == _myCard)
        {printf(" Q%s  ",DIAMOND);}
        
        else if (KING == _myCard)
        {printf(" K%s  ",DIAMOND);}
            
        else if (ACE == _myCard)
        {printf(" A%s  ",DIAMOND);}
       
        else
        {printf(" %d%s  ",_myCard + 2 ,DIAMOND);}
}

/* Print Heartnd Card */
void PrintHeartCard(Card _myCard)
{
        _myCard = _myCard % NUM_OF_CARDS_AT_SHAPE;
        
        if (JACK == _myCard)
        {printf(" J%s  ",HEART);}
        
        else if (QUEEN == _myCard)
        {printf(" Q%s  ",HEART);}
        
        else if (KING == _myCard)
        {printf(" K%s  ",HEART);}
            
        else if (ACE == _myCard)
        {printf(" A%s  ",HEART);}
       
        else
        {printf(" %d%s  ",_myCard + 2 ,HEART);}
}

/* Print Peak Card */
void PrintPeakCard(Card _myCard)
{
        _myCard = _myCard % NUM_OF_CARDS_AT_SHAPE;
        
        if (JACK == _myCard)
        {printf(" J%s  ",PEAK);}
        
        else if (QUEEN == _myCard)
        {printf(" Q%s  ",PEAK);}
        
        else if (KING == _myCard)
        {printf(" K%s  ",PEAK);}
            
        else if (ACE == _myCard)
        {printf(" A%s  ",PEAK);}
       
        else
        {printf(" %d%s  ",_myCard + 2 ,PEAK);}
}







