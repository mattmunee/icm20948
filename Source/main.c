#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "ICM_20948_REGISTERS.h"

/* main.c */
int main(int argc, char *argv[]) {
    printf("Hello\n");

    int file;
    int adapter_nr = 1; /* probably dynamically determined */
    int addr = 0x68;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
    if (ioctl(file,I2C_SLAVE,addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
    
    __u8 reg = WHO_AM_I; /* Device register to access */
  //__s32 res;
  ICM_20948_WHO_AM_I_t res;
  char buf[10];
  printf("Size of ICM_20948_WHO_AM_I_t: %d",sizeof(ICM_20948_WHO_AM_I_t));
  /* Using SMBus commands */
  res = i2c_smbus_read_word_data(file, reg);
  if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
  } else {
    printf("Result at register %02x: %02x\n",reg,res);
    /* res contains the read word */
  }

  /*
   * Using I2C Write, equivalent of
   * i2c_smbus_write_word_data(file, reg, 0x6543)
   */
  buf[0] = reg;
  buf[1] = 0x43;
  buf[2] = 0x65;
  if (write(file, buf, 3) != 3) {
    /* ERROR HANDLING: i2c transaction failed */
  }

  /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
  if (read(file, buf, 1) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
  } else {
    /* buf[0] contains the read byte */
  }
    return 0;
}
