/* gcc -g -ansi -pedantic vector_checks.c vector_functions.c -o vector_checks.out */
#include <stdio.h>
#include "vector.h"
#include "ADTDErr.h"
#define MAGIC 243547

/****************** get func ****************/
Vector* GetVectorAdrress(Vector* _vec);
int GetItemByInedex(Vector* _vec, size_t _index);
size_t GetOriginalSize(Vector* _vec);
size_t GetSize(Vector* _vec);
size_t GetNumberOfElements(Vector* _vec);
size_t GetBlockSize(Vector* _vec);
int GetMegicNumber(Vector* _vec);

/****************** check func ****************/
void PrintTheStruct(Vector* _vec);

void CheckCreate1(void);
void CheckCreate2(void);
void CheckCreate3(void);
void CheckCreate4(void);
void CheckCreate5(void);
void CheckCreate6(void);
void CheckCreate7(void);
void CheckCreate8(void);
void CheckCreate9(void);

void CheckDestroy1(void);

void CheckAdd1(void);
void CheckAdd2(void);
void CheckAdd3(void);
void CheckAdd4(void);
void CheckAdd5(void);
void CheckAdd6(void);

void CheckDelet1(void);
void CheckDelet2(void);
void CheckDelet3(void);
void CheckDelet4(void);
void CheckDelet5(void);
void CheckDelet6(void);

void CheckGet1(void);
void CheckGet2(void);
void CheckGet3(void);
void CheckGet4(void);

void CheckSet1(void);
void CheckSet2(void);
void CheckSet3(void);

void CheckNumOfItems1(void);
void CheckNumOfItems2(void);
void CheckNumOfItems3(void);

/*************** main for check *************/
int main (void)
{
	/*		
	Vector* myVec = VectorCreate (1,3);
	PrintTheStruct(myVec);
	*/

    CheckCreate1();
	CheckCreate2(); 
	CheckCreate3();
	CheckCreate4();
	CheckCreate5(); 
	CheckCreate6();
	CheckCreate7();
	CheckCreate8();
    CheckCreate9();

	CheckDestroy1();

	CheckAdd1();
	CheckAdd2();
	CheckAdd3();
	CheckAdd4();
	CheckAdd5();
	CheckAdd6();

	CheckDelet1();
	CheckDelet2();
	CheckDelet3();
	CheckDelet4();
	CheckDelet5();
	CheckDelet6();

	CheckGet1();
	CheckGet2();
	CheckGet3();
	CheckGet4();

	CheckSet1();
	CheckSet2();
	CheckSet3();

	CheckNumOfItems1();
	CheckNumOfItems2();
	CheckNumOfItems3();

    return 0;
}

void PrintTheStruct(Vector* _vec)
{
    printf("\nvector adrress: %p\n", (void*)GetVectorAdrress(_vec));
    printf("original size: %ld\n", GetOriginalSize(_vec));
    printf("vectur size: %ld\n", GetSize(_vec));
    printf("number of items: %ld\n",GetNumberOfElements(_vec));
    printf("bloc size: %ld\n", GetBlockSize(_vec));
    printf("megic number: %d\n\n",GetMegicNumber(_vec));
}


/**************** creat checks ***********/

void CheckCreate1(void) /* zero zero input */
{
    if (NULL == VectorCreate(0,0)){
        printf ("Check Create 1 pass\n");
    }
    else{
         printf ("Check Create 1 fail\n");    
    }
}

void CheckCreate2(void) /* initial Size zero input */
{
    if (NULL != VectorCreate(0,5)){
        printf ("Check Create 2 pass\n");
    }
    else{
         printf ("CheckCreate 2 fail\n");    
    }
}

void CheckCreate3(void) /* extension blockSize zero input */
{
    if (NULL != VectorCreate(5,0)){
        printf ("Check Create 3 pass\n");
    }
    else{
         printf ("Check Create 3 fail\n");    
    }
}

