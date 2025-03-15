/*
 * SYSTICK.C
 *
 *  Created on: Jul 26, 2024
 *      Author: dell
 */

#include "SysTick.H"
//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts.
                This function is used to setup the timer to generate periodic interrupts every specified time in milliseconds.
 *************************************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;               /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = ((a_TimeInMilliSeconds/1000) * (SysClock_Freq))-1;         /* Set the Reload value */
    SYSTICK_CURRENT_REG = 0;               /* Clear the Current Register value */

    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SysTick_Start();
    SYSTICK_CTRL_REG |= 0x06;
}

//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique.
                The function should exit when the time is elapsed and stops the timer at the end.
 *************************************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = ((a_TimeInMilliSeconds/1000) * (SysClock_Freq))-1;        /* Set the Reload value */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */

    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SysTick_Start();
    SYSTICK_CTRL_REG |= 0x04;

    /*wait until the time is elapsed*/
    while(!(SYSTICK_CTRL_REG & (1<<16))); /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */

    /*stops the timer*/
    SysTick_Stop();
}

//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt use to call the call-back function.
 *************************************************************************************/
void SysTick_Handler(void){
    if(g_CallBackPtr != NULL_PTR){
        (*g_CallBackPtr)(); //calls the callback function.
    }
}

//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): void(*Ptr2Func)(void) - pointer that receives(holds) the address of the call back function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
 *************************************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
    g_CallBackPtr = Ptr2Func; //the pointer now has the address of the callback function
}

//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Stop the SysTick timer.
 *************************************************************************************/
void SysTick_Stop(void){
    /*stops the timer*/
    SYSTICK_CTRL_REG   &= ~(1<<0);//Disable SysTick
}
//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Start/Resume the SysTick timer.
 *************************************************************************************/
void SysTick_Start(void){
    /*enable SysTick timer*/
    SYSTICK_CTRL_REG   |= (1<<0);
}
//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
/************************************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to De-initialize the SysTick Timer.
 *************************************************************************************/
void SysTick_DeInit(void){
    SysTick_Stop();
    SYSTICK_RELOAD_REG  = 0;    /* Clear the Reload register */
    SYSTICK_CURRENT_REG = 0;    /* Clear the Current Register value */
}
//////////////////////////////////////////////////////////////////////////////////////**********************************************************************************************************************/
