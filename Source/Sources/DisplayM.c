

#include "DisplayM.h"
#include "Driver_SLCD.h"
#include "string.h"
#include "OS.h"

#define DISPM_TRUE                      TRUE
#define DISPM_FALSE                     FALSE

#define DISPM_FIRST_PIXEL_X             1u
#define DISPM_FIRST_PIXEL_Y             1u

#define DISPM_SMALL_STRING              1u
#define DISPM_BIG_STRING                2u

#define DISPM_INTER_STRING_SPACES       5u
#define DISPM_MAX_STRING_LEN            20u
#define DISPM_GLOBAL_BUFFER_SIZE        (DISPM_MAX_STRING_LEN + DISPM_INTER_STRING_SPACES)


#define DISPM_MAX_ROW_CHRS              10u
#define DISPM_CHAR_WIDTH                3u
#define DISPM_CHAR_HEIGHT               5u
#define DISPM_LCD_MAX_ROWS              8u

#define DISPM_DYNAMIC_DISP_INC          5u

typedef struct {
  uint32_t usedBufferSize;
  uint8_t stringType;
  uint8_t newStringAvailable;
  uint8_t currentPriority;
  uint8_t delayDisplay;
  uint8_t originalStringLen;
} DispM_InfoType;

static uint8_t DispM_aui8UnalteredStringBuffer[CHAR_SIZE * DISPM_MAX_STRING_LEN];
static uint8_t DispM_aui8GlobalStringBuffer[CHAR_SIZE * DISPM_GLOBAL_BUFFER_SIZE];
static uint8_t *DispM_pDisplayBuffer;
static DispM_StateType DispM_state;
static DispM_InfoType DispM_info;


static uint32_t DispM_Strlen(char * pString);
static void DispM_UpdateBaseDisplayBuffer(char *pString);
static void DispM_IdleState(void);
static void DispM_UpdateDisplayBuffer(void);
static void DispM_DisplayBuffer(void);
static void DispM_DisplayNormal(void);
static void DispM_Error(void);
uint8_t DispM_SetDisplay(uint8_t *buffer, uint8_t pixelX, uint8_t pixelY);


void DispM_Init(void)
{    
  _SLCDModule_Init();
  DispM_pDisplayBuffer = DispM_aui8GlobalStringBuffer;
  DispM_state.currentState = DISPM_IDLE;
  DispM_state.pDoState[DISPM_IDLE] = DispM_IdleState;
  DispM_state.pDoState[DISPM_UPDATE_DISPLAY_BUFFER] = DispM_UpdateDisplayBuffer;
  DispM_state.pDoState[DISPM_DISPLAY_BUFFER] = DispM_DisplayBuffer;
  DispM_state.pDoState[DISPM_DISPLAY_NORMAL] = DispM_DisplayNormal;
  DispM_state.pDoState[DISPM_ERROR] = DispM_Error;
  
  DispM_info.usedBufferSize = 0u;
  DispM_info.currentPriority = 100u;
  DispM_info.stringType = DISPM_SMALL_STRING;
  DispM_info.newStringAvailable = DISPM_FALSE;
  DispM_info.delayDisplay = DISPM_FALSE;
  
}

static uint32_t DispM_Strlen(char * pString)
{
  uint32_t chrCnt = 0;
  while (*pString++ != '\0') {
    chrCnt++;
  }
  
  return chrCnt;
}

void DispM_MainTask(void *params)
{
  while (1) {
    if (DispM_info.stringType != DISPM_SMALL_STRING) {
      DispM_state.pDoState[DispM_state.currentState](); 
    }
    Task_Delay(500);    
    
  }
}

static void DispM_UpdateBaseDisplayBuffer(char *pString)
{
  uint32_t rowIdx;
  uint32_t colIdx;
  uint32_t stringIdx;
  uint8_t *pBuffer;
  uint8_t const  *pCurrentChr;
  
  
  
  /* clear the display buffer */
  for (rowIdx = 0u; rowIdx < (CHAR_SIZE * DISPM_MAX_STRING_LEN); rowIdx++) {
    DispM_aui8UnalteredStringBuffer[rowIdx] = 0u;
  }
  
  
  pBuffer = DispM_aui8UnalteredStringBuffer;  
  
  for (stringIdx = 0u; stringIdx < DispM_info.originalStringLen; stringIdx++) {
    pCurrentChr = Fonts[pString[stringIdx] - 0x30 + 0x10];
    for (colIdx = 0u; colIdx < (DISPM_CHAR_WIDTH); colIdx++) {
      for (rowIdx = 0u; rowIdx < DISPM_CHAR_HEIGHT; rowIdx++) {
        *pBuffer++ = pCurrentChr[rowIdx * DISPM_CHAR_WIDTH + colIdx];
      }
    }
  }
  
}


