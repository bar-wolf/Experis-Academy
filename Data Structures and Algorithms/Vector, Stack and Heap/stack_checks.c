#include <stdio.h>
#include "ADTDErr.h"
#include "vector.h"
#include "stack.h"
#define MAGIC 243547

void CheckCreate1(void);
void CheckCreate2(void);
void CheckCreate3(void);
void CheckCreate4(void);
void CheckCreate5(void);

void CheckDestroy1(void);

void CheckPush1(void);
void CheckPush2(void);
void CheckPush3(void);

void CheckPop1(void);
void CheckPop2(void);
void CheckPop3(void);

void CheckTop1(void);
void CheckTop2(void);
void CheckTop3(void);

void CheckStackIsEmpty1(void);
void CheckStackIsEmpty2(void);
void CheckStackIsEmpty3(void);

void CheckGeneral1(void);
void CheckGeneral2(void);
void CheckGeneral3(void);

int main(void)
{

	CheckCreate1();
	CheckCreate2();
	CheckCreate3();
	CheckCreate4();
	CheckCreate5();

	CheckDestroy1();

	CheckPush1();
	CheckPush2();
	CheckPush3();

	CheckPop1();
	CheckPop2();
	CheckPop3();
	
	CheckTop1();
	CheckTop2();
	CheckTop3();

	CheckStackIsEmpty1();
	CheckStackIsEmpty2();
	CheckStackIsEmpty3();

	CheckGeneral1();
	CheckGeneral2();
	CheckGeneral3();

	return 0;
}

/******* Stack Create *******/

void CheckCreate1(void) /* zero zero input */
{
    if (NULL == StackCreate(0,0)){
        printf ("Check Create 1 pass\n");
    }
    else{
         printf ("Check Create 1 fail\n");    
    }
}

void CheckCreate2(void) /* initial Size zero input */
{
    if (NULL != StackCreate(0,1)){
        printf ("Check Create 2 pass\n");
    }
    else{
         printf ("Check Create 2 fail\n");    
    }
}

void CheckCreate3(void) /* extension blockSize zero input */
{
    if (NULL != StackCreate(1,0)){
        printf ("Check Create 3 pass\n");
    }
    else{
         printf ("Check Create 3 fail\n");    
    }
}

void CheckCreate4(void) /* the megic number correct */
{
	Stack* myStack = StackCreate (5, 13);
    if (MAGIC == GetMegic(myStack)){
        printf ("Check Create 4 pass\n");
    }
    else{
         printf ("Check Create 4 fail\n");    
    }
	StackDestroy(myStack);
}

void CheckCreate5(void) /* malloc fail */
{
    if (NULL == StackCreate (-1,0)){
        printf ("Check Create 5 pass\n");
    }
    else{
         printf ("Check Create 5 fail\n");    
    }
}

/******* Stack Destroy *******/

void CheckDestroy1(void) /* megic & NULL */
{
	Stack* myStack = StackCreate (5, 5);
	StackDestroy(myStack);
    if (MAGIC != GetMegic(myStack)){
        printf ("Check Destroy 1 pass\n");
    }
    else{
        printf ("Check Destroy 1 fail\n");    
    }
}

/******* Stack Push *******/

void CheckPush1(void) /* input NULL */
{
    if (ERR_NOT_INITIALIZED == StackPush(NULL, 5)){
        printf ("Check Push 1 pass\n");
    }
    else{
         printf ("Check Push 1 fail\n");    
    }
}

