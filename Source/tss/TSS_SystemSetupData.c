/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_SystemSetupData.c
*
* @brief  Defines the structs and information needed for the configuration and decoders usage 
*
* @version 1.0.44.0
* 
* @date Feb-22-2011
* 
* All the declarations of structures and information are bassed in the values
* provided by the user in the SystemSetup.h file                             
*
***********************************************************************************************************************/


#include "TSS_SystemSetup.h"
#include "TSS_API.h"
#include "TSS_SystemSetupVal.h"
#include "derivative.h" 

/* The section below declares all the structures needed for each decoder */

#if TSS_N_CONTROLS > 0
    #if (TSS_C0_TYPE == TSS_CT_KEYPAD)                  /* Validates the Controler Type */
        TSS_CSKeypad TSS_C0_STRUCTURE;                  /* Declares the control KeyPad Structure */
        TSS_KeypadContext TSS_C0_STRUCTURE_CONTEXT;     /* Declares the context KeyPad Structure */
        #define C0_BUFFMASK_BIT 0u                      /* Defines 1 bit to determinate if is a KeyPad or Slider/Rotary*/
        #define C0_BUFFLN       16u                 
        #define C0_DECODER      TSS_KeypadDecoder       /* Defines a reference constant for the Decodet type function */
    #elif (TSS_C0_TYPE == TSS_CT_SLIDER)                /* Validates the Controler Type */
        TSS_CSSlider TSS_C0_STRUCTURE;                  /* Declares the control Slider Structure */
        TSS_SingleContext TSS_C0_STRUCTURE_CONTEXT;     /* Declares the context Slider Structure */
        #define C0_BUFFMASK_BIT 1u                      /* Defines 1 bit to determinate if is a KeyPad or Slider/Rotary */
        #define C0_DECODER      TSS_SliderDecoder       /* Defines a reference constant for the Decodet type functions */
    #else
        TSS_CSRotary TSS_C0_STRUCTURE;                  /* Declares the control Rotary Structure */
        TSS_SingleContext    TSS_C0_STRUCTURE_CONTEXT;  /* Declares the context Rotary Structure */
        #define C0_BUFFMASK_BIT 1u                      /* Defines 1 bit to determinate if is a KeyPad (0) or Slider/Rotary (1) */
        #define C0_DECODER      TSS_SliderDecoder       /* Defines a reference constant for the Decoder type functions */
    #endif
    #define C0_CONTROLID (UINT8)(TSS_C0_TYPE << 4u)     /* Assign a control ID (4 LSB) and a control type (4 MSB)*/
    #define C0_BUFFMASK (UINT8)(C0_BUFFMASK_BIT)        /* Assign each CO_MASK_BIT a diferent position depending on the number of control*/ 
    void TSS_C0_CALLBACK(UINT8 u8ControlId);            /* Declares the callback fucntion */
    void C0_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer); /* Declares the decoder type function */
#endif

