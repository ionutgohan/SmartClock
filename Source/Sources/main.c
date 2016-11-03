
#include "stdlib.h"
#include "OS.h"
#include "Task.h"
#include "MK40X256VMD100.h"
#include "Clock.h"
#include "DisplayM.h"
#include "Driver_SLCD.h"
#include "TD.h"
#include "ds18b20.h"
#include "SM.h"
#include <string.h>


extern void DispM_MainTask(void *params);
extern void TD_MainTask(void *params);
extern void DS_MainTask(void *params);

const OS_ScheduledTasksListType OS_scheduledTaskList[] = {
  {1, DispM_MainTask, 0, 512, 10},
  {2, TD_MainTask, 0, 512, 10},
  {3, DS_MainTask, 0, 512, 10},
  {4, SM_MainTask, 0, 512, 10},
  {.pMainHandler = NULL_PTR}   /* must ALWAYS be the last entry */
};


int main(void)
{   
  InitClock();
  
  DispM_Init();
  
  TD_Init();
  
  DS_Init();  
  
  SM_Init();
  
  OS_Init();
  
  OS_StartScheduler();
  
  while (1) {
    ;
  }
  return 0;
}