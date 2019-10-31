/*

This file contains a useful c translation of the datasheet register map

*/

#ifndef _ICM_20948_REGISTERS_H_
#define _ICM_20948_REGISTERS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

//Icm20948UserBank0Reg
typedef enum{
	// User Bank Select
	REG_BANK_SEL                 = 0x7F,

	// User Bank 0 Registers
	REG_WHO_AM_I                     = 0x00,
	REG_USER_CTRL                    = 0x03,
	REG_LP_CONFIG                    = 0x05,
	REG_PWR_MGMT_1                   = 0x06,
	REG_PWR_MGMT_2                   = 0x07,
	REG_INT_PIN_CFG                  = 0x0F,
	REG_INT_ENABLE                   = 0x10,
	REG_INT_ENABLE_1                 = 0x11,
	REG_INT_ENABLE_2                 = 0x12,
	REG_INT_ENABLE_3                 = 0x13,
	REG_I2C_MST_STATUS               = 0x17,
	REG_INT_STATUS                   = 0x19,
	REG_INT_STATUS_1                 = 0x1A,
	REG_INT_STATUS_2                 = 0x1B,
	REG_INT_STATUS_3                 = 0x1C,
	REG_DELAY_TIMEH                  = 0x28,
	REG_DELAY_TIMEL                  = 0x29,
	REG_ACCEL_XOUT_H                 = 0x2D,
	REG_ACCEL_XOUT_L                 = 0x2E,
	REG_ACCEL_YOUT_H                 = 0x2F,
	REG_ACCEL_YOUT_L                 = 0x30,
	REG_ACCEL_ZOUT_H                 = 0x31,
	REG_ACCEL_ZOUT_L                 = 0x32,
	REG_GYRO_XOUT_H                  = 0x33,
	REG_GYRO_XOUT_L                  = 0x34,
	REG_GYRO_YOUT_H                  = 0x35,
	REG_GYRO_YOUT_L                  = 0x36,
	REG_GYRO_ZOUT_H                  = 0x37,
	REG_GYRO_ZOUT_L                  = 0x38,
	REG_TEMP_OUT_H                   = 0x39,
	REG_TEMP_OUT_L                   = 0x3A,
	REG_EXT_SLV_SENS_DATA_00         = 0x3B,
	REG_EXT_SLV_SENS_DATA_01         = 0x3C,
	REG_EXT_SLV_SENS_DATA_02         = 0x3D,
	REG_EXT_SLV_SENS_DATA_03         = 0x3E,
	REG_EXT_SLV_SENS_DATA_04         = 0x3F,
	REG_EXT_SLV_SENS_DATA_05         = 0x40,
	REG_EXT_SLV_SENS_DATA_06         = 0x41,
	REG_EXT_SLV_SENS_DATA_07         = 0x42,
	REG_EXT_SLV_SENS_DATA_08         = 0x43,
	REG_EXT_SLV_SENS_DATA_09         = 0x44,
	REG_EXT_SLV_SENS_DATA_10         = 0x45,
	REG_EXT_SLV_SENS_DATA_11         = 0x46,
	REG_EXT_SLV_SENS_DATA_12         = 0x47,
	REG_EXT_SLV_SENS_DATA_13         = 0x48,
	REG_EXT_SLV_SENS_DATA_14         = 0x49,
	REG_EXT_SLV_SENS_DATA_15         = 0x4A,
	REG_EXT_SLV_SENS_DATA_16         = 0x4B,
	REG_EXT_SLV_SENS_DATA_17         = 0x4C,
	REG_EXT_SLV_SENS_DATA_18         = 0x4D,
	REG_EXT_SLV_SENS_DATA_19         = 0x4E,
	REG_EXT_SLV_SENS_DATA_20         = 0x4F,
	REG_EXT_SLV_SENS_DATA_21         = 0x50,
	REG_EXT_SLV_SENS_DATA_22         = 0x51,
	REG_EXT_SLV_SENS_DATA_23         = 0x52,
	REG_FIFO_EN_1                    = 0x66,
	REG_FIFO_EN_2                    = 0x67,
	REG_FIFO_RST                     = 0x68,
	REG_FIFO_MODE                    = 0x69,
	REG_FIFO_COUNTH                  = 0x70,
	REG_FIFO_COUNTL                  = 0x71,
	REG_FIFO_R_W                     = 0x72,
	REG_DATA_RDY_STATUS              = 0x74,
	REG_FIFO_CFG                     = 0x76,

	// User Bank 1 Registers
	REG_SELF_TEST_X_GYRO             = 0x02,
	REG_SELF_TEST_Y_GYRO             = 0x03,
	REG_SELF_TEST_Z_GYRO             = 0x04,
	REG_SELF_TEST_X_ACCEL            = 0x0E,
	REG_SELF_TEST_Y_ACCEL            = 0x0F,
	REG_SELF_TEST_Z_ACCEL            = 0x10,
	REG_XA_OFFS_H                    = 0x14,
	REG_XA_OFFS_L                    = 0x15,
	REG_YA_OFFS_H                    = 0x17,
	REG_YA_OFFS_L                    = 0x18,
	REG_ZA_OFFS_H                    = 0x1A,
	REG_ZA_OFFS_L                    = 0x1B,
	REG_TIMEBASE_CORRECTION_PLL      = 0x28,

	// User Bank 2 Registers
	REG_GYRO_SMPLRT_DIV              = 0x00,
	REG_GYRO_CONFIG_1                = 0x01,
	REG_GYRO_CONFIG_2                = 0x02,
	REG_XG_OFFS_USRH                 = 0x03,
	REG_XG_OFFS_USRL                 = 0x04,
	REG_YG_OFFS_USRH                 = 0x05,
	REG_YG_OFFS_USRL                 = 0x06,
	REG_ZG_OFFS_USRH                 = 0x07,
	REG_ZG_OFFS_USRL                 = 0x08,
	REG_ODR_ALIGN_EN                 = 0x09,
	REG_ACCEL_SMPLRT_DIV_1           = 0x10,
	REG_ACCEL_SMPLRT_DIV_2           = 0x11,
	REG_ACCEL_INTEL_CTRL             = 0x12,
	REG_ACCEL_WOM_THR                = 0x13,
	REG_ACCEL_CONFIG                 = 0x14,
	REG_ACCEL_CONFIG_2               = 0x15,
	REG_FSYNC_CONFIG                 = 0x52,
	REG_TEMP_CONFIG                  = 0x53,
	REG_MOD_CTRL_USR                 = 0x54,

	// User Bank 3 Registers
	REG_I2C_MST_ODR_CONFIG           = 0x00,
	REG_I2C_MST_CTRL                 = 0x01,
	REG_I2C_MST_DELAY_CTRL           = 0x02,
	REG_I2C_SLV0_ADDR                = 0x03,
	REG_I2C_SLV0_REG                 = 0x04,
	REG_I2C_SLV0_CTRL                = 0x05,
	REG_I2C_SLV0_DO                  = 0x06,
	REG_I2C_SLV1_ADDR                = 0x07,
	REG_I2C_SLV1_REG                 = 0x08,
	REG_I2C_SLV1_CTRL                = 0x09,
	REG_I2C_SLV1_DO                  = 0x0A,
	REG_I2C_SLV2_ADDR                = 0x0B,
	REG_I2C_SLV2_REG                 = 0x0C,
	REG_I2C_SLV2_CTRL                = 0x0D,
	REG_I2C_SLV2_DO                  = 0x0E,
	REG_I2C_SLV3_ADDR                = 0x0F,
	REG_I2C_SLV3_REG                 = 0x10,
	REG_I2C_SLV3_CTRL                = 0x11,
	REG_I2C_SLV3_DO                  = 0x12,
	REG_I2C_SLV4_ADDR                = 0x13,
	REG_I2C_SLV4_REG                 = 0x14,
	REG_I2C_SLV4_CTRL                = 0x15,
	REG_I2C_SLV4_DO                  = 0x16,
	REG_I2C_SLV4_DI                  = 0x17

}ICM_20948_REGISTER_MAP;

