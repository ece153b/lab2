/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2C
 */
 
#include "stm32l476xx.h"

#include "LED.h"
#include "RTC.h"
#include "SysClock.h"

char strTime[12] = {0};
char strDate[12] = {0};

void RTC_Set_Alarm(void) {
	//Disable both alarms
	RTC->CR &= ~(RTC_CR_ALRAE); 
	RTC->CR &= ~(RTC_CR_ALRBE);
	
	//Remove write protection
	RTC_Disable_Write_Protection(); 
	
	//Clear alarm enable bits and the interrupt enable bits
	RTC->CR &= ~(RTC_CR_ALRAE); 
	RTC->CR &= ~(RTC_CR_ALRBE);
	
	RTC->CR &= ~(RTC_CR_ALRAIE); 
	RTC->CR &= ~(RTC_CR_ALRBIE); 
	
	//wait until access to both registers is allowed
	while(!((RTC->ISR & RTC_ISR_ALRAWF) == RTC_ISR_ALRAWF) || !((RTC->ISR & RTC_ISR_ALRBWF) == RTC_ISR_ALRBWF))
	{}

	//Set alarm A for every 30 seconds
	RTC->ALRMAR |= RTC_ALRMAR_MSK4; 
	RTC->ALRMAR |= RTC_ALRMAR_MSK3; 
	RTC->ALRMAR |= RTC_ALRMAR_MSK2; 
	RTC->ALRMAR &= ~(RTC_ALRMAR_MSK1); 
	RTC->ALRMAR &= ~(RTC_ALRMAR_ST); //Clear tens seconds register
	RTC->ALRMAR &= ~(RTC_ALRMAR_SU); //Clear unit seconds register
	RTC->ALRMAR |= (0x03 << 4); 	 //Set tens seconds regisiter to 3
	RTC->ALRMAR |= (0X00 << 0); 	 //Set units seconds register to 0
		
	//Set alarm B for every 1 seconds
	RTC->ALRMBR |= RTC_ALRMBR_MSK4; 
	RTC->ALRMBR |= RTC_ALRMBR_MSK3; 
	RTC->ALRMBR |= RTC_ALRMBR_MSK2; 
	RTC->ALRMBR |= RTC_ALRMBR_MSK1; 
	/*
	RTC->ALRMBR &= ~(RTC_ALRMBR_MSK1); 
	RTC->ALRMBR |= (0x00 << 4); 	
	RTC->ALRMBR |= (0X01 << 0);
	*/

	//Enable both alarms - COMMENT OUT UNNEEDED ALARM HERE
	//RTC->CR |= RTC_CR_ALRAE; 
	RTC->CR |= RTC_CR_ALRBE;
	//RTC->CR |= RTC_CR_ALRAIE; 
	RTC->CR |= RTC_CR_ALRBIE; 
	
	//Enable write protection
	RTC_Enable_Write_Protection(); 
}

void RTC_Alarm_Enable(void) {
	// Configure EXTI Trigger
	EXTI->RTSR1 |= EXTI_RTSR1_RT18;
	
	// Set interrupt mask and event mask
	EXTI->IMR1 |= EXTI_IMR1_IM18;
	EXTI->EMR1 |= EXTI_EMR1_EM18; 
	
	//Clear pending interrupt
	EXTI->PR1 |= EXTI_PR1_PIF18; 
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	NVIC_SetPriority(RTC_Alarm_IRQn, 0); 
}

void RTC_Alarm_IRQHandler(void) {
	// Clear interrupt pending bit
	/*
	Green_LED_Toggle(); 
	RTC->ISR &= ~(RTC_ISR_ALRAF); 
	RTC->ISR &= ~(RTC_ISR_ALRBF); 
	EXTI->PR1 |= EXTI_PR1_PIF18;
	*/
	
	if((RTC->ISR & RTC_ISR_ALRAF) == RTC_ISR_ALRAF)
	{
		//Alarm A
		Green_LED_Toggle();
		EXTI->PR1 |= EXTI_PR1_PIF18;
		RTC->ISR &= ~(RTC_ISR_ALRAF); 
	}
	else if((RTC->ISR & RTC_ISR_ALRBF) == RTC_ISR_ALRBF)
	{
		//Alarm B
		Green_LED_Toggle(); 
		EXTI->PR1 |= EXTI_PR1_PIF18;
		RTC->ISR &= ~(RTC_ISR_ALRBF); 
	}


}

int main(void) {	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	LED_Init();
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		Get_RTC_Calendar(strTime, strDate); 
	}
}
