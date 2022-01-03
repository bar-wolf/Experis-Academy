#define _XOPEN_SOURCE 600 

#include <stdlib.h> /* malloc & free */
#include <time.h>   /* __clockid_t */

#include "myTime.h"
#include "task.h"
#include "vector.h" 

struct Task
{
   TaskFunc   m_taskFunc;
   size_t     m_nextStartTime;  
   size_t     m_timeCycle;  
   void*      m_context;
};



Task* TaskCreate(TaskFunc _func, void* _context, size_t _period_ms)
{
   Task* myTask;

   if (_func == NULL)
   {
      return NULL;
   }

   myTask = (Task*)malloc(sizeof(Task));
   if (myTask == NULL)
   {
      return NULL;   
   }

   myTask->m_taskFunc = _func;
   myTask->m_nextStartTime = 0;
   myTask->m_timeCycle = _period_ms;
   myTask->m_context = _context;

   return myTask;
}



void TaskDestroy(void* _task)
{
   Task* tempTask = (Task*)_task; 

   if (_task == NULL)
   {
      return;
   }

   free(tempTask);
}



int TaskRun(Task* _task, __clockid_t _clockID)
{
   size_t time;
   size_t stop;
   int ans;

   if (_clockID != CLOCK_REALTIME_COARSE && _clockID != CLOCK_MONOTONIC && _clockID != CLOCK_REALTIME)
   {
      return 1;
   }

   if (_task == NULL)
   {
      return 1;
   }

   time = GetTime(_clockID);

   if (_task->m_nextStartTime <= time)
   {
      ans = _task->m_taskFunc(_task->m_context);
      _task->m_nextStartTime = GetTime(_clockID) + _task->m_timeCycle;
      return ans;
   }

   stop = _task->m_nextStartTime - time; 
   TimeWait(stop);

   ans = _task->m_taskFunc(_task->m_context);
   _task->m_nextStartTime = GetTime(_clockID) + _task->m_timeCycle;
   return ans;
}



void TaskTimeUpdate(Vector* _vec, __clockid_t _clockID)
{
   size_t i;
   void* task;
   Task* tempTask;

   if (_clockID != CLOCK_REALTIME_COARSE && _clockID != CLOCK_MONOTONIC && _clockID != CLOCK_REALTIME)
   {
      return;
   }

   if (_vec == NULL)
   {
      return;
   }

   for (i = 0; i < VectorSize(_vec); i++)
   {
      VectorGet(_vec, i, &task);
      tempTask = (Task*)(task);
      tempTask->m_nextStartTime = GetTime(_clockID) + tempTask->m_timeCycle;   
   }
}



int IsLessTime(const void* _firstTask, const void* _secndTask)
{
   Task* _first = (Task*)_firstTask;
   Task* _secnd = (Task*)_secndTask;

   if (_first == NULL || _secnd == NULL)
   {
      return 0;
   }

   if (TimeComper(_first->m_nextStartTime, _secnd->m_nextStartTime) == FIRST_SMALLER)
   {
      return 0;
   }

   return 1;
}







