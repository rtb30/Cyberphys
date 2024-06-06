/*
 * BubbleSort_Blink.c
 *
 *  Created on: Feb 21, 2024
 *      Author: brophy
 */

#include <stdint.h>
#include "msp.h"
#include "/Users/brophy/Documents/Starter Codes/inc/CortexM.h"
#include "/Users/brophy/Documents/Starter Codes/inc/SysTickInts.h"
#include "/Users/brophy/Documents/Starter Codes/inc/LaunchPad.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Clock.h"

// declare global variables
#define BLUE 0x04
uint32_t count;
uint32_t period = 750000;
#define LEDOUT (*((volatile uint8_t *)(0x42098040)))

void SysTick_Handler(void){
    if((LaunchPad_Input()) == 0x01 && (count % 8 == 0)) { // P1.1 is pressed
        P1->OUT ^= 0x01;       // toggle P1.0
    }

    if(LaunchPad_Input() == 0x02) { // P1.4 is pressed
        P2->OUT ^= BLUE; // friendly :)
    }

    if (LaunchPad_Input() == 0x00 || LaunchPad_Input() == 0x03){
        P1->OUT &= ~0x01;
        P2->OUT &= ~BLUE;
    }

    count++;
}

int main(void) {
    // init calls
    Clock_Init48MHz();
    SysTick_Init(period, 2);
    LaunchPad_Init();
    EnableInterrupts();

    // init variables
    count = 0;
    P1->OUT &= ~0x01;

    while(1) {

        //WaitForInterrupt();

        // create variables
        uint32_t i, j, temp, length;

        // create array to sort
        uint32_t a[100]={5000,5308,5614,5918,6219,6514,
        6804,7086,7361,7626,7880,8123,8354,8572,8776,8964,9137,
        9294,9434,9556,9660,9746,9813,9861,9890,9900,9890,9861,
        9813,9746,9660,9556,9434,9294,9137,8964,8776,8572,8354,
        8123,7880,7626, 7361,7086,6804,6514,6219,5918,5614,
        5308,5000,4692,4386,4082,3781,3486,3196,2914,2639,2374,
        2120,1877,1646,1428,1224,1036,863,706,566,444,340,254,
        187,139,110,100,110,139,187,254,340,444,566,706,863,
        1036, 1224, 1428, 1646,1877,2120,2374,2639,2914,
        3196,3486,3781,4082,4386,4692};

        length = 100; // init variable length

        // sorting algorithm
        for (i = 0; i < length; i++) {
            for (j = 0; j < length - i - 1; j++) {
                if (a[j + 1] < a[j]) {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }
    }
}
