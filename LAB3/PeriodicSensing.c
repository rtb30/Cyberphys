/*
 * PeriodicSensing.c
 *
 *  Created on: Feb 22, 2024
 *      Author: brophy
 */

#include <stdint.h>
#include "msp.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Reflectance.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Clock.h"
#include "/Users/brophy/Documents/Starter Codes/inc/CortexM.h"
#include "/Users/brophy/Documents/Starter Codes/inc/SysTickInts.h"
#include "/Users/brophy/Documents/Starter Codes/inc/LaunchPad.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Bump.h"

// define 8 colors for IR mapping
#define DARK    0x00
#define RED     0x01
#define GREEN   0x02
#define YELLOW  0x03
#define BLUE    0x04
#define PINK    0x05
#define SKYBLUE 0x06
#define WHITE   0x07

// global variables
uint32_t count;
uint8_t result;

// this function maps IR input data to an LED output
uint8_t LED_map(uint8_t IR_result) {

    uint8_t map = 0, count = 0, LED = 0, i; // init variables

    for(i = 0; i < 8; i++) {
        map = (IR_result >> i) & 0x01;
        count++;                            // keep track of how many times we shift

        if(map == 1) {
            LED = count;                    // set o/p to which IR is high
        }
    }

    if(LED == 8) {                          // reverse around to RED b/c of options
        LED = 1;
    }

    if(IR_result == 0xFF) {                 // default result value when IRs arent powered
        LED = 0;
    }

    return LED;
}

// this function maps bump switch input data to an LED output
uint8_t LED_map2(uint8_t bump_result) {
    uint8_t map = 0, count = 0, bump = 0, i;

    for(i = 0; i < 6; i++) {
        map = (bump_result >> i) & 0x01;
        count++;                // keep track of how many times we shift

        if(map == 0) {
            bump = count;       // set return value if negative logic shows which bump is pressed
        }
    }

        return bump;
}

// reflectance handler
void SysTick_Handler(void) {

    // ISR is called at a 1kHz, this is called at 100Hz
    if(count % 10 == 0) {                               // turn on IRs, charge RC, turn P7 to inputs
        Reflectance_Start();
    }

    // also called at 100Hz, but 1ms later than reflectance start
    if(count % 10 == 1) {                               // read in inputs and store data in "result" and turn off IRs
        result = Reflectance_End();
        P2->OUT = (P2->OUT & ~0x07) | LED_map(result);  // use mapping to turn on LEDs
    }

    count++; // increase count by 1
}

// bump switch handler
void SysTick_Handler1(void) {

                                                        // ISR is called at a 1kHz, this is called at 100Hz
    if(count % 10 == 0) {                               // reads in bump switch data
        result = Bump_Read();
        P2->OUT = (P2->OUT & ~0x07) | LED_map2(result); // use mapping to turn on LEDs
    }

    count++;
}

int main(void) {
    // init calls
    Clock_Init48MHz();
    SysTick_Init(48000, 2); // this gives a period of 1kHz
    LaunchPad_Init();
    EnableInterrupts();
    Bump_Init();

    // init variables
    count = 0, result = 0;
    P1->OUT = (P1->OUT & ~0x01);


    while(1) {                          // running bubble sort

        uint32_t i, j, temp, length;    // create variables

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

        length = 100;                   // init variable length

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
