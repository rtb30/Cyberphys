/*
 * InputOutput_extern.h
 *
 *  Created on: Jan 19, 2024
 *      Author: brophy
 */

#ifndef INPUTOUTPUT_EXTERN_H_
#define INPUTOUTPUT_EXTERN_H_

//***BUTTONS***//
void P5_init(void) {
    P5->SEL0 &= ~0x05;  // xxxx xxxx & 1111 1010
    P5->SEL1 &= ~0x05;  // 1) set P5.0 and P5.2 as GPIOs
    P5->DIR &= ~0x05;   // 2) set P5.0 and P5.2 as in
    P5->REN &= ~0x05;   // 3) Disable the resistor (P5->OUT can have any value)
}

uint8_t P5_input(void) {
    return (P5->IN & 0x05);
}

//***LEDs***//
void P2_init(void) {
    P2->SEL0 &= ~0xC0;  // xxxx xxxx & 0011 1111
    P2->SEL1 &= ~0xC0;  // 1) Set P2.7 and P2.6 as GPIOs
    P2->DIR |= 0xC0;    // 2) Set P2.7 and P2.6 as out
    P2->DS |= 0xC0;     // 3) Set drive strength high for LEDs (have 100 res: 500mA or 330mA)
    P2->OUT &= ~0xC0;   // 4) Set all LEDs off at initialization
}

void P2_output(uint8_t data) {
    P2->OUT = (P2->OUT & ~0xC0) | data;
}

#endif /* INPUTOUTPUT_EXTERN_H_ */
