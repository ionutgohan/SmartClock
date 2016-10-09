
#ifndef DISPLAYM_H_
#define DISPLAYM_H_


#include <stdint.h>


#define DISPM_OK                0u
#define DISPM_INCORRECT_ROW     1u
#define DISPM_INCORRECT_COLUMN  2u
#define DISPM_INCORRECT_BUFFER  3u

typedef enum {
  DISPM_IDLE = 0,
  DISPM_UPDATE_DISPLAY_BUFFER,
  DISPM_DISPLAY_BUFFER,
  DISPM_DISPLAY_NORMAL,
  DISPM_ERROR,
  DISPM_NO_OF_STATES
} DispM_ActualStateType;

typedef struct {
  DispM_ActualStateType currentState;
  void (*pDoState[DISPM_NO_OF_STATES])(void);
} DispM_StateType;


void DispM_Init(void);
void DispM_PrintString(char *pString, uint8_t priority);

#endif