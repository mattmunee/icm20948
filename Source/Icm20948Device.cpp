#include <string>
#include <sstream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include "../Include/Icm20948Device.hpp"

Icm20948Device::Icm20948Device(
	unsigned short adapter_number,
	long device_address,
	std::ostream& stream) 
	:debugStream_(stream),
	adapter_number_(adapter_number),
	device_address_(device_address)
{

}

Icm20948ErrorCodes Icm20948Device::whoAmI(ICM_20948_WHO_AM_I_t& out_t)
{
	Icm20948ErrorCodes success = openDevice();
	if (SUCCESS != success) {
		return success;
	}
	else {
		__s32 res;

		if (success = readRegister(0, REG_WHO_AM_I, res)){
			/* ERROR HANDLING: i2c transaction failed */
			out_t.WHO_AM_I = (uint8_t)((res >> WHO_AM_I_BIT_INDEX) & WHO_AM_I_BIT_MASK);
		}
		else {
			return success;
		}
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::openDevice()
{
	std::stringstream ss;
	ss << "/dev/i2c-" << adapter_number_;
	std::string filename = ss.str();
	if ((device_file_ = open(filename.c_str(), O_RDWR)) < 0) {
		debugStream_ << "Failed to open adapter!" << std::endl;
		return FAILED_TO_OPEN_ADAPTER;
	}
	else {
		debugStream_ << "Successfully opened adapter. File: " << device_file_ << std::endl;
	}
	if (ioctl(device_file_, I2C_SLAVE, device_address_) < 0) {
		debugStream_ << "Failed to acquire bus access and/or talk to slave!" << std::endl;
		return FAILED_TO_TALK_TO_SLAVE;
	}
	else {
		debugStream_ << "Successfully acquired bus access." << std::endl;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::readRegister(
	unsigned short user_bank,
	ICM_20948_REGISTER_MAP register_name,
	__s32& data) 
{
	Icm20948ErrorCodes success = openDevice();
	if (SUCCESS != success) {
		debugStream_ << "Failed to open device!" << std::endl;
		return success;
	}

	/* Using SMBus commands */
	__s32 ret;
	ret = i2c_smbus_read_word_data(device_file_, register_name);
	if (ret < 0) {
		debugStream_ << "Failed to read word data!" << std::endl;
		return FAILED_TO_READ_WORD_DATA;
	}
	else {
		debugStream_ << "Successfully read word data: Data = "<< data << std::endl;
		data = ret;
	}

	return SUCCESS;
}
