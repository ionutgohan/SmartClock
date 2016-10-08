
#include "Port.h"
#include "OS_Cfg.h"
#include "OS.h"
#include "Clock.h"



#define __disable_interrupts()        __disable_interrupt()
#define __enable_interrupts()         __enable_interrupt()

#define PORT_INITIAL_EXEC_RETURN_VAL     (0xFFFFFFFD)
#define PORT_INITIAL_XPSR                (0x01000000)


void Port_Init(void)
{
#ifdef FPU_ENABLE
  Port_EnableVFP();
#endif
}


void Port_SetupInterrupts(void)
{
  SysTick_Config((uint32_t)CORE_CLOCK / OS_TICK_FREQ);
  /* Make PendSV and SysTick the lowest priority interrupts. */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
  NVIC_SetPriority(PendSV_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
}

void SysTick_Handler(void)
{
  __disable_interrupts();
  
  OS_TickHandler();

  __enable_interrupts();  
}

void Port_TaskExitError(void)
{
  
}

void Port_InitializeTaskStack(Task_t *pTask)
{
  
  pTask->pTopStack--;
  *pTask->pTopStack = PORT_INITIAL_XPSR; /* xPSR */
  

  pTask->pTopStack--;
  *pTask->pTopStack = (uint32_t)pTask->mainHandler; /* PC */
  pTask->pTopStack--;
  *pTask->pTopStack = (uint32_t)Port_TaskExitError;   /* save the LR */  
  
  /* Save code space by skipping register initialisation. */
  pTask->pTopStack -= 5; /* R12, R3, R2 and R1. */
  
  /* A save method is being used that requires each task to maintain its
	own exec return value. */
  pTask->pTopStack--;
  *pTask->pTopStack = PORT_INITIAL_EXEC_RETURN_VAL;
  
  /* save R4-R11 */
  /* initial value of the registers is not really important */
  pTask->pTopStack -= 8u; 
}

