
#include "TSS.h"
#include "Driver_Electrodes.h"
#include "Task.h"
#include "SM.h"

#define TSS_TRUE        1u
#define TSS_FALSE       0u

#define TSS_CYCLIC_DELAY        5u       /* in ms */
#define TSS_SHORT_PRESS_THR     60u  
#define TSS_LONG_PRESS_THR      500u 

enum {
  TSS_ELECTRODE0 = 0,
  TSS_ELECTRODE1,
  TSS_ELECTRODE2,
  TSS_ELECTRODE3,
  TSS_ELECTRODE4,
  TSS_ELECTRODE5,
  TSS_NO_OF_ELECTRODES
};
  
typedef struct {
  uint8_t oldState;
  uint8_t currentState;
  uint8_t stateChanged;
} TSS_ElectrodeStateType;

static void TSS_CheckElectrodeXState(uint32_t electrode, TSS_ElectrodeStateType *pElectrodeState);

static TSS_ElectrodeStateType TSS_electrode0State;
static TSS_ElectrodeStateType TSS_electrode1State;
static TSS_ElectrodeStateType TSS_electrode2State;
static TSS_ElectrodeStateType TSS_electrode3State;
static TSS_ElectrodeStateType TSS_electrode4State;
static TSS_ElectrodeStateType TSS_electrode5State;

void TSS_InitTSS(void)
{
  _Electrodes_Init();
  
  TSS_electrode0State.oldState = TSS_electrode0State.currentState = TSS_NOT_PRESSED;
  TSS_electrode1State.oldState = TSS_electrode1State.currentState = TSS_NOT_PRESSED;
  TSS_electrode2State.oldState = TSS_electrode2State.currentState = TSS_NOT_PRESSED;
  TSS_electrode3State.oldState = TSS_electrode3State.currentState = TSS_NOT_PRESSED;
  TSS_electrode4State.oldState = TSS_electrode4State.currentState = TSS_NOT_PRESSED;
  TSS_electrode5State.oldState = TSS_electrode5State.currentState = TSS_NOT_PRESSED;
}

static void TSS_CheckElectrodeXState(uint32_t electrode, TSS_ElectrodeStateType *pElectrodeState)
{
  static uint32_t touchCnt[TSS_NO_OF_ELECTRODES] = {0u};
  static uint8_t previousElectrodeState[TSS_NO_OF_ELECTRODES] = {0u};
  uint8_t electrodeState = 0u;
  
  pElectrodeState->oldState = pElectrodeState->currentState;
  pElectrodeState->currentState = TSS_NOT_PRESSED;
  electrodeState = (ElectrodeFlags & (1u << electrode)) && TSS_TRUE;
  
  if (electrodeState != previousElectrodeState[electrode]) {
    touchCnt[electrode] = 0u;
  } else {    
    touchCnt[electrode] += TSS_CYCLIC_DELAY;
    if (electrodeState) {
      if (touchCnt[electrode] >= TSS_SHORT_PRESS_THR) {
        pElectrodeState->currentState = TSS_SHORT_PRESS;
      }  
      if (touchCnt[electrode] >= TSS_LONG_PRESS_THR) {
        pElectrodeState->currentState = TSS_LONG_PRESS;
      }             
    }
  }
  previousElectrodeState[electrode] = electrodeState;
  
  if (pElectrodeState->currentState == pElectrodeState->oldState) {
    pElectrodeState->stateChanged = TSS_FALSE;
  } else {
    pElectrodeState->stateChanged = TSS_TRUE;
  }  
 
}

uint8_t DispCnt;

void TSS_MainTask(void *params)
{
  
  while (1) {
    
    TSS_Task();    
    
    TSS_CheckElectrodeXState(TSS_ELECTRODE0, &TSS_electrode0State);
    TSS_CheckElectrodeXState(TSS_ELECTRODE1, &TSS_electrode1State);
    TSS_CheckElectrodeXState(TSS_ELECTRODE2, &TSS_electrode2State);
    TSS_CheckElectrodeXState(TSS_ELECTRODE3, &TSS_electrode3State);
    TSS_CheckElectrodeXState(TSS_ELECTRODE4, &TSS_electrode4State);
    TSS_CheckElectrodeXState(TSS_ELECTRODE5, &TSS_electrode5State);
    
    if ((TSS_electrode0State.stateChanged == TSS_TRUE) && (TSS_electrode0State.currentState == TSS_SHORT_PRESS)) {
      //SM_RequestNextState();
        DispCnt++;
        if (DispCnt > 9u) {
          DispCnt = 0u;
        }
    } else if (TSS_electrode1State.stateChanged == TSS_TRUE) {
      SM_RequestPreviousState();
    }
    Task_Delay(TSS_CYCLIC_DELAY);
  }
}