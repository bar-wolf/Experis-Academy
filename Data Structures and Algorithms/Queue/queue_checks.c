#include <stdio.h>
#include "queue.h"
#include "ADTDErr.h"
#define MAGIC 332938 

void PrintTheStruct(Queue* _queue);

void CheckCreate1(void);
void CheckCreate2(void);
void CheckCreate3(void);
void CheckCreate4(void);
void CheckCreate5(void);
void CheckCreate6(void);
void CheckCreate7(void);

void CheckDestroy1(void);

void CheckInsert1(void);
void CheckInsert2(void);
void CheckInsert3(void);
void CheckInsert4(void);

void CheckRemove1(void);
void CheckRemove2(void);
void CheckRemove3(void);
void CheckRemove4(void);
void CheckRemove5(void);
void CheckRemove6(void);
void CheckRemove7(void);

void CheckQueueIsEmpty1(void);
void CheckQueueIsEmpty2(void);
void CheckQueueIsEmpty3(void);

void CheckGeneral1(void);

int main (void)
{   
int x = 100;
    Queue* myQueue = QueueCreate(3);
    QueueInsert(myQueue,12);
    QueueInsert(myQueue,3);
    QueueInsert(myQueue,17);
    QueueInsert(myQueue,15);
    QueueInsert(myQueue,3);
    QueueInsert(myQueue,18);
    QueueRemove(myQueue, &x);
    QueueInsert(myQueue,12345);
    QueuePrint(myQueue);
    printf("x= %d\n",x);
    PrintTheStruct(myQueue);
    
    /*
    CheckCreate1();
	CheckCreate2(); 
	CheckCreate3();
	CheckCreate4();
	CheckCreate5(); 
	CheckCreate6();
    CheckCreate7();
    
    CheckDestroy1();

    CheckInsert1();
    CheckInsert2();
    CheckInsert3();    
    CheckInsert4();
    
    CheckRemove1();
    CheckRemove2();
    CheckRemove3();
    CheckRemove4();
    CheckRemove5();
    CheckRemove6();
    CheckRemove7();
    
    CheckQueueIsEmpty1();
    CheckQueueIsEmpty2();
    CheckQueueIsEmpty3();
    
    CheckGeneral1();*/

	return 0;
}

void PrintTheStruct(Queue* _queue)
{
    printf("\nQueue adrress: %p\n", (void*)GetQueueAdrress(_queue));
    printf("queue size: %d\n", GetSize(_queue));
    printf("head index: %d\n",GetHead(_queue));
    printf("tail index: %d\n", GetTail(_queue));
    printf("number of elemnts: %d\n", GetNumberOfElements(_queue));
    printf("megic number: %d\n\n",GetMegicNumber(_queue));
}

/**************** creat checks ***********/

void CheckCreate1(void) /* zero input */
{
    if (NULL == QueueCreate(0)){
        printf ("Check Create 1 pass\n");
    }
    else{
         printf ("Check Create 1 fail\n");    
    }
}

void CheckCreate2(void) /* the Size correct */
{
	Queue* myQueue = QueueCreate(5);
    if (5 == GetSize(myQueue)){
        printf ("Check Create 2 pass\n");
    }
    else{
         printf ("Check Create 2 fail\n");    
    }
	QueueDestroy(myQueue);
}

void CheckCreate3(void) /* the head correct */
{
	Queue* myQueue = QueueCreate (5);
    if (0 == GetHead(myQueue)){
        printf ("Check Create 3 pass\n");
    }
    else{
         printf ("Check Create 3 fail\n");    
    }
	QueueDestroy(myQueue);
}

void CheckCreate4(void) /* the tail correct */
{
	Queue* myQueue = QueueCreate (5);
    if (0 == GetTail(myQueue)){
        printf ("Check Create 4 pass\n");
    }
    else{
         printf ("Check Create 4 fail\n");    
    }
	QueueDestroy(myQueue);
}

void CheckCreate5(void) /* the number of elements correct */
{
	Queue* myQueue = QueueCreate (5);
    if (0 == GetNumberOfElements(myQueue)){
        printf ("Check Create 5 pass\n");
    }
    else{
         printf ("Check Create 5 fail\n");    
    }
	QueueDestroy(myQueue);
}

void CheckCreate6(void) /* the megic number correct */
{
	Queue* myQueue = QueueCreate (5);
    if (MAGIC == GetMegicNumber(myQueue)){
        printf ("Check Create 6 pass\n");
    }
    else{
         printf ("Check Create 6 fail\n");    
    }
	QueueDestroy(myQueue);
}

void CheckCreate7(void) /* malloc fail */
{
    if (NULL ==  QueueCreate (-1)){
        printf ("Check Create 7 pass\n");
    }
    else{
         printf ("Check Create 7 fail\n");    
    }
}

/**************** destroy checks ***********/

void CheckDestroy1(void) /* megic & NULL */
{
	Queue* myQueue = QueueCreate (5);
	QueueDestroy(myQueue);
    if (MAGIC != GetMegicNumber(myQueue)){
        printf ("Check Destroy 1 pass\n");
    }
    else{
         printf ("Check Destroy 1 fail\n");    
    }
}

/**************** insert checks  ***********/

void CheckInsert1(void) /* input NULL */
{
    if (ERR_NOT_INITIALIZED == QueueInsert(NULL, 5)){
        printf ("Check Insert 1 pass\n");
    }
    else{
         printf ("Check Insert 1 fail\n");    
    }
}

