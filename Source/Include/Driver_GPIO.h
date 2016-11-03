#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

  #include "MK40X256VMD100.h"
  #include "PounceTypes_v2.h"
   
  /**
    Global defines
  */
  #define PORTA       0
  #define PORTB       1
  #define PORTC       2
  #define PORTD       3
  #define PORTE       4

  /**
    Public Functions Prototypes
  */
  void _GPIO_Init(U08 Port, U08 Bit);
  void _GPIO_Set_Pin(U08 Port, U08 Bit);
  void _GPIO_Clear_Pin(U08 Port, U08 Bit);
  void _GPIO_Toggle_Pin(U08 Port, U08 Bit);
  
#endif /* __DRIVER_GPIO_H__ */  