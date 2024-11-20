#include <stdio.h>
#include <stdlib.h> /* malloc free */
#include "DLlist.h"
#include "ADTDErr.h"

int main(void)
{
    List* myList = ListCreate();
    
    ListPushTail(myList, 9);
    
    ListPushHead(myList, 77);
    ListPushTail(myList, 9);
   
    ListPrint(myList);
    
    return 0;
}


























