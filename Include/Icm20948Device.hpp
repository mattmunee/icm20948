#ifndef ICM_20948_DEVICE_HPP
#define ICM_20948_DEVICE_HPP

#include "ICM_20948_REGISTERS.h"
#include <linux/types.h>
#include <string>
#include <iostream>
#include <vector>

typedef enum {
	SUCCESS,
	FAILED_TO_OPEN_ADAPTER,
	FAILED_TO_TALK_TO_SLAVE,
	FAILED_TO_READ_WORD_DATA,
	DEVICE_NOT_OPEN,
	INVALID_USER_BANK,
	INVALID_ACCEL_RANGE,
	INVALID_WOM_THRESHOLD
}Icm20948ErrorCodes;

typedef enum {
	ACCEL_FS_2G = 0,
	ACCEL_FS_4G = 1,
	ACCEL_FS_8G = 2,
	ACCEL_FS_16G = 3,
}AccelScale;

class Icm20948Device {
public:
	
	Icm20948Device(
		unsigned short adapter_number,
		long device_address,
		std::ostream& stream = std::cout);
	Icm20948ErrorCodes openDevice();

	Icm20948ErrorCodes whoAmI(ICM_20948_WHO_AM_I_t& out_t);
	Icm20948ErrorCodes sleep(bool sleepOrWake);
	Icm20948ErrorCodes reset();
	Icm20948ErrorCodes getRawAcceleration(std::vector<int16_t>& accel);
	Icm20948ErrorCodes getAcceleration(std::vector<float>& accel_g);
	Icm20948ErrorCodes getAccelFS(AccelScale& accel_fs_sel);
	Icm20948ErrorCodes setAccelFS(AccelScale accel_fs_sel);
	Icm20948ErrorCodes getWomThreshold(unsigned int& threshold_mg);
	Icm20948ErrorCodes setWomThreshold(unsigned int threshold_mg);

private:
	std::ostream& debugStream_;
	unsigned short adapter_number_;
	long device_address_;
	int device_file_;
	bool is_open_ = false;
	unsigned short user_bank_ = 9;

	Icm20948ErrorCodes readRegister(
		unsigned short user_bank, 
		ICM_20948_REGISTER_MAP register_name,
		__s32& data);
	Icm20948ErrorCodes writeRegister(
		unsigned short user_bank,
		ICM_20948_REGISTER_MAP register_name,
		__u8 data);
	Icm20948ErrorCodes selectUserBank(unsigned short user_bank);
	
};

#endif
