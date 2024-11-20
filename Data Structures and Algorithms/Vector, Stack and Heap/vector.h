#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "ADTDErr.h"

typedef struct Vector Vector;

/*  create 
description: creat a vector with initial size (of integers) and block size if need to incres
input: 1. initial size of the vector 
	   2. block size for incres
       (can NOT get zero for both variables)  
output: pointer to vector 
error: return NULL
*/
Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);


/*  destroy  
description: destroy the vector (free the place in memory)   
input: address of vector
output: void
error: 
*/
void VectorDestroy(Vector* _vec);


/* add
description: add an item to the end of the vector. if ther is no place can incres the vector 
input: 1. address of the vector
       2. item to add      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_REALLOCATION_FAILED; ERR_OVERFLOW
*/
ADTErr VectorAdd(Vector* _vec, int _item); 


/* delet
description: delete the lest item from the vector and return it to the user
input: 1. address of vector
       2. address to storge the deleted item       
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_UNDERFLOW
*/
ADTErr VectorDelete(Vector* _vec, int* _item); 


/* get
description: get an item of specific index of the vector (vecrot do not chang)
input: 1. address of vector
       2. address to storge the item
	   3. index of the item      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_WRONG_INDEX	 
*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);


/* set
description: set a value in specific index
input: 1. address of vector
       2. item to set
	   3. index for seting      
output: ERR_OK
error: ERR_NOT_INITIALIZED; ERR_WRONG_INDEX	
*/
ADTErr VectorSet(Vector *_vector, size_t _index, int  _item);


/* items number
description: faind the amount of the items
input: 1. address of vector
       2. address for the answer      
output: ERR_OK
error: ERR_NOT_INITIALIZED;
*/
ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems);


/* print
description: print the items in the vector 
input: address of vector     
output: void
error: 
*/
void VectorPrint(Vector *_vec);

#endif 
