/* 
 * File:   machine.h
 * Author: Lachlan
 *
 * Created on 15 December 2018, 10:05 PM
 */

#ifndef MACHINE_H
#define	MACHINE_H

#ifdef	__cplusplus
extern "C" {
#endif

void machine_initialise();
void machine_destroy();
void delay();
void machine_warn_user();
void machine_notify_user();
void machine_led_flash(Led led);
void machine_flag_seen(unsigned machineId);
void setDevice(unsigned device);
unsigned machine_connections();


#ifdef	__cplusplus
}
#endif

#endif	/* MACHINE_H */