typedef enum {
	ACCEL_FS_2G = 0,
	ACCEL_FS_4G = 1,
	ACCEL_FS_8G = 2,
	ACCEL_FS_16G = 3,
}ICM_20948_ACCEL_SCALE;

typedef enum {
	ALGO_STORE_INITIAL_REFERENCE_FOR_COMPARISON = 0,
	ALGO_RUNNING_COMPARISON_CURRENT_TO_PREVIOUS = 1
}ICM_20948_WOM_ALGORITHM;

// Type definitions for the registers
typedef struct{
	uint8_t WHO_AM_I;
}ICM_20948_WHO_AM_I_t;

typedef enum {
	WHO_AM_I_BIT_INDEX           = 0,
	WHO_AM_I_BIT_MASK            = 0xFF,
}ICM_20948_WHO_AM_I_BITMASKS;

typedef struct {
	uint8_t reserved_0                 : 1;
	uint8_t I2C_MST_RST                : 1;
	uint8_t SRAM_RST                   : 1;
	uint8_t DMP_RST                    : 1;
	uint8_t	I2C_IF_DIS                 : 1;
	uint8_t I2C_MST_EN                 : 1;
	uint8_t FIFO_EN                    : 1;
	uint8_t DMP_EN                     : 1;
}ICM_20948_USER_CTRL_t;

