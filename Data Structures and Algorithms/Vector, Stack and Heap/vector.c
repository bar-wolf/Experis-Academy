#include <stdio.h>
#include <stdlib.h> /*realooc & malloc*/
#include "ADTDErr.h"
#include "vector.h"
#define MAGIC 243547

struct Vector{
    void*    m_items;
    size_t  m_originalSize;   	
    size_t  m_size;           	    
    size_t  m_nItems;     	    
    size_t  m_blockSize;
    int     m_magic_num;
};

/***************************************************************/

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	int* items;
	Vector* ptr;
    if (_initialSize == 0 && _extensionBblockSize == 0)
    {
        return NULL;
    }
    ptr = (Vector*)malloc(sizeof(Vector));
    if (ptr == NULL)
    {
        return NULL;
    }
    
    items = (int*) malloc (_initialSize * sizeof (int));
    if (items == NULL)
    {
        free(ptr);
        return NULL; 
    }
    
    ptr->m_items = items;
    ptr->m_originalSize = _initialSize;
    ptr->m_size = _initialSize;
    ptr->m_nItems = 0;
    ptr->m_blockSize = _extensionBblockSize;
    ptr->m_magic_num = MAGIC;
    return ptr;
}

/***************************************************************/

void VectorDestroy(Vector* _vec)
{
    if (_vec == NULL || _vec->m_items == NULL)
	{
		return;	
	}
    if (_vec->m_magic_num == MAGIC)  
    {
        free(_vec->m_items);
		_vec->m_items = NULL;
        _vec->m_magic_num = 0;
        free (_vec);
    }
}

/***************************************************************/

ADTErr VectorAdd(Vector* _vec, int _item)
{
	int* temp;
    if(_vec == NULL || _vec->m_items == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (_vec->m_nItems >= _vec->m_size)
    {
        if (_vec->m_blockSize <= 0) 
        {
            return ERR_OVERFLOW;
        }
        temp = (int*)realloc(_vec->m_items, (_vec->m_size + _vec->m_blockSize) * sizeof(int));           /* TODO Maybe send Temp to Riallock */
        if(temp == NULL)
        {
            return ERR_REALLOCATION_FAILED;
        }
        _vec->m_size = _vec->m_size + _vec->m_blockSize; 
        _vec->m_items = temp;
    }  
    *(_vec->m_items + _vec->m_nItems) = _item;
    _vec->m_nItems = _vec->m_nItems + 1;
    return ERR_OK;
}

/***************************************************************/

ADTErr VectorDelete(Vector* _vec, int* _item)
{
	int* temp;
	if (_vec == NULL || _vec->m_items == NULL || _item == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
	if (_vec-> m_nItems == 0) 
    {
        return ERR_UNDERFLOW;
    }
	*_item = *(_vec->m_items + _vec->m_nItems - 1);
    _vec->m_nItems -= 1;

	if ((_vec->m_size - _vec->m_nItems >  2 * _vec->m_blockSize) && _vec->m_size > _vec->m_originalSize)
	{
		temp = (int*)realloc(_vec->m_items, (_vec->m_size - _vec->m_blockSize) * sizeof(int));
		if(temp == NULL)
        {
            return;
        }
		_vec->m_size -=  _vec->m_blockSize;
   		_vec->m_items = temp;
	}
	return ERR_OK;
}

/***************************************************************/

ADTErr VectorGet(Vector *_vec, size_t _index, int *_item)
{
	if (_vec == NULL || _vec->m_items == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_index >= _vec->m_nItems)
	{
		return ERR_WRONG_INDEX;	
	}
	*_item = *(_vec->m_items + _index);
	return ERR_OK;
}

/***************************************************************/

ADTErr VectorSet(Vector *_vec, size_t _index, int  _item)
{
	if (_vec == NULL || _vec->m_items == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_index >= _vec->m_nItems)
	{
		return ERR_WRONG_INDEX;	
	}
	*(_vec->m_items + _index) =  _item;
	return ERR_OK;
}

/***************************************************************/

ADTErr VectorItemsNum(Vector *_vec, size_t*  _numOfItems)
{
	if (_vec == NULL || _vec->m_items == NULL || _numOfItems == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	*_numOfItems = _vec->m_nItems;
	return ERR_OK;
}

/***************************************************************/

void VectorPrint(Vector *_vec)
{
	int index;
	if (_vec == NULL || _vec->m_items == NULL)
	{
		return;
	}
		
	for (index = 0; index < _vec->m_nItems; index++)
	{
		printf("%d ", *(_vec->m_items + index));
	}  
	printf("\n");	
}

/****************** get func ****************/

int* GetVectorAdrress(Vector* _vec)
{
	return _vec->m_items; 
}

int GetItemByInedex(Vector* _vec, size_t _index)
{
	return (_vec->m_items)[_index];		
}

size_t GetOriginalSize(Vector* _vec)
{
	return _vec->m_originalSize; 
}

size_t GetSize(Vector* _vec)
{
	return _vec->m_size;
}

size_t GetNumberOfElements(Vector* _vec)
{
	return _vec->m_nItems; 
}

size_t GetBlockSize(Vector* _vec)
{
	return _vec->m_blockSize;
}

int GetMegicNumber(Vector* _vec)
{
	return _vec->m_magic_num;
}





  
