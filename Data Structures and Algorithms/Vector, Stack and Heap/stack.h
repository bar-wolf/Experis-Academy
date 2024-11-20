#ifndef __STACK_H__
#define __STACK_H__
#include "ADTDErr.h"
#define NOT_EMPTY -1
#define EMPTY -2

typedef struct Stack Stack;

/*  create 
description: creat a stack of items with initial size (of integers) and block size if need to incres.   
input: 1. initial size of the stack 
       2. block size to incres
       (can NOT get zero for both variables)  
output: pointer to Stack 
error: return NULL 
*/
Stack* StackCreate(size_t _size, size_t _blockSize);


/*  destroy  
description: destroy the stack (free the place in memory)   
input: address of stack
output: void
error: 
*/
void StackDestroy(Stack* _stack);


/* push
description: add an item in to the stack. if ther is no place can incres the stack  
input: 1. address of the stack
       2. item to add      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_REALLOCATION_FAILED; ERR_OVERFLOW
*/
ADTErr StackPush(Stack* _stack, int  _item);


/* pop
description: delete the lest item from the stack and return it to the user
input: 1. address of stack
       2. address to storge the deleted item      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_UNDERFLOW 
*/
ADTErr StackPop(Stack* _stack, int* _item);


/* top
description: get the lest item from the stack without delete it 
input: 1. address of stack
       2. address to storge the item      
output: ERR_OK
error: EMPTY; ERR_NOT_INITIALIZEF; ERR_GENERAL 
*/
ADTErr StackTop(Stack* _stack, int* _item);


/* empty?
description: return if the stuck is empty or not 
input: address of stack       
output: EMPTY / NOT EMPTY
error: if the stack not initialized return EMPTY
*/
int StackIsEmpty(Stack* _stack);

/* print
description: print the items in the stack 
input: address of stack     
output: void
error: 
*/
void StackPrint (Stack *_stack);

#endif 