typedef enum {
	I2C_MST_RST_BIT_INDEX        = 1,
	SRAM_RST_BIT_INDEX           = 2,
	DMP_RST_BIT_INDEX            = 3,
	I2C_IF_DIS_BIT_INDEX         = 4,
	I2C_MST_EN_BIT_INDEX         = 5,
	FIFO_EN_BIT_INDEX            = 6,
	DMP_EN_BIT_INDEX             = 7,

	I2C_MST_RST_BIT_MASK         = 0x01,
	SRAM_RST_BIT_MASK            = 0x01,
	DMP_RST_BIT_MASK             = 0x01,
	I2C_IF_DISBIT_MASK           = 0x01,
	I2C_MST_EN_BIT_MASK          = 0x01,
	FIFO_EN_BIT_MASK             = 0x01,
	DMP_EN_BIT_MASK              = 0x01
	
}ICM_20948_USER_CTRL_BITMASKS;

typedef struct{
	uint8_t reserved_0                 : 4;
	uint8_t GYRO_CYCLE                 : 1;
	uint8_t ACCEL_CYCLE                : 1;
	uint8_t I2C_MST_CYCLE              : 1;
	uint8_t reserved_1                 : 1;
}ICM_20948_LP_CONFIG_t;

typedef enum{
	GYRO_CYCLE_BIT_INDEX         = 4,
	ACCEL_CYCLE_BIT_INDEX        = 5,
	I2C_MST_CYCLE_BIT_INDEX      = 6,
	
	GYRO_CYCLE_BIT_MASK          = 0x01,
	ACCEL_CYCLE_BIT_MASK         = 0x01,
	I2C_MST_CYCLE_BIT_MASK       = 0x01
	
}ICM_20948_LP_CONFIG_BITMASKS;

typedef struct{
	uint8_t CLKSEL                     : 3;
	uint8_t TEMP_DIS                   : 1;
	uint8_t reserved_0                 : 1;
	uint8_t LP_EN                      : 1;
	uint8_t SLEEP                      : 1;
	uint8_t DEVICE_RESET               : 1;
}ICM_20948_PWR_MGMT_1_t;

typedef enum{
	CLKSEL_BIT_INDEX             = 0,
	TEMP_DIS_BIT_INDEX           = 3,
	LP_EN_BIT_INDEX              = 5,
	SLEEP_BIT_INDEX              = 6,
	DEVICE_RESET_BIT_INDEX       = 7,
	
	CLKSEL_BIT_MASK              = 0x07,
	TEMP_DIS_BIT_MASK            = 0x01,
	LP_EN_BIT_MASK               = 0x01,
	SLEEP_BIT_MASK               = 0x01,
	DEVICE_RESET_BIT_MASK        = 0x01
	
}ICM_20948_PWR_MGMT_1_BITMASKS;

typedef struct{
	uint8_t DISABLE_GYRO               : 3;
	uint8_t DIABLE_ACCEL               : 3;
	uint8_t reserved_0                 : 2;
}ICM_20948_PWR_MGMT_2_t;

typedef enum{
	DISABLE_GYRO_BIT_INDEX       = 0,
	DISABLE_ACCEL_BIT_INDEX       = 3,

	DISABLE_GYRO_BIT_MASK        = 0x07,
	DISABLE_ACCEL_BIT_MASK        = 0x07
	
}ICM_20948_PWR_MGMT_2_BITMASKS;

typedef struct{
	uint8_t reserved_0                 : 1;
	uint8_t BYPASS_EN                  : 1;
	uint8_t FSYNC_INT_MODE_EN          : 1;
	uint8_t ACTL_FSYNC                 : 1;
	uint8_t INT_ANYRD_2CLEAR           : 1;
	uint8_t INT1_LATCH_EN              : 1;
	uint8_t INT1_OPEN                  : 1;
	uint8_t INT1_ACTL                  : 1;
}ICM_20948_INT_PIN_CFG_t;

