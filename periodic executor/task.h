#ifndef __TASK_H__
#define __TASK_H__

#include "vector.h"
#include "executor.h"

typedef struct Task Task;


/** @brief create new task.
 * 
 * @par _func- action function.
 * @par _context- will send to _func.  
 * @par _period_ms- periods time thet _func will run (in millisecends)  
 * 
 * @return Task pointer on success. NULL on fail 
 */
Task* TaskCreate(TaskFunc _func, void* _context, size_t _period_ms);


/**
 * @brief destroy task.
 * 
 * @par _task- task to destroy
 */
void TaskDestroy(void* _task);


/**
 * @brief run the task one time
 * 
 * @par _task- task to run
 * @par _clockID- clock typ 
 * 
 * @return the _func return (zero to keep run)
 */
int TaskRun(Task* _task, __clockid_t _clockID); 


/**
 * @brief update tha time the task will run after
 * 
 * @par _vec- vector of tasks
 * @par  _clockID- clock typ
 */ 
void TaskTimeUpdate(Vector* _vec, __clockid_t _clockID);


/**
 * @brief function thet comper the start time of tasks
 * 
 * @par _firstTime- first task to comper
 * @par _secndTime- secnd task to comper
 * 
 * @return NON zero if first time is smaller
 */ 
int IsLessTime(const void* _firstTime, const void* _secndTime);
    
    
#endif  /* __TESK_H__ */ 
