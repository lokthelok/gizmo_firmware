#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "aj_hal.h"

bool timerOverflow;

void timerOverflowCallback()
{
    timerOverflow = 1;
}
void initialiseSleepTimer()
{
    TMR1_Initialize();
    TMR1_SetInterruptHandler(timerOverflowCallback);
    timerOverflow = 0;
}
void startSleepTimer()
{
    TMR1_StartTimer();
}
void stopSleepTimer()
{
    TMR1_StopTimer();
}
void resetSleepTimer()
{
    TMR1_Reload();
}
bool isItSleepTime()
{
    bool sleep = timerOverflow;
    timerOverflow = 0;
    return sleep;
}
