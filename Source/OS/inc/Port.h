

#ifndef PORT_H_
#define PORT_H_

#include <stdint.h>

#include "MK40X256VMD100.h"
#include "Task.h"


#define Port_SetPendSVInterruptReq()        (SCB_ICSR |= SCB_ICSR_PENDSVSET_MASK)    

void Port_Init(void);
void Port_SetupInterrupts(void);
void Port_InitializeTaskStack(Task_t *pStack);
extern void Port_StartFirstTask(void);
extern void Port_EnableVFP(void);


#endif