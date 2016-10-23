
#ifndef SM_H_
#define SM_H_

typedef enum {
  DISPLAY_TIME = 0,
  DISPLAY_DATE,
  DISPLAY_TEMP,
  SET_TIME,
  SET_DATE,
  SM_TOTAL_STATES
} SM_StateType;

typedef struct {
  SM_StateType currentState;
  void (*stateMainHandler[SM_TOTAL_STATES])(void);
} SM_StateInfoType;

void SM_Init(void);


#endif