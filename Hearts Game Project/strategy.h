#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "ADTDErr.h"
#include "vector.h"
#include "cards.h"


typedef ADTErr(*Strategy)(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, int _trickNumber, int _isHeartsPossible, int* _table, Card* _card);

/* TODO description **works only when sort */
ADTErr GetCardStrategy(Vector* _clav, Vector* _diamond, Vector* _heart, Vector* _peak, int _trickNumber, int _isHeartsPossible, int* _table, Card* _card);

#endif
