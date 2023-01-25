
#ifndef ADXL345_H_
#define ADXL345_H_

#include "i2c.h"

#define dev_id_reg                 (0x00)
#define dev_addr                   (0x53)
#define data_format_reg            (0x31)
#define pwr_ctrl_reg               (0x2D)
#define data_start_addr            (0x32)
#define fourG                      (0x01) // see range bits use as 0-1 bits of data format reg
#define reset                      (0x00) // see wakeup  of power_ctrl
#define set_measure_G              (0x08) // see measure of power_ctrl




void adxl_init(void);
void read_adxl_byte(uint8_t reg);
void write_adxl(uint8_t reg, char value);
void read_adxl_nbyte(uint8_t reg);


#endif
