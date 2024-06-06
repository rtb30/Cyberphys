/*
 * UART0_RX_main.c
 *
 *  Created on: Mar 23, 2024
 *      Author: brophy
 */

#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/UART0.h"
#include "../inc/LaunchPad.h"
#include <string.h>

// define LED names
#define DARK        0x00    // ---
#define RED         0x01    // R--
#define GREEN       0x02    // -G-
#define YELLOW      0x03    // RG-
#define BLUE        0x04    // --B
#define PINK        0x05    // R-B
#define SKYBLUE     0x06    // -GB
#define WHITE       0x07    // RGB

//---------- MAIN Q3 ----------//
void main3(void) {
    Clock_Init48MHz();  // set system clock to 48 MHz
    UART0_Init();       // UART0 init
    LaunchPad_Init();
    P1->OUT &= ~0x01;
    //LaunchPad_Output(BLUE);

    uint16_t max = 10;
    char *command;

    while(1){
        UART0_InString(command, max);

        if(strcmp(command, "DARK") == 0) {
            LaunchPad_Output(DARK);
        }

        if(strcmp(command, "RED") == 0) {
            LaunchPad_Output(RED);
            //command = 0;
        }

        if(strcmp(command, "GREEN") == 0) {
            LaunchPad_Output(GREEN);
        }

        if(strcmp(command, "YELLOW") == 0) {
            LaunchPad_Output(YELLOW);
        }

        if(strcmp(command, "BLUE") == 0) {
            LaunchPad_Output(BLUE);
        }

        if(strcmp(command, "PINK") == 0) {
            LaunchPad_Output(PINK);
        }

        if(strcmp(command, "SKYBLUE") == 0) {
            LaunchPad_Output(SKYBLUE);
        }

        if(strcmp(command, "WHITE") == 0) {
            LaunchPad_Output(WHITE);
        }

    }
}
