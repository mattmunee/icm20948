#include <iostream>
#include <iomanip>
#include "Icm20948Device.hpp"

/* main.c */
int main(int argc, char *argv[]) {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << "Instantiating ICM-20948 Device" << std::endl;

	Icm20948Device dev(1,0x68);
	Icm20948ErrorCodes success;
	std::vector<int16_t> accel = {0,0,0};
	success = dev.openDevice();
	if (SUCCESS != success) {
		std::cout << "Error! Failed to open device: " << success << std::endl;
	}
	else {
		std::cout << "Successfully opened device." << std::endl;
	}

	ICM_20948_WHO_AM_I_t whoIsDev;
	success = dev.whoAmI(whoIsDev);
	if (SUCCESS != success) {
		std::cout << "Failed to return Who I Am! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout << "Result of Who Am I?: " 
			<< "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(whoIsDev.WHO_AM_I) << std::endl;
	}
	
	std::cout<<"Sleep"<<std::endl;
	success = dev.sleep(true);
	if (SUCCESS != success) {
		std::cout << "Failed to Sleep! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to Sleep! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout<<"Wake"<<std::endl;
	success = dev.sleep(false);
	if (SUCCESS != success) {
		std::cout << "Failed to Wake! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to Sleep! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout<<"Sleep"<<std::endl;
	success = dev.sleep(true);
	if (SUCCESS != success) {
		std::cout << "Failed to Sleep! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to Sleep! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout<<"Wake"<<std::endl;
	success = dev.sleep(false);
	if (SUCCESS != success) {
		std::cout << "Failed to Wake! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to Sleep! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}
		
    return 0;
}
