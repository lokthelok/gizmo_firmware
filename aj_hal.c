#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"

//Contains HAL-ish functions to further abstract buttons, LEDs and Serial


//################### SERIAL #####################
//enableSerial - Enable TX channel
void enableSerial ()
{
    RCSTAbits.SPEN = 1; //Enable UART (sets RX/TX Pins as digital serial)
    __delay_ms(1); //Wait for idle line
}

//disableSerial - Disable RX channel
void disableSerial ()
{
    __delay_ms(1); //Wait for any stop bits
    RCSTAbits.SPEN = 0; //Disable UART (releases RX/TX Pins from digital)
}

//EUSART_RxCheck - Check for received bytes
bool EUSART_RxCheck ()
{
    return PIR1bits.RCIF;
}

//################### LED PWM ####################
void stopLEDs ()
{
    PWM1_Stop();
    PWM2_Stop();
    PWM3_Stop();
}

void startLEDs ()
{
    PWM1_Start();
    PWM2_Start();
    PWM3_Start();
}

void setLEDs (uint16_t led1, uint16_t led2, uint16_t led3)
{
    startLEDs();
    PWM1_DutyCycleSet(led1);
    PWM1_LoadBufferSet();
    PWM2_DutyCycleSet(led2);
    PWM2_LoadBufferSet();
    PWM3_DutyCycleSet(led3);
    PWM3_LoadBufferSet();
}

void setupLEDs (uint16_t period)
{
    const uint16_t initial_duty = 0;
    const uint16_t initial_phase = 0;
    stopLEDs();
    
    PWM1_PhaseSet(initial_phase);
    PWM1_PeriodSet(period);
    
    PWM2_PhaseSet(initial_phase);
    PWM2_PeriodSet(period);
    
    PWM3_PhaseSet(initial_phase);
    PWM3_PeriodSet(period);
    
    setLEDs(initial_duty, initial_duty, initial_duty);
}

void setLED (uint16_t duty, uint8_t LEDno)
{
    if(LEDno == 3)
    {
        PWM1_DutyCycleSet(duty);
        PWM1_LoadBufferSet();
    }
    else if(LEDno == 2)
    {
        PWM2_DutyCycleSet(duty);
        PWM2_LoadBufferSet();
    }
    else if(LEDno == 1)
    {
        PWM3_DutyCycleSet(duty);
        PWM3_LoadBufferSet();
    }
}

void connectHandler() {
    //Serial connection detected. Do serial exchange.
    setLEDs(2000, 2000, 2000);enableSerial();
    __delay_ms(100);
    while(!EUSART_is_tx_ready());
    EUSART_Write('+');
    while(!EUSART_is_tx_ready());
    EUSART_Write('+');
    while(!EUSART_is_tx_ready());
    EUSART_Write('+');
    while(!EUSART_is_tx_ready());
    EUSART_Write('+');
    while(!EUSART_is_tx_ready());
    EUSART_Write('+');
    while(!EUSART_is_tx_done());
    __delay_ms(900);
    disableSerial();
    while(PORTAbits.RA5 == 0);
}

//setupConnectInterrupt - sets buttonHandler as interrupt handler
void setupConnectInterrupt () {
    IOCAF5_SetInterruptHandler(connectHandler);
}

//#################### SLEEP #####################
//buttonHandler - interrupt handler for Button, checks for reset/wake
void buttonHandler ()
{
    if(0) { //If RX Pin - Do Serial Exchange
        
    }
    else if(0) { //If AN0/TX Pin - Wake (Do Nothing)
        
    }
    else {
        
    }
}
//setupButtonInterrupt - sets buttonHandler as interrupt handler
void setupButtonInterrupt ()
{
    IOCAF0_SetInterruptHandler(buttonHandler);
}
//goToSleep - Sets RA0 digital in, Turn off LEDs, Serial off, sleep, wake-up nop
void goToSleep ()
{
    //Disable Peripherals for minimum Power
    setLEDs(0,0,0);
    
    //Set RA0 for IOC
    disableSerial(); //Not at all necessary, can be enabled.
    ADCON0bits.ADON = 0; //Turn off ADC0 - Not necessary
    ANSELAbits.ANSA0 = 0; //Set RA0 as digital - IS necessary
    TRISAbits.TRISA0 = 1; //Set RA0 as input (already set)
    
    //Sleep
    SLEEP();
    
    //Sleeping...
    
    //Wake Up NOP
    NOP();
    
    //Execute buttonHandler (IOC Interrupt Handler)
    
    TRISAbits.TRISA0 = 1; //Set RA0 as input (already set)
    ANSELAbits.ANSA0 = 0; //Set RA0 as digital - IS necessary
    ADCON0bits.ADON = 0; //Turn off ADC0 - Not necessary
}

//################## INTERRUPT ###################
//Interrupts on - Global and Peripheral
void enableInterrupts () {
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
}
//Interrupts off - Global and Peripheral
void disableInterrupts () {
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
}


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