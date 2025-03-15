/*
 * SYSTICK.H
 *
 *  Created on: Jul 26, 2024
 *      Author: dell
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"
#include "tm4c123gh6pm_registers.h"
/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")


#define SysClock_Freq 16*(1000000) //16 MHZ
static volatile void (*g_CallBackPtr)(void) = NULL_PTR; //callback pointer to function

/*******************************************************************************
 *                           Functions Prototypes                           *
 *******************************************************************************/
/*Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts.
 *             This function is used to setup the timer to generate periodic interrupts every specified time in milliseconds.*/
void SysTick_Init(uint16 a_TimeInMilliSeconds);


/*Description: Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique.
 *             The function should exit when the time is elapsed and stops the timer at the end. */
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

//Description: Handler for SysTick interrupt use to call the call-back function.
void SysTick_Handler(void);

//Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));

//Description: Stop the SysTick timer.
void SysTick_Stop(void);

// Description: Start/Resume the SysTick timer.
void SysTick_Start(void);

//Description: Function to De-initialize the SysTick Timer.
void SysTick_DeInit(void);

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
#endif /* SYSTICK_H_ */
