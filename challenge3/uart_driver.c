#include <stdbool.h>
#include <stdio.h>
#include "uart_driver.h"

static int  array_iterator = 0;
static bool is_enabled = false;

void uart_driver_start_communication() {
    /** dummy function, don't care about the code inside */
    is_enabled = true;
}

void uart_driver_stop_communication() {
    /** dummy function, don't care about the code inside */
    is_enabled = false;
}

unsigned char uart_driver_get_byte() {
    /** dummy function, the code inside is provided only for debug purposes */
    if(is_enabled == false) {
        printf("the uart communication has not been enabled. please call `uart_driver_start_communication` first\n");
        return 0;
    }
    
    unsigned char data[] = {0x01, 0xFF, 0xA1, 0x00, 0x00, 0xFF, 0x13, 0x08};
    array_iterator++;
    return data[array_iterator - 1];
}

void uart_driver_send_byte(unsigned char data) {
    /** dummy function, don't care about the code inside */
}
