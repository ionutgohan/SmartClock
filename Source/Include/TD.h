

#ifndef TIME_DATE_H_
#define TIME_DATE_H_

#include <stdint.h>

#define TD_TRUE              1u
#define TD_FALSE             0u

typedef enum {
  MONDAY = 0u,
  TUESDAY,
  WEDNSDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY,
  DAYS_IN_A_WEEK
} TD_WeekDaysType;

typedef enum {
  JANUARY = 0u,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER,
  MONTHS_IN_A_YEAR
} TD_MonthType;

typedef struct {
  uint8_t hour;
  uint8_t minutes;
  uint8_t seconds;
} TD_TimeType;

typedef struct {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  TD_WeekDaysType dayOfTheWeek;
} TD_DateType;


void TD_Init(void);
void TD_GetTime(TD_TimeType *pTime);
void TD_GetDate(TD_DateType *pDate);


#endif