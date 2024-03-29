#ifndef GIMBAL_DEFS_H
#define GIMBAL_DEFS_H

#define START 0x3E
#define ALEX_MOS_MAX_PACKET_LEN 260
#define CHSUM                   0x00


#define CMD_CALIB_ACC 			65
#define CMD_CALIB_BAT 			66
#define CMD_CONFIRM 			67
#define CMD_CONTROL 			67
#define CMD_REALTIME_DATA 		68
#define CMD_EXECUTE_MENU 		69
#define CMD_USE_DEFAULTS		70
#define CMD_CALIB_EXT_GAIN 		71
#define CMD_HELPER_DATA 		72
#define CMD_GET_ANGLES 			73
#define CMD_MOTORS_ON 			77
#define CMD_CALIB_OFFSET 		79
#define CMD_CALIB_POLES			80
#define CMD_READ_PARAMS 		82
#define CMD_TRIGGER_PIN 		84
#define CMD_BOARD_INFO 			86
#define CMD_WRITE_PARAMS 		87
#define CMD_CALIB_GYRO 			103
#define CMD_MOTORS_OFF 			109
#define CMD_RESET 				114

// Board v3.x only
#define CMD_BOARD_INFO_3 		20
#define CMD_READ_PARAMS_3 		21
#define CMD_WRITE_PARAMS_3 		22
#define CMD_REALTIME_DATA_3 	23
#define CMD_REALTIME_DATA_4 	25
#define CMD_SELECT_IMU_3 		24
#define CMD_READ_PROFILE_NAMES 	28
#define CMD_WRITE_PROFILE_NAMES	29
#define CMD_QUEUE_PARAMS_INFO_3 30
#define CMD_SET_ADJ_VARS 		31
#define CMD_SAVE_PARAMS_3 		32
#define CMD_READ_PARAMS_EXT 	33
#define CMD_WRITE_PARAMS_EXT 	34
#define CMD_AUTO_PID 			35
#define CMD_SERVO_OUT 			36
#define CMD_I2C_WRITE_REG_BUF 	39
#define CMD_I2C_READ_REG_BUF	40
#define CMD_WRITE_EXTERNAL_DATA 41
#define CMD_READ_EXTERNAL_DATA	42
#define CMD_READ_ADJ_VARS_CFG 	43
#define CMD_WRITE_ADJ_VARS_CFG 	44
#define CMD_API_VIRT_CH_CONTROL 45
#define CMD_ADJ_VARS_STATE 		46
#define CMD_EEPROM_WRITE 		47
#define CMD_EEPROM_READ 		48
#define CMD_BOOT_MODE_3 		51
#define CMD_READ_FILE 			53
#define CMD_WRITE_FILE 			54
#define CMD_FS_CLEAR_ALL 		55
#define CMD_AHRS_HELPER 		56
#define CMD_RUN_SCRIPT 			57
#define CMD_SCRIPT_DEBUG 		58
#define CMD_CALIB_MAG 			59
#define CMD_DEBUG_VARS_INFO_3 	253
#define CMD_DEBUG_VARS_3 		254
#define CMD_ERROR 				255

#endif // GIMBAL_DEFS_H
