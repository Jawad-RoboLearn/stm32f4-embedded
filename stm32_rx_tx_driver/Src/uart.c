/* Author: Jawad Mehmood Butt*/
// Learn STM32 with Jawad
// UART RX-TX Drivers

#include "uart.h"
#define usart_clk_enable   (1U<<17)
#define port_A_clk_enable  (1U<<0)
#define tx_enable          (1U<<3)
#define rx_enable          (1U<<2)
#define uart_enable        (1U<<13)
#define sr_txe             (1U<<7)
#define sr_rxne            (1U<<5)

#define sys_freq           16000000
#define clk_sig            sys_freq
#define baudrate           115200



// create the uart init function
void uart_init(void)
{
	// Part A: UART GPIO Pin setup
	// enable clock to APB1 as its connected to USART2 USB port
	RCC->AHB1ENR |= port_A_clk_enable;

	// MODER OF GPIOA to Alternate FCN mode PA2 TX
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Alternate function setting: See alternate fcn map in data sheet, PA2 for USART TX is AFR7
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8);

	// MODER OF GPIOA to Alternate FCN mode PA3 RX
		GPIOA->MODER &= ~(1U<<6);
		GPIOA->MODER |= (1U<<7);

		// Alternate function setting: See alternate fcn map in data sheet, PA2 for USART TX is AFR7
		GPIOA->AFR[0] &= ~(1U<<15);
		GPIOA->AFR[0] |= (1U<<14);
		GPIOA->AFR[0] |= (1U<<13);
		GPIOA->AFR[0] |= (1U<<12);

	// Part B: USART configuration
	RCC->APB1ENR |= usart_clk_enable; // clk enable
	set_baud(USART2, clk_sig, baudrate); // set baudrate
	USART2->CR1 = tx_enable; // transmitter enable
	USART2->CR1 |= rx_enable; // receiver enable
	USART2->CR1 |= uart_enable; // uart enable
	//USART2->CR1 &= word_length; // word length 1 start 8 data 1 stop

}


// set the baud rate for uart
uint16_t calc_baud(uint32_t clksignal, uint32_t baudval)
{
	return ((clksignal + (baudval/2U))/baudval);

}

void set_baud(USART_TypeDef *USARTx, uint32_t clksignal, uint32_t baudval)
{
	USARTx->BRR = calc_baud(clksignal, baudval);
}

char uart_read()
{
	while(!(USART2->SR & sr_rxne)){}
	return USART2->DR;
}

void uart_write_single(int x)
{
	// clear the data register by status register
	while(!(USART2->SR & sr_txe)){}
	// write data
	USART2->DR = (x & 0xFF);
}
