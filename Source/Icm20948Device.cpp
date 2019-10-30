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
	__s32 res;
	Icm20948ErrorCodes success = readRegister(0, REG_WHO_AM_I, res);
	
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		out_t.WHO_AM_I = (uint8_t)((res >> WHO_AM_I_BIT_INDEX) & WHO_AM_I_BIT_MASK);
	}
	

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::openDevice()
{
	is_open_ = false;

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
		is_open_ = true;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::readRegister(
	unsigned short user_bank,
	ICM_20948_REGISTER_MAP register_name,
	__s32& data) 
{
	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

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
