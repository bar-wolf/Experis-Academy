#ifndef __HEAP_H__
#define __HEAP_H__
#include <stdlib.h> 
#include "ADTDErr.h"
#include "vector.h"

typedef struct Heap Heap;

Heap* HeapBuild(Vector* _vec); /* O(n) */

void HeapDestroy(Heap* _heap);

ADTErr HeapInsert(Heap* _heap, int _data); /* O(log n) */

ADTErr HeapMax(Heap* _heap, int* _data);

ADTErr HeapExtractMax(Heap* _heap, int* _data); /* O(log n) */

int HeapItemsNum(Heap* _heap);

void HeapPrint(Heap* _heap);


#endif




