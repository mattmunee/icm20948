#include <iostream>
#include "Icm20948Device.hpp"

/* main.c */
int main(int argc, char *argv[]) {
	std::cout << "Instantiating ICM-20948 Device" << std::endl;

	Icm20948Device dev(1,0x68);
	ICM_20948_WHO_AM_I_t whoIsDev;
	Icm20948ErrorCodes success = dev.whoAmI(whoIsDev);
	if (SUCCESS != success) {
		std::cout << "Error! Return Value: " << success << std::endl;
	}
	else {
		std::cout << "Result of Who Am I?: " << whoIsDev.WHO_AM_I << std::endl;
	}
	
	
    return 0;
}
