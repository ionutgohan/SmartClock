
#include "MK40X256VMD100.h"
#include "ds18b20.h"
#include "OS.h"


#define Us_CyclesNr	30u
#define DS_Delay3Us()	DS_DelayCycles(3 * Us_CyclesNr)
#define DS_Delay9Us()	DS_DelayCycles(9 * Us_CyclesNr)
#define DS_Delay10Us()	DS_DelayCycles(10 * Us_CyclesNr)
#define DS_Delay50Us()	DS_DelayCycles(50 * Us_CyclesNr)
#define DS_Delay60Us()	DS_DelayCycles(60 * Us_CyclesNr)

static uint32_t DS_sensorOff;

static void DS_DelayCycles(uint32_t nr_cycles)
{
	while (--nr_cycles);
}

void DS_Init(void)
{
  
  /* enable clock for PORTA */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
  
  DS_DATA_CTRL_REG = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
  
}



void DS_Reset(void)
{
  uint8_t i;
  /* set pin as output */
  DS_DATA_PORT |= DS_DATA_PIN;
  /* reset pin */
  DS_DATA_CLEAR_REG |= DS_DATA_PIN;
  
  for(i = 0; i < 55; i++){
    DS_Delay10Us();
  }
}

void DS_ResetCommunication()
{
  uint8_t i;
  
  
  /* set pin as output */
  DS_DATA_PORT |= DS_DATA_PIN;
  
  
  /* reset pin */
  DS_DATA_CLEAR_REG |= DS_DATA_PIN;
  
  ///delay 480 us
  for(i = 0; i < 48; i++) {
    DS_Delay10Us();
  }
  
  /* set pin as input */
  DS_DATA_PORT &= ~DS_DATA_PIN;
  
  DS_Delay60Us();
  
  /* read pin's value */
  DS_sensorOff = DS_DATA_READ_REG & DS_DATA_PIN; 
  
  //delay 480 us
  for(i = 0; i < 48 ; i++) {
    DS_Delay10Us();
  }
}

void DS_WriteCommand(uint8_t command)
{
  uint8_t i;
  for(i = 0;i < 8; i++)
  {
    /* set pin as output */
    DS_DATA_PORT |= DS_DATA_PIN;
    /* reset pin */
    DS_DATA_CLEAR_REG |= DS_DATA_PIN;
    
    DS_Delay10Us();
    
    if(command & 0x01){
      /* set pin as input */
      DS_DATA_PORT &= ~DS_DATA_PIN;
    }
    
    DS_Delay50Us();
    /* set pin as input */
    DS_DATA_PORT &= ~DS_DATA_PIN;
    DS_Delay10Us();
    command >>= 1;
  }
  DS_Delay10Us();
}

uint8_t DS_Read()
{
  uint8_t i;
  uint8_t data = 0;
  
  for(i = 0; i < 8; i++)
  {
    /* set pin as output */
    DS_DATA_PORT |= DS_DATA_PIN;
    /* reset pin */
    DS_DATA_CLEAR_REG |= DS_DATA_PIN;
    
    DS_Delay3Us();
    /* set pin as input */
    DS_DATA_PORT &= ~DS_DATA_PIN;
    
    DS_Delay9Us();
    
    data >>= 1;
    
    /* read pin value */
    if((DS_DATA_READ_REG & DS_DATA_PIN) != 0u){
      data |= 0x80;
    }
    
    DS_Delay60Us();
  }
  DS_Delay10Us();
  
  return data;
}

void DS_ReadROM(uint8_t *data)
{
  uint8_t i;
  DS_WriteCommand(0x33);
  for(i= 0 ;i < 8; i++)
  {
    *data = DS_Read();
    data++;
  }
}

int16_t DS_ReadTemp()
{
  uint8_t i;
  uint8_t data;
  volatile uint8_t crc;
  uint8_t memData[8];
  uint16_t temp;
  
  DS_ResetCommunication();
  if(DS_sensorOff){
    return -1;
  }
  
  DS_WriteCommand(0xCC);//Skip ROM command
  DS_WriteCommand(0x44);//start conversion command
  
  while(1)
  {
    /* set pin as output */
    DS_DATA_PORT |= DS_DATA_PIN;
    /* reset pin */
    DS_DATA_CLEAR_REG |= DS_DATA_PIN;
    
    DS_Delay3Us();
    
    /* set pin as input */
    DS_DATA_PORT &= ~DS_DATA_PIN;
    
    DS_Delay9Us();
    
    data = DS_DATA_READ_REG & DS_DATA_PIN;//read pin value
    DS_Delay50Us();
    
    if(data){
      break;
    }
    DS_Delay10Us();
  }
  
  /////temperature read////
  DS_ResetCommunication();
  if(DS_sensorOff){
    return -1;
  }
  DS_WriteCommand(0xCC);
  DS_WriteCommand(0xBE);
  for(i = 0; i < 8; i++){
    memData[i] = DS_Read();
  }
  crc = DS_Read();
  temp = ((uint16_t)memData[1] << 8) + memData[0];
  
  return temp;
  
}

int16_t DS_GetTemperature()
{
  int32_t temp;
  int16_t temperature;
  temperature = DS_ReadTemp();
  if(temperature == -1){
    return INVALID_TEMP;
  } else if(temperature & 0xf000){//negative temperature
    temp = -1;
    temperature = (temperature ^ 0xffff) + 1;
  } else temp = 1;
  
  temp *= (int32_t)temperature * 625;
  temperature = (int16_t)(temp/100);
  
  return temperature;
}

//store in pTemp the temperature such as "sxx.xx C",where s is the sign
void DS_GetStringTemperature(uint8_t *pTemp)
{
  int16_t temperature;
  uint32_t temp;
  
  temperature = DS_ReadTemp();
  
  if(temperature == -1){
    *pTemp = 250;
  }
  else {
    if(temperature & 0xf000){// negative temperature
      *pTemp = '-';
      temperature = (temperature ^ 0xffff) + 1;
    }
    else
      *pTemp = '+';
    
    pTemp++;
    temp = (uint32_t)temperature * 625;
    temperature = (uint16_t)(temp/100);
    
    *pTemp++ = (temperature/1000) + '0';
    temperature = temperature % 1000;
    *pTemp++ = (temperature/100) + '0';
    temperature = temperature % 100;
    *pTemp++ = '.';
    *pTemp++ = (temperature/10) + '0';
    *pTemp++ = (temperature%10) + '0';
    *pTemp++ = ' ';
    *pTemp++ = 'C';
    
  }
}


int16_t temperature;
void DS_MainTask(void *params)
{
  
  while (1) {
    
    
    temperature = DS_GetTemperature();
    
    Task_Delay(5);    
    
  }
}
