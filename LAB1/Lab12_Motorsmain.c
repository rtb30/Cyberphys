// Lab12_Motorsmain.c
// Runs on MSP432
// Solution to Motors lab
// Daniel and Jonathan Valvano
// December 17, 2018

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

//**************RSLK1.1***************************
// Left motor direction connected to P5.4 (J3.29)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P5.5 (J3.30)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)

#include "msp.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Bump.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Clock.h"
#include "/Users/brophy/Documents/Starter Codes/inc/SysTick.h"
#include "/Users/brophy/Documents/Starter Codes/inc/LaunchPad.h"
#include "/Users/brophy/Documents/Starter Codes/inc/MotorSimple.h"

// Driver test
void Pause(void){
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}

int main(void) {
    // call all initialization funcs
    Clock_Init48MHz();
    LaunchPad_Init();
    SysTick_Init();
    Motor_InitSimple();
    while(1) {

        // Pause();                            // wait for SW1 and SW2 press and release
        // Motor_ForwardSimple(9900, 250);     // just for funzies

        Pause();                            // wait for SW1 and SW2 press and release
        Motor_ForwardSimple(2500, 250);     // forward 25% duty cycle for 2.5s
        Motor_LeftSimple(2500, 125);        // 90 deg right turn
        Motor_ForwardSimple(2500, 250);     // forward 25% duty cycle for 2.5s
        Motor_RightSimple(2500, 125);       // 90 deg left turn
        Motor_ForwardSimple(2500, 250);     // forward 25% duty cycle for 2.5s
        Motor_RightSimple(2500, 125);       // 90 deg left turn
        Motor_ForwardSimple(2500, 250);     // forward 25% duty cycle for 2.5s
        Motor_LeftSimple(2500, 125);        // 90 deg right turn
        Motor_BackwardSimple(2500, 500);    // backward 25% duty cycle for 2.5s
        Motor_StopSimple();
    }
}
