


#include "SM.h"
#include "TD.h"
#include "DisplayM.h"


static void SM_DisplayDate(void);
static void SM_DisplayTime(void);
static void SM_DisplayTemperature(void);

static SM_StateInfoType SM_stateInfo;

void SM_Init(void)
{
  SM_stateInfo.currentState = DISPLAY_TIME;
  SM_stateInfo.stateMainHandler[DISPLAY_TIME] = SM_DisplayTime;
  SM_stateInfo.stateMainHandler[DISPLAY_DATE] = SM_DisplayDate;  
}



static void SM_DisplayDate(void)
{
  TD_DateType currentDate;
  char stringBuffer[8];
  
  TD_GetDate(&currentDate);
  
  stringBuffer[0] = currentDate.day / 10 + '0';
  stringBuffer[1] = currentDate.day % 10 + '0';
  
  stringBuffer[3] = currentDate.month / 10 + '0';
  stringBuffer[4] = currentDate.month % 10 + '0';
  
  stringBuffer[6] = currentDate.year / 10 + '0';
  stringBuffer[7] = currentDate.year % 10 + '0';
  
  stringBuffer[2] = stringBuffer[5] = '.';
  
  DispM_PrintString(stringBuffer, 5);
}

static void SM_DisplayTime(void)
{
  TD_TimeType currentTime;
  char stringBuffer[8];
  
  TD_GetTime(&currentTime);
  
  stringBuffer[0] = currentTime.hour / 10 + '0';
  stringBuffer[1] = currentTime.hour % 10 + '0';
  
  stringBuffer[3] = currentTime.minutes / 10 + '0';
  stringBuffer[4] = currentTime.minutes % 10 + '0';
  
  stringBuffer[6] = currentTime.seconds / 10 + '0';
  stringBuffer[7] = currentTime.seconds % 10 + '0';
  
  stringBuffer[2] = stringBuffer[5] = '.';
  
  DispM_PrintString(stringBuffer, 5);
}

static void SM_DisplayTemperature(void)
{
  
}