typedef enum{
	BYPASS_EN_BIT_INDEX          = 1,
	FSYNC_INT_MODE_EN_BIT_INDEX  = 2,
	ACTL_FSYNC_BIT_INDEX         = 3,
	INT_ANYRD_2CLEAR_BIT_INDEX   = 4,
	INT1_LATCH_EN_BIT_INDEX      = 5,
	INT1_OPEN_BIT_INDEX          = 6,
	INT1_ACTL_BIT_INDEX          = 7,
	
	BYPASS_EN_BIT_MASK           = 0x01,
	FSYNC_INT_MODE_EN_BIT_MASK   = 0x01,
	ACTL_FSYNC_BIT_MASK          = 0x01,
	INT_ANYRD_2CLEAR_BIT_MASK    = 0x01,
	INT1_LATCH_EN_BIT_MASK       = 0x01,
	INT1_OPEN_BIT_MASK           = 0x01,
	INT1_ACTL_BIT_MASK           = 0x01
	
}ICM_20948_INT_PIN_CFG_BITMASKS;

typedef struct{
	uint8_t I2C_MST_INT_EN             : 1;
	uint8_t DMP_INT1_EN                : 1;
	uint8_t PLL_READY_EN               : 1;
	uint8_t WOM_INT_EN                 : 1;
	uint8_t reserved_0                 : 3;
	uint8_t REG_WOF_EN                 : 1;
}ICM_20948_INT_ENABLE_t;

typedef enum{
	I2C_MST_INT_EN_BIT_INDEX     = 0,
	DMP_INT1_EN_BIT_INDEX        = 1,
	PLL_READY_EN_BIT_INDEX       = 2,
	WOM_INT_EN_BIT_INDEX         = 3,
	REG_WOF_EN_BIT_INDEX         = 7,
	
	I2C_MST_INT_EN_BIT_MASK      = 0x01,
	DMP_INT1_EN_BIT_MASK         = 0x01,
	PLL_READY_EN_BIT_MASK        = 0x01,
	WOM_INT_EN_BIT_MASK          = 0x01,
	REG_WOF_EN_BIT_MASK          = 0x01
	
}ICM_20948_INT_ENABLE_BITMASKS;

typedef struct{
	uint8_t RAW_DATA_0_RDY_EN          : 1;
	uint8_t reserved_0                 : 7;
}ICM_20948_INT_ENABLE_1_t;

typedef enum{
	RAW_DATA_0_RDY_EN_BIT_INDEX  = 0,
	
	RAW_DATA_0_RDY_EN_BIT_MASK   = 0x01
}ICM_20948_INT_ENABLE_1_BITMASKS;

typedef union{
	struct{
		uint8_t FIFO_OVERFLOW_EN_40    : 5;
		uint8_t reserved_0             : 3;
	}grouped;
	struct{
		uint8_t FIFO_OVERFLOW_EN_0     : 1;
		uint8_t FIFO_OVERFLOW_EN_1     : 1;
		uint8_t FIFO_OVERFLOW_EN_2     : 1;
		uint8_t FIFO_OVERFLOW_EN_3     : 1;
		uint8_t FIFO_OVERFLOW_EN_4     : 1;
		uint8_t reserved_0             : 3;
	}individual;
}ICM_20948_INT_ENABLE_2_t;

typedef enum{
	FIFO_OVERFLOW_EN_BIT_INDEX   = 0,
	
	FIFO_OVERFLOW_EN_BIT_MASK    = 0x0F
}ICM_20948_INT_ENABLE_2_BITMASKS;

typedef union{
	struct{
		uint8_t FIFO_WM_EN_40          : 5;
		uint8_t reserved_0             : 3;
	}grouped;
	struct{
		uint8_t FIFO_WM_EN_0           : 1;
		uint8_t	FIFO_WM_EN_1           : 1;
		uint8_t FIFO_WM_EN_2           : 1;
		uint8_t FIFO_WM_EN_3           : 1;
		uint8_t FIFO_WM_EN_4           : 1;
		uint8_t reserved_0             : 3;
	}individual;
}ICM_20948_INT_ENABLE_3_t;

typedef enum{
	FIFO_WM_EN_BIT_INDEX         = 0,
	
	FIFO_WM_EN_BIT_MASK          = 0x0F
}ICM_20948_INT_ENABLE_3_BITMASKS;

typedef struct{
	uint8_t I2C_SLV0_NACK              : 1;
	uint8_t I2C_SLV1_NACK              : 1;
	uint8_t I2C_SLV2_NACK              : 1;
	uint8_t I2C_SLV3_NACK              : 1;
	uint8_t I2C_SLV4_NACK              : 1;
	uint8_t I2C_LOST_ARB               : 1;
	uint8_t I2C_SLV4_DONE              : 1;
	uint8_t PASS_THROUGH               : 1;
}ICM_20948_I2C_MST_STATUS_t;

