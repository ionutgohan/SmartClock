
#include <stdlib.h>
#include "Task.h"
#include "List.h"
#include "OS.h"
#include "OS_types.h"
#include "OS_Cfg.h"

#define Task_GetNextReadyTask()    (Task_pCurrentTask = (Task_t *)Task_ReadyList.pElems->pCurrentItem)  

List_t Task_ReadyList;
List_t Task_BlockedList;
List_t Task_SuspendedList;

Task_t * Task_pCurrentTask;

static void Task_AddTaskInReadyList(List_t * const list, ListItem_t * const pNewItem);
static void Task_InsertInReadyList(ListItem_t * const pItem);
static uint8_t Task_CheckDelayedTasks(void);


static void Task_InsertInReadyList(ListItem_t * const pItem)
{
  uint32_t readyListHeadAddr;
  List_t *readyListParser;
  Task_t *pSelectedTask = NULL;
  uintx_t restoreAddr;
  
  readyListParser = &Task_ReadyList;
  readyListHeadAddr = (uint32_t)readyListParser->pElems;
  restoreAddr = 0u;
  pSelectedTask = pItem->pCurrentItem;
  for (;;) {
    if ((pSelectedTask->priority < (((Task_t *)readyListParser->pElems->pCurrentItem)->priority)) || \
      (readyListParser->pElems->pNext == NULL)) {
        List_InsertElement(readyListParser, pItem);
        break;
      } else {
        restoreAddr = 1u;
        readyListParser->pElems = readyListParser->pElems->pNext;
      }
  }
  if (restoreAddr == 1u) {
    readyListParser->pElems = (ListItem_t *)readyListHeadAddr;
  }
}

static void Task_AddTaskInReadyList(List_t * const list, ListItem_t * const pNewItem)
{
  uint32_t headAddr;
  
  headAddr = (uint32_t)list->pElems;
  
  /* insert element at the end of the list, but before Idle task */
  
  if (((Task_t*)pNewItem->pCurrentItem)->taskId != OS_IDLE_TASK) {
    while (list->pElems->pNext != NULL) {
      list->pElems = list->pElems->pNext;
    }
  }
  List_InsertElement(list, pNewItem);
  
  /* at leat one task, beside Idle task, is the in the list */
  
  if (list->size > 2u) {
    list->pElems = (ListItem_t *)headAddr;
  }
  
}

void Task_Init(void)
{
  /* initialize the Ready List tasks */
  Task_ReadyList.pElems = NULL;
  Task_ReadyList.size = 0u;
  
  /* initialize the Blocked List tasks */
  Task_BlockedList.pElems = NULL;
  Task_BlockedList.size = 0u;
  
  /* initialize the Suspended List tasks */
  Task_SuspendedList.pElems = NULL;
  Task_SuspendedList.size = 0u;
  
}

void Task_Create(uint32_t taskID, Task_MainHandlerType pMainHandler, uint32_t paramSize, uint32_t stackSize, uint8_t priority)
{
  Task_t * pNewTask;
  ListItem_t * pNewElement;
  
  pNewTask = malloc(sizeof(Task_t));
  
  if (pNewTask != NULL) {
    pNewTask->mainHandler = pMainHandler;
    pNewTask->priority = priority;
    pNewTask->runningCnt = 0u;
    pNewTask->blockedCnt = 0u;
    pNewTask->pStackAddr = (uint32_t *)malloc(stackSize);
    if (pNewTask->pStackAddr != NULL) {
      pNewTask->pTopStack = (uint32_t *)(pNewTask->pStackAddr + stackSize);
      Port_InitializeTaskStack(pNewTask);
    }
    pNewTask->taskId = taskID;
    pNewTask->state = TASK_READY;
    
    
    pNewElement = List_CreateListItem((void*)pNewTask);
    Task_AddTaskInReadyList(&Task_ReadyList, pNewElement);
    
    if ((Task_pCurrentTask == NULL) || (Task_pCurrentTask->taskId == OS_IDLE_TASK)) {
      Task_GetNextReadyTask();
    }
  }
}

void Task_Block(uint32_t taskId)
{
  List_t * listParser;
  Task_t * pTask;
  ListItem_t * pItem;
  uint32_t readyListHeadAddr;
  
  listParser = &Task_ReadyList;
  readyListHeadAddr = (uint32_t)listParser->pElems;
  while (listParser->pElems->pNext != NULL) {
    pTask = (Task_t *)listParser->pElems->pCurrentItem; 
    if (pTask->taskId == taskId) {
      pItem = List_RemoveElement(listParser);
      pTask->state = TASK_BLOCKED;
      List_InsertElement(&Task_BlockedList, pItem);
      break;
    }
    listParser->pElems = listParser->pElems->pNext;
  }  
  listParser->pElems = (ListItem_t *)readyListHeadAddr;
}


void Task_Release(uint32_t taskId)
{
  List_t * listParser;
  Task_t * pTask;
  ListItem_t * pItem;
  uint32_t blockedListHeadAddr;
  
  listParser = &Task_BlockedList;
  blockedListHeadAddr = (uint32_t)listParser->pElems;
  while (listParser->pElems->pNext != NULL) {
    pTask = (Task_t *)listParser->pElems->pCurrentItem; 
    if (pTask->taskId == taskId) {
      pItem = List_RemoveElement(listParser);
      pTask->state = TASK_BLOCKED;
      List_InsertElement(&Task_ReadyList, pItem);
      break;
    }
    listParser->pElems = listParser->pElems->pNext;
  }  
  listParser->pElems = (ListItem_t *)blockedListHeadAddr;
}

