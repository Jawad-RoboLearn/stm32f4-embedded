// I2C by Jawad Mehmood Butt

#include "adxl345.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

extern uint8_t data_rec[6];
int16_t x, y, z;
float xg, yg, zg;
float scale_G = 0.0078;

int main(void)
{
	adxl_init();

	while(1)
	{
		read_adxl_nbyte(data_start_addr); // read the start of data address
		x = ((data_rec[1]<<8) | data_rec[0]); // shift data_rec[1] to bit # 9-16
		y = ((data_rec[3]<<8) | data_rec[2]);// shift data_rec[3] to bit # 9-16
		z = ((data_rec[5]<<8) | data_rec[4]);// shift data_rec[5] to bit # 9-16

		xg = x * scale_G;
		yg = y * scale_G;
		zg = z * scale_G;
	}
	return 0;
}

