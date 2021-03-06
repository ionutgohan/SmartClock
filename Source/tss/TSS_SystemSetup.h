/*                                                                                           
*  Touch Sensing Library System Setup File                                                   
*                                                                                            
*  Auto-generated by System Setup Creator Tool                                               
*                                                                                            
*  This file contains electrode and other Touch Sensing System setup parameters              
*/                                                                                             

#ifndef __TSS_SYSTEM_SETUP_H__
  #define __TSS_SYSTEM_SETUP_H__
  
  
  /* Define CTS/ATL low layer sensing algorithm to be used */
  #undef TSS_USE_ATL_LOW_LEVEL
  #define TSS_USE_CTS_LOW_LEVEL             1

  #define TSS_USE_DELTA_LOG                 1
  
  #define TSS_USE_GPIO_STRENGTH             0
  
  #define TSS_USE_GPIO_SLEW_RATE            0
  
  #define TSS_USE_IIR_FILTER                1
  
  #define TSS_USE_NOISE_AMPLITUDE_FILTER    1
  
  #define TSS_ONFAULT_CALLBACK              TSS_fOnFault /* Identifier of the user's OnFault callback */
  
  #define TSS_N_ELECTRODES                  6         /* Number of electrodes present in the system */
  
  /* Electrode's GPIOs configuration */
  
  #define TSS_E0_P                    B                 /* Electrode port */
  #define TSS_E0_B                    0                 /* Electrode bit  */

  #define TSS_E1_P                    A                 /* Electrode port */
  #define TSS_E1_B                    4                 /* Electrode bit  */

  #define TSS_E2_P                    A                 /* Electrode port */
  #define TSS_E2_B                    24                /* Electrode bit  */
  
  #define TSS_E3_P                    A                 /* Electrode port */
  #define TSS_E3_B                    25                /* Electrode bit  */

  #define TSS_E4_P                    A                 /* Electrode port */
  #define TSS_E4_B                    26                /* Electrode bit  */
  
  #define TSS_E5_P                    A                 /* Electrode port */
  #define TSS_E5_B                    27                /* Electrode bit  */

  /* Electrode's measurement method configuration */
  
  #define TSS_E0_TYPE                 GPIO             /* Default GPIO Method */
  #define TSS_E1_TYPE                 GPIO             /* Default GPIO Method */
  #define TSS_E2_TYPE                 GPIO             /* Default GPIO Method */
  #define TSS_E3_TYPE                 GPIO             /* Default GPIO Method */
  #define TSS_E4_TYPE                 GPIO             /* Default GPIO Method */
  #define TSS_E5_TYPE                 GPIO             /* Default GPIO Method */
  
  /* Controls configuration */
  
  #define TSS_N_CONTROLS              1
  
  #define TSS_C0_TYPE                 TSS_CT_KEYPAD    /* Control type */
  #define TSS_C0_ELECTRODES           6                /* Number of electrodes in the control */
  #define TSS_C0_STRUCTURE            cKey0            /* Name of the C&S struct to create */
  #define TSS_C0_CALLBACK             TSS1_fCallBack0  /* Identifier of the user's callback */
  
  #define TSS_HW_TIMER                FTM1
  #define TSS_SENSOR_PRESCALER        4               /* Defines the prescaler for all used Timers */
  #define TSS_SENSOR_TIMEOUT          0X1FF            /* Defines the timeout for all used Timers */

  #define TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE 8
  #define TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE 8
  #define TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE 8
  #define TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE 8
  #define TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE 8
  #define TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE 8
#endif /*__TSS_SYSTEM_SETUP_H__*/