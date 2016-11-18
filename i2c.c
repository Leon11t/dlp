#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include "i2c.h"


int file;
void i2c_open(char *i2cBus, int addr)
{
    int status;
    file = open(i2cBus, O_RDWR);
    if (file < 0)
    {
        printf("ERROR: open (%s) failed\n", i2cBus);
        exit(1);
    }

    status = ioctl(file, I2C_SLAVE, addr);
    if (status < 0)
    {
        printf("ERROR: set the i2c-address: 0x%02x\n", addr);
        close(file);
        exit(1);
    }
}

void i2c_close()
{
    close(file);
}

int i2c_write(uint8_t reg, uint32_t value)
{
    uint8_t data[5];

    data[0] = reg;

    data[1] = (value >> 24);
    data[2] = (value >> 16);
    data[3] = (value >> 8);
    data[4] = (value >> 0);

    printf("0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n", data[0], data[1], data[2], data[3], data[4]);
    if (write(file, data, 5) != 5) {
        printf("ERROR: write data failur");
        return 1;
    }
    return 0;
}

uint32_t i2c_read(uint8_t reg)
{
    uint8_t write_data[2];
    uint8_t read_data[4];
    write_data[0] = 0x15;
    write_data[1] = reg;

    if (write(file, write_data, 2) != 2) {
        printf("ERROR: i2c_read - write data failur");
    }

    if (read(file, read_data, 4) != 4) {
        printf("ERROR: i2c_read - read data failur");
    }

    return (read_data[0] << 24) | (read_data[1] << 16) | (read_data[2] << 8) | (read_data[3] << 0);
}

void dlp_write(uint8_t array[], int array_size)
{
    for(int i =0; i < array_size; i = i+BYTE_COUNT)
    {
        i2c_open(I2C_BUS, DLP_ADDR);
        uint8_t data[4] = {0};
        uint8_t reg = array[i];
        int index = i;
        uint32_t value = 0;

        for(int j = 1; j < (BYTE_COUNT); j++)
        {
            index = i+j;
            data[j-1] = array[index];
            value = value << 8;
            value |= data[j-1];
        }
        int error = i2c_write(reg, value);
        if(error > 0)
        {
            i2c_close();
            exit(1);
        }
        i2c_close();

    }
}

void dlp_icp_write(uint32_t cmd, uint32_t param)
{
    i2c_open(I2C_BUS, DLP_ADDR);
    i2c_write(0x3a, 1);
    i2c_write(0x39, param);
    i2c_write(0x38, cmd);
    usleep(200000);
    i2c_close();
}
