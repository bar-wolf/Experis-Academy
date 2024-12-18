#include <stdio.h>
#include <stdlib.h> /* malloc, free ,size_t */
#include "ADTDErr.h"
#include "queue.h"
#define EMPTY 100
#define NOT_EMPTY 101
#define MAGIC 332938 

struct Queue
{
    int*    m_que;
    size_t  m_size;
    size_t  m_head;      /* Index of head in m_que. */
    size_t  m_tail;      /* Index of tail in m_que. */
    size_t  m_nItems;
	int 	m_magic;
};

/*********************** create *******************************/

Queue* QueueCreate(size_t _size)
{
    int* que;
	Queue* queue;
	if (_size == 0)
	{
		return NULL;
	}
	queue = (Queue*) malloc (sizeof(Queue));
	if (queue == NULL)
    {
        return NULL;
    }
	que = (int*) malloc (_size * sizeof (int));
    if (que == NULL)
    {
        free(queue);
        return NULL; 
    }
    queue->m_que = que;
    queue->m_size = _size;
    queue->m_head = 0;
    queue->m_tail = 0;
    queue->m_nItems = 0;
    queue->m_magic = MAGIC;
	return queue;
}

/*********************** destroy *******************************/

void QueueDestroy(Queue* _queue)
{
    if(_queue == NULL || _queue->m_que == NULL)
    {
        return;
    }
    if (_queue->m_magic == MAGIC)  
    {
        free(_queue->m_que);
		_queue->m_que = NULL;
        _queue->m_magic = 0;
        free (_queue);
    }
}

/*********************** insert *******************************/

ADTErr QueueInsert(Queue* _queue, int _item)
{
    if(_queue == NULL || _queue->m_que == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    if ((_queue->m_nItems == _queue->m_size) && (_queue->m_head == _queue->m_tail))
    {
        return ERR_OVERFLOW;  
    }
    *(_queue->m_que + _queue->m_head) = _item;
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    _queue->m_nItems += 1; 
     return ERR_OK;    
}

/*********************** remove *******************************/

ADTErr QueueRemove(Queue* _queue, int* _item)
{
    if (_queue == NULL || _queue->m_que == NULL || _item == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    if ((_queue->m_nItems == 0) && (_queue->m_head == _queue->m_tail))
    {
        return ERR_UNDERFLOW;   
    }
    *_item = *(_queue->m_que + _queue->m_tail);
    _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size; 
    _queue->m_nItems -= 1;
     return ERR_OK;             
}

/*********************** empty? *******************************/

int QueueIsEmpty(Queue *_queue)
{
    if (_queue == NULL || _queue->m_que == NULL)
    {
        return EMPTY;
    }
    if (_queue->m_nItems == 0)
    {
        return EMPTY;
    }
    return NOT_EMPTY;
}

/*********************** print *******************************/

void QueuePrint(Queue *_queue)
{
    size_t = i;
    size_t j = 0;
    if (_queue == NULL || _queue->m_que == NULL)
    {
        return;
    }
    for (i = _queue->m_tail; j < _queue->m_nItems; i = (i + 1) % _queue->m_size)
    {
        printf ("%d ", *(_queue->m_que + i));
        j++;
    } 
    printf("\n"); 
}

/*********************** get functions *******************************/

int* GetQueueAdrress(Queue* _queue)
{
	return _queue->m_que; 
}

size_t GetSize(Queue* _queue)
{
	return _queue->m_size; 
}

size_t GetHead(Queue* _queue)
{
	return _queue->m_head;
}

size_t GetTail(Queue* _queue)
{
	return _queue->m_tail; 
}

size_t GetNumberOfElements(Queue* _queue)
{
	return _queue->m_nItems; 
}

int GetMegicNumber(Queue* _queue)
{
	return _queue->m_magic;
}







