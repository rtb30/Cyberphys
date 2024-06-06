/*
 * Author: Brophy
 * Date: 3/27/24
 *
 * This program is to take UART data initially given via BLE and
 * execute certain motor functions.
 */

#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/UART0.h"
#include "../inc/LaunchPad.h"
#include "../inc/Motor.h"
#include "../inc/PWM.h"
#include "../inc/BumpInt.h"
#include "../inc/SysTickInts.h"
#include "../inc/CortexM.h"
#include <string.h>

char * BumpMessage = "Slow Down!";
uint32_t syscount = 0;
char command; // variable to pass to function to change


//---------- SysTick Handler ----------//
void SysTick_Handler(void) {
    // ISR is called at a 1kHz, this is called at 100Hz
        if(command == 'F') {
            LaunchPad_Output(0x02);
            Motor_Forward(2000, 2000);
        }

        if(command == 'B') {
            LaunchPad_Output(0x03);
            Motor_Backward(2000, 2000);
        }

        if(command == 'S') {
            LaunchPad_Output(0x01);
            Motor_Stop();
        }
}


//---------- COLLISION HANDLER ----------//
void HandleCollision(uint8_t bumpSensor){
    command = 'S';
    UART0_OutString(BumpMessage);   // transmit bump message
}

//---------- MAIN ----------//
void main(void)
{
    Clock_Init48MHz();              // set system clock to 48 MHz
    UART0_Init();                   // UART0 init
    LaunchPad_Init();               // launch pad init
    Motor_Init();                   // motor init
    BumpInt_Init(&HandleCollision); // bump init
    SysTick_Init(48000, 2);         // this gives a period of 1kHz

    EnableInterrupts();
    LaunchPad_LED(0x00);

    while(1){
        //WaitForInterrupt();
        command = UART0_InChar();    // read in user value (from BLE)
        UART0_OutChar(command);
        UART0_OutChar(CR);
        UART0_OutChar(LF);
    }
}
