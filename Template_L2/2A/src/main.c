/*
 * ECE 153B
 *
 * Name(s): Vishal S. and Aden J. 
 * Section: Tuesdays @ 6 PM
 * Lab: 2A
 */

#include "stm32l476xx.h"

void GPIO_Init(void){	
	//Enable clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	//Configure pins as output
	GPIOC->MODER  |= GPIO_MODER_MODE5_0; //Pin 5 output
	GPIOC->MODER  |= GPIO_MODER_MODE6_0; //Pin 6 output
	GPIOC->MODER  |= GPIO_MODER_MODE8_0; //Pin 8 output
	GPIOC->MODER  |= GPIO_MODER_MODE9_0; //Pin 9 output

	//Set output speed to fast
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_1; //Pin 5 fast
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_1; //Pin 6 fast
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_1; //Pin 8 fast
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_1; //Pin 9 fast	
	
	//Set output type to push pull
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT5); //Pin 5
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT6); //Pin 6
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT8); //Pin 8
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT9); //Pin 9

	//Set pins to no pull-up, no pull-down
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD5); //Pin 5
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD6); //Pin 6
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD8); //Pin 8
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD9); //Pin 9
}


#define DELAY 60000	// delay between steps of the sequences

void Full_Stepping_Clockwise(void){
	//Step 1
	GPIOC->ODR &= ~(GPIO_ODR_OD5); 
	GPIOC->ODR |= GPIO_ODR_OD6; 
	GPIOC->ODR |= GPIO_ODR_OD8; 
	GPIOC->ODR &= ~(GPIO_ODR_OD9);
	for(int i = 0; i < DELAY; i++){} 
	
	
	//Step 2
	GPIOC->ODR &= ~(GPIO_ODR_OD5); 
	GPIOC->ODR |= GPIO_ODR_OD6; 
	GPIOC->ODR &= ~(GPIO_ODR_OD8);
	GPIOC->ODR |= GPIO_ODR_OD9; 
	for(int i = 0; i < DELAY; i++){} 

	
	//Step 3
	GPIOC->ODR |= GPIO_ODR_OD5; 
	GPIOC->ODR &= ~(GPIO_ODR_OD6); 
	GPIOC->ODR &= ~(GPIO_ODR_OD8);
	GPIOC->ODR |= GPIO_ODR_OD9; 
	for(int i = 0; i < DELAY; i++){} 

	
	//Step 4
	GPIOC->ODR |= GPIO_ODR_OD5; 
	GPIOC->ODR &= ~(GPIO_ODR_OD6); 
	GPIOC->ODR |= GPIO_ODR_OD8; 
	GPIOC->ODR &= ~(GPIO_ODR_OD9);
	for(int i = 0; i < DELAY; i++){} 

	
}

void Full_Stepping_CounterClockwise(void){
	// [TODO]
}

void Half_Stepping_Clockwise(void){
	// [TODO]	
}

void Half_Stepping_CounterClockwise(void){
	// [TODO]
}


int main(void){
	GPIO_Init();
	
	// Rotate 360 degrees either clockwise or counter-clockwise
	Full_Stepping_Clockwise(); 
}