/* Depending on the number of controls declared by the user the strcutures are created */
#if TSS_N_CONTROLS > 1                                  
    #if (TSS_C1_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C1_STRUCTURE;
        TSS_KeypadContext TSS_C1_STRUCTURE_CONTEXT;
        #define C1_BUFFMASK_BIT 0u
        #define C1_BUFFLN       16u
        #define C1_DECODER      TSS_KeypadDecoder
    #elif (TSS_C1_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C1_STRUCTURE;
        TSS_SingleContext TSS_C1_STRUCTURE_CONTEXT;
        #define C1_BUFFMASK_BIT 1u
        #define C1_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C1_STRUCTURE;
        TSS_SingleContext TSS_C1_STRUCTURE_CONTEXT;
        #define C1_BUFFMASK_BIT 1u
        #define C1_DECODER      TSS_SliderDecoder
    #endif
    #define C1_CONTROLID ((UINT8)(TSS_C1_TYPE << 4u) | 1u)
    #define C1_BUFFMASK (UINT8)(C1_BUFFMASK_BIT << 1u)
    void TSS_C1_CALLBACK(UINT8 u8ControlId);
    void C1_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 2
    #if (TSS_C2_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C2_STRUCTURE;
        TSS_KeypadContext TSS_C2_STRUCTURE_CONTEXT;
        #define C2_BUFFMASK_BIT 0u
        #define C2_BUFFLN       16u
        #define C2_DECODER      TSS_KeypadDecoder
    #elif (TSS_C2_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C2_STRUCTURE;
        TSS_SingleContext TSS_C2_STRUCTURE_CONTEXT;
        #define C2_BUFFMASK_BIT 1u
        #define C2_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C2_STRUCTURE;
        TSS_SingleContext TSS_C2_STRUCTURE_CONTEXT;
        #define C2_BUFFMASK_BIT 1u
        #define C2_DECODER      TSS_SliderDecoder
    #endif
    #define C2_CONTROLID ((UINT8)(TSS_C2_TYPE << 4u) | 2u)
    #define C2_BUFFMASK (UINT8)(C2_BUFFMASK_BIT << 2u)
    void TSS_C2_CALLBACK(UINT8 u8ControlId);
    void C2_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 3
    #if (TSS_C3_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C3_STRUCTURE;
        TSS_KeypadContext TSS_C3_STRUCTURE_CONTEXT;
        #define C3_BUFFMASK_BIT 0u
        #define C3_BUFFLN       16u
        #define C3_DECODER      TSS_KeypadDecoder
    #elif (TSS_C3_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C3_STRUCTURE;
        TSS_SingleContext    TSS_C3_STRUCTURE_CONTEXT;
        #define C3_BUFFMASK_BIT 1u
        #define C3_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C3_STRUCTURE;
        TSS_SingleContext TSS_C3_STRUCTURE_CONTEXT;
        #define C3_BUFFMASK_BIT 1u
        #define C3_DECODER      TSS_SliderDecoder
    #endif
    #define C3_CONTROLID ((UINT8)(TSS_C3_TYPE << 4u) | 3u)
    #define C3_BUFFMASK (UINT8)(C3_BUFFMASK_BIT << 3u)
    void TSS_C3_CALLBACK(UINT8 u8ControlId);
    void C3_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 4
    #if (TSS_C4_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C4_STRUCTURE;
        TSS_KeypadContext TSS_C4_STRUCTURE_CONTEXT;
        #define C4_BUFFMASK_BIT 0u
        #define C4_BUFFLN       16u
        #define C4_DECODER      TSS_KeypadDecoder
    #elif (TSS_C4_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C4_STRUCTURE;
        TSS_SingleContext    TSS_C4_STRUCTURE_CONTEXT;
        #define C4_BUFFMASK_BIT 1u
        #define C4_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C4_STRUCTURE;
        TSS_SingleContext TSS_C4_STRUCTURE_CONTEXT;
        #define C4_BUFFMASK_BIT 1u
        #define C4_DECODER      TSS_SliderDecoder
    #endif
    #define C4_CONTROLID ((UINT8)(TSS_C4_TYPE << 4u) | 4u)
    #define C4_BUFFMASK (UINT8)(C4_BUFFMASK_BIT << 4u)
    void TSS_C4_CALLBACK(UINT8 u8ControlId);
    void C4_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 5
    #if (TSS_C5_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C5_STRUCTURE;
        TSS_KeypadContext TSS_C5_STRUCTURE_CONTEXT;
        #define C5_BUFFMASK_BIT 0u
        #define C5_BUFFLN       16u
        #define C5_DECODER      TSS_KeypadDecoder
    #elif (TSS_C5_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C5_STRUCTURE;
        TSS_SingleContext    TSS_C5_STRUCTURE_CONTEXT;
        #define C5_BUFFMASK_BIT 1u
        #define C5_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C5_STRUCTURE;
        TSS_SingleContext TSS_C5_STRUCTURE_CONTEXT;
        #define C5_BUFFMASK_BIT 1u
        #define C5_DECODER      TSS_SliderDecoder
    #endif
    #define C5_CONTROLID ((UINT8)(TSS_C5_TYPE << 4u) | 5u)
    #define C5_BUFFMASK (UINT8)(C5_BUFFMASK_BIT << 5u)
    void TSS_C5_CALLBACK(UINT8 u8ControlId);
    void C5_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 6
    #if (TSS_C6_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C6_STRUCTURE;
        TSS_KeypadContext TSS_C6_STRUCTURE_CONTEXT;
        #define C6_BUFFMASK_BIT 0u
        #define C6_BUFFLN       16u
        #define C6_DECODER      TSS_KeypadDecoder
    #elif (TSS_C6_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C6_STRUCTURE;
        TSS_SingleContext    TSS_C6_STRUCTURE_CONTEXT;
        #define C6_BUFFMASK_BIT 1u
        #define C6_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C6_STRUCTURE;
        TSS_SingleContext TSS_C6_STRUCTURE_CONTEXT;
        #define C6_BUFFMASK_BIT 1u
        #define C6_DECODER      TSS_SliderDecoder
    #endif
    #define C6_CONTROLID ((UINT8)(TSS_C6_TYPE << 4u) | 6u)
    #define C6_BUFFMASK (UINT8)(C6_BUFFMASK_BIT << 6u)
    void TSS_C6_CALLBACK(UINT8 u8ControlId);
    void C6_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 7
    #if (TSS_C7_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C7_STRUCTURE;
        TSS_KeypadContext TSS_C7_STRUCTURE_CONTEXT;
        #define C7_BUFFMASK_BIT 0u
        #define C7_BUFFLN       16u
        #define C7_DECODER      TSS_KeypadDecoder
    #elif (TSS_C7_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C7_STRUCTURE;
        TSS_SingleContext    TSS_C7_STRUCTURE_CONTEXT;
        #define C7_BUFFMASK_BIT 1u
        #define C7_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C7_STRUCTURE;
        TSS_SingleContext TSS_C7_STRUCTURE_CONTEXT;
        #define C7_BUFFMASK_BIT 1u
        #define C7_DECODER      TSS_SliderDecoder
    #endif
    #define C7_CONTROLID ((UINT8)(TSS_C7_TYPE << 4u) | 7u)
    #define C7_BUFFMASK (UINT8)(C7_BUFFMASK_BIT << 7u)
    void TSS_C7_CALLBACK(UINT8 u8ControlId);
    void C7_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 8
    #if (TSS_C8_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C8_STRUCTURE;
        TSS_KeypadContext TSS_C8_STRUCTURE_CONTEXT;
        #define C8_BUFFMASK_BIT 0u
        #define C8_BUFFLN       16u
        #define C8_DECODER      TSS_KeypadDecoder
    #elif (TSS_C8_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C8_STRUCTURE;
        TSS_SingleContext    TSS_C8_STRUCTURE_CONTEXT;
        #define C8_BUFFMASK_BIT 1u
        #define C8_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C8_STRUCTURE;
        TSS_SingleContext TSS_C8_STRUCTURE_CONTEXT;
        #define C8_BUFFMASK_BIT 1u
        #define C8_DECODER      TSS_SliderDecoder
    #endif
    #define C8_CONTROLID ((UINT8)(TSS_C8_TYPE << 4u) | 8u)
    #define C8_BUFFMASK (UINT8)(C8_BUFFMASK_BIT << 0u)
    void TSS_C8_CALLBACK(UINT8 u8ControlId);
    void C8_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 9
    #if (TSS_C9_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C9_STRUCTURE;
        TSS_KeypadContext TSS_C9_STRUCTURE_CONTEXT;
        #define C9_BUFFMASK_BIT 0u
        #define C9_BUFFLN       16u
        #define C9_DECODER      TSS_KeypadDecoder
    #elif (TSS_C9_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C9_STRUCTURE;
        TSS_SingleContext    TSS_C9_STRUCTURE_CONTEXT;
        #define C9_BUFFMASK_BIT 1u
        #define C9_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C9_STRUCTURE;
        TSS_SingleContext TSS_C9_STRUCTURE_CONTEXT;
        #define C9_BUFFMASK_BIT 1u
        #define C9_DECODER      TSS_SliderDecoder
    #endif
    #define C9_CONTROLID ((UINT8)(TSS_C9_TYPE << 4u) | 9u)
    #define C9_BUFFMASK (UINT8)(C9_BUFFMASK_BIT << 1u)
    void TSS_C9_CALLBACK(UINT8 u8ControlId);
    void C9_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 10
    #if (TSS_C10_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C10_STRUCTURE;
        TSS_KeypadContext TSS_C10_STRUCTURE_CONTEXT;
        #define C10_BUFFMASK_BIT 0u
        #define C10_BUFFLN       16u
        #define C10_DECODER      TSS_KeypadDecoder
    #elif (TSS_C10_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C10_STRUCTURE;
        TSS_SingleContext    TSS_C10_STRUCTURE_CONTEXT;
        #define C10_BUFFMASK_BIT 1u
        #define C10_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C10_STRUCTURE;
        TSS_SingleContext TSS_C10_STRUCTURE_CONTEXT;
        #define C10_BUFFMASK_BIT 1u
        #define C10_DECODER      TSS_SliderDecoder
    #endif
    #define C10_CONTROLID ((UINT8)(TSS_C10_TYPE << 4u) | 10u)
    #define C10_BUFFMASK (UINT8)(C10_BUFFMASK_BIT << 2u)
    void TSS_C10_CALLBACK(UINT8 u8ControlId);
    void C10_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 11
    #if (TSS_C11_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C11_STRUCTURE;
        TSS_KeypadContext TSS_C11_STRUCTURE_CONTEXT;
        #define C11_BUFFMASK_BIT 0u
        #define C11_BUFFLN       16u
        #define C11_DECODER      TSS_KeypadDecoder
    #elif (TSS_C11_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C11_STRUCTURE;
        TSS_SingleContext    TSS_C11_STRUCTURE_CONTEXT;
        #define C11_BUFFMASK_BIT 1u
        #define C11_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C11_STRUCTURE;
        TSS_SingleContext TSS_C11_STRUCTURE_CONTEXT;
        #define C11_BUFFMASK_BIT 1u
        #define C11_DECODER      TSS_SliderDecoder
    #endif
    #define C11_CONTROLID ((UINT8)(TSS_C11_TYPE << 4u) | 11u)
    #define C11_BUFFMASK (UINT8)(C11_BUFFMASK_BIT << 3u)
    void TSS_C11_CALLBACK(UINT8 u8ControlId);
    void C11_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 12
    #if (TSS_C12_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C12_STRUCTURE;
        TSS_KeypadContext TSS_C12_STRUCTURE_CONTEXT;
        #define C12_BUFFMASK_BIT 0u
        #define C12_BUFFLN       16u
        #define C12_DECODER      TSS_KeypadDecoder
    #elif (TSS_C12_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C12_STRUCTURE;
        TSS_SingleContext    TSS_C12_STRUCTURE_CONTEXT;
        #define C12_BUFFMASK_BIT 1u
        #define C12_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C12_STRUCTURE;
        TSS_SingleContext TSS_C12_STRUCTURE_CONTEXT;
        #define C12_BUFFMASK_BIT 1u
        #define C12_DECODER      TSS_SliderDecoder
    #endif
    #define C12_CONTROLID ((UINT8)(TSS_C12_TYPE << 4u) | 12u)
    #define C12_BUFFMASK (UINT8)(C12_BUFFMASK_BIT << 4u)
    void TSS_C12_CALLBACK(UINT8 u8ControlId);
    void C12_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 13
    #if (TSS_C13_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C13_STRUCTURE;
        TSS_KeypadContext TSS_C13_STRUCTURE_CONTEXT;
        #define C13_BUFFMASK_BIT 0u
        #define C13_BUFFLN       16u
        #define C13_DECODER      TSS_KeypadDecoder
    #elif (TSS_C13_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C13_STRUCTURE;
        TSS_SingleContext    TSS_C13_STRUCTURE_CONTEXT;
        #define C13_BUFFMASK_BIT 1u
        #define C13_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C13_STRUCTURE;
        TSS_SingleContext TSS_C13_STRUCTURE_CONTEXT;
        #define C13_BUFFMASK_BIT 1u
        #define C13_DECODER      TSS_SliderDecoder
    #endif
    #define C13_CONTROLID ((UINT8)(TSS_C13_TYPE << 4u) | 13u)
    #define C13_BUFFMASK (UINT8)(C13_BUFFMASK_BIT << 5u)
    void TSS_C13_CALLBACK(UINT8 u8ControlId);
    void C13_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 14
    #if (TSS_C14_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C14_STRUCTURE;
        TSS_KeypadContext TSS_C14_STRUCTURE_CONTEXT;
        #define C14_BUFFMASK_BIT 0u
        #define C14_BUFFLN       16u
        #define C14_DECODER      TSS_KeypadDecoder
    #elif (TSS_C14_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C14_STRUCTURE;
        TSS_SingleContext    TSS_C14_STRUCTURE_CONTEXT;
        #define C14_BUFFMASK_BIT 1u
        #define C14_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C14_STRUCTURE;
        TSS_SingleContext TSS_C14_STRUCTURE_CONTEXT;
        #define C14_BUFFMASK_BIT 1u
        #define C14_DECODER      TSS_SliderDecoder
    #endif
    #define C14_CONTROLID ((UINT8)(TSS_C14_TYPE << 4u) | 14u)
    #define C14_BUFFMASK (UINT8)(C14_BUFFMASK_BIT << 6u)
    void TSS_C14_CALLBACK(UINT8 u8ControlId);
    void C14_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

