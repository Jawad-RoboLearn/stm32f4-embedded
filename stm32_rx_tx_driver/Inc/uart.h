/* Author: Jawad Mehmood Butt*/
// Learn STM32 with Jawad
// UART RX-TX Drivers


#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include <stdint.h>

void uart_init(void);

uint16_t calc_baud(uint32_t clksignal, uint32_t baudval);
void set_baud(USART_TypeDef *USARTx, uint32_t clksignal, uint32_t baudval);
void uart_write_single(int x);
char uart_read(void);


#endif
