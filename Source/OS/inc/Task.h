
#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>



#define TASK_MAX_RUN_TIME             5u              /* preemption time for a task in ms */

typedef enum {
  TASK_RUNNING = 0,
  TASK_READY,
  TASK_BLOCKED,
  TASK_SUSPENDED
} Task_StateType;

typedef void (*Task_MainHandlerType)(void *);

typedef struct {
  uint32_t *pTopStack;
  uint32_t taskId;
  Task_StateType state;
  Task_MainHandlerType mainHandler;
  uint32_t *pStackAddr;
  uint32_t runningCnt;
  uint32_t blockedCnt;
  uint8_t priority;
} Task_t;

void Task_Init(void);
void Task_Create(uint32_t taskID, Task_MainHandlerType pMainHandler, uint32_t paramSize, uint32_t stackSize, uint8_t priority);
uint8_t Task_Schedule(void);
void Task_SwitchContext(void);
void Task_Delay(uint32_t delayTime_ms);
void Task_Block(uint32_t taskId);
void Task_Release(uint32_t taskId);
void Task_Suspend(uint32_t taskId);
void Task_Resume(uint32_t taskId);

#endif