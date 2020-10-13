/** @file   lives.h
    @author Troy Tomlins, William Chen
    @date   11th Oct
    @brief  header for the lives count
*/
#ifndef LIVES_H
#define LIVES_H

/* Starting number of lives */
#define LIVES_NUM 3
#define FLASH_TICKS 30

// Shows lives on led
void show_lives(void);

// Checks if player is hit
void check_hit(int8_t shell_pos);

// Returns lives remaining
void init_lives(void);

// Sets lives to default
void set_lives(void);

uint8_t get_lives(void);

#endif
