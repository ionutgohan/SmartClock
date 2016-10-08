
   
        SECTION .text:CODE:REORDER(2)
        THUMB
   
   
   
        EXTERN Task_pCurrentTask
	EXTERN Task_SwitchContext
        
        PUBLIC Port_StartFirstTask
        PUBLIC Port_EnableVFP
        PUBLIC PendSV_Handler
        PUBLIC SVC_Handler

PendSV_Handler:

        mrs r0, psp
	isb
	/* Get the location of the current TCB. */
	ldr	r3, =Task_pCurrentTask
	ldr	r2, [r3]

        #ifdef FPU_ENABLE
	/* Is the task using the FPU context?  If so, push high vfp registers. */
	tst r14, #0x10
	it eq
	vstmdbeq r0!, {s16-s31}
        #endif
	/* Save the core registers. */
	stmdb r0!, {r4-r11, r14}

	/* Save the new top of stack into the first member of the TCB. */
	str r0, [r2]

	stmdb sp!, {r3}
	mov r0, #0x28
	msr basepri, r0
	bl Task_SwitchContext
	mov r0, #0
	msr basepri, r0
	ldmia sp!, {r3}

	/* The first item in pxCurrentTCB is the task top of stack. */
	ldr r1, [r3]
	ldr r0, [r1]

	/* Pop the core registers. */
	ldmia r0!, {r4-r11, r14}


        #ifdef FPU_ENABLE
	/* Is the task using the FPU context?  If so, pop the high vfp registers
	too. */
	tst r14, #0x10
	it eq
	vldmiaeq r0!, {s16-s31}
        #endif
	msr psp, r0
	isb
	#ifdef WORKAROUND_PMU_CM001 /* XMC4000 specific errata */
		#if WORKAROUND_PMU_CM001 == 1
			push { r14 }
			pop { pc }
		#endif
	#endif
        
	bx r14
/*-----------------------------------------------------------*/


SVC_Handler:
	/* Get the location of the current TCB. */
	ldr	r3, =Task_pCurrentTask
	ldr r1, [r3]
	ldr r0, [r1]
        
	/* Pop the core registers. */
	ldmia r0!, {r4-r11, r14}
	msr psp, r0
	isb
	mov r0, #0
	msr	basepri, r0
	bx r14

/*-----------------------------------------------------------*/

Port_StartFirstTask
	/* Use the NVIC offset register to locate the stack. */
	ldr r0, =0xE000ED08
	ldr r0, [r0]
	ldr r0, [r0]
	/* Set the msp back to the start of the stack. */
	msr msp, r0
	/* Call SVC to start the first task. */
	cpsie i
	dsb
	isb
	svc 0
        

/*-----------------------------------------------------------*/

Port_EnableVFP:
	/* The FPU enable bits are in the CPACR. */
	ldr.w r0, =0xE000ED88
	ldr	r1, [r0]

	/* Enable CP10 and CP11 coprocessors, then save back. */
	orr	r1, r1, #( 0xf << 20 )
	str r1, [r0]
	bx	r14
/*-----------------------------------------------------------*/

        END