
#ifndef _OS_H_
#define _OS_H_



#include <stdint.h>
#include "OS_Types.h"
#include "Task.h"

#define OS_IDLE_TASK                  0u
#define OS_IDLE_TASK_PRIORITY       100u

#define OS_REQ_CONTEXT_SWITCH       0u
#define OS_NO_CONTEXT_SWITCH        1u

typedef struct {
    uint32_t taskId;
    Task_MainHandlerType pMainHandler;
    uint32_t paramSize;
    uint32_t stackSize;
    uint8_t priority;
} OS_ScheduledTasksListType;


extern const OS_ScheduledTasksListType OS_scheduledTaskList[];

void OS_Init(void);
void OS_TickHandler(void);
void OS_StartScheduler(void);
void OS_IdleTask(void *params);

#endif