typedef enum{
	I2C_SLV0_NACK_BIT_INDEX      = 0,
	I2C_SLV1_NACK_BIT_INDEX      = 1,
	I2C_SLV2_NACK_BIT_INDEX      = 2,
	I2C_SLV3_NACK_BIT_INDEX      = 3,
	I2C_SLV4_NACK_BIT_INDEX      = 4,
	I2C_LOST_ARB_BIT_INDEX       = 5,
	I2C_SLV4_DONE_BIT_INDEX      = 6,
	PASS_THROUGH_BIT_INDEX       = 7,
	
	I2C_SLV0_NACK_BIT_MASK       = 0x01,
	I2C_SLV1_NACK_BIT_MASK       = 0x01,
	I2C_SLV2_NACK_BIT_MASK       = 0x01,
	I2C_SLV3_NACK_BIT_MASK       = 0x01,
	I2C_SLV4_NACK_BIT_MASK       = 0x01,
	I2C_LOST_ARB_BIT_MASK        = 0x01,
	I2C_SLV4_DONE_BIT_MASK       = 0x01,
	PASS_THROUGH_BIT_MASK        = 0x01
}ICM_20948_I2C_MST_STATUS_BITMASKS;

typedef struct{
	uint8_t I2C_MST_INT                : 1;
	uint8_t DMP_INT1                   : 1;
	uint8_t PLL_RDY_INT                : 1;
	uint8_t WOM_INT                    : 1;
	uint8_t reserved_0                 : 4;
}ICM_20948_INT_STATUS_t;

typedef enum{
	I2C_MST_INT_BIT_INDEX        = 0,
	DMP_INT1_BIT_INDEX           = 1,
	PLL_RDY_INT_BIT_INDEX        = 2,
	WOM_INT_BIT_INDEX            = 3,
	
	I2C_MST_INT_BIT_MASK         = 0x01,
	DMP_INT1_BIT_MASK            = 0x01,
	PLL_RDY_INT_BIT_MASK         = 0x01,
	WOM_INT_BIT_MASK             = 0x01
}ICM_20948_INT_STATUS_BITMASKS;

typedef struct{
	uint8_t RAW_DATA_0_RDY_INT         : 1;
	uint8_t reserved_0                 : 7;
}ICM_20948_INT_STATUS_1_t;

typedef enum{
	RAW_DATA_0_RDY_INT_BIT_INDEX = 0,
	
	RAW_DATA_0_RDY_INT_BIT_MASK  = 0x01,
}ICM_20948_INT_STATUS_1_BITMASKS;

typedef struct{
	uint8_t FIFO_OVERFLOW_INT_40       : 5;
	uint8_t reserved_0                 : 3;
}ICM_20948_INT_STATUS_2_t;

typedef enum{
	FIFO_OVERFLOW_INT_BIT_INDEX  = 0,
	
	FIFO_OVERFLOW_INT_BIT_MASK   = 0x0F,
}ICM_20948_INT_STATUS_2_BITMASKS;

typedef struct{
	uint8_t FIFO_WM_INT40              : 5;
	uint8_t reserved_0                 : 3;
}ICM_20948_INT_STATUS_3_t;

typedef enum{
	FIFO_WM_INT_BIT_INDEX        = 0,
	
	FIFO_WM_INT_BIT_MASK         = 0x0F,
}ICM_20948_INT_STATUS_3_BITMASKS;

typedef struct{
	uint8_t DELAY_TIMEH;
}ICM_20948_DELAY_TIMEH_t;

typedef struct{
	uint8_t DELAY_TIMEL;
}ICM_20948_DELAY_TIMEL_t;

typedef struct{
	uint8_t ACCEL_XOUT_H;
}ICM_20948_ACCEL_XOUT_H_t;

typedef struct{
	uint8_t ACCEL_XOUT_L;
}ICM_20948_ACCEL_XOUT_L_t;

typedef struct{
	uint8_t ACCEL_YOUT_H;
}ICM_20948_ACCEL_YOUT_H_t;

typedef struct{
	uint8_t ACCEL_YOUT_L;
}ICM_20948_ACCEL_YOUT_L_t;

typedef struct{
	uint8_t ACCEL_ZOUT_H;
}ICM_20948_ACCEL_ZOUT_H_t;

