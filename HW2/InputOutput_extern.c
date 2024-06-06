/*
 * InputOutput_extern.c
 *
 *  Created on: Jan 19, 2024
 *      Author: brophy
 */

#include <stdint.h>
#include "msp.h"

#include "InputOutput_extern.h"

#define SW1     0x01 // port 5.0 (0000 0001)
#define SW2     0x04 // port 5.2 (0000 0100)
#define LED1    0x80 // port 2.7 (1000 0000)
#define LED2    0x40 // port 2.6 (0100 0000)

int main(void) {
    uint8_t input_status;
    P5_init();
    P2_init();

    while(1) {
        input_status = P5_input();

        switch(input_status) {
        case 0x04:              // SW1 is pressed
            P2_output(LED1);
            break;

        case 0x01:              // SW2 is pressed
            P2_output(LED2);
            break;

        case 0x00:
            P2_output(LED1 + LED2);
            break;

        case 0x05:
            P2_output(0);
            break;

        }
    }
}
