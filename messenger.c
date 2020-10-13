/** @file   messenger.c
    @authors Troy Tomlins, William Chen
    @date   13th Oct
    @brief  Messenger module source code, responsible for sending and recieveing
    through the IR. The messenger module has three key functionalities. Alternating sending and recieving,
* 	a linked list for messages, and an "encryption" buffer. This is all to make the IR communications
*   more robust.
*/

#include <stddef.h>

#include "ir_uart.h"
#include "shells.h"
#include "messenger.h"
#include "gameover.h"


typedef struct mess_body message_t;

struct mess_body {
    int8_t message;
    message_t* next;
    bool active;
};

/* static declarations for the head and tail of the linked list,
 * an array (pool) for messages to be stored,
 * two booleans, sender and player1.
 * Sender stores whether this funkit is currently sending, or recieving (true and false respectively)
*/
static message_t* head;
static message_t* tail;
static message_t message_pool[MAX_MESSAGE_QUEUE];
static bool sender;
static bool player1;

// returns whether this funkit is currently expecting to recieve a message or send one.
bool get_sender(void)
{
    return(sender);
}

// inits the messenger as player 1 (or 2 if not player 1)
// the other funkit should init as the other player, as enforced by either gameover or readyup
void init_messenger(bool is_player1)
{
    uint8_t i;
    for(i=0; i<MAX_MESSAGE_QUEUE; i++) {
        // deactivate all messages
        message_t* message = &message_pool[i];
        message->active = false;
    }
    head = NULL;
    tail = NULL;
    player1 = is_player1;
    sender = is_player1;
}

// adds a message to the list of to-send messages. Adds an encryption value if this is player 1
void add_message(int8_t message)
{
    uint8_t i;
    message_t* new;
    bool added = false;
    for(i=0; i < MAX_MESSAGE_QUEUE; i++) {
        // searches for a non-active message
        if(!message_pool[i].active && !added) {
            // places message value into the available slot and links to the linked list
            new = &message_pool[i];
            if(player1) {
                new->message = message + ENCRYPTION_ADD;
            } else {
                new->message = message;
            }
            new->active = true;
            if(head == NULL) {
                head = new;
            }
            if(tail == NULL) {
                tail = new;
            } else {
                tail->next = new;
                tail = tail->next;
            }
            added = true;
        }
    }
}

// takes the head of the list and sends it
void send_message(void)
{
    int8_t message;
    if(head != NULL && head->active) {
        // if the head is an active message, send it
        head->active = false;
        message = head->message;
        ir_uart_putc(message);
        if(head->next != NULL && head->next->active) {
            // move the head to the next message in the list if it's valid
            head = head->next;
        } else {
            head = NULL;
        }
    } else {
        // if there is no message to send, send a blank
        ir_uart_putc(BLANK);
    }
    sender = !sender; //switch to receiving mode
}

/** cleans an ir input to make sure it is valid (prevents invalid ir inputs)
    a safety precaution against crashes. */
static bool clean_ir(int8_t* in)
{
    // over codes and blanks are valid and they don't get the encryption added to them
    if((*in == OVER_CODE) || (*in == BLANK)) {
        return true;
    }
    // if this board is not player1, decrypt by subtracting ENCRYPTION_ADD
    // from the incoming message, ignoring over codes and blanks.
    if(!player1) {
        *in = *in - ENCRYPTION_ADD;
    }

    // if the (possibly decrypted) incoming message is still valid, return true
    if((*in >= 0 && *in < TINYGL_WIDTH)) {
        return true;
    } else {
        return false;
    }
}

void read_message(void)
{
    // Checks for incoming message from opponent and makes sure this kit isn't writing
    if (ir_uart_read_ready_p() && ir_uart_write_finished_p()) {
        int8_t incoming = ir_uart_getc();
        if(clean_ir(&incoming)) { // if cleaned message is valid
            if (incoming == OVER_CODE) { // Game over win
                game_over(1); // 1 indictates win
            } else {
                create_shell(incoming);
            }
            sender = !sender; //once a valid message is recieved, switch to sender mode
        }
    }
}

// sends or recieves a message depending on sender boolean
void do_messages(void)
{
    if(sender) {
        send_message();
    } else {
        read_message();
    }
}






