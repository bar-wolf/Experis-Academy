#define _XOPEN_SOURCE 600 

#include <stdlib.h> /* malloc & free */
#include <string.h> /* strlng & strcopy */
#include <time.h>

#include "heap.h"
#include "vector.h"

#include "myTime.h"
#include "executor.h"
#include "task.h"

#define VECTOR_SIZE 20
#define GO 1
#define STOP 0

struct PeriodicExecutor
{
    char*         m_name;
    Vector*       m_vector;
    __clockid_t   m_clk_id;
    int           m_fleg;
};



/** TODO: all name fings */ 
PeriodicExecutor* PeriodicExecutorCreate(const char* _name, __clockid_t _clk_id)  
{
    Vector* myVec;
    PeriodicExecutor* myExecutor;

    if (_clk_id != CLOCK_REALTIME_COARSE && _clk_id != CLOCK_MONOTONIC && _clk_id != CLOCK_REALTIME)
    {
        return NULL;
    }
    

    myVec = VectorCreate(VECTOR_SIZE, VECTOR_SIZE);
    if (myVec == NULL)
    {
        return NULL;
    }

    myExecutor = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor));
    if (myExecutor == NULL)
    {
        free(myVec);
        return NULL;
    }
    
    myExecutor->m_clk_id = _clk_id;
    myExecutor->m_vector = myVec;
    myExecutor->m_fleg = GO;

    return myExecutor;    
}


/** TODO: free the name to */
void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{
    if (_executor == NULL)
    {
        return;
    }    
    
    VectorDestroy(&_executor->m_vector, TaskDestroy); 
    free(_executor);
}



int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunc _func, void* _context, size_t _period_ms)
{
    Task* myTask;

    if (_executor == NULL || _func == NULL)
    {
        return ADD_FAIL; 
    }

    myTask = TaskCreate(_func, _context, _period_ms);
    if (myTask == NULL)
    {
        return ADD_FAIL;
    }

    if  (VectorAdd(_executor->m_vector, myTask) != VECTOR_SUCCESS)
    {
        TaskDestroy(&myTask);
        return ADD_FAIL;
    }

    return ADD_SUCCESS;
}



size_t PeriodicExecutorRun(PeriodicExecutor* _executor)
{
    size_t counter = 0;
    Heap* myHeap;
    Task* myTask;
    int ans;

    if(_executor == NULL)
    {
        return -1;
    }

    TaskTimeUpdate (_executor->m_vector, _executor->m_clk_id);

    myHeap = HeapBuild(_executor->m_vector, IsLessTime);
    if (myHeap == NULL)
    {
        return -1;
    }

    _executor->m_fleg = GO;
    while(_executor->m_fleg == GO)
    {
        myTask = (Task*)HeapExtract(myHeap);
        if (myTask == NULL)
        {
            HeapDestroy(&myHeap);
            return counter;
        }

        ans = TaskRun(myTask, _executor->m_clk_id);
        counter++;
        if (ans == 0)
        {
            if (HEAP_SUCCESS != HeapInsert(myHeap ,myTask))
            {
                return -1;
            }            
        }
        
        else
        {
            TaskDestroy(myTask);
        }
    }

    HeapDestroy(&myHeap);
    return counter;
}



size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
    if (_executor == NULL)
    {
        return -1;
    }

    _executor->m_fleg = STOP;
    return VectorSize(_executor->m_vector);
}




/**** get functions ****/

Vector* GetExecutorVector(PeriodicExecutor* _executor)
{
    return _executor->m_vector;
}