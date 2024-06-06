#include "msp.h"
#include "../inc/Reflectance.h"
#include "../inc/Clock.h"
#include "../inc/Motor.h"
#include "../inc/LaunchPad.h"
#include "../inc/SysTickInts.h"
#include "../inc/CortexM.h"
#include "../inc/BumpInt.h"

void motorState(uint8_t state);
void SysTick_Handler(void);
void collision(uint8_t);

struct State {
  uint32_t out;//2-bit output
  const struct State *next[6]; // Next if 2-bit input is 0-3
};
typedef const struct State State_t;

#define Center    &fsm[0]
#define Left      &fsm[1]
#define Right     &fsm[2]
#define LookF     &fsm[3]
#define LookB     &fsm[4]
#define LookR     &fsm[5]
#define LookL     &fsm[6]
#define Lost      &fsm[7]
#define FastL     &fsm[8]
#define FastR     &fsm[9]

State_t fsm[10]={ //ORDER OF STATES

    {0x1, {Center, Left, Right, LookF, FastL, FastR }}, //same order as states defined above^^^^^
    {0x2, {Center, Left, Right, LookF, FastL, FastR  }},
    {0x3, {Center, Left, Right, LookF, FastL, FastR }},
    {0x4, {Center, Left, Right, LookB, FastL, FastR }},
    {0x5, {Center, Left, Right, LookL, FastL, FastR }},
    {0x6, {Center, Left, Right, LookR, FastL, FastR }},
    {0x7, {Center, Left, Right, LookL,  FastL, FastR }},
    {0x8, {Lost,   Lost, Lost,  Lost,  Lost, Lost }},
    {0x9, {Center, Left, Right, LookF, FastL, FastR }},
    {0xA, {Center, Left, Right, LookF, FastL, FastR  }}
};

State_t *StatePtr;  //pointer to the current state
uint8_t Input;
volatile uint8_t data;

int main(void){
  Clock_Init48MHz();
  Motor_Init();
  Reflectance_Init();
  SysTick_Init(48000, 2);
  LaunchPad_Init();
  BumpInt_Init(&collision);

  StatePtr = Center;

  EnableInterrupts();

  while(1)
      WaitForInterrupt();
}

void motorState(uint8_t state) { //WHAT MOTORS DO IN EACH STATE
    switch(state){
        case 0x1:
            Motor_Forward(3000, 3000);//center
            break;
        case 0x2:
            Motor_Left(0, 2000);//left
            break;
        case 0x3:
            Motor_Right(2000, 0);//right
            break;
        case 0x4:
            Motor_Forward(3000, 3000); //look forward
            Clock_Delay1ms(50);
            break;
        case 0x5:
            Motor_Backward(3000, 3000); //look backward
            Clock_Delay1ms(100);
            break;
        case 0x6:
            Motor_Left(2000, 2000); //look left
            Clock_Delay1ms(300);
            break;
        case 0x7:
            Motor_Right(2000, 2000); //look right
            Clock_Delay1ms(300);
        case 0x8:
            Motor_Stop(); //lost catch all state
            break;
        case 0x9:
            Motor_Left(4000, 4000); //fast turn left
            break;
        case 0xA:
            Motor_Right(4000, 4000); //fast turn right
            break;
        default:
            break;
    }
}


void SysTick_Handler(void){
    volatile static uint8_t count = 0;

    if(count % 10 == 0)
        Reflectance_Start();

    else if(count % 10 == 1) {
                data = Reflectance_End();
                Input = Reflectance_Position(data); //READ IN REFLECTANCE DATA AND CHANGE STATE
                motorState(StatePtr->out);
                StatePtr = StatePtr->next[Input];
    }
    count++;
}


void collision(uint8_t bump){
    StatePtr = Lost;
}

