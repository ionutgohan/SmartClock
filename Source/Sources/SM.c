


#include "SM.h"
#include "TD.h"
#include "DisplayM.h"
#include "Task.h"


static void SM_DisplayTest(void);
static void SM_DisplayDate(void);
static void SM_DisplayTime(void);
static void SM_DisplayTemperature(void);
static void SM_SetDate(void);
static void SM_SetTime(void);

static SM_StateInfoType SM_stateInfo;

void SM_Init(void)
{
  SM_stateInfo.currentState = DISPLAY_TEST;
  SM_stateInfo.stateMainHandler[DISPLAY_TEST] = SM_DisplayTest;
  SM_stateInfo.stateMainHandler[DISPLAY_TIME] = SM_DisplayTime;
  SM_stateInfo.stateMainHandler[DISPLAY_DATE] = SM_DisplayDate; 
  SM_stateInfo.stateMainHandler[DISPLAY_TEMP] = SM_DisplayTemperature;   
  SM_stateInfo.stateMainHandler[SET_TIME] = SM_SetTime;  
  SM_stateInfo.stateMainHandler[SET_DATE] = SM_SetDate;
}

extern uint8_t DispCnt;
static void SM_DisplayTest(void)
{  
  char stringBuffer;
  
  stringBuffer = DispCnt + '0';
  
  DispM_PrintString(&stringBuffer, 1);
}



static void SM_DisplayDate(void)
{
  TD_DateType currentDate;
  char stringBuffer[9];
  
  TD_GetDate(&currentDate);
  
  stringBuffer[0] = currentDate.day / 10 + '0';
  stringBuffer[1] = currentDate.day % 10 + '0';
  
  stringBuffer[3] = currentDate.month / 10 + '0';
  stringBuffer[4] = currentDate.month % 10 + '0';
  
  stringBuffer[6] = (currentDate.year / 10) % 10 + '0';
  stringBuffer[7] = currentDate.year % 10 + '0';
  
  stringBuffer[2] = stringBuffer[5] = '.';
  
  stringBuffer[8] = '\0';
  
  DispM_PrintString(stringBuffer, 5);
}

static void SM_DisplayTime(void)
{
  TD_TimeType currentTime;
  char stringBuffer[9];
  
  TD_GetTime(&currentTime);
  
  stringBuffer[0] = currentTime.hour / 10 + '0';
  stringBuffer[1] = currentTime.hour % 10 + '0';
  
  stringBuffer[3] = currentTime.minutes / 10 + '0';
  stringBuffer[4] = currentTime.minutes % 10 + '0';
  
  stringBuffer[6] = currentTime.seconds / 10 + '0';
  stringBuffer[7] = currentTime.seconds % 10 + '0';
  
  stringBuffer[2] = stringBuffer[5] = ':';
  
  stringBuffer[8] = '\0';
  
  DispM_PrintString(stringBuffer, 5);
}

static void SM_DisplayTemperature(void)
{
    DispM_PrintString("12345678987654",5);
}


static void SM_SetDate(void)
{

}


static void SM_SetTime(void)
{

}

void SM_RequestNextState(void)
{
  if (SM_stateInfo.currentState < (SM_TOTAL_STATES - 1)) {
    SM_stateInfo.currentState++;
  }
}

void SM_RequestPreviousState(void)
{  
  if (SM_stateInfo.currentState > DISPLAY_TIME) {
    SM_stateInfo.currentState--;
  }
}



void SM_MainTask(void *params) 
{
  while (1) {
    SM_stateInfo.stateMainHandler[SM_stateInfo.currentState]();
    
    Task_Delay(50);    
  }
}