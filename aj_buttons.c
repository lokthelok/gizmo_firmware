#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "aj_hal.h"

//################### BUTTONS ####################
#define LIM1 27
#define LIM2 81
#define LIM3 97
#define LIM4 124
#define LIM5 140
#define LIM6 151
#define LIM7 157
#define LIM8 255

//Blocking while ADC Converts
void checkButtons(bool buttons[]) //buttons[3]
{
    disableSerial();
    __delay_ms(1);
    uint16_t adc = (ADC1_GetConversion(channel_AN0) >> 8) & 0xFF;
    uint8_t i = 0;
    for(i = 0; i < 3; i++)
    {
        buttons[i] = 0;
    }
    
    if(adc <= LIM1)
    {
        //No Button
    }
    else if(adc > LIM1 && adc <= LIM2)
    {
        //Left Button
        buttons[2] = 1;
    }
    else if(adc > LIM2 && adc <= LIM3)
    {
        //Middle Button
        buttons[1] = 1;
    }
    else if(adc > LIM3 && adc <= LIM4)
    {
        //Left,Middle Button
        buttons[2] = 1;
        buttons[1] = 1;
    }
    else if(adc > LIM4 && adc <= LIM5)
    {
        //Right Button
        buttons[0] = 1;
    }
    else if(adc > LIM5 && adc <= LIM6)
    {
        //Left,Right Button
        buttons[2] = 1;
        buttons[0] = 1;
    }
    else if(adc > LIM6 && adc <= LIM7)
    {
        //Right,Middle Button
        buttons[1] = 1;
        buttons[0] = 1;
    }
    else if(adc > LIM7 && adc <= LIM8)
    {
        //Left,Middle,Right Button
        buttons[2] = 1;
        buttons[1] = 1;
        buttons[0] = 1;
    }
}
