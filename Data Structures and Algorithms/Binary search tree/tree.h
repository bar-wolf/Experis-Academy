#ifndef __TREE_H__
#define __TREE_H__
#include "ADTDErr.h"

typedef struct Tree Tree;
typedef struct Node Node;

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} TreeTraverse;

/*  create 
description: create binary search tree   
input: void  
output: pointer to Tree
error: return NULL      */
Tree* TreeCreate();


/*  destroy 
description: delite the binary search tree   
input: pointer to Tree
output: void
error: void      */
void TreeDestroy(Tree* _tree);


/*  insert 
description: insert data to the binary search tree   
input: 1. pointer to Tree
       2. data
output: ERR_OK
error: ERR_NOT_INITIALIZED, ERR_ALLOCATION_FAILED     */
ADTErr TreeInsert(Tree* _tree, int _data);


/*  found TODO
description: ????    
input: 1. pointer to Tree
       2. data 
output: ????
error: return NULL      */
int TreeIsDataFound(Tree* _tree, int _data);


/*  print
description: print the tree   
input: 1. pointer to tree
       2. style of print 
output: void
error: ERR_NOT_INITIALIZED      */
void    TreePrint(Tree* _tree, TreeTraverse _traverseMode);


#endif 
