/**********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************************************************//*!
*
* @file   TSS_StatusCodes.h
*
* @brief  Header file that defines the Return Status Codes used by the TSS Library
*
* @version 1.0.16.0
* 
* @date Dec-14-2010
* 
* These Return Status Codes are used by the User Application Level and also internally in the Library
*
***********************************************************************************************************************/


#ifndef __TSS_STAT_CODES_H__
  #define __TSS_STAT_CODES_H__

  /* TSS Task Status Codes */
  #define TSS_STATUS_OK                           0u
  #define TSS_STATUS_PROCESSING                   1u

  /* Sample Electrode Commands */
  #define TSS_SAMPLE_COMMAND_DUMMY                0x00u   /* Command for SampleElectrode function */
  #define TSS_SAMPLE_COMMAND_RESTART              0x01u   /* Command for SampleElectrode function */
  #define TSS_SAMPLE_COMMAND_PROCESS              0x02u   /* Command for SampleElectrode function */        
  #define TSS_SAMPLE_COMMAND_RECALIB              0x03u   /* Command for SampleElectrode function */        
  #define TSS_SAMPLE_COMMAND_GET_NEXT_ELECTRODE   0x04u   /* Command for SampleElectrode function */        
  #define TSS_SAMPLE_COMMAND_ENABLE_ELECTRODE     0x05u   /* Command for SampleElectrode function */        

  /* Sample Electrode Status Codes */
  #define TSS_SAMPLE_STATUS_OK                    0x00u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_STATUS_PROCESSING            0x01u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_STATUS_CALIBRATION_CHANGED   0x02u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_RECALIB_REQUEST_LOCAP        0x03u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_RECALIB_REQUEST_HICAP        0x04u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_ERROR_SMALL_AUTOTRG_PERIOD   0x05u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_ERROR_CHARGE_TIMEOUT         0x06u   /* Return value from the SampleElectrode function */
  #define TSS_SAMPLE_ERROR_SMALL_CAP              0x07u   /* Return value from the SampleElectrode function */

  /* Sensor Init Commands Commands */
  #define TSS_INIT_COMMAND_DUMMY                  0x00u   /* Command for SensorInit function */
  #define TSS_INIT_COMMAND_INIT_MODULES           0x01u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_ENABLE_ELECTRODES      0x02u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_SET_NSAMPLES           0x03u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_INIT_TRIGGER           0x04u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_SW_TRIGGER             0x05u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_INIT_LOWPOWER          0x06u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_GOTO_LOWPOWER          0x07u   /* Command for SensorInit function */        
  #define TSS_INIT_COMMAND_RECALIBRATE            0x08u   /* Command for SensorInit function */        

  /* Sensor Init Return Codes */
  #define TSS_INIT_STATUS_OK                      0x00u   /* Return values from SensorInit function */
  #define TSS_INIT_STATUS_LOWPOWER_SET            0x01u   /* Return values from SensorInit function */
  #define TSS_INIT_STATUS_LOWPOWER_ELEC_SET       0x02u   /* Return values from SensorInit function */
  #define TSS_INIT_STATUS_TRIGGER_SET             0x04u   /* Return values from SensorInit function */
  #define TSS_INIT_STATUS_AUTOTRIGGER_SET         0x08u   /* Return values from SensorInit function */
  #define TSS_INIT_STATUS_CALIBRATION_CHANGED     0x10u   /* Return values from SensorInit function */
  #define TSS_INIT_ERROR_RECALIB_FAULT            0x20u   /* Return values from SensorInit function */

  /* Key Detector Status Codes */
  #define TSS_KEYDETECT_STATUS_OK                 0x00u   /* Return value from the KeyDetector function */
  #define TSS_KEYDETECT_STATUS_PROCESSING         0x01u   /* Return value from the KeyDetector function */
  #define TSS_KEYDETECT_ERROR_LARGE_CAP           0x02u   /* Return value from the KeyDetector function */
  #define TSS_KEYDETECT_ERROR_SMALL_CAP           0x04u   /* Return value from the KeyDetector function */        
  #define TSS_KEYDETECT_ERROR_SMALL_AUTOTRG_VAL   0x08u   /* Return value from the KeyDetector function */        

  /* Keypad Decoder Status Codes */
  #define TSS_ERROR_KEYPAD_NOT_IDLE               0x11u   /* Return values from the KeyPadConfig function */
  #define TSS_ERROR_KEYPAD_ILEGAL_PARAMETER       0x12u   /* Return values from the KeyPadConfig function */
  #define TSS_ERROR_KEYPAD_READ_ONLY_PARAMETER    0x13u   /* Return values from the KeyPadConfig function */
  #define TSS_ERROR_KEYPAD_OUT_OF_RANGE           0x14u   /* Return values from the KeyPadConfig function */
  #define TSS_ERROR_KEYPAD_ILEGAL_CONTROL_TYPE    0x15u   /* Return values from the KeyPadConfig function */

  /* Slider Decoder Status Codes */
  #define TSS_ERROR_SLIDER_NOT_IDLE               0x21u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_SLIDER_ILEGAL_PARAMETER       0x22u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_SLIDER_READ_ONLY_PARAMETER    0x23u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_SLIDER_OUT_OF_RANGE           0x24u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_SLIDER_ILEGAL_CONTROL_TYPE    0x25u

  /* Rotary Decoder Status Codes */
  #define TSS_ERROR_ROTARY_NOT_IDLE               0x31u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_ROTARY_ILEGAL_PARAMETER       0x32u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_ROTARY_READ_ONLY_PARAMETER    0x33u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_ROTARY_OUT_OF_RANGE           0x34u   /* Return values from the TSS_SliderConfig function */
  #define TSS_ERROR_ROTARY_ILEGAL_CONTROL_TYPE    0x35u

  /* System Config & Mgnt Status Codes */
  #define TSS_ERROR_CONFSYS_NOT_IDLE              0x41u    /* Return values from the TSS_SetSystemConfig function */
  #define TSS_ERROR_CONFSYS_ILLEGAL_PARAMETER     0x42u    /* Return values from the TSS_SetSystemConfig function */
  #define TSS_ERROR_CONFSYS_READ_ONLY_PARAMETER   0x43u    /* Return values from the TSS_SetSystemConfig function */
  #define TSS_ERROR_CONFSYS_OUT_OF_RANGE          0x44u    /* Return values from the TSS_SetSystemConfig function */
  #define TSS_ERROR_CONFSYS_LOWPOWER_SOURCE_NA    0x45u    /* Return values from the TSS_SetSystemConfig function */
  #define TSS_ERROR_CONFSYS_INCORRECT_LOWPOWER_EL 0x46u    /* Return values from the TSS_SetSystemConfig function */
  #define TSS_ERROR_CONFSYS_TRIGGER_SOURCE_NA     0x47u    /* Return values from the TSS_SetSystemConfig function */

#endif /* __TSS_STAT_CODES_H__ */