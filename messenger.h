/** @file   readyup.h
    @author William Chen, Troy Tomlins
    @date   8th Oct
    @brief  header for readyup module
*/
#ifndef MESS_H
#define MESS_H

/* Define Message data */
#define MAX_MESSAGE_QUEUE 10
#define OVER_CODE 9 // arbitrary as long sa it isn't 0,1,2,3,4 or 13
#define ENCRYPTION_ADD 50
#define BLANK 37

void init_messenger(bool is_player1);

void add_message(int8_t message);

void send_message(void);

void reset_messenger(void);

void do_messages(void);

void read_message(void);


#endif

