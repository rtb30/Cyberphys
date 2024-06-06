/*
 * InputOutput_mod.h
 *
 *  Created on: Jan 19, 2024
 *      Author: brophy
 */

#ifndef INPUTOUTPUT_MOD_H_
#define INPUTOUTPUT_MOD_H_

void Port1_Init(void) {
  P1->SEL0 &= ~0x13;    // xxxx xxxx & 1110 1101 = xxx0 xx0x (preserves unused bits)
  P1->SEL1 &= ~0x13;    // 1) configure P1.4  P1.1 as GPIO
  P1->DIR &= ~0x12;     // 2) make P1.4 and P1.1 "in"
  P1->REN |= 0x12;      // 3) enable resistors on P1.4 and P1.1
  P1->OUT |= 0x12;      //    P1.4 and P1.1 are pull-up bc they are switches (pressed switch = P1IN.x is gnd)
}

uint8_t Port1_Input(void) {
  return (P1->IN & 0x12);   // read P1.4,P1.1 inputs
}

void Port2_Init(void) {
  P2->SEL0 &= ~0x07;    // xxxx xxxx & 1111 1000 (preserves unused bits)
  P2->SEL1 &= ~0x07;    // 1) configure P2.2-P2.0 as GPIO
  P2->DIR |= 0x07;      // 2) make P2.2-P2.0 out
  P2->DS |= 0x07;       // 3) activate increased drive strength for P2.2-P2.0
  P2->OUT &= ~0x07;     // 4) set all LEDs off
}

void Port2_Output(uint8_t data) {  // write three outputs bits of P2
  P2->OUT = (P2->OUT & 0xF8)|data;
}

#endif /* INPUTOUTPUT_MOD_H_ */
