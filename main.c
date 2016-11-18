#include <stdio.h>
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
#include "PRJ_Data.h"

int main(void)

{

        DLP_WRITE(Internal_pattern_direction);
        DLP_WRITE(nHD_RGB888);
        DLP_WRITE(InitData_FlashDataLoading);

        i2c_open(I2C_BUS, DLP_ADDR);
        printf("Read Data 0X%08x\n", i2c_read(0x07));
        i2c_close();

        DLP_WRITE(InitData_TransferCtrlToI2C);
        usleep(2000000);

        DLP_WRITE(RGB_led_on);
        DLP_WRITE(I_white);
        DLP_WRITE(Free_run);

   //    i2c_open(I2C_BUS, DLP_ADDR);
  //    i2c_write(0x1f, 0);
 //      usleep(200000);





//printf("Version 0X%08x\n", i2c_read(0xeb));
//printf("Version 0X%08x\n", i2c_read(0xec));
//printf("Version 0X%08x\n", i2c_read(0xf0));


       i2c_close();
       usleep(100000);
    //}


}