static uint8_t DispM_SetDisplay(uint8_t *buffer, uint8_t pixelX, uint8_t pixelY)
{
  uint8_t row, column;
  
  if (pixelX > (DISPM_LCD_MAX_ROWS - DISPM_CHAR_HEIGHT)) {
    return DISPM_INCORRECT_ROW;
  }
  
  if (pixelY > (CHAR_MAX_POSITION_VALUE - DISPM_CHAR_WIDTH)) {
    return DISPM_INCORRECT_COLUMN;
  }
  
  if (buffer == _NULL) {
    return DISPM_INCORRECT_BUFFER;
  }
  
  
  for (column = pixelY; column < CHAR_MAX_POSITION_VALUE; column++) {
    for (row = pixelX; row < (pixelX + DISPM_CHAR_HEIGHT); row++) {
      if (buffer[(column - pixelY) * DISPM_CHAR_HEIGHT + (row - pixelX)]) {
        _SLCDModule_SetSegment(column, row);
      } else {
        _SLCDModule_ClearSegment(column, row);
      }
    }
  }
  
  return DISPM_OK;
}


static void DispM_IdleState(void)
{
  
}

static void DispM_UpdateDisplayBuffer(void)
{
  uint32_t idx;
  
  for (idx = 0u; idx < (CHAR_SIZE * DISPM_MAX_STRING_LEN); idx++) {
    DispM_aui8GlobalStringBuffer[idx] = DispM_aui8UnalteredStringBuffer[idx];
  }
  
  DispM_info.usedBufferSize = DispM_info.originalStringLen * CHAR_SIZE;
  
  if (DispM_info.stringType == DISPM_BIG_STRING) {
    for (idx = (CHAR_SIZE * DISPM_MAX_STRING_LEN); idx < (CHAR_SIZE * DISPM_GLOBAL_BUFFER_SIZE); idx++) {
      DispM_aui8GlobalStringBuffer[idx] = 0u;
    }
    
  DispM_info.usedBufferSize += DISPM_INTER_STRING_SPACES * CHAR_SIZE;
  }
  
  DispM_info.delayDisplay = DISPM_FALSE;
  
  DispM_pDisplayBuffer = DispM_aui8GlobalStringBuffer;
  
  DispM_state.currentState = DISPM_DISPLAY_BUFFER;
}

static void DispM_DisplayBuffer(void)
{
  uint32_t currentRemainder;
  uint8_t tempBuffer[CHAR_MAX_POSITION_VALUE * DISPM_CHAR_HEIGHT];
  
  
  currentRemainder = (DispM_aui8GlobalStringBuffer + DispM_info.usedBufferSize) - DispM_pDisplayBuffer;
  
  if (currentRemainder < sizeof(tempBuffer) ) {
    memcpy(tempBuffer, DispM_pDisplayBuffer, currentRemainder);
    
    memcpy(tempBuffer + currentRemainder, DispM_aui8UnalteredStringBuffer, sizeof(tempBuffer) - currentRemainder);
    DispM_SetDisplay(tempBuffer, DISPM_FIRST_PIXEL_X, DISPM_FIRST_PIXEL_Y);
  } else {
    DispM_SetDisplay(DispM_pDisplayBuffer, DISPM_FIRST_PIXEL_X, DISPM_FIRST_PIXEL_Y);
  }
  
  DispM_pDisplayBuffer += DISPM_DYNAMIC_DISP_INC;
  
  if ((DispM_pDisplayBuffer - DispM_aui8GlobalStringBuffer) >= DispM_info.usedBufferSize) {
    DispM_pDisplayBuffer = DispM_aui8GlobalStringBuffer;
    if (DispM_info.delayDisplay == DISPM_TRUE) {
      DispM_state.currentState = DISPM_UPDATE_DISPLAY_BUFFER;
    }
  }
}


static void DispM_DisplayNormal(void)
{
  _SLCDModule_PrintString((char*)DispM_pDisplayBuffer, 0);
}

static void DispM_Error(void)
{
  _SLCDModule_ClearLCD(0);
}

void DispM_PrintString(char *pString, uint8_t priority)
{
  DispM_info.originalStringLen = DispM_Strlen(pString);
  if (DispM_info.originalStringLen > DISPM_MAX_ROW_CHRS) {
    DispM_UpdateBaseDisplayBuffer(pString);    
    DispM_info.stringType = DISPM_BIG_STRING;
    if (priority < DispM_info.currentPriority) {
      /* 0 is the highest priority */
      DispM_state.currentState = DISPM_UPDATE_DISPLAY_BUFFER;
    } else {
      DispM_info.delayDisplay = DISPM_TRUE;
    }
  } else if (priority < DispM_info.currentPriority) {
    DispM_info.stringType = DISPM_SMALL_STRING;
    _SLCDModule_ClearLCD(0);
    _SLCDModule_PrintString(pString, 0);
  } else {    
    DispM_state.currentState = DISPM_DISPLAY_NORMAL;
  }
  
  DispM_info.newStringAvailable = DISPM_TRUE;
  DispM_info.currentPriority = priority;
  
}