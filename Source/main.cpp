#include <iostream>
#include <iomanip>
#include "Icm20948Device.hpp"

/* main.c */
int main(int argc, char *argv[]) {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << "Instantiating ICM-20948 Device" << std::endl;

	Icm20948Device dev(1,0x68);
	Icm20948ErrorCodes success;
	std::vector<int16_t> rawaccel = {0,0,0};
	std::vector<float> accel = { 0.0,0.0,0.0 };
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

	std::cout<<"Wake"<<std::endl;
	success = dev.sleep(false);
	if (SUCCESS != success) {
		std::cout << "Failed to Wake! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(rawaccel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Raw Accel: " << rawaccel[0] << ", " << rawaccel[1] << ", " << rawaccel[2] << std::endl;
	}

	success = dev.getAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Scaled Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout << "Set Scale to 4G" << std::endl;
	success = dev.setAccelFS(ACCEL_FS_4G);
	if (SUCCESS != success) {
		std::cout << "Failed set accel scale! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(rawaccel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Raw Accel: " << rawaccel[0] << ", " << rawaccel[1] << ", " << rawaccel[2] << std::endl;
	}

	success = dev.getAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Scaled Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout << "Set Scale to 8G" << std::endl;
	success = dev.setAccelFS(ACCEL_FS_8G);
	if (SUCCESS != success) {
		std::cout << "Failed set accel scale! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(rawaccel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Raw Accel: " << rawaccel[0] << ", " << rawaccel[1] << ", " << rawaccel[2] << std::endl;
	}

	success = dev.getAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Scaled Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout << "Set Scale to 16G" << std::endl;
	success = dev.setAccelFS(ACCEL_FS_16G);
	if (SUCCESS != success) {
		std::cout << "Failed set accel scale! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(rawaccel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Raw Accel: " << rawaccel[0] << ", " << rawaccel[1] << ", " << rawaccel[2] << std::endl;
	}

	success = dev.getAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Scaled Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}

	std::cout << "Set Scale to 2G" << std::endl;
	success = dev.setAccelFS(ACCEL_FS_2G);
	if (SUCCESS != success) {
		std::cout << "Failed set accel scale! Return Value: " << (unsigned)success << std::endl;
	}

	success = dev.getRawAcceleration(rawaccel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Raw Accel: " << rawaccel[0] << ", " << rawaccel[1] << ", " << rawaccel[2] << std::endl;
	}

	success = dev.getAcceleration(accel);
	if (SUCCESS != success) {
		std::cout << "Failed to get raw accel! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "Scaled Accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << std::endl;
	}
		
    return 0;
}
