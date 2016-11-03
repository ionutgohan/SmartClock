#include "Driver_Electrodes.h"

/**
  Global variables
*/
U08 ElectrodeFlags = 0;
U08 ElectrodeFlagsPrevious = 0;

/**
  Function Name	: _Electrodes_Init
  Engineer      : Manglio González Carrasco
  Date          : 05/01/2011
  
  Parameters	: Nothing
  Returns       : Nothing
  Notes         : This function enables and configures the FTM, GPIO's and TSS
*/
void _Electrodes_Init(void)
{   
  /**
  Needed for TSS
  */
  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
 
  _GPIO_Init(PORTA,4);  
  _GPIO_Init(PORTA,24);
  _GPIO_Init(PORTA,25);
  _GPIO_Init(PORTA,26);
  _GPIO_Init(PORTA,27);          
  _GPIO_Init(PORTB,0); 
  
  (void)TSS_Init();

  (void)TSS_KeypadConfig(cKey0.ControlId,Keypad_Events_Register,(TSS_KEYPAD_TOUCH_EVENT_EN_MASK|TSS_KEYPAD_RELEASE_EVENT_EN_MASK));
  (void)TSS_KeypadConfig(cKey0.ControlId,Keypad_ControlConfig_Register,(TSS_KEYPAD_CALLBACK_EN_MASK|TSS_KEYPAD_CONTROL_EN_MASK));   
  
  /**
    Configures the Response Time 
  */
  (void)TSS_SetSystemConfig(System_ResponseTime_Register,7);
  (void)TSS_SetSystemConfig(System_NSamples_Register,10);
  (void)TSS_SetSystemConfig(System_StuckKeyTimeout_Register,200);

  /**   
    Configures the DC Traker value 
  */
  (void)TSS_SetSystemConfig(System_DCTrackerRate_Register,0x40);
 

  /**
    Calibrate the  electrodes
  */
  (void)TSS_SetSystemConfig(System_Sensitivity_Register+0, 15); //E1
  (void)TSS_SetSystemConfig(System_Sensitivity_Register+1, 15); //E2
  (void)TSS_SetSystemConfig(System_Sensitivity_Register+2, 22); //E3
  (void)TSS_SetSystemConfig(System_Sensitivity_Register+3, 22); //E4        
  (void)TSS_SetSystemConfig(System_Sensitivity_Register+4, 15); //E5
  (void)TSS_SetSystemConfig(System_Sensitivity_Register+5, 15); //E6  

  /**
    Enable TSS
  */
  (void)TSS_SetSystemConfig(System_SystemConfig_Register,(TSS_SYSTEM_EN_MASK|TSS_DC_TRACKER_EN_MASK|TSS_STUCK_KEY_EN_MASK));     
}

/**
  Function Name	: _Electrodes_Check
  Engineer      : Manglio González Carrasco
  Date          : 05/01/2011
  
  Parameters	: Nothing
  Returns       : Nothing
  Notes         : This function just calls the TSS_Task()
*/
void _Electrodes_Check(void)
{  
   TSS_Task();
}

/****************************************************************************************************
* Fault interrupt (software interrupt)
* ---------------------------------------------------------------------------------------------------
* Re-enables the electrode with fault in the case is disabled
*****************************************************************************************************/
void TSS_fOnFault(void)
{
    if(tss_CSSys.Faults.ChargeTimeout || tss_CSSys.Faults.SmallCapacitor) /* If large or small capacitor fault  */
    {    
      (void) TSS_SetSystemConfig(System_Faults_Register, 0x00);             /* Clear the fault flag */
      (void) TSS_SetSystemConfig(System_ElectrodeEnablers_Register, 0xFF);  /* Re-enable all electrodes  */
    }
}
/***************************************************************************
**     Event       :  TSS Init
** -------------------------------------------------------------------------
**     Component   :  TSS1 [TSS_Library]
**     Description :
**         Callback definition for when TSS Init is complete. In this case
**         no action is needed, so it is an empty function included to keep
**         the TSS library happy.
**     Parameters  : None
**                    
**     Returns     : Nothing
****************************************************************************/
void TSS_fOnInit(void)
{

}

/***************************************************************************
**     Event       :  TSS1_fCallBack0 (module Events)
** -------------------------------------------------------------------------
**     Component   :  TSS1 [TSS_Library]
**     Description :
**         Callback definition for Control 0. This event is enabled
**         only if Control 0 is enabled.
**         The default CallBack Name is automatically generated with
**         automatic prefix update by current Component Name. User can
**         define own name, but then the automatic name update is not
**         functional.
**     Parameters  :
**         NAME            - DESCRIPTION
**         u8ControlId     - Valid unique Identifier of
**                           the Control which generated the CallBack
**                           function. This Id can be used for finding
**                           of Callback's source Control.
**     Returns     : Nothing
****************************************************************************/
void TSS1_fCallBack0(TSS_CONTROL_ID u8ControlId)
{
    /* Write your code here ... */
    UINT8 u8Event; /* 8 bits local variable used to store the event information */
 
    while (!TSS_KEYPAD_BUFFER_EMPTY(cKey0))  /* While unread events are in the buffer */
    {
      TSS_KEYPAD_BUFFER_READ(u8Event,cKey0); /* Read the buffer and store the event in the u8Event variable */

      if (u8Event & 0x80) 
      {                                      /* If was a release event */
        u8Event = (UINT8) (u8Event & 0x0F);  /* Remove the release flag */

        if (u8Event == 0x00)
        {
          ElectrodeFlags &= ~TSS_ELECTRODE_0;     
        }
        if (u8Event == 0x01)
        {
          ElectrodeFlags &= ~TSS_ELECTRODE_1;
        }
        if (u8Event == 0x02)
        {
          ElectrodeFlags &= ~TSS_ELECTRODE_2;
        }
        if (u8Event == 0x04)
        {
          ElectrodeFlags &= ~TSS_ELECTRODE_4;          
        }
        if (u8Event == 0x03)
        {
          ElectrodeFlags &= ~TSS_ELECTRODE_3;          
        }
        if (u8Event == 0x05)
        {
          ElectrodeFlags &= ~TSS_ELECTRODE_5;
        }   
      } 
      else
      {                                      /* If was a touch event */          
        if (u8Event == 0x00)
        {
          ElectrodeFlags |= TSS_ELECTRODE_0;     
        }
        if (u8Event == 0x01)
        {
          ElectrodeFlags |= TSS_ELECTRODE_1;
        }
        if (u8Event == 0x02)
        {
          ElectrodeFlags |= TSS_ELECTRODE_2;
        }
        if (u8Event == 0x04)
        {
          ElectrodeFlags |= TSS_ELECTRODE_4;          
        }
        if (u8Event == 0x03)
        {
          ElectrodeFlags |= TSS_ELECTRODE_3;          
        }
        if (u8Event == 0x05)
        {
          ElectrodeFlags |= TSS_ELECTRODE_5;
        }        
      }
    }       
  (void) u8ControlId;
}
