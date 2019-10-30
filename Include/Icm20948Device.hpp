#ifndef ICM_20948_DEVICE_HPP
#define ICM_20948_DEVICE_HPP

#include "ICM_20948_REGISTERS.h"
#include <string>

typedef enum {
	SUCCESS,
	FAILED_TO_OPEN_ADAPTER,
	FAILED_TO_TALK_TO_SLAVE,
	FAILED_TO_READ_WORD_DATA
}Icm20948ErrorCodes;

class Icm20948Device {
public:
	

	Icm20948Device(
		unsigned short adapter_number,
		long device_address);
	static double Entropy(int pos, int neg);

	Icm20948ErrorCodes whoAmI(ICM_20948_WHO_AM_I_t& out_t);

private:
	unsigned short adapter_number_;
	long device_address_;
	int device_file_;


	Icm20948ErrorCodes openDevice();

	Icm20948ErrorCodes readRegister(
		unsigned short user_bank, 
		ICM_20948_REGISTER_MAP register_name,
		__s32& data);
};

#endif