typedef struct{
	uint8_t ACCEL_ZOUT_L;
}ICM_20948_ACCEL_ZOUT_L_t;

typedef struct{
	uint8_t GYRO_XOUT_H;
}ICM_20948_GYRO_XOUT_H_t;

typedef struct{
	uint8_t GYRO_XOUT_L;
}ICM_20948_GYRO_XOUT_L_t;

typedef struct{
	uint8_t GYRO_YOUT_H;
}ICM_20948_GYRO_YOUT_H_t;

typedef struct{
	uint8_t GYRO_YOUT_L;
}ICM_20948_GYRO_YOUT_L_t;

typedef struct{
	uint8_t GYRO_ZOUT_H;
}ICM_20948_GYRO_ZOUT_H_t;

typedef struct{
	uint8_t GYRO_ZOUT_L;
}ICM_20948_GYRO_ZOUT_L_t;

typedef struct{
	uint8_t TEMP_OUT_H;
}ICM_20948_TEMP_OUT_H_t;

typedef struct{
	uint8_t TEMP_OUT_L;
}ICM_20948_TEMP_OUT_L_t;

typedef struct{
	uint8_t DATA;				// Note: this is not worth copying 24 times, despite there being 24 registers like this one
}ICM_20948_EXT_SLV_SENS_DATA_t;

typedef struct{
	uint8_t SLV_0_FIFO_EN              : 1;
	uint8_t SLV_1_FIFO_EN              : 1;
	uint8_t SLV_2_FIFO_EN              : 1;
	uint8_t SLV_3_FIFO_EN              : 1;
	uint8_t reserved_0                 : 4;
}ICM_20948_FIFO_EN_1_t;

typedef struct{
	uint8_t TEMP_FIFO_EN               : 1;
	uint8_t GYRO_X_FIFO_EN             : 1;
	uint8_t GYRO_Y_FIFO_EN             : 1;
	uint8_t GYRO_Z_FIFO_EN             : 1;
	uint8_t ACCEL_FIFO_EN              : 1;
	uint8_t reserved_0                 : 3;
}ICM_20948_FIFO_EN_2_t;

typedef struct{
	uint8_t FIFO_RESET                 : 5;
	uint8_t reserved_0                 : 3;
}ICM_20948_FIFO_RST_t;

typedef struct{
	uint8_t FIFO_MODE                  : 5;
	uint8_t reserved_0                 : 3;
}ICM_20948_FIFO_MODE_t;

typedef struct{
	uint8_t FIFO_COUNTH;
}ICM_20948_FIFO_COUNTH_t;

typedef struct{
	uint8_t FIFO_COUNTL;
}ICM_20948_FIFO_COUNTL_t;

typedef struct{
	uint8_t FIFO_R_W;	// Reading from or writing to this register actually reads from or writes to the FIFO
}ICM_20948_FIFO_R_W_t;

typedef struct{
	uint8_t RAW_DATA_RDY               : 4;
	uint8_t reserved_0                 : 3;
	uint8_t WOF_STATUS                 : 1;
}ICM_20948_DATA_RDY_STATUS_t;

typedef struct{
	uint8_t FIFO_CFG                   : 1;
	uint8_t reserved_0                 : 7;
}ICM_20948_FIFO_CFG_t;


// User bank 1 Types

typedef struct{
	uint8_t XG_ST_DATA;
}ICM_20948_SELF_TEST_X_GYRO_t;

typedef struct{
	uint8_t YG_ST_DATA;
}ICM_20948_SELF_TEST_Y_GYRO_t;

typedef struct{
	uint8_t ZG_ST_DATA;
}ICM_20948_SELF_TEST_Z_GYRO_t;

typedef struct{
	uint8_t XA_ST_DATA;
}ICM_20948_SELF_TEST_X_ACCEL_t;

typedef struct{
	uint8_t YA_ST_DATA;
}ICM_20948_SELF_TEST_Y_ACCEL_t;

typedef struct{
	uint8_t ZA_ST_DATA;
}ICM_20948_SELF_TEST_Z_ACCEL_t;

typedef struct{
	uint8_t XA_OFFS_14_7;
}ICM_20948_XA_OFFS_H_t;

typedef struct{
	uint8_t reserved_0                 : 1;
	uint8_t XA_OFFS_6_0                : 7;
}ICM_20948_XA_OFFS_L_t;

typedef struct{
	uint8_t YA_OFFS_14_7;
}ICM_20948_YA_OFFS_H_t;

