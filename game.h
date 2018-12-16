/* 
 * File:   game.h
 * Author: Lachlan
 *
 * Created on 15 December 2018, 9:49 PM
 */

#ifndef GAME_H
#define	GAME_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "led.h"

void game_initialise();
void game_destroy();
void game_display();
void game_wait();
bool game_status();
void game_check_it( Led led );
void game_key(uint8_t key);
uint8_t game_topscore();


#ifdef	__cplusplus
}
#endif

#endif	/* GAME_H */

