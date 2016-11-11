#ifndef __DRIVER_ELECTRODES_H__
  #define __DRIVER_ELECTRODES_H__
  
  #include "PounceTypes_v2.h"
  #include "TSS_API.h"
//  #include "MK40X256VMD100.h"
  #include "Driver_GPIO.h"

  /**
    Global defines
  */
  
  #define TSS_ELECTRODE_0                 0x01 //E1
  #define TSS_ELECTRODE_1                 0x02 //E2
  #define TSS_ELECTRODE_2                 0x04 //E3
  #define TSS_ELECTRODE_3                 0x08 //E4
  #define TSS_ELECTRODE_4                 0x10 //E5
  #define TSS_ELECTRODE_5                 0x20 //E6

/* R60287: definitions for FreTris game: 

[EXIT]  ------------------------------  [RIGHT]  [JLINK]
[NULL]  |                             | [SPIN]
[DROP]  ------------------------------  [LEFT]


*/

  #define KEYNULL   0x00
  #define START     0x01
  #define RIGHT     0x02
  #define SPIN      0x08
  #define DROP      0x10
  #define LEFT      0x20
  #define FEXIT     0x80

  /**
    External variables
  */
  extern U08 ElectrodeFlags;
  extern U08 ElectrodeFlagsPrevious;
  
  /**
    Public Function Prototypes
  */
  void _Electrodes_Init(void);
  void _Electrodes_Check(void);
  extern void TSS_fOnFault(void);
  extern void TSS1_fCallBack0(TSS_CONTROL_ID u8ControlId);
  void TSS_fOnInit(void);


#endif /*__DRIVER_ELECTRODES_H__*/