#include <stdio.h>
#include <stdlib.h> /* malloc */
#include "list.h"

/*
struct Person
{
    int     m_id;         /* Primary Key 
    char    m_name[128];
    int     m_age;
    Person* m_next;
}
*/

int main(void)
{
    Person* GetHeadItem;
    Person* Head = (Person*)malloc(sizeof(Person)); 
    Person perArr [] =
    {
        {30, "ravid", 28, NULL}, 
        {20, "bar", 30, NULL},
        {10, "mitzi", 1, NULL},
        {20, "rexi", 13, NULL},
        {4, "twist", 7, NULL},
    }; 
    
    Head = ListInsertHead(NULL, perArr);
    Head = ListInsertHead(Head, perArr + 1);
    Head = ListInsertHead(Head, perArr + 2);
    PrintList(Head);
    printf("\n************************************\n");
    Head = ListRemoveByKeyRec(Head, 30, &GetHeadItem);
    PrintList(Head);
    /* 
    Head = ListInsertByKey(Head, (perArr + 3)->m_id ,perArr + 3);
    PrintList(Head); 
    printf("\n\n head = %p\n\n", (void*)Head); 
    
    Head = ListRemoveByKey(Head, (perArr + 2)->m_id , &GetHeadItem);
    PrintList(Head); 
    printf("\n\n head = %p\n\n", (void*)Head);  
    
    PrintList(GetHeadItem);
    */
    
    return 0;
}

