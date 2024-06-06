// Reflectance.c
// Provide functions to take measurements using the kit's built-in
// QTRX reflectance sensor array.  Pololu part number 3672. This works by outputting to the
// sensor, waiting, then reading the digital value of each of the
// eight phototransistors.  The more reflective the target surface is,
// the faster the voltage decays.
// Daniel and Jonathan Valvano
// July 11, 2019

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
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

// reflectance even LED illuminate connected to P5.3
// reflectance odd LED illuminate connected to P9.2
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include <stdint.h>
#include "msp432.h"
#include "..\inc\Clock.h"

// ------------Reflectance_Init------------
// Initialize the GPIO pins associated with the QTR-8RC
// reflectance sensor.  Infrared illumination LEDs are
// initially off.
// Input: none
// Output: none
void Reflectance_Init(void){
    // write this as part of Lab 6

    //BITS 7-0
    //port 7
    //MUST BE INPUTS
    P7->SEL0 &= ~0xFF;
    P7->SEL1 &= ~0xFF;//set all as GPIO
    P7->DIR &= ~0xFF;//input
    P7->OUT |= 0xFF;

    //CTRL EVEN
    //port 5.3 should be an output and initially turned off
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08;//p5.3 GPIO
    P5->DIR |= 0x08;//output
    P5->OUT &= ~0x08;//turn off

    //CTRL ODD
    //port 9.2 should be an output and initially turned off
    P9->SEL0 &= ~0x04;
    P9->SEL1 &= ~0x04;//p9.2 GPIO
    P9->DIR |= 0x04;//output
    P9->OUT &= ~0x04;//turn off

}

// ------------Reflectance_Read------------
// Read the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Read(uint32_t time){

    //set result to 0 initially
    uint8_t result=0;

    // Turn on all LEDs
    P5->OUT |= 0x08;
    P9->OUT |= 0x04;

    // Pulse sensors high for 10 us;
    P7->DIR |= 0xFF; // Make pins output
    P7->OUT |= 0xFF; // Make high
    Clock_Delay1us(10); // 10 us

    // Make pulse sensors input
    P7->DIR &= ~0xFF;
    Clock_Delay1us(time);

    // Read sensors
    result = P7->IN;

    // Turn off all LED's
    P5->OUT &= ~0x08;
    P9->OUT &= ~0x04;

    //return the 8 bit result
    return result;
}

// Perform sensor integration
// Input: data is 8-bit result from line sensor
// Output: position in 0.1mm relative to center of line
int32_t Reflectance_Position(uint8_t data){

    //position variable will contain distance from center
    int32_t position;

    //distance of each sensor from center in microns
    int32_t w[8] = {-33400, -23800, -14300, -4800,
                    4800,   14300,  23800,  33400};

    int32_t numerator = 0; //numerator of distance equation
    int32_t denominator = 0; //denominator of distance equation
    uint8_t bi = 0; //binary states

    //loop allows for summation of the numerator and denominator
    for(uint32_t i = 0 ; i < 8; i++)
    {
        bi = 0b1 << i; //each of the discrete binary states will be looped through via bit shifting
        numerator += (data & bi) * w[7-i]; //summation of the product between (binary states anded with the sensor data) and the distance of each sensor
        denominator += (data & bi); //summation of the binary states anded with the sensor data
    }

    position = numerator/denominator; //answer of the weighted average equation

    //IF STATEMENTS TO CHANGE THE POSITION OF FSM BASED ON SENSOR DATA
    if(position == 0)
        return 0x3;

    //forward
    if(position > -10000 && position < 10000)
        return 0x0;

    //left
    if(position > 10000 && position < 20000)
        return 0x2;

    //right
    if(position < -10000 && position > -20000)
        return 0x1;

    //hard right
    if(position > 20000)
        return 0x5;

    //hard left
    if(position < -20000)
        return 0x4;

    else
        return 0x0;
}


// ------------Reflectance_Start------------
// Begin the process of reading the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// Input: none
// Output: none
// Assumes: Reflectance_Init() has been called
void Reflectance_Start(void){
    P5->OUT |= 0x08;//turn on 4 even IR LEDs
    P9->OUT |= 0x04;//turn on 4 odd IR LEDs
    P7->DIR = 0xFF;//make P7 bits outputs
    P7->OUT = 0xFF;//charge capacitor for measurement

    Clock_Delay1us(10);//wait for capacitor charge
    P7->DIR = ~0xFF;//make P7 bits inputs
}


// ------------Reflectance_End------------
// Finish reading the eight sensors
// Read sensors
// Turn off the 8 IR LEDs
// Input: none
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
// Assumes: Reflectance_Start() was called 1 ms ago
uint8_t Reflectance_End(void){
    P7->OUT = ~0xFF;//turn off all 7 IR LEDs with QTRX mask
    return P7->IN;//return read in results from LEDs
}
