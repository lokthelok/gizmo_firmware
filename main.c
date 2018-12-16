/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC12LF1572
        Driver Version    :  2.00
 */

#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdbool.h>
#include "aj_hal.h"
#include "game.h"
#include "machine.h"
#include "flashValue.h"

bool buttons[3];

void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    setupLEDs(2000);
    machine_warn_user();
    
    game_initialise();
    
    while (1) {
        //Wait for Button 'Event'
        bool waitingForButton = 1;
        do {
            checkButtons(buttons);
            if(buttons[0] == 1 || buttons[1] == 1 || buttons[2] == 1)
            {
                waitingForButton = 0;
            }
        } while (waitingForButton);
        
        //Wait for Debounce / Second Button
        __delay_ms(300);
        
        //Re-Check after Debounce
        checkButtons(buttons);
        
        //Check which buttons
        if(buttons[1] == 1 && buttons[2] == 1)
        {
            //Connect Score - Two Left Buttons
            machine_notify_user();
            flashValue(123);
            machine_warn_user();
            game_initialise();
        }
        else if(buttons[0] == 1 && buttons[1] == 1)
        {
            //Game Score - Two Right Buttons
            machine_notify_user();
            flashValue(game_topscore());
            machine_warn_user();
            game_initialise();
        }
        else
        {
            Led button_pressed;
            if(buttons[0]) button_pressed = green;
            if(buttons[1]) button_pressed = yellow;
            if(buttons[2]) button_pressed = red;

            setLED(2000, button_pressed);

            //Wait for Release
            bool waitingForRelease = 1;
            do {
                checkButtons(buttons);
                if(buttons[0] == 0 & buttons[1] == 0 && buttons[2] == 0)
                {
                    waitingForRelease = 0;
                }
            } while (waitingForRelease);

            setLED(0, button_pressed);

            game_check_it(button_pressed);
        }
    }
}
/**
 End of File
 */