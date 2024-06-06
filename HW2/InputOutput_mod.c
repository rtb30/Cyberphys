/*
 * main.c
 *
 *  Created on: Jan 19, 2024
 *      Author: brophy
 */

#include <stdint.h>
#include "msp.h"
#include "InputOutput_mod.h"

// define variables for LEDs on specific ports
#define SW1       0x02 // port1.1 (0000 0010) - near power LED
#define SW2       0x10 // port1.4 (0001 0000)
#define RED       0x01 // port2.0 (0000 0001)
#define GREEN     0x02 // port2.1 (0000 0010)
#define BLUE      0x04 // port2.2 (0000 0100)

int main(void) {
    uint8_t status;
    Port1_Init();                    // initialize P1.1 and P1.4 and make them inputs (P1.1 and P1.4 built-in buttons)
                                        // initialize P1.0 as output to red LED
    Port2_Init();                   // initialize P2.2-P2.0 and make them outputs (P2.2-P2.0 built-in LEDs)

    while(1) {
        status = Port1_Input();

        switch(status) {                 // switches are negative logic on P1.1 and P1.4
            case 0x10:                    // SW1 pressed
               Port2_Output(RED+GREEN);
               break;

            case 0x02:                    // SW2 pressed
                Port2_Output(GREEN+BLUE);
                break;

            case 0x00:                    // both switches pressed (both grounded - xxx0 xx0x)
                Port2_Output(BLUE+RED+GREEN);
                break;

            case 0x12:                    // neither switch pressed (both pulled up to VCC - xxx1 xx1x)
                Port2_Output(GREEN);
                break;
        }
    }
}
