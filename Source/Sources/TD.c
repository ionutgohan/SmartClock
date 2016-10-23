

#include "TD.h"
#include "OS.h"
#include "DisplayM.h"


static TD_TimeType TD_currentTime;
static TD_DateType TD_currentDate;
static uint8_t TD_ui1ChangeDay;

static const uint8_t TD_daysInAMonth[MONTHS_IN_A_YEAR] = {31 , 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static void TD_UpdateTime(void);
static void TD_UpdateDate(void);

void TD_Init(void)
{
  TD_currentDate.day = 28;
  TD_currentDate.month = FEBRUARY;
  TD_currentDate.year = 2016;
  TD_currentDate.dayOfTheWeek = SUNDAY;
  
  TD_currentTime.hour = 23;
  TD_currentTime.minutes = 59;
  TD_currentTime.seconds = 55;
  
  TD_ui1ChangeDay = TD_FALSE;
}

void TD_MainTask(void *params)
{
  static uint8_t ui8TaskCnt = 0u;
  
  while (1) {
    
  ui8TaskCnt++;
  if (ui8TaskCnt == 2u) {
    TD_UpdateTime();
    TD_UpdateDate();
    DispM_PrintString("9876543210123456789", 5);
    ui8TaskCnt = 0u;
  }  
  
  Task_Delay(500);    
    
  }
}

static void TD_UpdateTime(void)
{
  TD_currentTime.seconds++;
  if (TD_currentTime.seconds == 60u) {
    TD_currentTime.seconds = 0u;
    TD_currentTime.minutes++;
    if (TD_currentTime.minutes == 60u) {
      TD_currentTime.minutes = 0u;
      TD_currentTime.hour++;
      if (TD_currentTime.hour == 24u) {
        TD_currentTime.hour = 0u;
        TD_ui1ChangeDay = TD_TRUE;
      }
    }
  }
}
static void TD_UpdateDate(void)
{
  uint8_t ui1LeapYear = TD_FALSE;
  
  if (((TD_currentDate.year % 4u == 0u) && (TD_currentDate.year % 100u != 0u)) || \
      ((TD_currentDate.year % 4u == 0u) && (TD_currentDate.year % 100u == 0u) && (TD_currentDate.year % 400u == 0u))) {
    ui1LeapYear = TD_TRUE;
  }
  
  if (TD_ui1ChangeDay == TD_TRUE) {
    TD_ui1ChangeDay = TD_FALSE;
    
    TD_currentDate.dayOfTheWeek++;
    if (TD_currentDate.dayOfTheWeek > SUNDAY) {
      TD_currentDate.dayOfTheWeek = MONDAY;
    }
    
    TD_currentDate.day++;
    if (TD_currentDate.day > TD_daysInAMonth[TD_currentDate.month]) {
      if ((TD_currentDate.month != FEBRUARY) || (ui1LeapYear == TD_FALSE) || (TD_currentDate.day > 29u)) {
        TD_currentDate.day = 1u;        
        TD_currentDate.month++;
      }
      if (TD_currentDate.month > DECEMBER) {
        TD_currentDate.month = JANUARY;
        TD_currentDate.year++;
      }
    }
  }
}


void TD_GetTime(TD_TimeType *pTime)
{
  pTime->hour = TD_currentTime.hour;
  pTime->minutes = TD_currentTime.minutes;
  pTime->seconds = TD_currentTime.seconds;  
}

void TD_GetDate(TD_DateType *pDate)
{
  pDate->day = TD_currentDate.day;
  pDate->month = TD_currentDate.month;
  pDate->year = TD_currentDate.year;
  pDate->dayOfTheWeek = TD_currentDate.dayOfTheWeek;
}