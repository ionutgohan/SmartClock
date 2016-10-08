;*************************************************
;*
;* Part one of the system initialization code, contains low-level
;* initialization, plain thumb variant.
;*
;* Copyright 2008 IAR Systems. All rights reserved.
;*
;* $Revision: 50748 $
;*
;*************************************************

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version with interrupt handler for MK49X256VMD100 from Freescale
;

        MODULE  ?vector_table

        AAPCS INTERWORK, VFP_COMPATIBLE, RWPI_COMPATIBLE
        PRESERVE8


        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA

__iar_init$$done:               ; The vector table is not needed
                                ; until after copy initialization is done

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

    ; Interrupt Handlers for Service Requests (SR) from XMC4500 Peripherals
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 0 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 1 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 2 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 3 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 4 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 5 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 6 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 7 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 8 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 9 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 10 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 11 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 12 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 13 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 14 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Channel 15 Transfer Complete */
	    DCD   UNDEF_IRQHandler   /*!< DMA Error Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Normal Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< FTFL Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Read Collision Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Low Voltage Detect, Low Voltage Warning */
	    DCD   UNDEF_IRQHandler   /*!< Low Leakage Wakeup */
	    DCD   UNDEF_IRQHandler   /*!< WDOG Interrupt */
	    DCD   0                  /*!< Reserved interrupt 39 */
	    DCD   UNDEF_IRQHandler   /*!< I2C0 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< I2C1 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< SPI0 Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< SPI1 Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< SPI2 Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN0 OR'd Message Buffers Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN0 Bus Off Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN0 Error Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN0 Tx Warning Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN0 Rx Warning Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN0 Wake Up Interrupt */
	    DCD   0                  /*!< Reserved interrupt 51 */
	    DCD   0                  /*!< Reserved interrupt 52 */
	    DCD   UNDEF_IRQHandler   /*!< CAN1 OR'd Message Buffers Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN1 Bus Off Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN1 Error Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN1 Tx Warning Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN1 Rx Warning Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CAN1 Wake Up Interrupt */
	    DCD   0                  /*!< Reserved interrupt 59 */
	    DCD   0                  /*!< Reserved interrupt 60 */
	    DCD   UNDEF_IRQHandler   /*!< UART0 Receive/Transmit interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART0 Error interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART1 Receive/Transmit interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART1 Error interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART2 Receive/Transmit interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART2 Error interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART3 Receive/Transmit interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART3 Error interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART4 Receive/Transmit interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART4 Error interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART5 Receive/Transmit interrupt */
	    DCD   UNDEF_IRQHandler   /*!< UART5 Error interrupt */
	    DCD   UNDEF_IRQHandler   /*!< ADC0 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< ADC1 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CMP0 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CMP1 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CMP2 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< FTM0 fault, overflow and channels interrupt */
	    DCD   UNDEF_IRQHandler   /*!< FTM1 fault, overflow and channels interrupt */
	    DCD   UNDEF_IRQHandler   /*!< FTM2 fault, overflow and channels interrupt */
	    DCD   UNDEF_IRQHandler   /*!< CMT interrupt */
	    DCD   UNDEF_IRQHandler   /*!< RTC interrupt */
	    DCD   0                  /*!< Reserved interrupt 83 */
	    DCD   UNDEF_IRQHandler   /*!< PIT timer channel 0 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< PIT timer channel 1 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< PIT timer channel 2 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< PIT timer channel 3 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< PDB0 Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< USB0 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< USBDCD Interrupt */
	    DCD   0                  /*!< Reserved interrupt 91 */
	    DCD   0                  /*!< Reserved interrupt 92 */
	    DCD   0                  /*!< Reserved interrupt 93 */
	    DCD   0                  /*!< Reserved interrupt 94 */
	    DCD   UNDEF_IRQHandler   /*!< I2S0 Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< SDHC Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< DAC0 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< DAC1 interrupt */
	    DCD   UNDEF_IRQHandler   /*!< TSI0 Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< MCG Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< LPTimer interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Segment LCD Interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Port A interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Port B interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Port C interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Port D interrupt */
	    DCD   UNDEF_IRQHandler   /*!< Port E interrupt */
	    DCD   0                  /*!< Reserved interrupt 108 */
	    DCD   0                  /*!< Reserved interrupt 109 */
	    DCD   0                  /*!< Reserved interrupt 110 */
	    DCD   0                  /*!< Reserved interrupt 111 */
	    DCD   0                  /*!< Reserved interrupt 112 */
	    DCD   0                  /*!< Reserved interrupt 113 */
	    DCD   0                  /*!< Reserved interrupt 114 */
	    DCD   0                  /*!< Reserved interrupt 115 */
	    DCD   0                   /*!< Reserved interrupt 116 */
	    DCD   0                   /*!< Reserved interrupt 117 */
	    DCD   0                   /*!< Reserved interrupt 118 */
	    DCD   0                  /*!< Reserved interrupt 119 */
 




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK MemManage_Handler
        PUBWEAK BusFault_Handler
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
;; MK49X256VMD100 interrupt handlers
        PUBWEAK   UNDEF_IRQHandler
	   

        SECTION .text:CODE:REORDER(2)
        THUMB

NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler

UNDEF_IRQHandler

Default_Handler
        NOCALL Default_Handler
        B Default_Handler


        SECTION .text:CODE:REORDER(2)
        THUMB
Reset_Handler:

        B __iar_program_start
       
        
        END
