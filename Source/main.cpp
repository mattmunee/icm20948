#include <iostream>
#include <iomanip>
#include "Icm20948Device.hpp"
#include <unistd.h>

/* main.c */
int main(int argc, char *argv[]) {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << "Instantiating ICM-20948 Device" << std::endl;

	Icm20948Device dev(1,0x68);
	Icm20948ErrorCodes success;
	std::vector<int16_t> rawaccel = {0,0,0};
	std::vector<float> accel = { 0.0,0.0,0.0 };
	unsigned int womThreshold = 0;

	success = dev.openDevice();
	if (SUCCESS != success) {
		std::cout << "Error! Failed to open device: " << success << std::endl;
	}
	else {
		std::cout << "Successfully opened device." << std::endl;
	}

	std::cout << "Reset" << std::endl;
	success = dev.reset();
	if (SUCCESS != success) {
		std::cout << "Failed to Reset! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Who am I?" << std::endl;
	ICM_20948_WHO_AM_I_t whoIsDev;
	success = dev.whoAmI(whoIsDev);
	if (SUCCESS != success) {
		std::cout << "Failed to return Who I Am! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Result of Who Am I?: " 
		<< "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(whoIsDev.WHO_AM_I) << std::endl;

	std::cout<<"Wake"<<std::endl;
	success = dev.sleep(false);
	if (SUCCESS != success) {
		std::cout << "Failed to Wake! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Getting WOM Threshold " << std::endl;
	success = dev.getWomThreshold(womThreshold);
	if (SUCCESS != success) {
		std::cout << "Failed to get WOM Threshold! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "WOM Threshold: " << womThreshold << std::endl;
	}

	womThreshold = 100;
	std::cout << "Setting WOM Threshold to " << womThreshold << std::endl;

	success = dev.setWomThreshold(womThreshold);
	if (SUCCESS != success) {
		std::cout << "Failed to set WOM Threshold! Return Value: " << (unsigned)success << std::endl;
	}
	
	std::cout << "Getting WOM Threshold " << std::endl;
	success = dev.getWomThreshold(womThreshold);
	if (SUCCESS != success) {
		std::cout << "Failed to get WOM Threshold! Return Value: " << (unsigned)success << std::endl;
	}
	else {
		std::cout.flags(f);
		std::cout << "WOM Threshold: " << womThreshold << std::endl;
	}	

	std::cout << "Enabling WOM Logic " << std::endl;
	success = dev.enableWomLogic(true, ALGO_RUNNING_COMPARISON_CURRENT_TO_PREVIOUS);
	if (SUCCESS != success) {
		std::cout << "Failed to enable WOM logic! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Enabling WOM Interrupt " << std::endl;
	success = dev.enableWomInterrupt(true);
	if (SUCCESS != success) {
		std::cout << "Failed to enable WOM interrupt! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Clear Interrupts:" << std::endl;
	success = dev.clearInterrupts();
	if (SUCCESS != success) {
		std::cout << "Failed to clear interrupts! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Sleep" << std::endl;
	//success = dev.sleep(true);
	if (SUCCESS != success) {
		std::cout << "Failed to sleep! Return Value: " << (unsigned)success << std::endl;
	}

	std::cout << "Entering wait for interrupt loop " << std::endl;
	ICM_20948_INT_STATUS_t out_t;
	do {
		sleep(1);
		dev.getInterruptStatus(out_t);
		std::cout << "Interrupt Status: I2C_MST_INT=" << unsigned(out_t.I2C_MST_INT) 
			<< ", DMP_INT1=" << unsigned(out_t.DMP_INT1) 
			<< ", PLL_RDY_INT=" << unsigned(out_t.PLL_RDY_INT) 
			<< ", WOM_INT=" << unsigned(out_t.WOM_INT) << std::endl;

	} while (0 == out_t.WOM_INT);
		
    return 0;
}
