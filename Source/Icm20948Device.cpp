#include "../Include/Icm20948Device.hpp"

Icm20948Device::Icm20948Device(
	unsigned short adapter_number,
	long device_address) 
	:adapter_number_(adapter_number),
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
	char filename[20];

	snprintf(filename, 19, "/dev/i2c-%d", adapter_number_);
	if ((device_file_ = open(filename, O_RDWR)) < 0) {
		printf("Failed to open the bus.");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		return FAILED_TO_OPEN_ADAPTER;
	}
	if (ioctl(device_file_, I2C_SLAVE, device_address_) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		return FAILED_TO_TALK_TO_SLAVE;
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
		return success;
	}

	/* Using SMBus commands */
	data = i2c_smbus_read_word_data(device_file_, register_name);
	if (data < 0) {
		return FAILED_TO_READ_WORD_DATA;
	}

	return SUCCESS;
}