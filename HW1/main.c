/*
 * main.c
 *
 *  Created on: Jan 9, 2024
 *      Author: brophy
 */

#include "msp.h"

int modify_value(int z); // function prototype

int main(void)
{
    // variable Declaration
    int i, j, x, y, alpha, beta, finished;

    // variable initialization
    x = 0;
    y = 0;
    finished = 0;
    alpha = 10;
    beta = 3;

    // main loop
    for(i = 0; i < alpha; i++)
    {
        for(j = 0; j < beta; j++)
        {
            y = modify_value(y); // change the argument to y to increment
        }
    }
    // flag indicating finished
    finished = 1; // y should be 30 at the end

    return 0;
}

// function definition
int modify_value(int z)
{
    //int w; don't need this variable
    z = z + 1; // increment passed parameter

    return(z); // return modified value
}
