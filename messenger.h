/** @file   messenger.h
    @author William Chen, Troy Tomlins // # Ids: wch99, tpt38, 47994832, 53494295
    @date   13th Oct
    @brief  header for messenger module. Contains non-private declarations
*/
#ifndef MESS_H
#define MESS_H


#define MAX_MESSAGE_QUEUE 10 //max messages that can be loaded at a time

// below are definitons of the codes used
// x coord codes are 0, 1, 2, 3, and 4
#define OVER_CODE 9
#define READY_CODE 13
#define BLANK 37

#define ENCRYPTION_ADD 50 // value to "encrypt" an output column


// get bool for if this funkits is sending or recieving
bool get_sender(void);

// sets all messages to inactive, resets the head and tail of the linked list
// and sets sender and player1 to is_player1
void init_messenger(bool is_player1);

// adds a message to the linked list, encrypts if this kit is player1
void add_message(int8_t message);

// sends the first message in the linked list, or a blank if there are none
void send_message(void);

// either sends a message or process a recieved one depending on sender bool
void do_messages(void);


// reads a message and decrypts it if this kit is player2
void read_message(void);


#endif

