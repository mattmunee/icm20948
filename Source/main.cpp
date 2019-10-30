#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "ICM_20948_REGISTERS.h"
#include "Icm20948Device.hpp"

/* main.c */
int main(int argc, char *argv[]) {
    printf("Hello\n");

	Icm20948Device dev(1,0x68);
	ICM_20948_WHO_AM_I_t whoIsDev;
	Icm20948ErrorCodes success = dev.whoAmI(whoIsDev);
	printf("Result of Who Am I?: %02x\n", whoIsDev.WHO_AM_I);
	
    return 0;
}
