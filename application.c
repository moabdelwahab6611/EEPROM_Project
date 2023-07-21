/* 
 * File     : application.c
 * Author   : Mohamed Ahmed Abdel Wahab
 * LinkedIn : https://www.linkedin.com/in/mohamed-abdel-wahab-162413253/
 * Github   : https://github.com/moabdelwahab6611
 * Created on May 21, 2023, 5:38 PM
 */

/**************************Includes-Section*****************************/
#include "application.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
/***********************************************************************/

/***********************************************************************/
uint8 eeprom_val = 0;
uint8 eeprom_read_val;

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

button_t btn_high = 
{
  .button_pin.port = PORTC_INDEX,
  .button_pin.pin = GPIO_PIN2,
  .button_pin.direction = GPIO_DIRECTION_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_connection = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};

button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_high_valid_status = BUTTON_RELEASED;
button_state_t btn_high_last_valid_status = BUTTON_RELEASED;

uint32 btn_high_valid = 0;
uint8 program_selected = 0;

void program_1(void)
{
    led_turn_on(&led1);
    __delay_ms(500);
    led_turn_off(&led1);
}

void program_2(void)
{
    uint8 counter = 0;
    for(counter = 0; counter < 2; counter++)
    {
        led_turn_on(&led1);
        __delay_ms(500);
        led_turn_off(&led1);
        __delay_ms(500);
    }
}

void program_3(void)
{
    uint8 counter = 0;
    for(counter = 0; counter < 3; counter++)
    {
        led_turn_on(&led1);
        __delay_ms(500);
        led_turn_off(&led1);
        __delay_ms(500);
    }   
}
/***********************************************************************/

/***********************Main Function-Section***************************/
int main() 
{ 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    ret =led_initialize(&led1);
    ret = Data_EEPROM_WriteByte(0x3ff, 0);
    
    while(1)
    {   
        ret = Data_EEPROM_WriteByte(0x3ff, eeprom_val++);
        __delay_ms(1000);
        ret = Data_EEPROM_ReadByte(0x3ff, &eeprom_read_val);
        if(5 == eeprom_read_val)
        {
            led_turn_on(&led1);
        }
        else
        {
            led_turn_off(&led1);
        }
    }
    return (EXIT_SUCCESS);
}
/***********************************************************************/

/*************************Functions-Section*****************************/
void application_intialize(void)
{
    Std_ReturnType ret = E_NOT_OK;       
    ecu_layer_intialize();
}
/***********************************************************************/