void Task_Resume(uint32_t taskId)
{
  List_t * listParser;
  Task_t * pTask;
  ListItem_t * pItem;
  uint32_t suspendedListHeadAddr;
  
  listParser = &Task_SuspendedList;
  suspendedListHeadAddr = (uint32_t)listParser->pElems;
  while (listParser->pElems->pNext != NULL) {
    pTask = (Task_t *)listParser->pElems->pCurrentItem; 
    if (pTask->taskId == taskId) {
      pItem = List_RemoveElement(listParser);
      pTask->state = TASK_READY;
      Task_AddTaskInReadyList(&Task_ReadyList, pItem);
      break;
    }
    listParser->pElems = listParser->pElems->pNext;
  }  
  listParser->pElems = (ListItem_t *)suspendedListHeadAddr;
}

void Task_Suspend(uint32_t taskId)
{
  List_t * listParser;
  Task_t * pTask;
  ListItem_t * pItem;
  uint32_t readyListHeadAddr;
  
  listParser = &Task_ReadyList;
  readyListHeadAddr = (uint32_t)listParser->pElems;
  while (listParser->pElems->pNext != NULL) {
    pTask = (Task_t *)listParser->pElems->pCurrentItem; 
    if (pTask->taskId == taskId) {
      pItem = List_RemoveElement(listParser);
      pTask->state = TASK_SUSPENDED;
      List_InsertElement(&Task_SuspendedList, pItem);
      break;
    }
    listParser->pElems = listParser->pElems->pNext;
  }  
  listParser->pElems = (ListItem_t *)readyListHeadAddr;
}

uint8_t Task_Schedule(void)
{  
  ListItem_t *pTransferItem = NULL;
  uint8_t reqContextSwitch;
  
  reqContextSwitch = Task_CheckDelayedTasks();
  
  Task_pCurrentTask->runningCnt++;
  if ((Task_pCurrentTask->runningCnt == TASK_MAX_RUN_TIME) && (Task_pCurrentTask->taskId != OS_IDLE_TASK)) {
    Task_pCurrentTask->runningCnt = 0u;
    pTransferItem = List_RemoveElement(&Task_ReadyList);
    Task_InsertInReadyList(pTransferItem);
    reqContextSwitch = OS_REQ_CONTEXT_SWITCH;
  }
  
  return reqContextSwitch;
}


static uint8_t Task_CheckDelayedTasks(void)
{
  uintx_t idx;
  uintx_t originalSize;
  uint32_t blockedListHeadAddr;
  List_t *blockedListParser;
  ListItem_t *pTransferItem = NULL;
  Task_t *pSelectedTask = NULL;
  uint8_t reqContextSwitch = OS_NO_CONTEXT_SWITCH;
  
  blockedListParser = &Task_BlockedList;
  blockedListHeadAddr = (uint32_t)blockedListParser->pElems;
  originalSize = blockedListParser->size;
  for (idx = 0u; idx < originalSize; idx++) {
    pSelectedTask = blockedListParser->pElems->pCurrentItem;
    pSelectedTask->blockedCnt--;
    if (pSelectedTask->blockedCnt == 0u) {
      /* move to ready list */
      pTransferItem = List_RemoveElement(blockedListParser);
      blockedListHeadAddr = (uint32_t)blockedListParser->pElems;
      Task_InsertInReadyList(pTransferItem);
      reqContextSwitch = OS_REQ_CONTEXT_SWITCH;
    } else {
      blockedListParser->pElems = blockedListParser->pElems->pNext;
    }
  }
  blockedListParser->pElems = (ListItem_t *)blockedListHeadAddr;
  return reqContextSwitch;
}

void Task_Delay(uint32_t delayTime_ms)
{
  ListItem_t *pItem;
  List_t *listParser;
  uint32_t blockedListAddr = 0u;
  Task_t *pSelectedTask = NULL;
  
  if (Task_pCurrentTask != NULL) {
    /* set time while task will be blocked */
    Task_pCurrentTask->blockedCnt = delayTime_ms * (OS_TICK_FREQ / 1000u);
    
    /* put the task in the Blocked list */
    pItem = List_RemoveElement(&Task_ReadyList); 
    listParser = &Task_BlockedList;
    blockedListAddr = (uint32_t)Task_BlockedList.pElems;
    for (;;) {
      pSelectedTask = listParser->pElems->pCurrentItem;
      if (Task_pCurrentTask->blockedCnt < pSelectedTask->blockedCnt) {
        /* insert the element here */
        List_InsertElement(listParser, pItem); 
        if (listParser->pElems->pPrevious == NULL) {
          
          blockedListAddr = (uint32_t)Task_BlockedList.pElems;
        }       
        break;
      } else {
        if (listParser->pElems->pNext == NULL) {
          List_InsertElementAtEnd(listParser, pItem);
          break;
        } else {
          listParser->pElems = listParser->pElems->pNext;
        }
      }
    }
    
    listParser->pElems = (ListItem_t *)blockedListAddr;   
    
    
    /* request context switch */
    OS_RequestContextSwitch();
  }
}

void Task_SwitchContext(void)
{
  Task_GetNextReadyTask();
}