void CheckInsert2(void) /* over flow  */
{
    Queue* myQueue = QueueCreate (1);
    QueueInsert(myQueue, 1);
    if (ERR_OVERFLOW == QueueInsert(myQueue, 1)){
        printf ("Check Insert 2 pass\n");
    }
    else{
         printf ("Check Insert 2 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckInsert3(void) /* incres number of elements  */
{
    Queue* myQueue = QueueCreate (3);
    int Check7 = QueueInsert(myQueue, 1);
    Check7 = QueueInsert(myQueue, 1);
    if (Check7 == ERR_OK && GetNumberOfElements(myQueue) == 2){
        printf ("Check Insert 3 pass\n");
    }
    else{
         printf ("Check Insert 3 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckInsert4(void) /* incres head  */
{
    Queue* myQueue = QueueCreate (5);
    int Check7 = QueueInsert(myQueue, 1);
    Check7 = QueueInsert(myQueue, 1);
    if (Check7 == ERR_OK && GetHead(myQueue) == 2){
        printf ("Check Insert 4 pass\n");
    }
    else{
         printf ("Check Insert 4 fail\n");    
    }
    QueueDestroy(myQueue);
}

/**************** remove checks  ***********/

void CheckRemove1(void) /* &item = NULL */
{
    Queue* myQueue = QueueCreate (1);
    if (ERR_NOT_INITIALIZED == QueueRemove(myQueue, NULL)){
        printf ("Check remove 1 pass\n");
    }
    else
	{
         printf ("Check remove 1 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckRemove2(void) /* &Queue = NULL */
{	
	int* x;
	Queue* myQueue = QueueCreate (1);
	if (x != NULL)
	{
   		if (ERR_NOT_INITIALIZED == QueueRemove(NULL, x))
		{
        	printf ("Check remove 2 pass\n");
    	}	
	}
	else
	{
        printf ("Check remove 2 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckRemove3(void) /* UNDER FLOW */
{	
	int* x;
	Queue* myQueue = QueueCreate (1);
	if (x != NULL){
    	if (ERR_UNDERFLOW == QueueRemove(myQueue, x))
		{
       	 	printf ("Check remove 3 pass\n");
   		}
	}
    else
	{
         printf ("Check remove 3 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckRemove4(void) /* get the remove number */
{
	int x = 5;
	int check;	
	Queue* myQueue = QueueCreate (6);
	QueueInsert(myQueue, 13);
	check = QueueRemove(myQueue, &x);
    if (ERR_OK == check && 13 == x)
	{
        printf ("Check remove 4 pass\n");
   	}
    else
	{
         printf ("Check remove 4 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckRemove5(void) /* reduce number of elements */
{
	int x = 5;
	int check;	
	Queue* myQueue = QueueCreate (5);
	QueueInsert(myQueue, 13);
	QueueInsert(myQueue, 13);
	check = QueueRemove(myQueue, &x);
    if (ERR_OK == check && GetNumberOfElements(myQueue) == 1)
	{
        printf ("Check remove 5 pass\n");
   	}
    else
	{
        printf ("Check remove 5 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckRemove6(void) /* incres tail  */
{
    int x = 10;
    Queue* myQueue = QueueCreate (5);
    int Check7 = QueueInsert(myQueue, 1);
    Check7 = QueueInsert(myQueue, 1);
    QueueRemove(myQueue, &x);
    if (Check7 == ERR_OK && GetTail(myQueue) == 1){
        printf ("Check remove 6 pass\n");
    }
    else{
         printf ("Check remove 6 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckRemove7(void) /* remove good  */
{
    int x = 10;
    int Check7;
    Queue* myQueue = QueueCreate (5);
    QueueInsert(myQueue, 17);
    QueueInsert(myQueue, 1);
    QueueRemove(myQueue, &x);
    if (Check7 == ERR_OK && x == 17){
        printf ("Check remove 7 pass\n");
    }
    else{
         printf ("Check remove 7 fail\n");    
    }
    QueueDestroy(myQueue);
}

/**************** empty checks  ***********/

void CheckQueueIsEmpty1(void) /* empty */
{
     Queue* myQueue = QueueCreate (1);
    if (EMPTY == QueueIsEmpty(myQueue)){
        printf ("Check QueueIsEmpty 1 pass\n");
    }
    else
	{
         printf ("Check QueueIsEmpty 1 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckQueueIsEmpty2(void) /* not empty */
{
    Queue* myQueue = QueueCreate (5);
	QueueInsert(myQueue, 1);
    if (NOT_EMPTY == QueueIsEmpty(myQueue)){
        printf ("Check QueueIsEmpty 2 pass\n");
    }
    else
	{
         printf ("Check QueueIsEmpty 2 fail\n");    
    }
    QueueDestroy(myQueue);
}

void CheckQueueIsEmpty3(void) /* empty NULL input */
{
     Queue* myQueue = QueueCreate (5);
    if (EMPTY == QueueIsEmpty(NULL)){
        printf ("Check QueueIsEmpty 3 pass\n");
    }
    else
	{
         printf ("Check QueueIsEmpty 3 fail\n");    
    }
    QueueDestroy(myQueue);
}

/**************** genral checks  ***********/

void CheckGeneral1(void) /* insert corect and remove corect */
{	
	int x = 101;
    Queue* myQueue = QueueCreate (4);
	QueueInsert(myQueue, 13);
	QueueRemove(myQueue, &x);
    if (13 == x){
        printf ("Check General 1 pass\n");
    }
    else
	{
         printf ("Check General 1 fail\n");    
    }
    QueueDestroy(myQueue);
}


