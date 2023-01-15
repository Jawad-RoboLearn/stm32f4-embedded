/* Author: Jawad Mehmood Butt*/
// Learn STM32 with Jawad
// LED


#ifndef LED_H_
#define LED_H_

#include "stm32f4xx.h"
#include <stdio.h>
#define GPIOA_5    (1U<<5)
#define led_pin    GPIOA_5

void led_init(void);


#endif
