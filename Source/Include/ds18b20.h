
#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <stdint.h>

#define INVALID_TEMP	0xFFFF

#define DS_DATA_PORT       (GPIOA_PDDR)
#define DS_DATA_CTRL_REG   (PORTA_PCR10)
#define DS_DATA_PIN        (1u << 10u)
#define DS_DATA_SET_REG    (GPIOA_PSOR)
#define DS_DATA_CLEAR_REG  (GPIOA_PCOR)
#define DS_DATA_READ_REG   (GPIOA_PDIR)


void DS_Init(void);
void DS_Reset(void);
void DS_ResetCommunication(void);
void DS_WriteCommand(uint8_t command);
uint8_t DS_Read(void);
void DS_ReadROM(uint8_t *data);
int16_t DS_ReadTemp(void);
int16_t DS_GetTemperature();
void DS_GetStringTemperature(uint8_t *pTemp);


#endif
