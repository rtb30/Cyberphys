#include <stdint.h>
#include "msp.h"
#include "/Users/brophy/Documents/Starter Codes/inc/Clock.h"
#include "/Users/brophy/Documents/Starter Codes/inc/SysTick.h"
#include "/Users/brophy/Documents/Starter Codes/inc/LaunchPad.h"


// create new struct to hold state variables
struct state {
    uint8_t out;                    // every struct has an o/p
    uint32_t time;                  // every struct has a wait time in 10ms
    const struct state *next[4];    // points to next state dependent on input
};

typedef const struct state state_t; // new type def for readable code

// define state names
#define z  &FSM[0]
#define f  &FSM[1]
#define t  &FSM[2]
#define ft &FSM[3]
#define tt &FSM[4]

// define LED names
#define DARK    0x00
#define RED     0x01
#define GREEN   0x02
#define BLUE    0x04
#define YELLOW  0x03
#define WHITE   0x07
#define LED1    0x01

state_t FSM[5] = {
  {DARK, 25,   {z, t, f, z}},      // state zero cents
  {DARK, 25,   {f, ft, t, f}},     // state five cents
  {DARK, 25,   {t, tt, ft, t}},    // state ten cents
  {LED1, 250,   {z, z, z, z}},      // state fifteen cents
  {LED1, 250,   {f, f, f, f}}};     // state twenty cents

int main(void) {
    state_t *pt;        // current state pointer
    uint8_t input;      // use variable to hold value of switch states
    Clock_Init48MHz();  // initialize 48MHz clock
    SysTick_Init();     // initialize systick regs
    LaunchPad_Init();   // initialize switches and LEDs

    pt = z;          // start at state zero

    while(1) {
        P1->OUT = (P1->OUT & ~0x01) | (pt->out);    // safely set RGBs to off and OR the specific states o/p
        SysTick_Wait10ms(pt->time);                 // wait specific state time in 10ms
        input = LaunchPad_Input();                  // use launch pad to do above instead
        pt = pt->next[input];                       // set pointer to next state and repeat
    }
}
