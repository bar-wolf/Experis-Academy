#define _XOPEN_SOURCE 600

#include <stdio.h>  /* printf & putchar */
#include <time.h>   /* __clookid_t */
#include "executor.h"
#include "vector.h"

#define PASS  printf(": [\x1B[32m" "OK" "\x1B[0m]\n");  /** print green OK */ 
#define FAIL  printf(": [\x1B[31m" "FAIL" "\x1B[0m]\n"); /** print red FAIL */

#define SEC_TO_MILLI(sec) (sec)*1000

typedef struct Test
{
    PeriodicExecutor* m_executor;
    size_t m_taskLeft;  
}Test;


/***** Test Functions *****/
void ExecutorCreateTest1(void);
void ExecutorCreateTest2(void);

void ExecutorAddTest1(void); 
void ExecutorAddTest2(void);

void ExecutorRunTest1(void);
void ExecutorRunTest2(void);

void PrintTtest(void);



int main (void)
{
    printf("\n************* Tests: **************\n");

    ExecutorCreateTest1();
    ExecutorCreateTest2();

    ExecutorAddTest1();
    ExecutorAddTest2();
    
    ExecutorRunTest1(); 
    ExecutorRunTest2(); 


    /*PrintTtest();*/

    putchar('\n');
    return 0;
}


/**** Print Func for test ****/
int Print_2_Sec(void* _contex)
{
    printf("--- 2 sec ---\n");
    return 1;
}

int Print_3_Sec(void* _contex)
{
    printf("--- 3 sec ---\n");
    return 1;
}

int Print_4_Sec(void* _contex)
{
    printf("--- 4 sec ---\n");
    return 1;
}

int Print_10_Sec(void* _contex)
{
    printf("--- 10 sec ---\n");
    return 1;
}

int Print_15_Sec(void* _contex)
{
    printf("--- 15 sec ---\n");
    return 1;
}

int DoNothinOneTime(void* _contex)
{
    return 1;
}

int StopRun(void* _contex)
{
    Test* test = (Test*)_contex;
    test->m_taskLeft = PeriodicExecutorPause(test->m_executor);
    return 1;    
}



/**** Executor Create Test ****/

void ExecutorCreateTest1(void) /* wrong __clookid_t */
{
    PeriodicExecutor* myExecutor;
    const char name = 'n'; 

    myExecutor = PeriodicExecutorCreate(&name, 138734);

    printf("Executor Create Test 1");
    if (myExecutor == NULL){
        PASS    
    }else{
        FAIL
    }            
}


void ExecutorCreateTest2(void) /* make PeriodicExecutor */
{
    PeriodicExecutor* myExecutor;
    const char name = 'n'; 

    myExecutor = PeriodicExecutorCreate(&name, CLOCK_REALTIME);

    printf("Executor Create Test 2");
    if (myExecutor != NULL){
        PASS    
    }else{
        FAIL
    }

    PeriodicExecutorDestroy(myExecutor);            
}



/**** Executor Add Test ****/

void ExecutorAddTest1(void) /* incres vector size */ 
{
    PeriodicExecutor* myExecutor;
    const char name = 'n';
    Vector* myVec;

    myExecutor = PeriodicExecutorCreate(&name, CLOCK_REALTIME);
    PeriodicExecutorAdd(myExecutor, Print_2_Sec, NULL, 2*1000);
    PeriodicExecutorAdd(myExecutor, Print_2_Sec, NULL, 2*1000);

    myVec = GetExecutorVector(myExecutor);

    printf("Executor Add Test 1");
    if (VectorSize(myVec) == 2){
        PASS    
    }else{
        FAIL
    }

    PeriodicExecutorDestroy(myExecutor);            
}


void ExecutorAddTest2(void) /* don't get null */ 
{
    PeriodicExecutor* myExecutor;
    const char name = 'n';
    int ans;

    myExecutor = PeriodicExecutorCreate(&name, CLOCK_REALTIME);
    ans = PeriodicExecutorAdd(myExecutor, NULL, NULL, 2*1000);

    printf("Executor Add Test 2");
    if (ans == ADD_FAIL){
        PASS    
    }else{
        FAIL
    }

    PeriodicExecutorDestroy(myExecutor);            
}



/**** Executor Run Test ****/ 

void ExecutorRunTest1(void)  /* count the operations */
{
    PeriodicExecutor* myExecutor;
    const char name = 'n';
    
    myExecutor = PeriodicExecutorCreate(&name, CLOCK_REALTIME);

    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 1);
    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 1);
    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 1);

    printf("Executor Run Test 1");
    if (3 == PeriodicExecutorRun(myExecutor)){
        PASS    
    }else{
        FAIL
    }

    PeriodicExecutorDestroy(myExecutor);            
}


void ExecutorRunTest2(void)  /* stop and return task left */
{
    const char name = 'n';
    PeriodicExecutor* myExecutor = PeriodicExecutorCreate(&name, CLOCK_REALTIME);
    Test test;
    test.m_executor = myExecutor;
    test.m_taskLeft = -1;

    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 5);
    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 10);
    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 30);    PeriodicExecutorAdd(myExecutor, DoNothinOneTime, NULL, 20);
    PeriodicExecutorAdd(myExecutor, StopRun, &test, 15);
    
    PeriodicExecutorRun(myExecutor);

    printf("Executor Run Test 2");
    if (test.m_taskLeft == 2){
        PASS    
    }else{
        FAIL
    }

    PeriodicExecutorDestroy(myExecutor);            
}



/**** Print Ttests ****/

void PrintTtest(void) 
{
    PeriodicExecutor* myExecutor;
    const char name = 'n';
    Vector* meVector;

    myExecutor = PeriodicExecutorCreate(&name, CLOCK_REALTIME);

    PeriodicExecutorAdd(myExecutor, Print_4_Sec, NULL, 4*1000);
    PeriodicExecutorAdd(myExecutor, Print_2_Sec, NULL, 2*1000);
    PeriodicExecutorAdd(myExecutor, Print_10_Sec, NULL, 10*1000);
    PeriodicExecutorAdd(myExecutor, Print_15_Sec, NULL, 15*1000);
    PeriodicExecutorAdd(myExecutor, Print_3_Sec, NULL, 3*1000);

    PeriodicExecutorRun(myExecutor);

    PeriodicExecutorDestroy(myExecutor);            
}
