#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define DLP_WRITE(ARRAY) (dlp_write(ARRAY, sizeof(ARRAY)))  //Macros for get array size in function argument

#define I2C_BUS "/dev/i2c-1"
#define DLP_ADDR 0x1b

#define BYTE_COUNT 5


void i2c_open(char *i2cBus, int addr);
void i2c_close();
int i2c_write(uint8_t reg, uint32_t value);
uint32_t i2c_read(uint8_t reg);

void dlp_write(uint8_t array[], int array_size);
void dlp_icp_write(uint32_t cmd, uint32_t param);

#endif // I2C_H
