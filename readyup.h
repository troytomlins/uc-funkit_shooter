/** @file   readyup.h
    @author William Chen, Troy Tomlins
    @date   8th Oct
    @brief  header for readyup module
*/
#ifndef READYUP_H
#define READYUP_H

#define MESSAGE_RATE 30
#define PACER_RATE 200

// displays ready messages and waits for ready inputs before continuing
// does not allow anything else to progress.
void ready_up(void);

#endif
