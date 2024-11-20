#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "ADTDErr.h"
#define EMPTY 100
#define NOT_EMPTY 101

typedef struct Queue Queue;

/*  create 
description: creat a queue of items with initial size. first item to get in is the first to get out.  
input: initial size of the queue (can not get zero)
output: pointer to Queue 
error: return NULL 
*/
Queue* QueueCreate(size_t _size);


/*  destroy  
description: destroy the queue (free the place in memory)   
input: address of Queue
output: void
error: 
*/
void QueueDestroy(Queue *_queue);

/* insert
description: add an item in to the queue. 
input: 1. address of the Queue
       2. item to add      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_OVERFLOW
*/
ADTErr QueueInsert(Queue *_queue, int _item);


/* remove
description: remove the first item from the queue and return it to the user
input: 1. address of Queue
       2. address to storge the remove item      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_UNDERFLOW 
*/
ADTErr QueueRemove(Queue *_queue, int *_item);


/* empty?
description: return if the queue is empty or not 
input: address of Queue       
output: EMPTY / NOT EMPTY
error: if the stack not initialized return EMPTY
*/
int QueueIsEmpty(Queue *_queue);


/* print
description: print the items in the queue 
input: address of Queue     
output: void
error: 
*/
void QueuePrint(Queue *_queue);

#endif 