#if TSS_N_CONTROLS > 15
    #if (TSS_C15_TYPE == TSS_CT_KEYPAD)
        TSS_CSKeypad TSS_C15_STRUCTURE;
        TSS_KeypadContext TSS_C15_STRUCTURE_CONTEXT;
        #define C15_BUFFMASK_BIT 0u
        #define C15_BUFFLN       16u
        #define C15_DECODER      TSS_KeypadDecoder
    #elif (TSS_C15_TYPE == TSS_CT_SLIDER)
        TSS_CSSlider TSS_C15_STRUCTURE;
        TSS_SingleContext    TSS_C15_STRUCTURE_CONTEXT;
        #define C15_BUFFMASK_BIT 1u
        #define C15_DECODER      TSS_SliderDecoder
    #else
        TSS_CSRotary TSS_C15_STRUCTURE;
        TSS_SingleContext TSS_C15_STRUCTURE_CONTEXT;
        #define C15_BUFFMASK_BIT 1u
        #define C15_DECODER      TSS_SliderDecoder
    #endif
    #define C15_CONTROLID ((UINT8)(TSS_C15_TYPE << 4u) | 15u)
    #define C15_BUFFMASK (UINT8)(C15_BUFFMASK_BIT << 7u)
    void TSS_C15_CALLBACK(UINT8 u8ControlId);
    void C15_DECODER(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

/*
 *  The section below defines all the CX_BUFFMASK elements 
 *  that have not been defined with "0"
 */

#ifndef C0_BUFFMASK
    #define C0_BUFFMASK 0u
#endif
#ifndef C1_BUFFMASK
    #define C1_BUFFMASK 0u
#endif
#ifndef C2_BUFFMASK
    #define C2_BUFFMASK 0u
#endif
#ifndef C3_BUFFMASK
    #define C3_BUFFMASK 0u
#endif
#ifndef C4_BUFFMASK
    #define C4_BUFFMASK 0u
#endif
#ifndef C5_BUFFMASK
    #define C5_BUFFMASK 0u
#endif
#ifndef C6_BUFFMASK
    #define C6_BUFFMASK 0u
#endif
#ifndef C7_BUFFMASK
    #define C7_BUFFMASK 0u
#endif
/* 8 decoders can only be represented by a Byte, if more decoders are needed another Byte must be used */
#if TSS_N_CONTROLS > 7   
    #ifndef C8_BUFFMASK                  
        #define C8_BUFFMASK 0u
    #endif
    #ifndef C9_BUFFMASK
        #define C9_BUFFMASK 0u
    #endif
    #ifndef C10_BUFFMASK
        #define C10_BUFFMASK 0u
    #endif
    #ifndef C11_BUFFMASK
        #define C11_BUFFMASK 0u
    #endif
    #ifndef C12_BUFFMASK
        #define C12_BUFFMASK 0u
    #endif
    #ifndef C13_BUFFMASK
        #define C13_BUFFMASK 0u
    #endif
    #ifndef C14_BUFFMASK
        #define C14_BUFFMASK 0u
    #endif
    #ifndef C15_BUFFMASK
        #define C15_BUFFMASK 0u
    #endif
#endif

/*
 * The section below defines an array of pointers to 
 * all the callback functions defined by the user for each decoder
 * 
 */

#if TSS_N_CONTROLS != 0
/* Pointer to Callback functions */
void (* const tss_faCallback[TSS_N_CONTROLS])(UINT8 u8ControlId) = 
{
    TSS_C0_CALLBACK,
    #if TSS_N_CONTROLS > 1
        TSS_C1_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 2
        TSS_C2_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 3
        TSS_C3_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 4
        TSS_C4_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 5
        TSS_C5_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 6
        TSS_C6_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 7
        TSS_C7_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 8
        TSS_C8_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 9
        TSS_C9_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 10
        TSS_C10_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 11
        TSS_C11_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 12
        TSS_C12_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 13
        TSS_C13_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 14
        TSS_C14_CALLBACK,
    #endif
    #if TSS_N_CONTROLS > 15
        TSS_C15_CALLBACK,
    #endif
};
#else          /* If there are no defined controlers a single element array es created */
    void (* const tss_faCallback[1])(UINT8 u8ControlId);  
#endif


/*
 * The section below declares an array of pointers with the
 * direction of all the decoders controls context structures
 * created in the sections above
 */

/* Array of pointers to decoders controls context data */ 
#if TSS_N_CONTROLS != 0
UINT8 * const tss_acpsDecContext[TSS_N_CONTROLS] = {
    (UINT8 *)&TSS_C0_STRUCTURE_CONTEXT,
    #if TSS_N_CONTROLS > 1
        (UINT8 *)&TSS_C1_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 2
        (UINT8 *)&TSS_C2_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 3
        (UINT8 *)&TSS_C3_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 4
        (UINT8 *)&TSS_C4_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 5
        (UINT8 *)&TSS_C5_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 6
        (UINT8 *)&TSS_C6_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 7
        (UINT8 *)&TSS_C7_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 8
        (UINT8 *)&TSS_C8_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 9
        (UINT8 *)&TSS_C9_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 10
        (UINT8 *)&TSS_C10_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 11
        (UINT8 *)&TSS_C11_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 12
        (UINT8 *)&TSS_C12_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 13
        (UINT8 *)&TSS_C13_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 14
        (UINT8 *)&TSS_C14_STRUCTURE_CONTEXT,
    #endif
    #if TSS_N_CONTROLS > 15
        (UINT8 *)&TSS_C15_STRUCTURE_CONTEXT,
    #endif
};
#else        /* If there are no defined controlers a single element array es created */
    UINT8 * const tss_acpsDecContext[1];
#endif

/*
 * The section below declares an array of pointers with the
 * direction of all the decoders controls system structures
 * created in the sections above
 */

#if TSS_N_CONTROLS != 0
/* Array of pointers to controls structure data */ 
const UINT8 * const tss_acpsCSStructs[TSS_N_CONTROLS] = {
    (UINT8 *)&TSS_C0_STRUCTURE,
    #if TSS_N_CONTROLS > 1
        (UINT8 *)&TSS_C1_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 2
        (UINT8 *)&TSS_C2_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 3
        (UINT8 *)&TSS_C3_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 4
        (UINT8 *)&TSS_C4_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 5
        (UINT8 *)&TSS_C5_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 6
        (UINT8 *)&TSS_C6_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 7
        (UINT8 *)&TSS_C7_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 8
        (UINT8 *)&TSS_C8_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 9
        (UINT8 *)&TSS_C9_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 10
        (UINT8 *)&TSS_C10_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 11
        (UINT8 *)&TSS_C11_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 12
        (UINT8 *)&TSS_C12_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 13
        (UINT8 *)&TSS_C13_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 14
        (UINT8 *)&TSS_C14_STRUCTURE,
    #endif
    #if TSS_N_CONTROLS > 15
        (UINT8 *)&TSS_C15_STRUCTURE,
    #endif
};
#else          /* If there are no defined controlers a single element array es created */
    const UINT8 * const tss_acpsCSStructs[1] = 
    {
        NULL
    };
#endif

/*
 * The section below declares an array with al the controls ID
 */

#if TSS_N_CONTROLS != 0
/* Array of Controls Id's declared as UINT8 */ 
const UINT8 tss_cau8CtrlIds[TSS_N_CONTROLS] = {
    C0_CONTROLID,
    #if TSS_N_CONTROLS > 1
        C1_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 2
        C2_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 3
        C3_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 4
        C4_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 5
        C5_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 6
        C6_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 7
        C7_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 8
        C8_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 9
        C9_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 10
        C10_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 11
        C11_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 12
        C12_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 13
        C13_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 14
        C14_CONTROLID,
    #endif
    #if TSS_N_CONTROLS > 15
        C15_CONTROLID,
    #endif
};
#else            /* If there are no defined controlers a single element array es created */
    const UINT8 tss_cau8CtrlIds[1] = 
    {
        0u
    };
#endif

/*
*
*
*
*/

#ifndef C0_BUFFLN
    #define C0_BUFFLN 0u
#endif
#ifndef C1_BUFFLN
    #define C1_BUFFLN 0u
#endif
#ifndef C2_BUFFLN
    #define C2_BUFFLN 0u
#endif
#ifndef C3_BUFFLN
    #define C3_BUFFLN 0u
#endif
#ifndef C4_BUFFLN
    #define C4_BUFFLN 0u
#endif
#ifndef C5_BUFFLN
    #define C5_BUFFLN 0u
#endif
#ifndef C6_BUFFLN
    #define C6_BUFFLN 0u
#endif
#ifndef C7_BUFFLN
    #define C7_BUFFLN 0u
#endif
#ifndef C8_BUFFLN
    #define C8_BUFFLN 0u
#endif
#ifndef C9_BUFFLN
    #define C9_BUFFLN 0u
#endif
#ifndef C10_BUFFLN
    #define C10_BUFFLN 0u
#endif
#ifndef C11_BUFFLN
    #define C11_BUFFLN 0u
#endif
#ifndef C12_BUFFLN
    #define C12_BUFFLN 0u
#endif
#ifndef C13_BUFFLN
    #define C13_BUFFLN 0u
#endif
#ifndef C14_BUFFLN
    #define C14_BUFFLN 0u
#endif
#ifndef C15_BUFFLN
    #define C15_BUFFLN 0u
#endif

#define BUFFLN_SUM (C0_BUFFLN + C1_BUFFLN + C2_BUFFLN + C3_BUFFLN + C4_BUFFLN + C5_BUFFLN + C6_BUFFLN + C7_BUFFLN + C8_BUFFLN + C9_BUFFLN + C10_BUFFLN + C11_BUFFLN + C12_BUFFLN + C13_BUFFLN + C14_BUFFLN + C15_BUFFLN)

#if (BUFFLN_SUM != 0u)
    UINT8 tss_au8EventsBuff[BUFFLN_SUM];
    UINT8 * const tss_pau8EventsBuff = tss_au8EventsBuff;
#else
    UINT8 * const tss_pau8EventsBuff = NULL;
#endif

/*
 * The section below determines the number of elements assigned to the defined decoders.
 * This provides information to the decoders allowing to reserve the required memory space
 *  
 */

#ifdef TSS_C0_ELECTRODES
    #if TSS_N_CONTROLS == 1
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 2
        #define N_BUFF_ELEMENTS ((UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES)
    #endif
    #if TSS_N_CONTROLS == 3
        #define N_BUFF_ELEMENTS ((UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES)
    #endif
    #if TSS_N_CONTROLS == 4
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 5
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 6
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 7
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 8
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 9
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 10
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 11
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 12
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 13
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES
        #endif
    #if TSS_N_CONTROLS == 14
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 15
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES + (UINT8)TSS_C14_ELECTRODES
    #endif
    #if TSS_N_CONTROLS == 16
        #define N_BUFF_ELEMENTS (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES + (UINT8)TSS_C14_ELECTRODES + (UINT8)TSS_C15_ELECTRODES
    #endif
#else
    #define N_BUFF_ELEMENTS 0u   /* If there are no elements assigned to any control N_BUFF_ELEMENTS is 0 */
#endif


/*
*
* The section below declares an array where strores the
* number of electrodes per decoder
*/


#if TSS_N_CONTROLS != 0
/* Sumatory of electrodes arranged by control */
const UINT8 tss_cau8GrpElecBound[TSS_N_CONTROLS] = {
    (UINT8)TSS_C0_ELECTRODES,
    #if TSS_N_CONTROLS > 1
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 2
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 3
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 4
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 5
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 6
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 7
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 8
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 9
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 10
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 11
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 12
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 13
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 14
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES + (UINT8)TSS_C14_ELECTRODES,
    #endif
    #if TSS_N_CONTROLS > 15
        (UINT8)TSS_C0_ELECTRODES + (UINT8)TSS_C1_ELECTRODES + (UINT8)TSS_C2_ELECTRODES + (UINT8)TSS_C3_ELECTRODES + (UINT8)TSS_C4_ELECTRODES + (UINT8)TSS_C5_ELECTRODES + (UINT8)TSS_C6_ELECTRODES + (UINT8)TSS_C7_ELECTRODES + (UINT8)TSS_C8_ELECTRODES + (UINT8)TSS_C9_ELECTRODES + (UINT8)TSS_C10_ELECTRODES + (UINT8)TSS_C11_ELECTRODES + (UINT8)TSS_C12_ELECTRODES + (UINT8)TSS_C13_ELECTRODES + (UINT8)TSS_C14_ELECTRODES + (UINT8)TSS_C15_ELECTRODES,
    #endif
};
#else
    const UINT8 tss_cau8GrpElecBound[1] =
    {
        (TSS_N_ELECTRODES - 1)
    };
#endif

/*
 * The section below declares an array where all the 
 * CX_BUFFER_MASK are joint into a two elemments array
 */

#if TSS_N_CONTROLS != 0
    const UINT8 tss_cau8BuffMask[(((TSS_N_CONTROLS - 1) / 8) + 1)] = 
    {
        C0_BUFFMASK | C1_BUFFMASK | C2_BUFFMASK | C3_BUFFMASK | C4_BUFFMASK | C5_BUFFMASK | C6_BUFFMASK | C7_BUFFMASK,
        #if TSS_N_CONTROLS > 8
            C8_BUFFMASK | C9_BUFFMASK | C10_BUFFMASK | C11_BUFFMASK | C12_BUFFMASK | C13_BUFFMASK | C14_BUFFMASK | C15_BUFFMASK,
        #endif
    };
#else       /* If there are no defined controlers a single element array es created */
    const UINT8 tss_cau8BuffMask[1] = 
    {
        0x00u
    };
#endif


/*
 * The section below defines an array of pointers to 
 * all the decoders functions defined above
 * 
 */

#if TSS_N_CONTROLS != 0
/* Pointer to Decoders functions */
void (* const tss_faDecoders[TSS_N_CONTROLS])(UINT8 u8CtrlNum, UINT8 *pu8Buffer) = 
{
    C0_DECODER,
    #if TSS_N_CONTROLS > 1
        C1_DECODER,
    #endif
    #if TSS_N_CONTROLS > 2
        C2_DECODER,
    #endif
    #if TSS_N_CONTROLS > 3
        C3_DECODER,
    #endif
    #if TSS_N_CONTROLS > 4
        C4_DECODER,
    #endif
    #if TSS_N_CONTROLS > 5
        C5_DECODER,
    #endif
    #if TSS_N_CONTROLS > 6
        C6_DECODER,
    #endif
    #if TSS_N_CONTROLS > 7
        C7_DECODER,
    #endif
    #if TSS_N_CONTROLS > 8
        C8_DECODER,
    #endif
    #if TSS_N_CONTROLS > 9
        C9_DECODER,
    #endif
    #if TSS_N_CONTROLS > 10
        C10_DECODER,
    #endif
    #if TSS_N_CONTROLS > 11
        C11_DECODER,
    #endif
    #if TSS_N_CONTROLS > 12
        C12_DECODER,
    #endif
    #if TSS_N_CONTROLS > 13
        C13_DECODER,
    #endif
    #if TSS_N_CONTROLS > 14
        C14_DECODER,
    #endif
    #if TSS_N_CONTROLS > 15
        C15_DECODER,
    #endif
};
#else          /* If there are no defined controlers a single element array es created */
    void (* const tss_faDecoders[1])(UINT8 u8CtrlNum, UINT8 *pu8Buffer);
#endif

/*
 * Declaration of main structures and arrays used by TSS 
 */

TSS_CSSystem tss_CSSys;
UINT8 tss_au8Sensitivity[TSS_N_ELECTRODES];
UINT8 tss_au8ElectrodeEnablers[((TSS_N_ELECTRODES - 1)/ 8) + 1];
UINT8 tss_au8ElectrodeStatus[((TSS_N_ELECTRODES - 1)/ 8) + 1];

UINT8 tss_au8ElectrodeMeasured[((TSS_N_ELECTRODES - 1)/ 8) + 1];

UINT16 tss_au16ElecBaseline[TSS_N_ELECTRODES];

/* Declaration of arrays used to store electrode behavior values */
INT8  tss_ai8CalPrevDelta[TSS_N_ELECTRODES];
UINT8 tss_au8ReleaseThreshold[TSS_N_ELECTRODES];
UINT8 tss_au8DebounceCount[TSS_N_ELECTRODES];
UINT8 tss_au8TouchCount[TSS_N_ELECTRODES];
UINT8 tss_au8ReleaseCount[TSS_N_ELECTRODES];
UINT8 tss_au8StuckCount[TSS_N_ELECTRODES];
UINT8 tss_au8ElecState[TSS_N_ELECTRODES];
UINT8 tss_au8Buffers[N_BUFF_ELEMENTS + 1u];                     /* The extra byte is because of the end of character */

/* Evaluate No of Controls */
#if TSS_N_CONTROLS != 0
    extern void TSS_ExecuteDecoders(void);

    void (* const tss_fExecuteDecoders) (void) = TSS_ExecuteDecoders;

    UINT8 tss_au8ScheduleCount[TSS_N_CONTROLS];
    UINT8 tss_au8IdleCounter[TSS_N_CONTROLS];
    UINT8 tss_au8IdleState[((TSS_N_CONTROLS - 1)/ 8) + 1];
    UINT8 tss_au8ChangeSignal[((TSS_N_CONTROLS - 1)/ 8) + 1];
    UINT8 tss_au8GrpEnablers[((TSS_N_CONTROLS - 1)/ 8) + 1];    /* Enablers for scaning */
    UINT8 tss_au8GrpState[((TSS_N_CONTROLS - 1)/ 8) + 1];       /* idle state flags */
#else
    void (* const tss_fExecuteDecoders) (void) = NULL;

    UINT8 tss_au8ScheduleCount[1];
    UINT8 tss_au8IdleCounter[1];
    UINT8 tss_au8IdleState[1];
    UINT8 tss_au8ChangeSignal[1];
    UINT8 tss_au8GrpEnablers[1];                                /* Enablers for scaning */
    UINT8 tss_au8GrpState[1];                                   /* idle state flags */
#endif

const UINT8 tss_cu8NumElecs = (UINT8)TSS_N_ELECTRODES;
const UINT8 tss_cu8NumCtrls = (UINT8)TSS_N_CONTROLS;
const UINT8 tss_cu8ElecBitFldLn = (UINT8)(((UINT8)TSS_N_ELECTRODES - 1U) / 8U) + 1U;

#if TSS_N_CONTROLS != 0
    const UINT8 tss_cu8CtrlBitFldLn = (UINT8)(((UINT8)TSS_N_CONTROLS - 1U) / 8u) + 1u;
#else
    const UINT8 tss_cu8CtrlBitFldLn = 1U;
#endif


/*
 * The section below defines separation of the functions 
 * called in low level functions according to selected low level TSS by user
 * 
 */

#if TSS_USE_IIR_FILTER
    extern void TSS_CalculateIIRFilter(UINT8 u8ElecNum);
    extern void TSS_InitIIRFilter(UINT8 u8ElecNum);
   
    void (* const tss_fCalculateIIRFilter) (UINT8 u8ElecNum) = TSS_CalculateIIRFilter;
    void (* const tss_fInitIIRFilter) (UINT8 u8ElecNum) = TSS_InitIIRFilter;
    
    UINT16 tss_au16PrevCapSample[TSS_N_ELECTRODES];
#else
    void (* const tss_fCalculateIIRFilter) (UINT8 u8ElecNum) = NULL;
    void (* const tss_fInitIIRFilter) (UINT8 u8ElecNum) = NULL;
#endif

#if TSS_USE_DELTA_LOG
    extern void TSS_FillDeltaLogBuffer(UINT8 u8ElecNum, INT8 i8Delta);
   
    void (* const tss_fFillDeltaLoglBuffer) (UINT8 u8ElecNum, INT8 i8Delta) = TSS_FillDeltaLogBuffer;

    INT8 tss_ai8InstantDelta[TSS_N_ELECTRODES];
#else
    void (* const tss_fFillDeltaLoglBuffer) (UINT8 u8ElecNum, INT8 i8Delta) = NULL;
#endif

#if TSS_USE_SIGNAL_LOG 
    extern void TSS_FillSignalLogBuffer(UINT8 u8ElecNum);
    
    void (* const tss_fFillSignalLoglBuffer) (UINT8 u8ElecNum) = TSS_FillSignalLogBuffer;
        
    UINT16 tss_au16InstantSignal[TSS_N_ELECTRODES];
#else
    void (* const tss_fFillSignalLoglBuffer) (UINT8 u8ElecNum) = NULL;
#endif

#if TSS_USE_DATA_CORRUPTION_CHECK
    extern void TSS_DataCorruptionCheck(UINT8 u8Command);
    
    void (* const tss_fDataCorruptionCheck) (UINT8 u8Command) = TSS_DataCorruptionCheck;
    
    UINT8 tss_u8ConfCheckSum;
#else
    void (* const tss_fDataCorruptionCheck) (UINT8 u8Command) = NULL;
#endif

#if TSS_USE_FREEMASTER_GUI
    extern void TSS_FmstrCall(void);
    
    void (* const tss_fFmstrCall) (void) = TSS_FmstrCall;
#else
    void (* const tss_fFmstrCall) (void) = NULL;
#endif
    
#if TSS_TRIGGER_USED
    extern UINT8 TSS_AutoTriggerConfig(UINT8 u8Parameter, UINT8 u8Value);
    
    UINT8 (* const tss_fAutoTriggerConfig) (UINT8 u8Parameter, UINT8 u8Value) = TSS_AutoTriggerConfig;
#else
    UINT8 (* const tss_fAutoTriggerConfig) (UINT8 u8Parameter, UINT8 u8Value) = NULL;
#endif

#if TSS_LOWPOWER_USED
    extern UINT8 TSS_LowPowerConfig(UINT8 u8Parameter, UINT8 u8Value);
    
    UINT8 (* const tss_fLowPowerConfig) (UINT8 u8Parameter, UINT8 u8Value) = TSS_LowPowerConfig;
#else
    UINT8 (* const tss_fLowPowerConfig) (UINT8 u8Parameter, UINT8 u8Value) = NULL;
#endif

UINT8 (* const tss_fSensorInit) (UINT8 u8Command) = TSS_SensorInit;

#ifdef TSS_ONFAULT_CALLBACK
    extern void TSS_ONFAULT_CALLBACK(void);
  
    void (* const tss_fOnFault) (void) = TSS_ONFAULT_CALLBACK;
#else 
    void (* const tss_fOnFault) (void) = NULL;
#endif
    
#ifdef TSS_ONINIT_CALLBACK
    extern void TSS_ONINIT_CALLBACK(void);
  
    void (* const tss_fOnInit) (void) = TSS_ONINIT_CALLBACK;
#else 
    extern void TSS_fOnInit(void);
    
    void (* const tss_fOnInit) (void) = TSS_fOnInit;
#endif

/***************************************************************************//*!
*
* @brief  Performs a calculation of new capacitance value by user defined 
*         IIR filter equation from the current capacitance value and 
*         previous capacitance value for a certain electrode 
*
* @param  u16CurrentCapSample - Current measured oversampled capacitance value
*         u8ElecNum - Defines electrode number
*
* @return New calculated capacitance value
*
* @remarks Array tss_au16PrevCapSample[] is used as global storage for 
*          backup of previous capacitance values. The parameter u8ElecNum of 
*          TSS_IIRFilterEquation() should be used as pointer on the currently 
*          used previous capacitance value e.g. tss_au16PrevCapSample[u8ElecNum].
*          The principle of IIR Filter is to modify u16CurrentCapSample by any 
*          weight of tss_au16PrevCapSample[u8ElecNum] and the calculated value is
*          returned to the library by the return value of TSS_IIRFilterEquation().
*          The user may edit the equation according to his requirements,
*          but he has to follow previous rules.
*          Warning: Design new equation with respect to unsigned integer value 
*                   range of variables and number of samples used by TSS.
*
****************************************************************************/
#if TSS_USE_IIR_FILTER
    UINT16 TSS_IIRFilterEquation(UINT16 u16CurrentCapSample, UINT8 u8ElecNum)
    {
      return (UINT16) ((u16CurrentCapSample + (3u * tss_au16PrevCapSample[u8ElecNum])) >> 2u);
    }
#endif




