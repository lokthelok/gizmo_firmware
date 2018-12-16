/* 
 * File:   aj_buttons.h
 * Author: Lachlan
 *
 * Created on 23 November 2018, 9:11 PM
 */

#ifndef AJ_BUTTONS_H
#define	AJ_BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

//################### BUTTONS ####################
//checkButtons - Disable Serial, Read the ADC (blocking), update buttons states.
//Pass in buttons[3] which contains boolean states (1=pressed) of each button.
void checkButtons(bool buttons[]); //buttons[3]


#ifdef	__cplusplus
}
#endif

#endif	/* AJ_BUTTONS_H */