typedef struct{
	uint8_t reserved_0                 : 1;
	uint8_t YA_OFFS_6_0                : 7;
}ICM_20948_YA_OFFS_L_t;

typedef struct{
	uint8_t ZA_OFFS_14_7;
}ICM_20948_ZA_OFFS_H_t;

typedef struct{
	uint8_t reserved_0                 : 1;
	uint8_t ZA_OFFS_6_0                : 7;
}ICM_20948_ZA_OFFS_L_t;

typedef struct{
	uint8_t TBC_PLL;
}ICM_20948_TIMEBASE_CORRECTION_PLL_t;

// User Bank 2 Types
typedef struct{
	uint8_t GYRO_SMPLRT_DIV;
}ICM_20948_GYRO_SMPLRT_DIV_t;

typedef enum {
	GYRO_SMPLRT_DIV_BIT_INDEX = 0,

	GYRO_SMPLRT_DIV_BIT_MASK = 0xFF
}ICM_20948_GYRO_SMPLRT_DIV_BITMASKS;

typedef struct{
	uint8_t GYRO_FCHOICE               : 1;
	uint8_t GYRO_FS_SEL                : 2;
	uint8_t GYRO_DLPFCFG               : 3;
	uint8_t reserved_0                 : 2;
}ICM_20948_GYRO_CONFIG_1_t;

typedef struct{
	uint8_t GYRO_AVGCFG                : 3;
	uint8_t ZGYRO_CTEN                 : 1;
	uint8_t YGYRO_CTEN                 : 1;
	uint8_t XGYRO_CTEN                 : 1;
	uint8_t reserved_0                 : 2;
}ICM_20948_GYRO_CONFIG_2_t;

typedef struct{
	uint8_t XG_OFFS_USER_H;
}ICM_20948_XG_OFFS_USRH_t;

typedef struct{
	uint8_t XG_OFFS_USER_L;
}ICM_20948_XG_OFFS_USRL_t;

typedef struct{
	uint8_t YG_OFFS_USER_H;
}ICM_20948_YG_OFFS_USRH_t;

typedef struct{
	uint8_t YG_OFFS_USER_L;
}ICM_20948_YG_OFFS_USRL_t;

typedef struct{
	uint8_t ZG_OFFS_USER_H;
}ICM_20948_ZG_OFFS_USRH_t;

typedef struct{
	uint8_t ZG_OFFS_USER_L;
}ICM_20948_ZG_OFFS_USRL_t;

typedef struct{
	uint8_t ODR_ALIGN_EN               : 1;
	uint8_t reserved_0                 : 7;
}ICM_20948_ODR_ALIGN_EN_t;

typedef struct{
	uint8_t ACCEL_SMPLRT_DIV_11_8      : 4;
	uint8_t reserved_0                 : 4;
}ICM_20948_ACCEL_SMPLRT_DIV_1_t;

typedef enum {
	ACCEL_SMPLRT_DIV_11_8_BIT_INDEX = 0,

	ACCEL_SMPLRT_DIV_11_8_BIT_MASK = 0x0F
}ICM_20948_ACCEL_SMPLRT_DIV_1_BITMASKS;

typedef struct{
	uint8_t ACCEL_SMPLRT_DIV_7_0;
}ICM_20948_ACCEL_SMPLRT_DIV_2_t;

typedef enum {
	ACCEL_SMPLRT_DIV_7_0_BIT_INDEX = 0,

	ACCEL_SMPLRT_DIV_7_0_BIT_MASK = 0xFF
}ICM_20948_ACCEL_SMPLRT_DIV_2_BITMASKS;

typedef struct{
	uint8_t ACCEL_INTEL_MODE_INT	: 1;
	ICM_20948_WOM_ALGORITHM ACCEL_INTEL_EN : 1;
	uint8_t reserved_0                 : 6;
}ICM_20948_ACCEL_INTEL_CTRL_t;

typedef enum {
	ACCEL_INTEL_MODE_INT_BIT_INDEX = 0,
	ACCEL_INTEL_EN_BIT_INDEX = 1,

	ACCEL_INTEL_MODE_INT_BIT_MASK = 0x01,
	ACCEL_INTEL_EN_BIT_MASK = 0x01,
}ICM_20948_ACCEL_INTEL_CTRL_BITMASKS;

typedef struct{
	uint8_t WOM_THRESHOLD;
}ICM_20948_ACCEL_WOM_THR_t;

typedef enum {
	WOM_THRESHOLD_BIT_INDEX = 0,

	WOM_THRESHOLD_BIT_MASK = 0xFF,
}ICM_20948_ACCEL_WOM_THR_BITMASKS;

