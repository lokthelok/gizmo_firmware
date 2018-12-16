#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "aj_hal.h"
#include "led.h"
#include "machine.h"

void machine_led_flash(Led led) {
    setLED(2000, led);
    __delay_ms(1000);
    setLED(0, led);
    __delay_ms(1000);
}

void machine_warn_user()
{
    uint8_t j;
    for(j=0 ; j < 5 ; j++)
    {
        setLEDs(2000, 2000, 2000);
        __delay_ms(200);
        setLEDs(0, 0, 0);
        __delay_ms(200);
    }
    __delay_ms(1500);
}

void machine_notify_user()
{
    uint16_t j,i;
    for(i=0 ; i < 3 ; i++)
    {
        for(j=0 ; j < 200 ; j++)
        {
            uint16_t val = j*5;
            setLEDs(val, val, val);
        }
    }
    setLEDs(0, 0, 0);
    __delay_ms(1500);
}