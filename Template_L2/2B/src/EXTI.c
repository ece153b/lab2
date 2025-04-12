/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2B
 */

#include "EXTI.h"
#include "LED.h"

void EXTI_Init(void) {
	// Initialize User Button
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER &= ~(GPIO_MODER_MODE13); //Set PC13 to input
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13); //Set PC13 to no pull up no pull down

	
	// Configure SYSCFG EXTI
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR1_EXTI4;//double check
	SYSCFG->EXTICR[3] |= ~SYSCFG_EXTICR1_EXTI4;

	
	// Configure EXTI Trigger
	// [TODO]
	
	// Enable EXTI
	// [TODO]
	
	// Configure and Enable in NVIC
	// [TODO]
}

// [TODO] Write Interrupt Handlers (look in startup_stm32l476xx.s to find the 
// interrupt handler names that you should use)

void ExampleInterruptHandler(void) {
	// Clear interrupt pending bit
	
	// Define behavior that occurs when interrupt occurs
}