typedef struct{
	uint8_t ACCEL_FCHOICE              : 1;
	uint8_t ACCEL_FS_SEL               : 2;
	uint8_t ACCEL_DLPFCFG              : 3;
	uint8_t reserved_0                 : 2;
}ICM_20948_ACCEL_CONFIG_t;

typedef enum {
	ACCEL_FCHOICE_BIT_INDEX = 0,
	ACCEL_FS_SEL_BIT_INDEX = 1,
	ACCEL_DLPFCFG_BIT_INDEX = 3,

	ACCEL_FCHOICE_BIT_MASK = 0x01,
	ACCEL_FS_SEL_BIT_MASK = 0x03,
	ACCEL_DLPFCFG_BIT_MASK = 0x07
}ICM_20948_ACCEL_CONFIG_BITMASKS;

typedef struct{
	uint8_t DEC3_CFG                   : 2;
	uint8_t AZ_ST_EN                   : 1;
	uint8_t AY_ST_EN                   : 1;
	uint8_t AX_ST_EN                   : 1;
	uint8_t reserved_0                 : 3;
}ICM_20948_ACCEL_CONFIG_2_t;

typedef struct{
	uint8_t EXT_SYNC_SET               : 4;
	uint8_t WOF_EDGE_INT               : 1;
	uint8_t WOF_DEGLITCH_EN            : 1;
	uint8_t reserved_0                 : 1;
	uint8_t DELAY_TIME_EN              : 1;
}ICM_20948_FSYNC_CONFIG_t;

typedef struct{
	uint8_t TEMP_DLPFCFG               : 3;
	uint8_t reserved_0                 : 5;
}ICM_20948_TEMP_CONFIG_t;

typedef struct{
	uint8_t REG_LP_DMP_EN              : 1;
	uint8_t reserved_0                 : 7;
}ICM_20948_MOD_CTRL_USR_t;

// Bank 3 Types

typedef struct{
	uint8_t I2C_MST_ODR_CONFIG         : 4;
	uint8_t reserved_0                 : 4;
}ICM_20948_I2C_MST_ODR_CONFIG_t;

typedef struct{
	uint8_t I2C_MST_CLK                : 4;
	uint8_t I2C_MST_P_NSR              : 1;
	uint8_t reserved_0                 : 2;
	uint8_t MULT_MST_EN                : 1;
}ICM_20948_I2C_MST_CTRL_t;

typedef struct{
	uint8_t I2C_SLV0_DELAY_EN          : 1;
	uint8_t I2C_SLV1_DELAY_EN          : 1;
	uint8_t I2C_SLV2_DELAY_EN          : 1;
	uint8_t I2C_SLV3_DELAY_EN          : 1;
	uint8_t I2C_SLV4_DELAY_EN          : 1;
	uint8_t reserved_0                 : 2;
	uint8_t DELAY_ES_SHADOW            : 1;
}ICM_20948_I2C_MST_DELAY_CTRL_t;

typedef struct{
	uint8_t ID                         : 7;
	uint8_t RNW                        : 1;
}ICM_20948_I2C_SLVX_ADDR_t;

typedef struct{
	uint8_t REG;	
}ICM_20948_I2C_SLVX_REG_t;

typedef struct{
	uint8_t LENG                       : 4;
	uint8_t GRP                        : 1;
	uint8_t REG_DIS                    : 1;
	uint8_t BYTE_SW                    : 1;
	uint8_t EN                         : 1;
}ICM_20948_I2C_SLVX_CTRL_t;

typedef struct{
	uint8_t DO;
}ICM_20948_I2C_SLVX_DO_t;

typedef struct{
	uint8_t DLY                        : 5;
	uint8_t REG_DIS                    : 1;
	uint8_t INT_EN                     : 1;
	uint8_t EN                         : 1;
}ICM_20948_I2C_SLV4_CTRL_t;

typedef struct{
	uint8_t DI;
}ICM_20948_I2C_SLV4_DI_t;


// Bank select register!

typedef struct{
	uint8_t reserved_0                 : 4;
	uint8_t USER_BANK                  : 2;
	uint8_t reserved_1                 : 2;
}ICM_20948_REG_BANK_SEL_t;

typedef enum {
	USER_BANK_BIT_INDEX = 4,

	USER_BANK_BIT_MASK = 0x03
}ICM_20948_REG_BANK_SEL_BITMASKS;

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* _ICM_20948_REGISTERS_H_ */
