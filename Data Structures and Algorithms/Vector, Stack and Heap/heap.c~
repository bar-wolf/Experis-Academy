#include <stdlib.h> 
#include <stdio.h>
#include "ADTDErr.h"
#include "heap.h"
#include "vector.h"

struct Heap
{
    Vector* m_vec;
    size_t  m_heapSize;
};

/********************* helping functions *************************/
void Heapify (Heap* _heap, size_t _index);
void CheckAndReplaceOneSon(Heap* _heap, size_t _index, size_t _son1_index);
size_t CheckAndReplaceTwoSons(Heap* _heap, size_t _index, size_t _s1, size_t _s2);
int GetDataFromVector(Heap* _heap, size_t _index);
int SetDataInVector(Heap* _heap, size_t _index, int _num);
Heap* HeapAllocation(Vector* _vec);

/********************* build *************************/

Heap* HeapBuild(Vector* _vec)
{
    Heap* heap;
    size_t youngstSan;
    size_t numOfItem;
    int i;
   
    if (_vec == NULL)
    {
        return NULL;
    }       
    
    heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL)
    {
        return NULL;
    }
    VectorItemsNum(_vec, &numOfItem);
    heap->m_heapSize = numOfItem;
    heap->m_vec = _vec;
    
    youngstSan = (numOfItem - 2) / 2;
    
    for (i = youngstSan; 0 <= i; i--)
    {
        Heapify(heap, i);    
    }
    
    return heap;
} 

/********************* destroy *************************/

void HeapDestroy(Heap* _heap)
{
    if (_heap != NULL)
    {
        free(_heap);
    }        
}

/********************* insert *************************/

ADTErr HeapInsert(Heap* _heap, int _data)
{
    if (_heap == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
}

/********************* max *************************/

ADTErr HeapMax(Heap* _heap, int* _data)
{
    if (_heap == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    *_data = GetDataFromVector(_heap, 0);
    return ERR_OK;
}

/********************* max remove *************************/

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
    int num;
    if (_heap == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    num = GetDataFromVector( _heap, (_heap->m_heapSize - 1) );
    SetDataInVector(_heap, 0, num);
    Heapify(_heap, 0);
    _heap->m_heapSize -= 1;
    return ERR_OK;
}

/********************* name of items *************************/

int HeapItemsNum(Heap* _heap)
{
    if (_heap == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    return _heap->m_heapSize;
}

/********************* print *************************/

void HeapPrint(Heap* _heap)
{
    if (_heap == NULL)
    {
        return;
    }
    VectorPrint(_heap->m_vec);
}

/******************* Heapify **************************/

void Heapify(Heap* _heap, size_t _index)
{
    size_t son1;
    size_t son2;
    size_t temp = _index; 
    
    if (_heap == NULL)
    {
        return;
    }    
    
    if (_heap->m_heapSize <= _index)
    {
        return; 
    }
    
    do
    {
        son1 = _index * 2 + 1;
        son2 = _index * 2 + 2;
        temp = _index;  
        
        if (son1 >= _heap->m_heapSize)    /* 1. no sons */
        {
            return;    
        }
        else if (son2 >= _heap->m_heapSize && son1 < _heap->m_heapSize)  /* 2. one son */
        {
            CheckAndReplaceOneSon(_heap, _index, son1);
            return;
        }  
        else if (son2 < _heap->m_heapSize) /* 3. two sons */
        {
            _index = CheckAndReplaceTwoSons(_heap, _index, son1, son2);
        }
    }while (_index != temp);
    
    return;
}

/********************************************************/

size_t CheckAndReplaceTwoSons(Heap* _heap, size_t _index, size_t _s1, size_t _s2)
{
    int san1 = GetDataFromVector(_heap, _s1);
    int san2 = GetDataFromVector(_heap, _s2);
    int index = GetDataFromVector(_heap, _index);
    
    if (san1 >= san2)   
    {
        if (san1 > index)  /* san 1 the bigst */
        {
            SetDataInVector(_heap, _index, san1);
            SetDataInVector(_heap, _s1, index);
            return _s1;                
        }
        else
        {
            return _index;  /* index the bigst */
        }
    }
    else
    {
        if (san2 > index)  /* san 2 the bigst */ 
        {
            SetDataInVector(_heap, _index, san2);
            SetDataInVector(_heap, _s2, index);
            return _s2;                        
        }
        else 
        {
            return _index;  /* index the bigst */
        }
    }
}

/********************************************************/

void CheckAndReplaceOneSon(Heap* _heap, size_t _index, size_t _s1)
{
        int son1 = GetDataFromVector(_heap, _s1);
        int index = GetDataFromVector(_heap, _index);
        if (son1 > index)
        {
            SetDataInVector(_heap, _index, son1);
            SetDataInVector(_heap, _s1, index); 
            return;      
        } 
}

/********************************************************/

int GetDataFromVector(Heap* _heap, size_t _index)
{
    int num;
    VectorGet(_heap->m_vec, _index, &num);
    return num;
}

/********************************************************/

int SetDataInVector(Heap* _heap, size_t _index, int _num)
{
    return VectorSet(_heap->m_vec, _index, _num); 
}

/********************************************************/

/************** swap
Swap(Vector* _vec, size_t _i, size_t _j)
{
    int temp;
    temp  = *(_vec->m_items + _i); 
    *(_vec->m_items + _i) = *(_vec->m_items + _j);
    *(_vec->m_items + _j) = temp;      
}
*********************/


/*Heap* HeapAllocation(Vector* _vec)
{
    size_t numOfItem;
    Heap* heap;
    heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL)
    {
        return NULL;
    }
    
    VectorItemsNum(_vec, &numOfItem);
    heap->m_heapSize = numOfItem;
    return heap;
}*/


