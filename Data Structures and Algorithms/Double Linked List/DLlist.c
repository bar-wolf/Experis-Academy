#include <stdio.h>  
#include <stdlib.h> /* malloc free */
#include "DLlist.h"
#include "ADTDErr.h"
#define MAGIC 563843

struct Node
{
    int    m_data;
    Node*  m_next;
    Node*  m_prev;
};

struct List
{
    Node  m_head;
    Node  m_tail;
    int   m_magic;
};

/********************** helping function **********************/
void NodesDestroy(Node _node);

/********************** list create ****************************/

List* ListCreate(void)
{
    List* MyList;
    Node head;
    Node tail;
    int x = 5;
    
    MyList = (List*)malloc(sizeof(List));
    if (NULL == MyList)
    {
        return NULL;      
    }
    
    head.m_data = 1000;
    head.m_next = &tail;
    head.m_prev = NULL;
     
    tail.m_data = 1111;
    tail.m_next = NULL;
    tail.m_prev = &head;
 
    MyList-> m_head = head;    
    MyList-> m_tail = tail;
    MyList-> m_magic = MAGIC;
  
    return MyList;
}

/********************** list destroy ****************************/

void ListDestroy(List* _list)
{
    if (NULL != _list && MAGIC == _list->m_magic)
    {
        NodesDestroy(_list->m_head);       
    }
    else
    {
    return;
    }
            
    _list->m_magic = 0;
    free(_list);    
}

void NodesDestroy(Node _node)
{
    Node* nodePtr;
    if( (*(_node.m_next)).m_next == NULL)
    {
        return;
    }
    NodesDestroy(*(_node.m_next));
    nodePtr = &_node;
    free(nodePtr);
}

/******************** list push to head ***********************/

ADTErr ListPushHead(List* _list, int _data)
{
    Node* nodeToPush;
    if (NULL == _list)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    nodeToPush = (Node*)malloc(sizeof(Node));
    if (NULL == nodeToPush)
    {
        return ERR_ALLOCATION_FAILED; 
    }
    
    nodeToPush->m_data = _data;
    
    nodeToPush->m_prev = _list-> m_head.m_next->m_prev;
    nodeToPush->m_next = _list-> m_head.m_next;
    
    _list-> m_head.m_next->m_prev = nodeToPush;
    _list-> m_head.m_next = nodeToPush; 
    
    return ERR_OK; 
}

/******************** list push to tail ***********************/

ADTErr ListPushTail(List* _list, int _data)
{
	Node* node = malloc(sizeof(Node));

	if(node == NULL || _list == NULL)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	node->m_data = _data;
	node->m_prev = _list->m_tail.m_prev;
	node->m_next = &_list->m_tail;
	
	_list->m_tail.m_prev->m_next = node;
	_list->m_tail.m_prev = node;

	return ERR_OK;
}

ADTErr ListPopHead(List* _list, int* _data);

ADTErr ListPopTail(List* _list, int* _data);

size_t ListCountItems(List* _list);

int ListIsEmpty(List* _list);

/******************** list print ***********************/
 
void ListPrint(List* _list)
{
    Node* runNode;
      
    if(NULL == _list)
    {
        return;
    }

    runNode = _list->m_head.m_next;
    while( runNode->m_data != 1111 )
    {
    printf ("%d ", runNode->m_data);
    runNode = runNode->m_next;
    }
    printf("\n");   
} 

/* void ListPrint(List* _list) */

/* while( (*(runNode->m_next)).m_next  != NULL ) */ 

/*void NodesFrint(Node _node);

void ListPrint(List* _list)
{
    if (NULL == _list)
    {
        return;
    }
    if ((*((_list->m_head).m_next)).m_next == NULL)
    {
        return;
    }
    NodesFrint( *((_list->m_head).m_next) );
}

void NodesFrint(Node _node)
{
    Node* nodePtr;
    if( (*(_node.m_next)).m_next == NULL)
    {
        return;
    }
    printf("%d ", _node.m_data);
    NodesFrint(*(_node.m_next));  
}*/









































