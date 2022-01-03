#include <stdlib.h> /* malloc, free */
#include <string.h>
#include "ADTDErr.h"
#include "game.h"
#include "player.h"
#include "round.h"

struct Game 
{
    Player**  m_players;  
    int*      m_points;    
    size_t    m_numberOfRound;
    size_t    m_numberOfPlayers;
    int       m_endScore; /* TODO get func continoe or tell how won*/
    int       m_magic;    
};

char namesArr [][7] = {"fistok", "pongo", "siton", "yuvel", "dorofir", "buzi", "evya"}; 

/******** helping to create ****************/
ADTErr CheckInput(size_t _numOfPlayers, size_t _numOfHumanPlayers, int _endScore);
ADTErr CreateThePlayers(Player** _myPlayers, size_t _numOfPlayers, size_t _numOfHumanPlayers);
/******** helping to Destroy ****************/
void DestroyThePlayers(Game* _myGame);


/**************** Creat Game ****************/
Game* GameCreate(size_t _numOfPlayers, size_t _numOfHumanPlayers, int _endScore) 
{
    Game* myGame; 
    Player** myPlayers;
    int* points; 
    
    if (ERR_OK != CheckInput(_numOfPlayers, _numOfHumanPlayers, _endScore))
    {
        return NULL;
    }
    
    myGame = (Game*)malloc(sizeof(Game));
    if (myGame == NULL)
    {
        return NULL;
    }    
    
    myGame->m_magic = MAGIC;
    
    myPlayers = (Player**)malloc(sizeof(Player*) * _numOfPlayers);
    if (myPlayers == NULL)
    {
        free(myGame);
        return NULL;
    }
    
    myGame->m_players = myPlayers;
    if  (ERR_OK != CreateThePlayers(myGame->m_players, _numOfPlayers, _numOfHumanPlayers))
    {
        GameDestroy(myGame);
        return NULL;
    }
    
    points = (int*)calloc(_numOfPlayers, sizeof(int));
    if (points == NULL)
    {
        GameDestroy(myGame);
        return NULL;
    }
     
    myGame->m_points = points;    
    myGame->m_numberOfRound = 0;
    myGame->m_numberOfPlayers = _numOfPlayers;
    myGame->m_endScore = _endScore;    
    
    return myGame;    
}     


/**************** Run Game ****************/
ADTErr GameRun(Game* _myGame)
{
    Round* myRound;
    int i;
    int tempScore;
    int highScore = 0;
    
    if (_myGame == NULL)
    {
        return ERR_NOT_INITIALIZED;       
    }
   
    while (highScore < _myGame->m_endScore)
    {
        myRound = RoundCreat(_myGame->m_players, _myGame->m_points, _myGame->m_numberOfRound, _myGame->m_numberOfPlayers);
           
        if (myRound == NULL)
        {
            return ERR_ALLOCATION_FAILED;
        }       
   
        RoundRun(myRound);
        highScore = 0;
        
        for (i = 0; i < _myGame->m_numberOfPlayers; i += 1)
        {
            tempScore = _myGame->m_points[i];
            if (tempScore > highScore)
            {
                highScore = tempScore; 
            }
        }
        
       _myGame->m_numberOfRound += 1; 
    }
     
    GameDestroy(_myGame); 
    
    return ERR_OK;
}


/**************** Destroy Game ****************/
void GameDestroy(Game* _myGame)
{
    if (_myGame == NULL || _myGame->m_magic != MAGIC)
    {
        return;
    }
    
    _myGame->m_magic = 0;
    
    if (_myGame->m_points != NULL)
    {
        free(_myGame->m_points);
    }
    
    if (_myGame->m_players != NULL)
    {
        DestroyThePlayers(_myGame);
        free(_myGame->m_players);
    }
    
    free(_myGame);
}


/******** helping to Destroy ****************/
/* Destroy The Players */
void DestroyThePlayers(Game* _myGame)
{
    int i;
    for (i = 0; i < _myGame->m_numberOfPlayers; i += 1)
    {
        PlayerDestroy(_myGame->m_players[i]);
    }
}


/******** helping to create ****************/
/* Check Input */
ADTErr CheckInput(size_t _numOfPlayers, size_t _numOfHumanPlayers, int _endScore)
{
    
    if (_numOfPlayers == 0 || _endScore == 0 || _numOfHumanPlayers > _numOfPlayers)
    {
        return ERR_WRONG_INPUT;
    }
       return ERR_OK; 
}

/* Create The Players */
ADTErr CreateThePlayers(Player** _myPlayers, size_t _numOfPlayers, size_t _numOfHumanPlayers)
{
    int i;
    Player* player;
    char name[MAX_CHARS_FOR_NAME];
    
    for (i = 0; i < _numOfHumanPlayers; i += 1)
    {
        PrintAskForName(name);
        player = PlayerCreate(name, i, HUMAN);
        if (player == NULL)
        {
            return ERR_ALLOCATION_FAILED;
        }
        _myPlayers[i] = player; 
    }
    
    for (; i < _numOfPlayers; i += 1)
    {
        player = PlayerCreate(namesArr[i], i, COMPUTER);
        if (player == NULL)
        {
            return ERR_ALLOCATION_FAILED;
        }
        _myPlayers[i] = player;
    }
    
    return ERR_OK;
}


