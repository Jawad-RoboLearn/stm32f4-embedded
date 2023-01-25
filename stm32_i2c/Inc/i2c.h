// I2C by Jawad

#ifndef I2C_H_
#define I2C_H_


#include "stm32f4xx.h"
void i2c_init(void);
void read_i2c_byte(char slave_addr, char mem_addr, char* data);
void i2c_burst_read(char slave_addr, char mem_addr, int nbyte, char* data);
void i2c_burst_write(char slave_addr, char mem_addr, int nbyte, char* data);

#endif
