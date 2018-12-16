#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "led.h"
#include "machine.h"
#include "game.h"

static uint8_t game_level = 1;
static uint8_t top_score = 1;
static Led moves[100];
static uint8_t move_current = 0;

void new_level()
{
    //machine_warn_user();
    
    //Set new top score
    if( game_level > top_score) {
        top_score = game_level;
    }
    
    //Increment Score
    game_level++;
    move_current = 0;
    uint8_t j;
    for( j = 0; j < game_level; j++ ) {
        machine_led_flash(moves[j]);
    }
    
}

void game_initialise()
{
    game_level = 1;
    
    //Determine Whole Game Sequence
    uint8_t i;
    for( i = 0; i < 100; i++ ) {
        uint16_t randomThree = rand();
        if(randomThree < 10923) moves[i] = green;
        else if(randomThree < 21846) moves[i] = yellow;
        else moves[i] = red;
    }
    
    new_level();
}
void game_destroy();
void game_display();
void game_wait();
bool game_status();

void game_check_it( Led led ) {
    bool result = 0;
    //Check if Button Correct - Increment Current Move
    if( moves[move_current] == led) {
        move_current++;
        result = 1;
    }
    //Otherwise, warn and go back to previous level.
    else {
        machine_warn_user();
        result = 0;
    }
    if( ! result ) {
        game_initialise();
    }
    //When current level complete, do next level.
    else if( move_current >= game_level) {
        __delay_ms(1500);
        new_level();
    }
}

void game_key(uint8_t key);

uint8_t game_topscore()
{
    return top_score;
}
