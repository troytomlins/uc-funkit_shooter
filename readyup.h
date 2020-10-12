/** @file   readyup.h
    @author William Chen, Troy Tomlins
    @date   8th Oct
    @brief  header for readyup module
*/
#ifndef READYUP_H
#define READYUP_H

/* Define Message data */
#define MESSAGE_RATE 50 // Message rate
#define PACER_RATE 200 // Pacer rate
#define READY_CODE 13 //arbitrary as long as it isn't 0,1,2,3, or 4
#define START_TEXT "  PRESS TO START"
#define READY_TEXT "  READY!"
#define OPPONENT_READY_TEXT "  OPPONENT READY!"

// displays ready messages and waits for ready inputs before continuing
// does not allow anything else to progress.
void ready_up(void);

#endif
