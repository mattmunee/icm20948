#include <string>
#include <sstream>
#include <iomanip>
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
	__s32 res=-1;
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

Icm20948ErrorCodes Icm20948Device::sleep(bool sleepOrWake)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_PWR_MGMT_1, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = (((sleepOrWake ? 0x01 : 0x00) & SLEEP_BIT_MASK) << SLEEP_BIT_INDEX);
		data = (data & ~(SLEEP_BIT_MASK << SLEEP_BIT_INDEX ) ) | thisdata;

		return writeRegister(0, REG_PWR_MGMT_1, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getRawAcceleration(std::vector<int16_t>& accel)
{
	Icm20948ErrorCodes success;
	__s32 dataH = -1, dataL = -1;
	accel = { 0,0,0 };

	success = readRegister(0, REG_ACCEL_XOUT_H, dataH);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	success = readRegister(0, REG_ACCEL_XOUT_L, dataL);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	
	accel[0] = (dataH << 8) | (dataL);

	success = readRegister(0, REG_ACCEL_YOUT_H, dataH);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	success = readRegister(0, REG_ACCEL_YOUT_L, dataL);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}

	accel[1] = (dataH << 8) | (dataL);

	success = readRegister(0, REG_ACCEL_ZOUT_H, dataH);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	success = readRegister(0, REG_ACCEL_ZOUT_L, dataL);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}

	accel[2] = (dataH << 8) | (dataL);

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getAcceleration(std::vector<float>& accel)
{
	Icm20948ErrorCodes success;
	std::vector<int16_t> raw_accel = { 0,0,0 };
	success = getRawAcceleration(raw_accel);
	if (SUCCESS != success) {
		debugStream_ << "Failed to get raw acceleration!" << std::endl;
		return success;
	}

	AccelScale accel_fs;
	success = getAccelFS(accel_fs);
	if (SUCCESS != success) {
		debugStream_ << "Failed to get Accel FS!" << std::endl;
		return success;
	}

	float sf = 1.0;
	switch (accel_fs)
	{
	case ACCEL_FS_2G:
		sf = 1.0 / 16384.0;
		break;
	case ACCEL_FS_4G:
		sf = 1.0 / 8192.0;
		break;
	case ACCEL_FS_8G:
		sf = 1.0 / 4096.0;
		break;
	case ACCEL_FS_16G:
		sf = 1.0 / 2048.0;
		break;
	case ACCEL_FS_NOT_SET:
		return INVALID_ACCEL_RANGE;
		break;
	}

	accel[0] = sf * (float)raw_accel[0];
	accel[1] = sf * (float)raw_accel[1];
	accel[2] = sf * (float)raw_accel[2];

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

	Icm20948ErrorCodes success = selectUserBank(user_bank);
	if (SUCCESS != success) {
		debugStream_ << "Failed to select user bank!" << std::endl;
		return success;
	}

	data = i2c_smbus_read_byte_data(device_file_, register_name);
	if (data < 0) {
		debugStream_ << "Failed to read data!" << std::endl;
		return FAILED_TO_READ_WORD_DATA;
	}
	else {
		debugStream_ << "Successfully read data from register "
			<< "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(register_name) 
			<< ": Data = "<< "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(data) << std::endl;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::writeRegister(
	unsigned short user_bank,
	ICM_20948_REGISTER_MAP register_name,
	__u8 data)
{
	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	Icm20948ErrorCodes success = selectUserBank(user_bank);
	if (SUCCESS != success) {
		debugStream_ << "Failed to select user bank!" << std::endl;
		return success;
	}

	debugStream_ << "Writing data to register "
		<< "0x" << std::hex << std::setw(2) << std::setfill('0') <<unsigned(register_name)
		<< ": Data = " << "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(data) << std::endl;

	__s32 ret = i2c_smbus_write_byte_data(device_file_, register_name, data);
	if (ret < 0) {
		debugStream_ << "Failed to write data!" << std::endl;
		return FAILED_TO_READ_WORD_DATA;
	}
	else {
		debugStream_ << "Successfully wrote data to register." << std::endl;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::selectUserBank(unsigned short user_bank)
{
	if (user_bank == user_bank_) {
		debugStream_ << "User bank unchange: " << user_bank_ << std::endl;
		return SUCCESS;
	}

	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	if (!(user_bank>=0 && user_bank<=3)) {
		debugStream_ << "Invalid User Bank.  Must be 0-3." << std::endl;
		return INVALID_USER_BANK;
	}

	uint8_t data = (user_bank & USER_BANK_BIT_MASK) << USER_BANK_BIT_INDEX;

	__s32 ret = i2c_smbus_write_byte_data(device_file_, REG_BANK_SEL, data);
	if (ret < 0) {
		debugStream_ << "Failed to write data!" << std::endl;
		return FAILED_TO_READ_WORD_DATA;
	}
	else {
		debugStream_ << "Successfully wrote data to register." << std::endl;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getAccelFS(AccelScale& accel_fs_sel)
{

	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(2, REG_ACCEL_CONFIG, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read Accel FS register." << std::endl;
		return success;
	}

	accel_fs_sel = (AccelScale)((data >> ACCEL_FS_SEL_BIT_INDEX) & ACCEL_FS_SEL_BIT_MASK);
	debugStream_ << "Accel FS set to " << unsigned(accel_fs_sel) << std::endl;

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::setAccelFS(AccelScale accel_fs_sel)
{

	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	if (!(accel_fs_sel >= 0 && accel_fs_sel <= 3)) {
		debugStream_ << "Invalid Accel Range.  Must be 0-3." << std::endl;
		return INVALID_ACCEL_RANGE;
	}

	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(2, REG_ACCEL_CONFIG, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read Accel FS register." << std::endl;
		return success;
	}

	uint16_t thisdata = ((accel_fs_sel & ACCEL_FS_SEL_BIT_MASK) << ACCEL_FS_SEL_BIT_INDEX);
	data = (data & ~(ACCEL_FS_SEL_BIT_MASK << ACCEL_FS_SEL_BIT_INDEX)) | thisdata;

	success = writeRegister(0, REG_ACCEL_CONFIG, data);
	if (SUCCESS != success) {
		debugStream_ << "Failed to write Accel FS register." << std::endl;
		return success;
	}

	return SUCCESS;
}
