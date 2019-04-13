#ifndef BUZZER_H
#define BUZZER_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// Repository:
//  UMSATS>Avionics-2019
//
// File Description:
//  Header file for buzzer.c
//
// History
// 2019-01-13 by Cole Wiebe
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "stm32f4xx_hal.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define COUNTER (84000000 * ((1/FREQ)/2)) //84000000 = clock frequency in hz
#define FREQ 4000 //in hertz
#define SECOND 4000
#define PIN1 GPIO_PIN_4
#define PIN2 GPIO_PIN_5


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Initializes the pins being used by the buzzer and the timer
//
// Returns:
//  void
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Initialization(void);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  makes a buzzer buzz for a given amount of seconds
//
// Returns:
//  int seconds
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void buzz(int seconds);

void Error_Handler(void);

#endif // BUZZER_H
