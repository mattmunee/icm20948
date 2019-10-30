#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "ICM_20948_REGISTERS.h"
#include "Icm20948Device.hpp"

ICM_20948_WHO_AM_I_t getWhoAmI(unsigned short adapter_number, long device_address){
	int file;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_number);
    if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
    if (ioctl(file,I2C_SLAVE,device_address) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
	__u8 reg = REG_WHO_AM_I; /* Device register to access */
	__s32 res;
	ICM_20948_WHO_AM_I_t res_t;
	
	char buf[10];
	printf("Size of ICM_20948_WHO_AM_I_t: %d",sizeof(ICM_20948_WHO_AM_I_t));
	/* Using SMBus commands */
	res = i2c_smbus_read_word_data(file, reg);
	if (res < 0) {
		/* ERROR HANDLING: i2c transaction failed */
	} else {
		printf("Result at register %02x: %02x\n",reg,res);
		res_t.WHO_AM_I = (uint8_t)((res >> WHO_AM_I_BIT_INDEX) & WHO_AM_I_BIT_MASK);
		return res_t;
	}
}
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
    
	ICM_20948_WHO_AM_I_t whoAmI = getWhoAmI(adapter_nr,addr);
	printf("Result of Who Am I?: %02x\n",whoAmI.WHO_AM_I);
	
    return 0;
}
