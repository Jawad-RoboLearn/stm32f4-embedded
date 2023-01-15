/* Author: Jawad Mehmood Butt*/
// Learn STM32 with Jawad
// LED


#include "led.h"



void led_init()
{
 // enable clk access
	RCC->AHB1ENR |= GPIOA_5;

// MODER
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}
