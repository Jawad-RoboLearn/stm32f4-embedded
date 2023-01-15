/* TRANSMIT and Receive through the UART : STM32 UART */
// Example Code
/*Jawad Mehmood Butt*/

#include "stm32f4xx.h"
#include "uart.h"
#include "led.h"

char data_rx;




int main(void)
{
	uart_init();
	led_init();
	while(1)
	{
		//uart_write_single('Y'); Transmit Y


		// Receive data and turn on LED
		data_rx = uart_read();
		if (data_rx == '1')
		{
			GPIOA->ODR |= led_pin;
		}
		else
		{
			GPIOA->ODR &= ~led_pin;
		}
	}




	return 0;
}
