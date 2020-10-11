/** @file   lives.h
    @author Troy Tomlins
    @date   11th Oct
    @brief  header for the lives count
*/
#ifndef LIVES_H
#define LIVES_H

// Starting number of lives
#define LIVES_NUM 3
#define FLASH_TICKS 10

void show_lives(void);

void check_hit(uint8_t shell_pos);

void set_lives(void);

#endif
