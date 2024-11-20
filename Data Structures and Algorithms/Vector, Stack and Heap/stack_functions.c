#include <stdio.h>
#include <stdlib.h>
#include "ADTDErr.h"
#include "vector.h"
#include "stack.h"
#define MAGIC 243547

struct Stack
{
    Vector* m_vector;
	int m_magic;
};

/*************************************************/

Stack* StackCreate(size_t _size, size_t _blockSize)
{
	Stack* stack;
	if (_size == 0 && _blockSize == 0)
	{
		return NULL;
	}
	stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL)
	{
		return NULL;
	}
	stack->m_vector = VectorCreate(_size, _blockSize);	
	if (stack->m_vector == NULL)
	{
		free(stack);
		return NULL;
	}
	stack->m_magic = MAGIC;
	return stack;
}

/*************************************************/

void StackDestroy(Stack* _stack)
{
	if (_stack == NULL || _stack->m_vector == NULL)
	{ 
		return;
	}
	if (_stack->m_magic == MAGIC)
	{
	VectorDestroy(_stack->m_vector);
	_stack->m_vector = NULL;
	_stack->m_magic = 0;
	free(_stack);
	}
}

/*************************************************/

ADTErr StackPush(Stack* _stack, int _item)
{
	if (_stack == NULL || _stack->m_vector == NULL)
	{
		return ERR_NOT_INITIALIZED; 	
	}
	return VectorAdd(_stack->m_vector, _item);
}

/*************************************************/

ADTErr StackPop(Stack* _stack, int* _item)
{
	if (_stack == NULL || _item == NULL || _stack->m_vector == NULL)
	{
		return ERR_NOT_INITIALIZED; 	
	}
	return VectorDelete(_stack->m_vector, _item);
}

/*************************************************/

ADTErr StackTop(Stack* _stack, int* _item)
{	
	int check;
	size_t length; 
	if (_stack == NULL || _item == NULL || _stack->m_vector == NULL)
	{
		return ERR_NOT_INITIALIZED; 	
	}
	check = VectorItemsNum(_stack->m_vector, &length);
	if (check != ERR_OK)
	{
		return ERR_GENERAL; /* not sore it is good */
	}
	if (length == 0)
	{
		return EMPTY; 		
	}
	return VectorGet(_stack->m_vector, length - 1, _item);	
}

/*************************************************/

int StackIsEmpty(Stack* _stack)
{
	int check;
	size_t length;
	if (_stack == NULL || _stack->m_vector == NULL)
	{
		return EMPTY;	
	}
	check = VectorItemsNum(_stack->m_vector, &length);
	if (check != ERR_OK)
	{
		return EMPTY;		
	}
	if (0 == length)
	{
		return EMPTY;
	}
	return NOT_EMPTY;	
}

/*************************************************/

void StackPrint (Stack* _stack)
{
	if (_stack == NULL || _stack->m_vector == NULL)
	{
		return;	
	}
	VectorPrint(_stack->m_vector);		
}

/****************** get func ****************/

int GetMegic(Stack* _stack)
{
	return _stack->m_magic; 
}

void* GetVector(Stack* _stack)
{
	return _stack->m_vector;		
}












