// I2C Drivers for STM32F4 by Jawad Mehmood Butt
// Tested on STM32F411RE

#include "i2c.h"

#define portB_clk_en         (1U<<1)
#define i2c_clk_en           (1U<<21)
#define i2c_100khz           80
#define sd_rise_edge         17
#define i2c_pe               (1U<<0)
#define i2c_sr_busy          (1U<<1)
#define i2c_cr1_start        (1U<<8)
#define i2c_sr1_start_flag   (1U<<0)
#define i2c_sr1_addr_flag    (1U<<1)
#define i2c_sr1_txe          (1U<<7)
#define i2c_cr1_ack          (1U<<10)
#define i2c_cr1_stop         (1U<<9)
#define i2c_sr1_rxne         (1U<<6)
#define i2c_sr1_btf          (1U<<2)


void i2c_init(){

	// Port B Clk Enable
	RCC->AHB1ENR |= portB_clk_en;

	// I2C Clk Enable
	RCC->APB1ENR |= i2c_clk_en;

	// SDA = D14 pin => PB9 = i2c1_sda,
	// SCL = D15 pin => PB8 = i2c1_scl

	// Alternate function mode for PB8 and PB9
    GPIOB->MODER |= (1U<<17);
    GPIOB->MODER &= ~(1U<<16);
    GPIOB->MODER |= (1U<<19);
    GPIOB->MODER &= ~(1U<<18);

    // output type register, set to open drain
    GPIOB->OTYPER |= (1U<<8);
    GPIOB->OTYPER |= (1U<<9);

    // pull up the PB8 and PB9 GPIOx_PUPDR
    GPIOB->PUPDR |= (1U<<16);
    GPIOB->PUPDR &= ~(1U<<17);
    GPIOB->PUPDR |= (1U<<18);
    GPIOB->PUPDR &= ~(1U<<19);

    // enter and exit reset
    I2C1->CR1 |= (1U<<15);
    I2C1->CR1 &= ~(1U<<15);

    // we keep the frequency of 16MHz see freq 0-5 bits of I2C_CR2
    I2C1->CR2 |= (1U<<4);

    // we keep I2C standard mode operating at 100KHz
    I2C1->CCR = i2c_100khz;

    // RISE EDGE
    I2C1->TRISE = sd_rise_edge;

    // periph enable
    I2C1->CR1 |= i2c_pe;

}

void read_i2c_byte(char slave_addr, char mem_addr, char* data){
	// check if the I2C is not busy
    while (I2C1->SR2 & (i2c_sr_busy)){}

    // start
    I2C1->CR1 |= i2c_cr1_start;

    // wait until start bit sets
    while (!(I2C1->SR1 & (i2c_sr1_start_flag))){}

    // transmit slave addr + write
    I2C1->DR = slave_addr << 1; // to position 1

    // wait for the addr flag to set
    while (!(I2C1->SR1 & (i2c_sr1_addr_flag))){}

    // clear the addr flag : See note reference manual 18.6.7
    volatile int tmp;
    tmp = I2C1->SR2;

    // send memory address
    I2C1->DR = mem_addr;

    // wait transmitter is empty
    while (!(I2C1->SR1 & (i2c_sr1_txe))){}

    // restart
    I2C1->CR1 |= i2c_cr1_start;

    // wait until start bit sets
    while (!(I2C1->SR1 & (i2c_sr1_start_flag))){}

    // transmit slave addr + read
    I2C1->DR = slave_addr << 1 | 1; // to position 1

    // wait for the addr flag to set
    while (!(I2C1->SR1 & (i2c_sr1_addr_flag))){}

    // disable the ack
    I2C1->CR1 &= ~i2c_cr1_ack;

    // clear the addr flag
    tmp = I2C1->SR2;

    // stop
    I2C1->CR1 |= i2c_cr1_stop;

    // wait for the RXNE to set (check if the data register are empty)
      while (!(I2C1->SR1 & (i2c_sr1_rxne))){}

    // read data from DR
    *data++ = I2C1->DR;

}

void i2c_burst_read(char slave_addr, char mem_addr, int nbyte, char* data)
{
	volatile int tmp;

	// not busy
	while(I2C1->SR2 & (i2c_sr_busy)){}

	// generate start
	I2C1->CR1 |= i2c_cr1_start;

	// wait to start
	while(!(I2C1->SR1 & (i2c_sr1_start_flag))){}

    // tx address + write
	I2C1->DR = slave_addr << 1;

	// wait for addr flag
	while(!(I2C1->SR1 & (i2c_sr1_addr_flag))){}

	// clear addr
	tmp = I2C1->SR2;

	// transmit mem addr
	I2C1->DR = mem_addr;

	 // wait transmitter is empty
	 while (!(I2C1->SR1 & (i2c_sr1_txe))){}

	 // restart
	 I2C1->CR1 |= i2c_cr1_start;

	 // wait until start bit sets
	 while (!(I2C1->SR1 & (i2c_sr1_start_flag))){}

	 // transmit slave addr + read
	 I2C1->DR = slave_addr << 1 | 1; // to position 1

	 // wait for the addr flag to set
	    while (!(I2C1->SR1 & (i2c_sr1_addr_flag))){}

     // clear addr
     tmp = I2C1->SR2;

     // enable the ack
     I2C1->CR1 |= i2c_cr1_ack;

     while(nbyte > 0U)
     {
    	 if (nbyte == 1)
    	 {
    		    // disable the ack
    		    I2C1->CR1 &= ~i2c_cr1_ack;
    		    // stop
    		    I2C1->CR1 |= i2c_cr1_stop;
    		    // wait for the RXNE to set (check if the data register are empty)
    		    while (!(I2C1->SR1 & (i2c_sr1_rxne))){}

    		    // read data from DR
    		    *data++ = I2C1->DR;

    		    break;
    	 }
    	 else
    	 {
    		 // wait for the RXNE to set (check if the data register are empty)
    	     while (!(I2C1->SR1 & (i2c_sr1_rxne))){}
    	     // read data from DR
    	     (*data++) = I2C1->DR;

    	     nbyte--;
    	 }
     }
}


void i2c_burst_write(char slave_addr, char mem_addr, int nbyte, char* data)
{
	volatile int tmp;
	// busy flag
	// not busy

		while(I2C1->SR2 & (i2c_sr_busy)){}

		// generate start
		I2C1->CR1 |= i2c_cr1_start;

		// wait to start
		while(!(I2C1->SR1 & (i2c_sr1_start_flag))){}

	    // tx address + write
		I2C1->DR = slave_addr << 1;

		// wait for addr flag
		while(!(I2C1->SR1 & (i2c_sr1_addr_flag))){}

		// clear addr
		tmp = I2C1->SR2;

		// wait transmitter is empty
		while (!(I2C1->SR1 & (i2c_sr1_txe))){}

		// transmit mem addr
		I2C1->DR = mem_addr;

		for (int i = 0; i<=nbyte; i++)
		{
			// wait transmitter is empty
			while (!(I2C1->SR1 & (i2c_sr1_txe))){}

			//write
			I2C1->DR = *data++;
		}

		while (!(I2C1->SR1 & (i2c_sr1_btf))){}

	    // stop
	    I2C1->CR1 |= i2c_cr1_stop;
}
