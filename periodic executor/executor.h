#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "vector.h"

enum PeriodicExecutorErrors
{
    ADD_FAIL,
    ADD_SUCCESS
};

typedef struct PeriodicExecutor PeriodicExecutor;


/** @brief user provided function thet will run at
 * periods time.
 * 
 * @par _context- can be NULL.
 * 
 * @return zero to keep run. 
 */
typedef int(*TaskFunc)(void* _context);



/**
* @brief create periodic executor thet run user functions on definde pereriod of time (in resolution of millisecens) 
*
* @par _name- name of periodic executor can be null
* @par _clk_id- warking clock typ
*
* @return PeriodicExecutor pointer at success. null at fail  
 */
PeriodicExecutor* PeriodicExecutorCreate(const char* _name, __clockid_t _clk_id);



/**
 * @brief destroy the periodic executor
 * 
 * @par _executor- periodic executor to destroy
 */
void PeriodicExecutorDestroy(PeriodicExecutor* _executor);



/**
 * @brief add task to the periodic executor
 * 
 * @par _executor- periodic executor to add
 * @par _func- task func, can NOT be null
 * @par _context- item that will be send to _func, can be null 
 * @par _period_ms- time period to operate _func (in millisecnds)
 * 
 * @return ADD_SUCCESS or ADD_FAIL
 */
int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunc _func, void* _context, size_t _period_ms);



/**
 * @brief run the periodic executor until the task finsh or operate PeriodicExecutorPause
 * 
 * @par _executor- periodic executor to run
 * 
 * @return number of operations or max of size_t at error   
 */
size_t PeriodicExecutorRun(PeriodicExecutor* _executor);



/**
 * @brief pause the periodic executor, operate as TaskFunc
 * 
 * @par _executor- periodic executor to stop
 * 
 * @return number of task thet wite in the executor or max of size_t at error
 */
size_t PeriodicExecutorPause(PeriodicExecutor* _executor);


#endif /* __EXECUTOR_H__ */