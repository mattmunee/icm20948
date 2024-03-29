#include <string>
#include <sstream>
#include <iomanip>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
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

Icm20948ErrorCodes Icm20948Device::enableLowPowerMode(bool enable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_PWR_MGMT_1, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {

		uint16_t thisdata = (((enable ? 0x01 : 0x00) & LP_EN_BIT_MASK) << LP_EN_BIT_INDEX);
		data = (data & ~(LP_EN_BIT_MASK << LP_EN_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_PWR_MGMT_1, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::disableTempSensor(bool disable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_PWR_MGMT_1, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = (((disable ? 0x01 : 0x00) & TEMP_DIS_BIT_MASK) << TEMP_DIS_BIT_INDEX);
		data = (data & ~(TEMP_DIS_BIT_MASK << TEMP_DIS_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_PWR_MGMT_1, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::disableAccel(bool disable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_PWR_MGMT_2, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = (((disable ? 0xFF : 0x00) & DISABLE_ACCEL_BIT_MASK) << DISABLE_ACCEL_BIT_INDEX);
		data = (data & ~(DISABLE_ACCEL_BIT_MASK << DISABLE_ACCEL_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_PWR_MGMT_2, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::disableGyro(bool disable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_PWR_MGMT_2, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = (((disable ? 0xFF : 0x00) & DISABLE_GYRO_BIT_MASK) << DISABLE_GYRO_BIT_INDEX);
		data = (data & ~(DISABLE_GYRO_BIT_MASK << DISABLE_GYRO_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_PWR_MGMT_2, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::enableAccelDutyCycle(bool enable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_LP_CONFIG, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		
		uint16_t thisdata = (((enable ? 0x01 : 0x00) & ACCEL_CYCLE_BIT_MASK) << ACCEL_CYCLE_BIT_INDEX);
		data = (data & ~(ACCEL_CYCLE_BIT_MASK << ACCEL_CYCLE_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_LP_CONFIG, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::enableGyroDutyCycle(bool enable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_LP_CONFIG, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = (((enable ? 0x01 : 0x00) & GYRO_CYCLE_BIT_MASK) << GYRO_CYCLE_BIT_INDEX);
		data = (data & ~(GYRO_CYCLE_BIT_MASK << GYRO_CYCLE_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_LP_CONFIG, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::setAccelSampleRate(unsigned int sample_rate_hz)
{

	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	if (!(sample_rate_hz >= 0 && sample_rate_hz <= 1125)) {
		debugStream_ << "Invalid WOM Threshold.  Must be 0-1125Hz." << std::endl;
		return INVALID_ACCEL_RANGE;
	}

	uint16_t div = (uint16_t)((1125.0f / (float)sample_rate_hz) - 1.0f);
	div = div > 4095 ? 4095 : div;

	__u8 divH = (__u8)((div >> (ACCEL_SMPLRT_DIV_11_8_BIT_INDEX + 8)) & ACCEL_SMPLRT_DIV_11_8_BIT_MASK);
	__u8 divL = (__u8)((div >> (ACCEL_SMPLRT_DIV_7_0_BIT_INDEX)) & ACCEL_SMPLRT_DIV_7_0_BIT_MASK);

	Icm20948ErrorCodes success = writeRegister(2, REG_ACCEL_SMPLRT_DIV_1, divH);
	if (SUCCESS != success) {
		debugStream_ << "Failed to write ACCEL_SMPLRT_DIV_1 register." << std::endl;
		return success;
	}

	success = writeRegister(2, REG_ACCEL_SMPLRT_DIV_2, divL);
	if (SUCCESS != success) {
		debugStream_ << "Failed to write ACCEL_SMPLRT_DIV_1 register." << std::endl;
		return success;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getAccelSampleRate(unsigned int& sample_rate_hz)
{

	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	__s32 divH = 0, divL = 0;

	Icm20948ErrorCodes success = readRegister(2, REG_ACCEL_SMPLRT_DIV_1, divH);
	if (SUCCESS != success) {
		debugStream_ << "Failed to write ACCEL_SMPLRT_DIV_1 register." << std::endl;
		return success;
	}

	success = readRegister(2, REG_ACCEL_SMPLRT_DIV_2, divL);
	if (SUCCESS != success) {
		debugStream_ << "Failed to write ACCEL_SMPLRT_DIV_1 register." << std::endl;
		return success;
	}

	divH = (divH & ACCEL_SMPLRT_DIV_11_8_BIT_MASK) << (ACCEL_SMPLRT_DIV_11_8_BIT_INDEX + 8);
	divL = (divL & ACCEL_SMPLRT_DIV_7_0_BIT_MASK) << (ACCEL_SMPLRT_DIV_7_0_BIT_INDEX);
	
	sample_rate_hz = 1125.0f / (1.0 + (divH | divL));

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::reset()
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_PWR_MGMT_1, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = ((0x01 & DEVICE_RESET_BIT_MASK) << DEVICE_RESET_BIT_INDEX);
		data = (data & ~(DEVICE_RESET_BIT_MASK << DEVICE_RESET_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_PWR_MGMT_1, data);
	}

	debugStream_ << "Sleeping for 100ms after reset." << std::endl;
	usleep(100000);

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::clearInterrupts() {

	__s32 data = -1;
	Icm20948ErrorCodes success;

	success = readRegister(0, REG_INT_STATUS, data);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register REG_INT_STATUS!" << std::endl;
		return success;
	}

	success = readRegister(0, REG_INT_STATUS_1, data);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register REG_INT_STATUS_1!" << std::endl;
		return success;
	}

	success = readRegister(0, REG_INT_STATUS_2, data);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register REG_INT_STATUS_2!" << std::endl;
		return success;
	}

	success = readRegister(0, REG_INT_STATUS_3, data);
	if (SUCCESS != success) {
		debugStream_ << "Failed to read register REG_INT_STATUS_3!" << std::endl;
		return success;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::enableWomInterrupt(bool enable)
{
	__s32 data = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_INT_ENABLE, data);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		uint16_t thisdata = (((enable ? 0x01 : 0x00) & WOM_INT_EN_BIT_MASK) << WOM_INT_EN_BIT_INDEX);
		data = (data & ~(WOM_INT_EN_BIT_MASK << WOM_INT_EN_BIT_INDEX)) | thisdata;

		return writeRegister(0, REG_INT_ENABLE, data);
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::enableWomLogic(bool enable, ICM_20948_WOM_ALGORITHM algorithm)
{

	uint8_t data = ((algorithm & ACCEL_INTEL_MODE_INT_BIT_MASK) << ACCEL_INTEL_MODE_INT_BIT_INDEX)
		| (((enable ? 0x01 : 0x00) & ACCEL_INTEL_EN_BIT_MASK) << ACCEL_INTEL_EN_BIT_INDEX);

	return writeRegister(2, REG_ACCEL_INTEL_CTRL, data);

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getInterruptStatus(ICM_20948_INT_STATUS_t& out_t)
{
	memset(&out_t, 0, sizeof(ICM_20948_INT_STATUS_t));
	__s32 res = -1;
	Icm20948ErrorCodes success = readRegister(0, REG_INT_STATUS, res);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}
	else {
		out_t.I2C_MST_INT = (uint8_t)((res >> I2C_MST_INT_BIT_INDEX) & I2C_MST_INT_BIT_MASK);
		out_t.DMP_INT1 = (uint8_t)((res >> DMP_INT1_BIT_INDEX) & DMP_INT1_BIT_MASK);
		out_t.PLL_RDY_INT = (uint8_t)((res >> PLL_RDY_INT_BIT_INDEX) & PLL_RDY_INT_BIT_MASK);
		out_t.WOM_INT = (uint8_t)((res >> WOM_INT_BIT_INDEX) & WOM_INT_BIT_MASK);
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

Icm20948ErrorCodes Icm20948Device::getAcceleration(std::vector<float>& accel_g)
{
	Icm20948ErrorCodes success;
	std::vector<int16_t> raw_accel = { 0,0,0 };
	success = getRawAcceleration(raw_accel);
	if (SUCCESS != success) {
		debugStream_ << "Failed to get raw acceleration!" << std::endl;
		return success;
	}

	ICM_20948_ACCEL_SCALE accel_fs;
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
	}

	accel_g[0] = sf * (float)raw_accel[0];
	accel_g[1] = sf * (float)raw_accel[1];
	accel_g[2] = sf * (float)raw_accel[2];

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

Icm20948ErrorCodes Icm20948Device::goToLowPowerWomMode(
	unsigned int accel_sampleRate_hz,
	unsigned int wom_threshold_mg,
	ICM_20948_WOM_ALGORITHM algorithm)
{
	Icm20948ErrorCodes success;

	debugStream_ << "Latch interrupt:" << std::endl;
	__u8 data = 0;
	data = (0x01 & INT1_LATCH_EN_BIT_MASK) << INT1_LATCH_EN_BIT_INDEX;
	writeRegister(0, REG_INT_PIN_CFG, data);

	debugStream_ << "disableTempSensor:" << std::endl;
	success = disableTempSensor(true);
	if (SUCCESS != success) {
		debugStream_ << "Failed to disableTempSensor!" << std::endl;
		return success;
	}

	debugStream_ << "disableGyro:" << std::endl;
	success = disableGyro(true);
	if (SUCCESS != success) {
		debugStream_ << "Failed to disableGyro!" << std::endl;
		return success;
	}
	
	debugStream_ << "setAccelSampleRate:" << std::endl;
	success = setAccelSampleRate(accel_sampleRate_hz);
	if (SUCCESS != success) {
		debugStream_ << "Failed to setAccelSampleRate!" << std::endl;
		return success;
	}

	debugStream_ << "enableAccelDutyCycle:" << std::endl;
	success = enableAccelDutyCycle(true);
	if (SUCCESS != success) {
		debugStream_ << "Failed to enableAccelDutyCycle!" << std::endl;
		return success;
	}

	debugStream_ << "setWomThreshold:" << std::endl;
	success = setWomThreshold(wom_threshold_mg);
	if (SUCCESS != success) {
		debugStream_ << "Failed to setWomThreshold!" << std::endl;
		return success;
	}
	
	debugStream_ << "enableWomLogic:" << std::endl;
	success = enableWomLogic(true, algorithm);
	if (SUCCESS != success) {
		debugStream_ << "Failed to enableWomLogic!" << std::endl;
		return success;
	}

	debugStream_ << "enableLowPowerMode:" << std::endl;
	success = enableLowPowerMode(true);
	if (SUCCESS != success) {
		debugStream_ << "Failed to enableLowPowerMode!" << std::endl;
		return success;
	}

	debugStream_ << "enableWomInterrupt:" << std::endl;
	success = enableWomInterrupt(true);
	if (SUCCESS != success) {
		debugStream_ << "Failed to enableWomInterrupt!" << std::endl;
		return success;
	}
	
	debugStream_ << "clearInterrupts:" << std::endl;
	success = clearInterrupts();
	if (SUCCESS != success) {
		debugStream_ << "Failed to clearInterrupts!" << std::endl;
		return success;
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

	unsigned int tries = 0;
	do {
		debugStream_ << "Attempting to read register. Try " << tries + 1 << " of 3" << std::endl;
		data = i2c_smbus_read_byte_data(device_file_, register_name);
		tries += 1;
		usleep(10000);
	} while (data < 0 && tries < 3);
	
	if (data < 0) {
		debugStream_ << "Failed to read data!" << std::endl;
		return FAILED_TO_READ_DATA;
	}
	else {
		debugStream_ << "Successfully read data from register "
			<< "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(register_name) 
			<< " ( User Bank " << std::dec << std::setw(1) << user_bank << ")"
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
		<< " ( User Bank " << std::dec << std::setw(1) << user_bank << ")"
		<< ": Data = " << "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(data) << std::endl;


	__s32 ret = 0;

	unsigned int tries = 0;
	do {
		debugStream_ << "Attempting to write to register. Try " << tries + 1 << " of 3" << std::endl;
		ret = i2c_smbus_write_byte_data(device_file_, register_name, data);
		tries += 1;
		usleep(10000);
	} while (ret < 0 && tries < 3);

	if (ret < 0) {
		debugStream_ << "Failed to write data!" << std::endl;
		return FAILED_TO_READ_DATA;
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
		return FAILED_TO_READ_DATA;
	}
	else {
		debugStream_ << "Successfully wrote to REG_BANK_SEL." << std::endl;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getAccelFS(ICM_20948_ACCEL_SCALE& accel_fs_sel)
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

	accel_fs_sel = (ICM_20948_ACCEL_SCALE)((data >> ACCEL_FS_SEL_BIT_INDEX) & ACCEL_FS_SEL_BIT_MASK);
	debugStream_ << "Accel FS set to " << unsigned(accel_fs_sel) << std::endl;

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::setAccelFS(ICM_20948_ACCEL_SCALE accel_fs_sel)
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

	uint8_t thisdata = ((accel_fs_sel & ACCEL_FS_SEL_BIT_MASK) << ACCEL_FS_SEL_BIT_INDEX);
	data = (data & ~(ACCEL_FS_SEL_BIT_MASK << ACCEL_FS_SEL_BIT_INDEX)) | thisdata;

	success = writeRegister(2, REG_ACCEL_CONFIG, data);
	if (SUCCESS != success) {
		debugStream_ << "Failed to write Accel FS register." << std::endl;
		return success;
	}

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::getWomThreshold(unsigned int& threshold_mg)
{
	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	__s32 res = -1;
	Icm20948ErrorCodes success = readRegister(2, REG_ACCEL_WOM_THR, res);

	if (SUCCESS != success) {
		debugStream_ << "Failed to read register!" << std::endl;
		return success;
	}

	// 4mg per LSB (from datasheet)
	threshold_mg = 4*(unsigned int)((res >> WOM_THRESHOLD_BIT_INDEX) & WOM_THRESHOLD_BIT_MASK);

	return SUCCESS;
}

Icm20948ErrorCodes Icm20948Device::setWomThreshold(unsigned int threshold_mg)
{

	if (!is_open_) {
		debugStream_ << "Device not open.  Call openDevice() first." << std::endl;
		return DEVICE_NOT_OPEN;
	}

	if (!(threshold_mg >= 0 && threshold_mg <= 1020)) {
		debugStream_ << "Invalid WOM Threshold.  Must be 0-1020mg." << std::endl;
		return INVALID_ACCEL_RANGE;
	}

	Icm20948ErrorCodes success = writeRegister(2, REG_ACCEL_WOM_THR, (__u8)(threshold_mg / 4));
	if (SUCCESS != success) {
		debugStream_ << "Failed to write WOM Thresh register." << std::endl;
		return success;
	}

	return SUCCESS;
}
