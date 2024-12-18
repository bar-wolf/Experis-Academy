#include <stdio.h>
#include "list.h"

/**************** insert head *******************/

Person* ListInsertHead(Person* _head ,Person* _p)
{
    if(NULL == _p)
    {
        return;
    }
    _p->m_next = _head;  
    return _p;
}

/**************** remove head *******************/

Person* ListRemoveHead(Person* _head, Person** _item)
{
    if(_head == NULL || _item == NULL)
    {
        return _head;
    }
    *(_item) = _head;
    return _head-> m_next;  
}

/**************** insert by key *******************/

Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
    Person* index = _head;
    Person* previousIndex;
    if(_p == NULL)
    {
        return _head;
    }
    while (index != NULL && _key > index-> m_id)
    {
        previousIndex = index;
        index = index->m_next;
    }
    
    if(_key == index-> m_id) /* ther is a same key in the list */ 
    {
        return _head;
    }
    
    if(index == _head) /* key is the smallest */ 
    {
        _p->m_next = _head;  
        return _p;
    }
    else if(index == NULL) /* key is the bigest */ 
    {
        previousIndex-> m_next = _p;
        _p-> m_next = NULL;
        return _head;           
    }
    else 
    {
        previousIndex-> m_next = _p;
        _p->m_next = index;
        return _head;
    }
}

/**************** insert by key recursia *******************/

Person* InsertByKeyRec(Person* _head, int _key, Person* _p) 
{
    if(_head == NULL || _head->m_id > _key)
    {
        _p->m_next = _head;  
        return _p; 
    }
    if(_head->m_id == _key)
    {
        return _head;
    }
   /* if(_head->m_id > _key) this "if" is 8 lins up
    {
        _p->m_next = _head;  
        return _p; 
    } */ 
    else
    {
        _head->m_next = InsertByKeyRec(_head->m_next, _key, _p);
        return _head;    
    }   
}

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
     if(_p == NULL)
     {
        return _head;
     }
     return InsertByKeyRec(_head, _key, _p);      
}

/**************** remove by key *******************/

/* TODO in case thet we do not remove *(_p) = NULL */

Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
    Person* index = _head;
    Person* previousIndex;
    if(_p == NULL || _head == NULL)
    {
        return _head;
    }
    while (index != NULL && _key != index-> m_id)
    {
        previousIndex = index;
        index = index->m_next;
    }
    if(index == _head) /* remonig key is like the first person */ 
    {
        *(_p) = _head;
        _head = _head->m_next;
        return _head;
    }
    else if(index == NULL) /* remonig key do not exist */ 
    {
        return _head;           
    }
    else 
    {
        *(_p) = index;
        previousIndex->m_next = index->m_next; 
        return _head;
    }    
}

/**************** remove by key recursia *******************/

Person* RemoveByKeyRec(Person* _head, int _key, Person** _p)
{
    if(_head == NULL)
    {
        return _head;
    }
    if(_head-> m_id == _key)
    {
        *(_p) == _head; 
        _head = _head-> m_next;
        return _head;
    }
    _head->m_next = RemoveByKeyRec(_head->m_next, _key, _p);
    return _head;  
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p)
{
    if(_p == NULL || _head == NULL)
    {
        return _head;
    }
    return RemoveByKeyRec(_head, _key, _p);          
}

/**************** print list *******************/

void PrintList(Person* _head)
{
    int i = 1;
    if(_head == NULL)
    {
        return;
    }
    for(; _head != NULL; i++) 
    {
        printf("\nperson %d: address: %p\n", i, (void*)_head);
        printf("person id: %d\t", _head-> m_id);
        printf("person name: %s\t", _head-> m_name);
        printf("person age: %d\t", _head-> m_age);
        printf("next person address: %p\t\n", (void*)_head-> m_next);
        _head = _head-> m_next;
    } 
}

/**************** return lest person recursia *******************/

struct List
{
    Node  m_head;
    Node  m_tail;
    int   m_magic;
};
n

struct Node
{
    int    m_data;
    Node*  m_next;
    Node*  m_prev;
};











