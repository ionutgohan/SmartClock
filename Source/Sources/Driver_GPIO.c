#include "Driver_GPIO.h"

/**
  Function Name	: _GPIO_Init
  Engineer      : Manglio González Carrasco
  Date          : 05/01/2011
  
  Parameters	: U08 Port, U08 Bit
  Returns       : Nothing
  Notes         : This function configures the port pin as a GPIO. Pull-ups are not enabled, thus
                  the pin will behave as an output.
*/
void _GPIO_Init(U08 Port, U08 Bit)
{
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
  switch (Port)
  {
    case PORTA:
      PORT_PCR_REG(PORTA_BASE_PTR, Bit) = PORT_PCR_MUX(1); 
      break;
    case PORTB:
      PORT_PCR_REG(PORTB_BASE_PTR, Bit) = PORT_PCR_MUX(1); 
      break;
    case PORTC:
      PORT_PCR_REG(PORTC_BASE_PTR, Bit) = PORT_PCR_MUX(1); 
      break;
    case PORTD:
      PORT_PCR_REG(PORTD_BASE_PTR, Bit) = PORT_PCR_MUX(1); 
      break;
    case PORTE:
      PORT_PCR_REG(PORTE_BASE_PTR, Bit) = PORT_PCR_MUX(1);  
      break;
    default:
      break;  
  }
}

/**
  Function Name	: _GPIO_Set_Pin
  Engineer      : Manglio González Carrasco
  Date          : 05/01/2011
  
  Parameters	: U08 Port, U08 Bit
  Returns       : Nothing
  Notes         : This function sets the given port pin.
*/
void _GPIO_Set_Pin(U08 Port, U08 Bit)
{ 
  switch (Port)
  {
    case PORTA:
      GPIOA_PSOR |= (1ul << Bit);
      GPIOA_PDDR |= (1ul << Bit);  
      GPIOA_PCOR &= ~(1ul << Bit);
      break;
    case PORTB:
      GPIOB_PSOR |= (1ul << Bit);
      GPIOB_PDDR |= (1ul << Bit);  
      GPIOB_PCOR &= ~(1ul << Bit);      
      break;
    case PORTC:
      GPIOC_PSOR |= (1ul << Bit);
      GPIOC_PDDR |= (1ul << Bit); 
      GPIOC_PCOR &= ~(1ul << Bit);      
      break;
    case PORTD:
      GPIOD_PSOR |= (1ul << Bit);
      GPIOD_PDDR |= (1ul << Bit); 
      GPIOD_PCOR &= ~(1ul << Bit);      
      break;
    case PORTE:
      GPIOE_PSOR |= (1ul << Bit);
      GPIOE_PDDR |= (1ul << Bit);  
      break;
    default:
      break;  
  }
}

/**
  Function Name	: _GPIO_Clear_Pin
  Engineer      : Manglio González Carrasco
  Date          : 05/01/2011
  
  Parameters	: U08 Port, U08 Bit
  Returns       : Nothing
  Notes         : This function clears the given port pin.
*/
void _GPIO_Clear_Pin(U08 Port, U08 Bit)
{
    switch (Port)
  {
    case PORTA:
      GPIOA_PCOR |= (1ul << Bit);
      GPIOA_PSOR &= ~(1ul << Bit);
      break;
    case PORTB:
      GPIOB_PCOR |= (1ul << Bit);
      GPIOB_PSOR &= ~(1ul << Bit);
      break;
    case PORTC:
      GPIOC_PCOR |= (1ul << Bit);
      GPIOC_PSOR &= ~(1ul << Bit);
      break;
    case PORTD:
      GPIOD_PCOR |= (1ul << Bit);
      GPIOD_PSOR &= ~(1ul << Bit);
      break;
    case PORTE:
      GPIOE_PCOR |= (1ul << Bit);
      GPIOE_PSOR &= ~(1ul << Bit);
      break;
    default:
      break;  
  }
}

/**
  Function Name	: _GPIO_Toggle_Pin
  Engineer      : Manglio González Carrasco
  Date          : 05/01/2011
  
  Parameters	: U08 Port, U08 Bit
  Returns       : Nothing
  Notes         : This function toggles the given port pin.
*/
void _GPIO_Toggle_Pin(U08 Port, U08 Bit)
{
    switch (Port)
  {
    case PORTA:
      GPIOA_PTOR |= (1ul << Bit);
      break;
    case PORTB:
      GPIOB_PTOR |= (1ul << Bit);
      break;
    case PORTC:
      GPIOC_PTOR |= (1ul << Bit);
      break;
    case PORTD:
      GPIOD_PTOR |= (1ul << Bit);
      break;
    case PORTE:
      GPIOE_PTOR |= (1ul << Bit);
      break;
    default:
      break;  
  }
}