
#ifndef OS_CFG_H_
#define OS_CFG_H_

#include "Port.h"

#define configPRIO_BITS       		__NVIC_PRIO_BITS

#define OS_TICK_FREQ              1000u              /* value in Hz */


#define OS_RequestContextSwitch()  Port_SetPendSVInterruptReq()


#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#endif