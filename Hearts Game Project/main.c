#include "game.h"
#include "ADTDErr.h"

int main(void)
{
    
    Game* heartsGame = GameCreate(NUM_OF_PLEYRS, 1, END_SCORE);
    
    if (heartsGame == NULL)
    {
        return 1;
    }
    
    GameRun(heartsGame);
    
    GameDestroy(heartsGame);
    
    return 0;
}










