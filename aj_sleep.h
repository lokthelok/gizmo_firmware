/* 
 * File:   aj_sleep.h
 * Author: Lachlan
 *
 * Created on 23 November 2018, 9:12 PM
 */

#ifndef AJ_SLEEP_H
#define	AJ_SLEEP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
    


void timerOverflowCallback();
void initialiseSleepTimer();
void startSleepTimer();
void stopSleepTimer();
void resetSleepTimer();
bool isItSleepTime();

#ifdef	__cplusplus
}
#endif

#endif	/* AJ_SLEEP_H */

