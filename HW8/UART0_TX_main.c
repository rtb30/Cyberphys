// Lab11_UARTmain.c
// Runs on MSP432
// Test the functions in UART0.c by printing various
// Busy-wait device driver for the UART UCA0.
// Daniel Valvano
// May 24, 2019

/* This example accompanies the book
"Embedded Systems: Introduction to Robotics,
Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
For more information about my classes, my research, and my books, see
http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2019, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/UART0.h"

//---------- MAIN Q1 ----------//
void main1(void) {
    Clock_Init48MHz();  // set system clock to 48 MHz
    UART0_Init();       // UART0 init

    char *initials = "RTB";

    while(1) {
        UART0_OutString(initials);  // print initials
        UART0_OutChar('!');         // print !
        UART0_OutChar(0x0A);         // print new line
        UART0_OutChar(0x0D);         // print CR
        Clock_Delay1ms(500);        // delay 500ms
    }
}

//---------- MAIN Q2 ----------//
void main(void) {
    Clock_Init48MHz();  // set system clock to 48 MHz
    UART0_Init();       // UART0 init

    char *initials = "RTB";

    while(1) {
        UART0_OutString(initials);  // print initials
        Clock_Delay1ms(1);        // delay 1ms
    }
}
