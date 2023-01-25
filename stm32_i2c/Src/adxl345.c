// ADXL345 by Jawad

#include "adxl345.h"
char data;
uint8_t data_rec[6];


// The function that should read a single byte
void read_adxl_byte(uint8_t reg)
{
	read_i2c_byte(dev_addr, reg, &data);
}

// the function that should write a single byte
void write_adxl(uint8_t reg, char value)
{
	// we want to use i2c_single_write
	char data_byte[1];
	data_byte[0] = value;

	i2c_burst_write(dev_addr, reg, 1, data_byte); // here data is value not address
}

// function that should read multibytes
void read_adxl_nbyte(uint8_t reg)
{
	i2c_burst_read(dev_addr, reg, 6, (char *)data_rec);
}

void adxl_init(void)
{
	// read the device id and it should return 0xE5
	read_adxl_byte(dev_id_reg);

	// we will set the data_format register to +-4G
	write_adxl(data_format_reg, fourG);

	// reset all bits
	write_adxl(pwr_ctrl_reg, reset);

    // configure power_ctrl measure bit
	write_adxl(pwr_ctrl_reg, set_measure_G);

}
