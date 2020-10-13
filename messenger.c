/** @file   player.c
    @authors Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Player module, responsible for storing, changing, and displaying
    information on the player
*/

#include "ir_uart.h"
#include "shells.h"
#include "messenger.h"
#include "gameover.h"
#include <stddef.h>
#include "readyup.h"


typedef struct mess_body message_t;

struct mess_body {
    int8_t message;
    message_t* next;
    bool active;
};

static message_t* head;
static message_t* tail;
static message_t message_pool[MAX_MESSAGE_QUEUE];
static bool sender;
static bool player1;

void reset_messenger(void)
{
	init_messenger(false);
}

void init_messenger(bool is_player1)
{
    head = NULL;
    tail = NULL;
	player1 = is_player1;
    sender = is_player1;
}

void add_message(int8_t message)
{
    uint8_t i;
    message_t* new;
    bool added = false;
    for(i=0; i<MAX_MESSAGE_QUEUE; i++) {
        if(!message_pool[i].active && !added) {
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

void send_message(void)
{
    int8_t message;
    if(head != NULL && head->active) {
        head->active = false;
        message = head->message;
        ir_uart_putc(message);
        if(head->next != NULL) {
            head = head->next;
        } else {
            head = NULL;
        }
    } else {
        if(player1) {
            ir_uart_putc(BLANK + ENCRYPTION_ADD);
        } else {
            ir_uart_putc(BLANK);
        }
    }
    sender = !sender;
}

/** cleans an ir input to make sure it is valid (prevents invalid ir inputs)
    a safety precaution against crashes. */
static bool clean_ir(int8_t* in)
{
    if(!player1 && *in != OVER_CODE) {
        *in = *in - ENCRYPTION_ADD;
    }

    if((*in >= 0 && *in <= 4) || (*in == OVER_CODE) || (*in == BLANK)) {
        return true;
    } else {
        return false;
    }
}

void read_message(void)
{
    // Checks for incoming message from opponent
    if (ir_uart_read_ready_p() && ir_uart_write_finished_p()) {
        int8_t incoming = ir_uart_getc();
        if(clean_ir(&incoming)) {
            if (incoming==OVER_CODE) { // Game over win
                game_over(1); // 1 indictates win
            } else {
                create_shell(incoming);

            }
            sender = !sender;
        }
    }
}

void do_messages(void)
{
    if(sender) {
		led_set (LED1, 1);
        send_message();
    } else {
		led_set (LED1, 0);
        read_message();
    }
}