void CheckPush2(void) /* realloc fail */
{
    Stack* myStac = StackCreate (1 , -1);
    int Check7 = StackPush(myStac, 1);
    Check7 = StackPush(myStac, 1);
    if (ERR_REALLOCATION_FAILED == Check7){
        printf ("Check Push 2 pass\n");
    }
    else{
         printf ("Check Push 2 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckPush3(void) /* over flow  */
{
    Stack* myStac = StackCreate (1, 0);
    int Check4 = StackPush(myStac, 1);
    if (ERR_OVERFLOW == StackPush(myStac, 1)){
        printf ("Check Push 3 pass\n");
    }
    else{
         printf ("Check Push 3 fail\n");    
    }
    StackDestroy(myStac);
}

/******* Stack Pop *******/

void CheckPop1(void) /* &item = NULL */
{
     Stack* myStac = StackCreate (1 , 5);
    if (ERR_NOT_INITIALIZED == StackPop(myStac, NULL)){
        printf ("Check Pop 1 pass\n");
    }
    else
	{
         printf ("Check Pop 1 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckPop2(void) /* UNDER FLOW */
{	
	int* x;
	Stack* myStac = StackCreate (1 , 0);
	if (x != NULL){
    	if (ERR_UNDERFLOW == StackPop(myStac, x))
		{
       	 	printf ("Check Pop 2 pass\n");
   		}
	}
    else
	{
         printf ("Check Pop 2 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckPop3(void) /* &stack = NULL */
{
	int x = 12;
     Stack* myStac = StackCreate (1 , 5);
    if (ERR_NOT_INITIALIZED == StackPop(NULL, &x)){
        printf ("Check Pop 3 pass\n");
    }
    else
	{
         printf ("Check Pop 3 fail\n");    
    }
    StackDestroy(myStac);
}

/******* Stack Top *******/

void CheckTop1(void) /* &stack = NULL */
{
	int x = 12;
     Stack* myStac = StackCreate (1 , 5);
    if (ERR_NOT_INITIALIZED == StackTop(NULL, &x)){
        printf ("Check Top 1 pass\n");
    }
    else
	{
         printf ("Check Top 1 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckTop2(void) /* &item = NULL */
{
     Stack* myStac = StackCreate (1 , 5);
    if (ERR_NOT_INITIALIZED == StackTop(myStac, NULL)){
        printf ("Check Top 2 pass\n");
    }
    else
	{
         printf ("Check Top 2 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckTop3(void) /* empty */
{
	int x = 8;
     Stack* myStac = StackCreate (1 , 5);
    if (EMPTY == StackTop(myStac, &x)){
        printf ("Check Top 3 pass\n");
    }
    else
	{
         printf ("Check Top 3 fail\n");    
    }
    StackDestroy(myStac);
}

/******* Stack Is Empty *******/

void CheckStackIsEmpty1(void) /* empty */
{
     Stack* myStac = StackCreate (1 , 5);
    if (EMPTY == StackIsEmpty(myStac)){
        printf ("Check StackIsEmpty 1 pass\n");
    }
    else
	{
         printf ("Check StackIsEmpty 1 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckStackIsEmpty2(void) /* not empty */
{
     Stack* myStac = StackCreate (1 , 5);
	StackPush(myStac, 1);
    if (NOT_EMPTY == StackIsEmpty(myStac)){
        printf ("Check StackIsEmpty 2 pass\n");
    }
    else
	{
         printf ("Check StackIsEmpty 2 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckStackIsEmpty3(void) /* empty */
{
     Stack* myStac = StackCreate (1 , 5);
    if (EMPTY == StackIsEmpty(NULL)){
        printf ("Check StackIsEmpty 3 pass\n");
    }
    else
	{
         printf ("Check StackIsEmpty 3 fail\n");    
    }
    StackDestroy(myStac);
}

/******* general *******/

void CheckGeneral1(void) /* posh corect and top corect */
{	
	int x = 101;
    Stack* myStac = StackCreate (1 , 5);
	StackPush(myStac, 13);
	StackTop(myStac, &x);
    if (13 == x){
        printf ("Check General 1 pass\n");
    }
    else
	{
         printf ("Check General 1 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckGeneral2(void) /* posh corect and pop corect */
{	
	int x = 101;
    Stack* myStac = StackCreate (1 , 5);
	StackPush(myStac, 13);
	StackPop(myStac, &x);
    if (13 == x){
        printf ("Check General 2 pass\n");
    }
    else
	{
         printf ("Check General 2 fail\n");    
    }
    StackDestroy(myStac);
}

void CheckGeneral3(void) /* pop redoce item */
{
	int x = 17;
     Stack* myStac = StackCreate (1 , 5);
	StackPush(myStac, 1);
	StackPop(myStac, &x);
    if (EMPTY == StackIsEmpty(myStac)){
        printf ("Check General 3 pass\n");
    }
    else
	{
         printf ("Check General 3 fail\n");    
    }
    StackDestroy(myStac);
}