void CheckCreate4(void) /* the block size correct */
{
	Vector* myVec = VectorCreate (1, 12);
    if (12 == GetBlockSize(myVec)){
        printf ("Check Create 4 pass\n");
    }
    else{
         printf ("Check Create 4 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckCreate5(void) /* the Original Size correct */
{
	Vector* myVec = VectorCreate (7, 12);
    if (7 == GetOriginalSize(myVec)){
        printf ("Check Create 5 pass\n");
    }
    else{
         printf ("Check Create 5 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckCreate6(void) /* the Size correct */
{
	Vector* myVec = VectorCreate (5, 12);
    if (5 == GetSize(myVec)){
        printf ("Check Create 6 pass\n");
    }
    else{
         printf ("Check Create 6 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckCreate7(void) /* the number of elements correct */
{
	Vector* myVec = VectorCreate (5, 12);
    if (0 == GetNumberOfElements(myVec)){
        printf ("Check Create 7 pass\n");
    }
    else{
         printf ("Check Create 7 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckCreate8(void) /* the megic number correct */
{
	Vector* myVec = VectorCreate (5, 13);
    if (MAGIC == GetMegicNumber(myVec)){
        printf ("Check Create 8 pass\n");
    }
    else{
         printf ("Check Create 8 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckCreate9(void) /* malloc fail */
{
    if (NULL == VectorCreate (-1,0)){
        printf ("Check Create 9 pass\n");
    }
    else{
         printf ("Check Create 9 fail\n");    
    }
}

/**************** Destroy checks ***********/

void CheckDestroy1(void) /* megic & NULL */
{
	Vector* myVec = VectorCreate (5, 5);
	VectorDestroy(myVec);
    if (MAGIC != GetMegicNumber(myVec)){
        printf ("Check Destroy 1 pass\n");
    }
    else{
         printf ("Check Destroy 1 fail\n");    
    }
}

/**************** add checks  ***********/

void CheckAdd1(void) /* input NULL */
{
    if (ERR_NOT_INITIALIZED == VectorAdd(NULL, 5)){
        printf ("Check add 1 pass\n");
    }
    else{
         printf ("Check add 1 fail\n");    
    }
}

void CheckAdd2(void) /* over flow  */
{
    Vector* myVec = VectorCreate (1, 0);
    int Check4 = VectorAdd(myVec, 1);
    if (ERR_OVERFLOW == VectorAdd(myVec, 1)){
        printf ("Check add 2 pass\n");
    }
    else{
         printf ("Check add 2 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckAdd3(void) /* realloc fail */
{
    Vector* myVec = VectorCreate (1 , -1);
    int Check7 = VectorAdd(myVec, 1);
    Check7 = VectorAdd(myVec, 1);
    if (ERR_REALLOCATION_FAILED == Check7){
        printf ("Check add 3 pass\n");
    }
    else{
         printf ("Check add 3 fail\n");    
    }
    VectorDestroy(myVec);
}
void CheckAdd4(void) /* incres size  */
{
    Vector* myVec = VectorCreate (1 , 7);
    int Check6 = VectorAdd(myVec, 1);
    Check6 = VectorAdd(myVec, 1);
    if (Check6 == ERR_OK && GetSize(myVec) == 8){
        printf ("Check add 4 pass\n");
    }
    else{
         printf ("Check add 4 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckAdd5(void) /* incres number of elements  */
{
    Vector* myVec = VectorCreate (1 , 5);
    int Check7 = VectorAdd(myVec, 1);
    Check7 = VectorAdd(myVec, 1);
    if (Check7 == ERR_OK && GetNumberOfElements(myVec) == 2){
        printf ("Check add 5 pass\n");
    }
    else{
         printf ("Check add 5 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckAdd6(void) /* add the item  */
{
    Vector* myVec = VectorCreate (1 , 5);
    int Check8 = VectorAdd(myVec, 1);
    Check8 = VectorAdd(myVec, 123);
    if (Check8 == ERR_OK && GetItemByInedex(myVec, 1) == 123){
        printf ("Check add 6 pass\n");
    }
    else{
         printf ("Check add 6 fail\n");    
    }
    VectorDestroy(myVec);
}

/**************** delete  ***********/

void CheckDelet1(void) /* &item = NULL */
{
    Vector* myVec = VectorCreate (1 , 5);
    if (ERR_NOT_INITIALIZED == VectorDelete(myVec, NULL)){
        printf ("Check Delet 1 pass\n");
    }
    else
	{
         printf ("Check Delet 1 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckDelet2(void) /* &vector = NULL */
{	
	int* x;
	Vector* myVec = VectorCreate (1 , 5);
	if (x != NULL)
	{
   		if (ERR_NOT_INITIALIZED == VectorDelete(NULL, x))
		{
        	printf ("Check Delet 2 pass\n");
    	}	
	}
	else
	{
        printf ("Check Delet 2 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckDelet3(void) /* UNDER FLOW */
{	
	int* x;
	Vector* myVec = VectorCreate (1 , 0);
	if (x != NULL){
    	if (ERR_UNDERFLOW == VectorDelete(myVec, x))
		{
       	 	printf ("Check Delet 3 pass\n");
   		}
	}
    else
	{
         printf ("Check Delet 3 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckDelet4(void) /* get the deleted number */
{
	int x = 5;
	int check;	
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 13);
	check = VectorDelete(myVec, &x);
    if (ERR_OK == check && 13 == x)
	{
        printf ("Check Delet 4 pass\n");
   	}
    else
	{
         printf ("Check Delet 4 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckDelet5(void) /* reduce number of elements */
{
	int x = 5;
	int check;	
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 13);
	check = VectorDelete(myVec, &x);
    if (ERR_OK == check && GetNumberOfElements(myVec) == 0)
	{
        printf ("Check Delet 5 pass\n");
   	}
    else
	{
         printf ("Check Delet 5 fail\n");    
    }
    VectorDestroy(myVec);
}

void CheckDelet6(void) /* realloc reduce size  */
{
	int x = 5;
	int check;	
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 1);
	VectorAdd(myVec, 2);
	VectorAdd(myVec, 3);
	VectorDelete(myVec, &x);
	VectorDelete(myVec, &x);
	check = VectorDelete(myVec, &x);
    if (ERR_OK == check && GetSize(myVec) == 2)
	{
        printf ("Check Delet 6 pass\n");
   	}
    else
	{
         printf ("Check Delet 6 fail\n");    
    }
    VectorDestroy(myVec);
}


/**************** get  ***********/

void CheckGet1(void) /* input pointer to vector NULL */
{
	int x = 1;
    if (ERR_NOT_INITIALIZED == VectorGet(NULL, 2, &x)){
        printf ("Check get 1 pass\n");
    }
    else{
         printf ("Check get 1 fail\n");    
    }
}

void CheckGet2(void) /* input pointer to item NULL */
{
	Vector* myVec = VectorCreate (1,1);
    if (ERR_NOT_INITIALIZED == VectorGet(myVec, 5, NULL)){
        printf ("Check get 2 pass\n");
    }
    else{
         printf ("Check get 2 fail\n");    
    }
	VectorDestroy(myVec);
}


void CheckGet3(void) /* wrong index */
{
	int x = 1;
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 11);
    if (ERR_WRONG_INDEX == VectorGet(myVec, 1, &x)){
        printf ("Check get 3 pass\n");
    }
    else{
         printf ("Check get 3 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckGet4(void) /* output is correct */
{
	int x = 1;
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 2);
	VectorAdd(myVec, 13);
    if (ERR_OK == VectorGet(myVec, 1, &x) && 13 == x){
        printf ("Check get 4 pass\n");
    }
    else{
         printf ("Check get 4 fail\n");    
    }
	VectorDestroy(myVec);
}

/**************** get  ***********/

void CheckSet1(void) /* input pointer to vector NULL */
{
    if (ERR_NOT_INITIALIZED == VectorSet(NULL, 2, 3)){
        printf ("Check set 1 pass\n");
    }
    else{
         printf ("Check get 1 fail\n");    
    }
}

void CheckSet2(void) /* wrong index */
{
	Vector* myVec = VectorCreate (1,1);
    if (ERR_WRONG_INDEX == VectorSet(myVec, 0, 3)){
        printf ("Check set 2 pass\n");
    }
    else{
         printf ("Check set 2 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckSet3(void) /* set is correct */
{
	int x = 1;
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 2);
	VectorSet(myVec, 0, 13);
    if (ERR_OK == VectorGet(myVec, 0, &x) && 13 == x){
        printf ("Check set 3 pass\n");
    }
    else{
         printf ("Check set 3 fail\n");    
    }
	VectorDestroy(myVec);
}

/**************** num of items  ***********/

void CheckNumOfItems1(void) /* input pointer to vector NULL */
{
	size_t x = 1;
    if (ERR_NOT_INITIALIZED == VectorItemsNum(NULL,  &x)){
        printf ("Check num of items 1 pass\n");
    }
    else{
         printf ("Check num of items 1 fail\n");    
    }
}

void CheckNumOfItems2(void) /* input pointer to num of items NULL */
{
	Vector* myVec = VectorCreate (1,1);
    if (ERR_NOT_INITIALIZED == VectorItemsNum(myVec, NULL)){
        printf ("Check num of items 2 pass\n");
    }
    else{
         printf ("Check num of items 2 fail\n");    
    }
	VectorDestroy(myVec);
}

void CheckNumOfItems3(void) /* get number of items correct */
{
	size_t x = 0;
	Vector* myVec = VectorCreate (1,1);
	VectorAdd(myVec, 2);
	VectorAdd(myVec, 2);
    if (ERR_OK == VectorItemsNum(myVec,&x) && 2 == x){
        printf ("Check num of items 3 pass\n");
    }
    else{
         printf ("Check num of items 3 fail\n");    
    }
	VectorDestroy(myVec);
}









