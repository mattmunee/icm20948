#ifndef ICM_20948_DEVICE_HPP
#define ICM_20948_DEVICE_HPP

#include "ICM_20948_REGISTERS.h"
#include <linux/types.h>
#include <string>
#include <iostream>

typedef enum {
	SUCCESS,
	FAILED_TO_OPEN_ADAPTER,
	FAILED_TO_TALK_TO_SLAVE,
	FAILED_TO_READ_WORD_DATA,
	DEVICE_NOT_OPEN,
	INVALID_USER_BANK
}Icm20948ErrorCodes;

class Icm20948Device {
public:
	

	Icm20948Device(
		unsigned short adapter_number,
		long device_address,
		std::ostream& stream = std::cout);
	Icm20948ErrorCodes openDevice();

	Icm20948ErrorCodes whoAmI(ICM_20948_WHO_AM_I_t& out_t);

private:
	std::ostream& debugStream_;
	unsigned short adapter_number_;
	long device_address_;
	int device_file_;
	bool is_open_ = false;
	unsigned short user_bank_ = 0;

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
