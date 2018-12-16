#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "aj_hal.h"
#include "led.h"
#include "flashValue.h"
#include "machine.h"

void flashit(Led colour, uint8_t flash)
{
    while( flash > 0 ) {
        setLED(2000, colour);
        __delay_ms(1700);
        setLED(0, colour);
        __delay_ms(1000);
        flash--;
    }
}

void flashValue(uint8_t times) {
    // printf(" flashing %d\n", value);
    __delay_ms(2500);
    setLEDs(0,0,0);
    if( times >= 100) {
        flashit( red, times / 100 );
        times = times % 100;
    }
    if( times >= 10) {
        flashit( yellow, times / 10 );
        times = times % 10;
    }
    if( times >= 1) {
        flashit( green, times );
    }
}