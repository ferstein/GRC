#ifndef __alex_mos32_h__
#define __alex_mos32_h__
#include <stdint.h>
#include "math.h"

#define alex_mos_getting_angles_interval  50 // miliSeconds
#define alex_mos_sending_control_interval 50 // miliSeconds

#define ALEX_MOS_DEFAULT_SERIAL_PORT_SPEED 38400

#define ALEX_MOS_MAX_ADJ_VARS_LEN 250

#define ALEX_MOS_CONTROL_MODE_NO_CONTROL  0
#define ALEX_MOS_CONTROL_MODE_SPEED       1
#define ALEX_MOS_CONTROL_MODE_ANGLE       2
#define ALEX_MOS_CONTROL_MODE_SPEED_ANGLE 3
#define ALEX_MOS_CONTROL_MODE_RC          4

#define ONE_UNIT_OF_RECIVED_ANGLE_DEG 0.02197265625f
#define ONE_UNIT_OF_RECIVED_ANGLE_RAD 0.001533980787886f
#define ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit 0.0003834951969714f //   2*Pi/2^14(16383)
#define angle_90_degrees 				4096
#define START 0x3E 
#define ALEX_MOS_MAX_PACKET_LEN 260
#define CHSUM                   0x00 

#define BOARD_FEATURE_3AXIS   1
#define BOARD_FEATURE_BAT_MONITORING   2
#define BOARD_FEATURE_ENCODERS   4
#define BOARD_FEATURE_BODE_TEST   8
#define BOARD_FEATURE_SCRIPTING   16
#define BOARD_FEATURE_CURRENT_SENSOR   32

#define PWM_FREQ_LOW = 0
#define PWM_FREQ_HIGH = 1
#define PWM_FREQ_ULTRA_HIGH = 2 //(BOARD_VER>=30)

//Mode of RC_ROLL input pin operation:
#define RC_VIRT_MODE_NORMAL 0
#define RC_VIRT_MODE_CPPM 1
#define RC_VIRT_MODE_SBUS 2     //(BOARD_VER >= 30)
#define RC_VIRT_MODE_SPEKTRUM 3 //(BOARD_VER >= 30)
#define RC_VIRT_MODE_API 10     //(BOARD_VER >= 30)

#define t1u uint8_t
#define t1s int8_t
#define t2u uint16_t
#define t2s int16_t
#define t4f float
#define t4s int32_t
#define t4u uint32_t



#define CMD_CALIB_ACC 				65
#define CMD_CALIB_BAT 				66
#define CMD_CONFIRM 					67
#define CMD_CONTROL 					67
#define CMD_REALTIME_DATA 		68
#define CMD_EXECUTE_MENU 			69
#define CMD_USE_DEFAULTS			70
#define CMD_CALIB_EXT_GAIN 		71
#define CMD_HELPER_DATA 			72
#define CMD_GET_ANGLES 				73
#define CMD_MOTORS_ON 				77
#define CMD_CALIB_OFFSET 			79
#define CMD_CALIB_POLES				80
#define CMD_READ_PARAMS 			82
#define CMD_TRIGGER_PIN 			84
#define CMD_BOARD_INFO 				86
#define CMD_WRITE_PARAMS 			87
#define CMD_CALIB_GYRO 				103
#define CMD_MOTORS_OFF 				109
#define CMD_RESET 						114

// Board v3.x only
#define CMD_BOARD_INFO_3 					20
#define CMD_READ_PARAMS_3 				21
#define CMD_WRITE_PARAMS_3 				22
#define CMD_REALTIME_DATA_3 			23
#define CMD_REALTIME_DATA_4 			25
#define CMD_SELECT_IMU_3 					24
#define CMD_READ_PROFILE_NAMES 		28
#define CMD_WRITE_PROFILE_NAMES		29
#define CMD_QUEUE_PARAMS_INFO_3 	30
#define CMD_SET_ADJ_VARS 					31
#define CMD_SAVE_PARAMS_3 				32
#define CMD_READ_PARAMS_EXT 			33
#define CMD_WRITE_PARAMS_EXT 			34
#define CMD_AUTO_PID 							35
#define CMD_SERVO_OUT 						36
#define CMD_I2C_WRITE_REG_BUF 		39
#define CMD_I2C_READ_REG_BUF		 	40
#define CMD_WRITE_EXTERNAL_DATA 	41
#define CMD_READ_EXTERNAL_DATA		42
#define CMD_READ_ADJ_VARS_CFG 		43
#define CMD_WRITE_ADJ_VARS_CFG 		44
#define CMD_API_VIRT_CH_CONTROL 	45
#define CMD_ADJ_VARS_STATE 				46
#define CMD_EEPROM_WRITE 					47
#define CMD_EEPROM_READ 					48
#define CMD_BOOT_MODE_3 					51
#define CMD_READ_FILE 						53
#define CMD_WRITE_FILE 						54
#define CMD_FS_CLEAR_ALL 					55
#define CMD_AHRS_HELPER 					56
#define CMD_RUN_SCRIPT 						57
#define CMD_SCRIPT_DEBUG 					58
#define CMD_CALIB_MAG 						59
#define CMD_DEBUG_VARS_INFO_3 		253
#define CMD_DEBUG_VARS_3 					254
#define CMD_ERROR 								255
//      Type (0..3 bits):
#define VAR_TYPE_UINT8 1
#define VAR_TYPE_INT8 2
#define VAR_TYPE_UINT16 3
#define VAR_TYPE_INT16 4
#define VAR_TYPE_UINT32 5
#define VAR_TYPE_INT32 6
#define VAR_TYPE_FLOAT 7 //(IEEE-754)
//      Flags (4..7 bits):
#define VAR_FLAG_ROLL 16    // its belong to ROLL axis
#define VAR_FLAG_PITCH 32   // its belong to PITCH axis
#define VAR_FLAG_YAW 48     // its belong to YAW axis
#define VAR_FLAG_ANGLE14 64 // its an angle (14bit per turn)

#pragma pack(push,1)
typedef struct __alexmos_debug_var__
  {
  uint8_t name[20];
  uint8_t type;
  uint32_t value;
}alexmos_debug_var_type;

typedef struct __alexmos_debug_vars__ 
  {
  uint8_t vars_count;
  alexmos_debug_var_type var[20];
  uint8_t DR;                     //new data ready (recived) flag
}alexmos_debug_vars_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_BOARD_INFO_TYPE
{
	t1u BOARD_VER  ;   		//(split into decimal digits X . X, for example 10 means 1.0)
  t2u FIRMWARE_VER  ;		// (split into decimal digits X . XX . X, for example 2305 means 2.30b5)
  t1u DEBUG_MODE ;  		//(should hide DEBUG output if DEBUG_MODE = 0)
  t2u BOARD_FEATURES ;
  t1u CONNECTION_FLAGS; 
  uint8_t reserved[11];
}cmd_board_info_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_BOARD_INFO_3_TYPE  // additional board information
{
	uint8_t deviceID[9]; 			// device ID
  uint8_t mcuID[12];   			// MCU ID
  t4u EEPROM_SIZE; 
  t2u SCRIPT_SLOT1_SIZE;  	// size of user-written scripts stored in each slot, 0 if slot is empty.
  t2u SCRIPT_SLOT2_SIZE;
  t2u SCRIPT_SLOT3_SIZE;
	t2u SCRIPT_SLOT4_SIZE;
	t2u SCRIPT_SLOT5_SIZE;
  uint8_t reserved[34];
}cmd_board_info_3_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_READ_PARAMS_3_TYPE // Receive parameters for single profile together with general parameters .
{
	t1u PROFILE_ID;  //ID of profile to read, starting from 0
	struct roll_pid
		{
			t1u P;
			t1u I ; //(multiplied by 100)
			t1u D ; 
			t1u POWER ;
			t1u INVERT ;  //(checked=1, not checked=0)
			t1u POLES ; 
		}_roll_pid;
	struct pitch_pid
		{
			t1u P;
			t1u I ; //(multiplied by 100)
			t1u D ; 
			t1u POWER ;
			t1u INVERT ;  //(checked=1, not checked=0)
			t1u POLES ; 
		}_pitch_pid;
	struct yaw_pid
		{
			t1u P;
			t1u I ; //(multiplied by 100)
			t1u D ; 
			t1u POWER ;
			t1u INVERT ;  //(checked=1, not checked=0)
			t1u POLES ; 
		}_yaw_pid;
	t1u ACC_LIMIT; 
  t1s EXT_FC_GAIN_ROLL;
  t1s EXT_FC_GAIN_PITCH;
	struct roll_rc //, PITCH, YAW]) 
		{
			t2s RC_MIN_ANGLE;//  2s
			t2s RC_MAX_ANGLE;//  2s
			t1u RC_MODE;//  1u
			t1u RC_LPF;// 1u
      t1u RC_SPEED;// 1u
      t1u RC_FOLLOW;//  1u
    }_roll_rc;
	struct pitch_rc 
		{
			t2s RC_MIN_ANGLE;//  2s
			t2s RC_MAX_ANGLE;//  2s
			t1u RC_MODE;//  1u
			t1u RC_LPF;// 1u
      t1u RC_SPEED;// 1u
      t1u RC_FOLLOW;//  1u
    }_pitch_rc;
	struct yaw_rc
		{
			t2s RC_MIN_ANGLE;//  2s
			t2s RC_MAX_ANGLE;//  2s
			t1u RC_MODE;//  1u
			t1u RC_LPF;// 1u
      t1u RC_SPEED;// 1u
      t1u RC_FOLLOW;//  1u
    }_yaw_rc;
   t1u GYRO_TRUST;// 1u
   t1u USE_MODEL ;//– 1u
   t1u PWM_FREQ ;//– 1u
   t1u SERIAL_SPEED;// 1u
   t1s RC_TRIM_ROLL ;//- 1s
   t1s RC_TRIM_PITCH;//  1s
   t1s RC_TRIM_YAW;//  1s
   t1u RC_DEADBAND;//  1u
   t1u RC_EXPO_RATE;//  1u
   t1u RC_VIRT_MODE;// 1u
   t1u RC_MAP_ROLL;//1u
   t1u RC_MAP_PITCH;//1u
   t1u RC_MAP_YAW;//1u
   t1u RC_MAP_CMD;//1u
   t1u RC_MAP_FC_ROLL;//1u
   t1u RC_MAP_FC_PITCH;//1u
   t1u RC_MIX_FC_ROLL;//1u
   t1u RC_MIX_FC_PITCH;// 1u
   t1u FOLLOW_MODE;//1u
   t1u FOLLOW_DEADBAND;//1u
   t1u FOLLOW_EXPO_RATE;//1u
	 t1s FOLLOW_OFFSET_ROLL;//1s
   t1s FOLLOW_OFFSET_PITCH;//1s © 2013-2015 Basecamelectronics®
   t1s FOLLOW_OFFSET_YAW;//1s
   t1s AXIS_TOP;//1s
   t1s AXIS_RIGHT;//1s
   t1s FRAME_AXIS_TOP;//1s
   t1s FRAME_AXIS_RIGHT;//1s
   t1u FRAME_IMU_POS;// 1u
   t1u GYRO_LPF;// 1u
   t1u GYRO_SENS;// 1u
   t1u I2C_INTERNAL_PULLUPS;// 1u
   t1u SKIP_GYRO_CALIB;// 1u
   t1u RC_CMD_LOW;// 1u
   t1u RC_CMD_MID;// 1u
   t1u RC_CMD_HIGH;// 1u
   t1u MENU_CMD_1;// 1u
   t1u MENU_CMD_2;// 1u
   t1u MENU_CMD_3;// 1u
   t1u MENU_CMD_4;// 1u
   t1u MENU_CMD_5;// 1u
   t1u MENU_CMD_LONG;// 1u
   t1u OUTPUT_ROLL;// 1u
   t1u OUTPUT_PITCH;// 1u
   t1u OUTPUT_YAW;// 1u
   t2s BAT_THRESHOLD_ALARM;// 2s
   t2s BAT_THRESHOLD_MOTORS;// 2s
   t2s BAT_COMP_REF;// 2s
   t1u BEEPER_MODES;// 1u
   t1u FOLLOW_ROLL_MIX_START;// 1u
   t1u FOLLOW_ROLL_MIX_RANGE;//- 1u
   t1u BOOSTER_POWER_ROLL; // 1u
   t1u BOOSTER_POWER_PITCH; // 1u
   t1u BOOSTER_POWER_YAW; // 1u
   t1u FOLLOW_SPEED_ROLL; // 1u
   t1u FOLLOW_SPEED_PITCH; // 1u
   t1u FOLLOW_SPEED_YAW; // 1u
   t1u FRAME_ANGLE_FROM_MOTORS; // 1u
   t2s RC_MEMORY_ROLL; // 2s
   t2s RC_MEMORY_PITCH; // 2s
   t2s RC_MEMORY_YAW; // 2s
   t1u SERVO1_OUT; // 1u
   t1u SERVO2_OUT; // 1u
   t1u SERVO3_OUT; // 1u
   t1u SERVO4_OUT; // 1u
   t1u SERVO_RATE; // 1u
   t1u ADAPTIVE_PID_ENABLED; // 1u
   t1u ADAPTIVE_PID_THRESHOLD; // 1u
   t1u ADAPTIVE_PID_RATE; // 1u
   t1u ADAPTIVE_PID_RECOVERY_FACTOR; // 1u
   t1u FOLLOW_LPF_ROLL; // 1u
   t1u FOLLOW_LPF_PITCH; // 1u
   t1u FOLLOW_LPF_YAW; // 1u
   t2u GENERAL_FLAGS1; // 2u
   t2u PROFILE_FLAGS1; // 2u
   t1u SPEKTRUM_MODE; // 1u
	 uint8_t RESERVED_BYTES[2];// 2b	 
   t1u CUR_IMU;//  1u (currently selected IMU)
   t1u CUR_PROFILE_ID;// 1u (profile ID which is currently active in the controller)
}cmd_read_params_3_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_READ_PARAMS_EXT_TYPE // read extended set of params for
{
  t1u PROFILE_ID; // 1u (ID of profile to read, starting from 0)
	struct profile_0{
			t1u NOTCH_FREQ[3]; // 1u * 3
		  t1u NOTCH_WIDTH[3];}_profile_0; // 1u * 3
	struct profile_1{
			t1u NOTCH_FREQ[3]; // 1u * 3
			t1u NOTCH_WIDTH[3];}_profile_1; // 1u * 3
	struct profile_2{
			t1u NOTCH_FREQ[3]; // 1u * 3
			t1u NOTCH_WIDTH[3];}_profile_2; // 1u * 3
  t2u LPF_FREQ[3];// 2u * 3
  t1u FILTERS_EN[3];// 1u * 3
  t2s ENCODER_OFFSET[3];// 2s * 3
  t2s ENCODER_FLD_OFFSET[3];// 2s * 3
  t1u ENCODER_MANUAL_SET_TIME[3];// 1u * 3
  t1u MOTOR_HEATING_FACTOR[3];// 1u * 3
  t1u MOTOR_COOLING_FACTOR[3];// 1u * 3
  t1u RESERVED_[3]; // 3b
  t1u MOTOR_MAG_LINK[3]; //  1u * 3
  t2u MOTOR_GEARING[3];  // 2u * 3
  t1s ENCODER_LIMIT_MIN[3]; // 1s * 3
  t1s ENCODER_LIMIT_MAX[3]; // 1s * 3
  t1u NOTCH1_GAIN[3];// 1u * 3
  t1u NOTCH2_GAIN[3];// 1u * 3
  t1u NOTCH3_GAIN[3];// 1u * 3
  t1u BEEPER_VOLUME;// 1u
  t2u ENCODER_GEAR_RATIO[3];// 2u * 3
  t1u ENCODER_TYPE[3];// 1u * 3
  t1u ENCODER_CFG[3];// 1u * 3
  t1u OUTER_P[3];// 1u * 3
  t1u OUTER_I[3];// 1u * 3
  t1s MAG_AXIS_TOP;// 1s
  t1s MAG_AXIS_RIGHT;// 1s
  t1u MAG_TRUST;// 1u	
	t1s MAG_DECLINATION;// 1s
  t1u RESERVED__[5];//  5b
}cmd_read_params_ext_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_REALTIME_DATA_3_type // receive real-time data for
{
	struct ROLL  { 
			t2s ACC; 		//2s
			t2s GYRO;}_ROLL; // 2s
	struct PITCH { 
			t2s ACC; 		//2s
			t2s GYRO;}_PITCH; // 2s
	struct  YAW  { 
			t2s ACC; 		//2s
			t2s GYRO;}_YAW; // 2s
  t2s DEBUG1; //  2s
  t2s DEBUG2; //  2s
  t2s DEBUG3; //  2s
  t2s DEBUG4; //  2s
  t2s RC_ROLL; //  2s
  t2s RC_PITCH; //  2s
  t2s RC_YAW; //  2s
  t2s RC_CMD; //  2s
  t2s EXT_FC_ROLL; //  2s
  t2s EXT_FC_PITCH; //  2s
  t2s ANGLE_ROLL; //  2s
  t2s ANGLE_PITCH; //  2s
  t2s ANGLE_YAW; //  2s
  t2s FRAME_IMU_ANGLE_ROLL; //  2s
  t2s FRMAE_IMU_ANGLE_PITCH; //  2s
  t2s FRAME_IMU_ANGLE_YAW; //  2s
  t2s RC_ANGLE_ROLL; //  2s
  t2s RC_ANGLE_PITCH; //  2s
  t2s RC_ANGLE_YAW; //  2s
  t2u CYCLE_TIME; //  2u
  t2u I2C_ERROR_COUNT; //  2u
  t1u ERROR_CODE; //  1u
  t2u BAT_LEVEL; //  2u
  t1u OTHER_FLAGS; //  1u
  t1u CUR_IMU; //  1u
  t1u CUR_PROFILE; //  1u
  t1u MOTOR_POWER_ROLL; //  1u
  t1u MOTOR_POWER_PITCH; //  1u
  t1u MOTOR_POWER_YAW; // 1u
}cmd_realtime_data_3_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_REALTIME_DATA_4_TYPE  // receive extended real-time data
{
	struct ROLL_S  { 
			t2s ACC; 		//2s
			t2s GYRO;}_ROLL_S; // 2s
	struct PITCH_S { 
			t2s ACC; 		//2s
			t2s GYRO;}_PITCH_S; // 2s
	struct  YAW_S  { 
			t2s ACC; 		//2s
			t2s GYRO;}_YAW_S; // 2s
  t2s DEBUG1; //  2s
  t2s DEBUG2; //  2s
  t2s DEBUG3; //  2s
  t2s DEBUG4; //  2s
  t2s RC_ROLL; //  2s
  t2s RC_PITCH; //  2s
  t2s RC_YAW; //  2s
  t2s RC_CMD; //  2s
  t2s EXT_FC_ROLL; //  2s
  t2s EXT_FC_PITCH; //  2s
  t2s ANGLE_ROLL; //  2s
  t2s ANGLE_PITCH; //  2s
  t2s ANGLE_YAW; //  2s
  t2s FRAME_IMU_ANGLE_ROLL; //  2s
  t2s FRMAE_IMU_ANGLE_PITCH; //  2s
  t2s FRAME_IMU_ANGLE_YAW; //  2s
  t2s RC_ANGLE_ROLL; //  2s
  t2s RC_ANGLE_PITCH; //  2s
  t2s RC_ANGLE_YAW; //  2s
  t2u CYCLE_TIME; //  2u
  t2u I2C_ERROR_COUNT; //  2u
  t1u ERROR_CODE; //  1u
  t2u BAT_LEVEL; //  2u
  t1u OTHER_FLAGS; //  1u
  t1u CUR_IMU; //  1u
  t1u CUR_PROFILE; //  1u
  t1u MOTOR_POWER_ROLL; //  1u
  t1u MOTOR_POWER_PITCH; //  1u
  t1u MOTOR_POWER_YAW; // 1u
  t2s FRAME_ANGLE_ROLL; // 2s
  t2s FRAME_ANGLE_PITCH; // 2s
  t2s FRAME_ANGLE_YAW; // 2s
  t1u RESERVED_; // 1b
  t2s BALANCE_ERROR_ROLL; // 2s
  t2s BALANCE_ERROR_PITCH; // 2s
  t2s BALANCE_ERROR_YAW; // 2s
  t2u CURRENT; // 2u (units: mA)
  t2s MAG_DATA_ROLL; // 2s
  t2s MAG_DATA_PITCH; // 2s
  t2s MAG_DATA_YAW; // 2s
  t1s FRAME_IMU_TEMPERATURE; // 1s (units: Celsius)
  t2s FRAME_CAM_ANGLE_ROLL; // 2s
  t2s FRAME_CAM_ANGLE_PITCH; // 2s
  t2s FRAME_CAM_ANGLE_YAW; // 2s
  t1u RESERVED__[32]; //  32b	
}cmd_realtime_data_4_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_CONFIRM_type // confirmation of previous command
{
  t1u CMD;// 1u
  t1u DATA[160];// depends on CMD
//Board sends confirmation on commands: A, G, P, W, etc. DATA is empty unless mentioned in command
//description.
}cmd_confirm_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_ERROR_TYPE // error on executing previous command
{
  t1u ERROR_CODE; // 1u
  t1u ERROR_DATA[4]; // 4b
//Data depends on error type.
}cmd_error_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_GET_ANGLES_TYPE // Information about actual RC control state
{
  struct ROLLangle 
		{
			t2s ANGLE; // 2s
			t2s RC_ANGLE; // 2s
			t2s RC_SPEED; // 2s
		}_ROLLangle;
	struct PITCHangle
		{
			t2s ANGLE; // 2s
			t2s RC_ANGLE; // 2s
			t2s RC_SPEED; // 2s
		}_PITCHangle;
	struct YAWangle
		{
			t2s ANGLE; // 2s
			t2s RC_ANGLE; // 2s
			t2s RC_SPEED; // 2s
		}_YAWangle;
		
}cmd_get_angles_type;
	

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_READ_PROFILE_NAMES_3_TYPE 
// receive profile names from EEPROM
//Each name is encoded in UTF-8 format and padded with '\0' character to 48 byte size
{
  t1u PROFILE1_NAME[48]; //   48b
  t1u PROFILE2_NAME[48]; //   48b
  t1u PROFILE3_NAME[48]; //   48b
  t1u PROFILE4_NAME[48]; //   48b
  t1u PROFILE5_NAME[48]; //   48b
}cmd_read_profile_names_3_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_I2C_READ_REG_BUF_TYPE 
//result of reading from I2C device
{
	t1u DATA[255]; // 1..255 byte, depends on the DATA_LEN parameter in the request.
}cmd_i2c_read_reg_buf_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_AUTO_PID_TYPE // progress of PID auto tuning
{
  t1u P_ROLL; // 1u
  t1u P_PITCH; // 1u
  t1u P_YAW; // 1u
  t1u I_ROLL; // 1u
  t1u I_PITCH; // 1u
  t1u I_YAW; // 1u
  t1u D_ROLL; // 1u
  t1u D_PITCH; // 1u
  t1u D_YAW; // 1u
  t2u RMS_ERR_R; // 2u
  t2u FREQ_R; // 2u
  t2u RMS_ERR_P; // 2u
  t2u FREQ_P; // 2u
  t2u RMS_ERR_Y; // 2u
  t2u FREQ_Y; // 2u
  t1u RESERVED[36]; // 36b
}cmd_auto_pid_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct __CMD_DEBUG_VARS_INFO_3_TYPE  // receive specification of the debug variables
{
	t1u debug_vars_num;// 1u - number of debug vars
  unsigned char debug_vars[ALEX_MOS_MAX_ADJ_VARS_LEN];
}cmd_debug_vars_info_3_type; 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
typedef struct __CMD_DEBUG_VARS_3_TYPE // values of some variables reflecting a state of the system.

A set and an order of variables is not strictly defined, and may vary depending on the firmware version. Use
CMD_DEBUG_VARS_INFO_3 to get a specification of the variables.

{
  
}
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_READ_EXTERNAL_DATA_TYPE 
  // receive user data, stored in the EEPROM
{
  t1u data[128]; // 128b
}cmd_read_external_data_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __actions_trigger_type__
{
  t1u SRC_CH; //  1u
  t1u ACTION1;//  1u
  t1u ACTION2;//  1u
  t1u ACTION3;//  1u
  t1u ACTION4;//  1u
  t1u ACTION5;//  1u
}actions_trigger_type;

typedef struct __analog_slots_type__
{
  t1u SRC_CH; //  1u
  t1u PARAM_ID; //  1u
  t1u MIN_VAL; //  1u
  t1u MAX_VAL; //  1u
}analog_slots_type;


typedef struct __CMD_READ_ADJ_VARS_CFG_TYPE 
/*  receive configuration of mapping of control inputs to adjustable
variables
There are 10 “trigger” slots and 15 “analog” slots. “Trigger” type is used to execute action depending on the
RC signal level, where full range is split into 5 levels (see Available actions). “Analog” type is used to adjust
parameter by RC signal. MIN_VAL and MAX_VAL specify a working range, that is combined with the native
range of particular parameter (see List of available parameters)*/
{
  actions_trigger_type actions[10];
  analog_slots_type analog[15];
  t1u RESERVED[8]; // 8b
}cmd_read_adj_vars_cfg_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*typedef struct __CMD_RESET_TYPE
Notification on device reset
Device sent this command when goes to reset. There is a delay 1000ms after this 
command is sent and reset is actually done. External application can free up 
resources and properly close the serial connection./
{ 
}cmd_reset_type;*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_EEPROM_READ_TYPE 
 // receive block of data from EEPROM at the specified address.
{
  t4u ADDR; // 4u, 64-byte aligned
  t1u DATA[255]; // any size, as specified in the CMD_EEPROM_READ outgoing command.
}cmd_eeprom_read_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_READ_FILE_TYPE 
// result of reading file from internal filesystem
//In case of success:
{
  t2u FILE_SIZE;  // 2u total size of file, bytes
  t2u PAGE_OFFSET;// 2u offset that was requested, in pages. 1 page = 64 bytes
  t1u DATA[2048];      // size that was requested, or less if end of file is reached
//In case of errors:
  t1u ERR_CODE;   // 1u (see error definitions in the CMD_WRITE_FILE command)
}cmd_read_file_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_SCRIPT_DEBUG_TYPE
//state of execution of user-written script
{
  t2u CMD_COUNT;// 2u current command counter
  t1u ERR_CODE; // 1u (see error definitions in the CMD_WRITE_FILE command)
}cmd_script_debug_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_AHRS_HELPER_TYPE
//current attitude in vector form
{
  float GRAVITY_VECTOR[3];// 3f
  float HEADING_VECTOR[3];// 3f
}cmd_ahrs_helper_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//                       Outgoing commands section
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_CALIB_GYRO_TYPE
//calibrate gyroscope
//Simple format: no parameters. Starts regular calibration of currently active IMU (set by CMD_SELECT_IMU_3
//command)
//Extended format (for both commands):
{
  t1u IMU_IDX;// 1u (0;//  currently active IMU, 1;//  main IMU, 2;//  frame IMU)
  t1u ACTION; // 1u
  /*
    1=  do regular calibration
    2=  reset all calibrations and restart
    3=  do temperature calibration
    4=  enable temp. calib. data, if present and restart
    5=  disable temp. calib. data (but keep in memory) and restart
  */
  t1u RESERVED[10];// 10b
//Confirmation is sent immediately on reception and in the end of calibration.
}cmd_out_calib_gyro_type;

#define CALIB_GYRO_REGULAR 1
#define CALIB_GYRO_RESET   2
#define CALIB_GYRO_TEMPERATURE 3
#define CALIB_GYRO_EN_TEMP_CAL_DATA 4
#define CALIB_GYRO_DIS_TEMP_CAL_DATA 5

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_CONTROL_TYPE
//control gimbal movement
{
  t1u CONTROL_MODE; //  1u
  t2s SPEED_ROLL; //  2s
  t2s ANGLE_ROLL; //  2s
  t2s SPEED_PITCH; //  2s
  t2s ANGLE_PITCH; //  2s
  t2s SPEED_YAW; //  2s
  t2s ANGLE_YAW; //  2s
}cmd_out_control_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_TRIGGER_PIN_TYPE 
//trigger output pin
{
  t1u PIN_ID;// 1u
  t1u STATE; // 1u
//Confirmation is sent only if pin is not used for input and is really triggered.
}cmd_out_trigger_pin_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_HELPER_DATA_TYPE 
//pass helper data
{
  t2s FRAME_ACC_X; //  2s
  t2s FRAME_ACC_Y; //  2s
  t2s FRAME_ACC_Z; //  2s
  t2s FRAME_ANGLE_ROLL; //  2s
  t2s FRAME_ANGLE_PITCH; //  2s
}cmd_out_helper_data_type; 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_WRITE_PROFILE_NAMES_3_TYPE
//Writes profile names to EEPROM
//Each name is encoded in UTF-8 format and padded with '\0' character to 48 byte size
{
  t1u PROFILE1_NAME[48];
  t1u PROFILE2_NAME[48];
  t1u PROFILE3_NAME[48];
  t1u PROFILE4_NAME[48];
  t1u PROFILE5_NAME[48];
}cmd_out_write_profile_names_3_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __ADJ_VAR_TYPE
{
  t1u PARAM1_ID;// 1u
  t4s PARAM1_VALUE;// 4s
}adj_var_type;

typedef struct __CMD_OUT_SET_ADJ_VARS_TYPE
// Change the value of selected parameter(s)
// This command is intended to change parameters on-the-fly during system operation, and does not save
// parameters to EEPROM. You need to send CMD_SAVE_PARAMS_3 to do this. List of available parameters
{
  t1u NUM_VARS; // 1u
  adj_var_type var[ALEX_MOS_MAX_ADJ_VARS_LEN];
//...repeat for remaining parameters...
//On success, confirmation is sent in response
}cmd_out_set_adj_vars_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_AUTO_PID_TYPE
//Starts automatic PID calibration
{
  t1u PROFILE_ID;  //  1u - switch to this profile before start of calibration
  t1u CFG_FLAGS;   //  1u
  t1u GAIN_VS_STABILITY; //  1u
  t1u RESERVED[16];
}cmd_out_auto_pid_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_SERVO_OUT_TYPE
// Output PWM signal on the specified pins
// Although it takes 8 values, the real number of hardware outputs depends on board version and may be less.
{
  t2s SERVO1_TIME;//  2s  - shared with FC_ROLL
  t2s SERVO2_TIME;//  2s  - shared with FC_PITCH
  t2s SERVO3_TIME;//  2s  - shared with RC_PITCH
  t2s SERVO4_TIME;//  2s  - shared with AUX1
  t2s SERVO5_TIME;//  2s  - reserved
  t2s SERVO6_TIME;//  2s  - reserved
  t2s SERVO7_TIME;//  2s  - reserved
  t2s SERVO8_TIME;//  2s  - reserved
}cmd_out_servo_out_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_I2C_WRITE_REG_BUF_TYPE
// writes data to any device connected to I2C line
{
  t1u DEVICE_ADDR;// 1u , where 1..7th bits specify address, 0th bit selects I2C 
                  // port: 0 for main (sensor) port, 1 for second (EEPROM) port
  t1u REG_ADDR;   // 1u address of register
  t1u DATA[253];  // 1..253 bytes
// On successful writing, confirmation CMD_CONFIRM is sent in response.
}cmd_out_i2c_write_reg_buf_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_I2C_READ_REG_BUF_TYPE
// Requests reading from any device connected to I2C line
{
  t1u DEVICE_ADDR ;// 1u, the same as for corresponding write command
  t1u REG_ADDR ;   // 1u address of register
  t1u DATA_LEN ;   // 1u length of the data to be read, 1..255
// On successful reading, CMD_I2C_READ_REG_BUF command is sent in response.
}cmd_out_i2c_read_reg_buf_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_API_VIRT_CH_CONTROL_TYPE
// Update a state of 32 virtual channels that named “API_VIRT_CHXX” in the GUI
// These channels can be selected as RC source to control camera or to do other tasks.
{
  t2s VAL_CH1; t2s VAL_CH2; t2s VAL_CH3; t2s VAL_CH4; t2s VAL_CH5; t2s VAL_CH6;
  t2s VAL_CH7; t2s VAL_CH8; t2s VAL_CH9; t2s VAL_CH10;t2s VAL_CH11;t2s VAL_CH12;
  t2s VAL_CH13;t2s VAL_CH14;t2s VAL_CH15;t2s VAL_CH16;t2s VAL_CH17;t2s VAL_CH18;
  t2s VAL_CH19;t2s VAL_CH20;t2s VAL_CH21;t2s VAL_CH22;t2s VAL_CH23;t2s VAL_CH24;
  t2s VAL_CH25;t2s VAL_CH26;t2s VAL_CH27;t2s VAL_CH28;t2s VAL_CH29;t2s VAL_CH30;
  t2s VAL_CH31;t2s VAL_CH32;
}cmd_out_api_virt_ch_control_type; // ©
 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_EEPROM_WRITE_TYPE
// Writes a block of data to EEPROM to specified address
{
  t4u ADDR; // 64-byte aligned
  t1u *DATA;// any size, 64-byte aligned
}cmd_out_eeprom_write_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_EEPROM_READ_TYPE
//Request a reading of block of data from EEPROM at the specified address and size.
{
  t4u ADDR;// 4u, 64-byte aligned
  t2u SIZE;// 2u, 64-byte aligned
// On success, CMD_EEPROM_READ is sent. See its description.
}cmd_out_eeprom_read_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_READ_FILE_TYPE
/*read file from internal filesystem
This command reads a portion of data from the file with identifier FILE_ID, 
started at PAGE_OFFSET pages(1page = 64byte). MAX_SIZE bytes will be read or 
less, if file end is reached. Size should not exceed maximum allowed command 
data length. Read data or error code is sent in the incoming command
CMD_READ_FILE. */
{
  t2u FILE_ID;// 2u
  t2u PAGE_OFFSET;// 2u
  t2u MAX_SIZE;   // 2u
  t1u RESERVED[14];
}cmd_out_read_file_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_WRITE_FILE_TYPE
  //Write file to internal filesystem
{
  t2u FILE_ID;
  t2u FILE_SIZE;
  t2u PAGE_OFFSET;
  t1u *DATA;   // 0 or any size
  /*
This command writes a portion of data to a file with identifier FILE_ID. If file is not exists, it is created. If
FILE_SIZE is not equal to existing file size, file is adjusted to new size. If DATA is empty, file is deleted.
In response CMD_CONFIRM is sent, with parameter ERR_CODE. Possible codes:
NO_ERROR = 0
ERR_EEPROM_FAULT = 1
ERR_FILE_NOT_FOUND = 2
ERR_FAT = 3
ERR_NO_FREE_SPACE = 4
ERR_FAT_IS_FULL = 5
ERR_FILE_SIZE = 6
ERR_CRC = 7
ERR_LIMIT_REACHED = 8
*/
}cmd_out_write_file_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_RUN_SCRIPT_TYPE
// start or stop user-written script
{
  t1u MODE;//(0 – stop, 1 – start, 2 – start with debug information is sent back 
           //in the CMD_SCRIPT_DEBUG)
  t1u SLOT;// 1u
  t1u RESERVED[32];
}cmd_out_run_script_type;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct __CMD_OUT_AHRS_HELPER_TYPE
// Use provided attitude instead of estimated attitude from main IMU sensor
{
  t1u MODE;//(0 – request data, 1 – set data)
  float GRAVITY_VECTOR[3];
  float HEADING_VECTOR[3];
}cmd_out_ahrs_helper_type;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct __alex_mos_msg_and_state
  { uint8_t total_bytes;
    uint8_t start;
    uint8_t command_id;
    uint8_t data_size;
    uint8_t header_cheksum;
    union
      {
        cmd_board_info_type            board_info;
        cmd_board_info_3_type          board_info_3;
        cmd_read_params_3_type         readed_params_3;
        cmd_read_params_ext_type       readed_params_ext;
        cmd_realtime_data_3_type       real_time_data_3 ;
        cmd_realtime_data_4_type       real_time_data_4 ;
        cmd_confirm_type               confirmation;
        cmd_error_type                 error;
        cmd_get_angles_type            getted_angles;
        cmd_read_profile_names_3_type  profile_names;
        cmd_i2c_read_reg_buf_type      i2c_reg_buf;
        cmd_auto_pid_type              auto_pid_progress;
        cmd_debug_vars_info_3_type     debug_vars_info_3; //
        cmd_read_external_data_type    external_data;
        cmd_read_adj_vars_cfg_type     readed_adj_vars_cfg;
        //cmd_reset_type                 reset;           //
        cmd_eeprom_read_type           eeprom_readed;
        //cmd_read_file_type             file;
        cmd_script_debug_type          script_debug;
        cmd_ahrs_helper_type           ahrs_helper;
        uint8_t debug_vars_3[250];
      }msg_union;
    uint8_t body_cheksum;
    uint16_t parsing_step;
    uint8_t *uint8_ptr;
    uint16_t onParseError;
    uint8_t detected;
    uint8_t serport;
    uint8_t enc_pitch_dvar_no;
    uint8_t enc_roll_dvar_no;
    uint8_t enc_yaw_dvar_no;

  }alex_mos_msg_and_state;

#pragma pack(pop)

//extern alexmos_debug_vars_type alexmos_debug_vars;
//extern alex_mos_msg_and_state alexmos;
//extern cmd_out_control_type alex_mos_ctrl_msg;

extern const uint8_t const_cmd_board_info[];
extern const uint8_t const_cmd_board_info3[];
extern const uint8_t const_cmd_read_params_3[];
extern const uint8_t const_cmd_read_params_ext[];
extern const uint8_t const_cmd_real_time_data_3[];
extern const uint8_t const_cmd_real_time_data_4[];
extern const uint8_t const_cmd_get_angles[];
extern const uint8_t const_cmd_read_profile_names[];
extern const uint8_t const_cmd_read_i2c_reg_buf[];
extern const uint8_t const_cmd_read_external_data[];
extern const uint8_t const_cmd_real_time_data[]			;
extern const uint8_t const_cmd_real_time_data_3[]		;
extern const uint8_t const_cmd_real_time_data_4[]		;
extern const uint8_t const_cmd_read_profile_names[]	;
extern const uint8_t const_cmd_read_i2c_reg_buf[]		;
extern const uint8_t const_cmd_read_external_data[]	;
extern const uint8_t const_cmd_calib_ext_gain[]			;
extern const uint8_t const_cmd_calib_poles[]				;
extern const uint8_t const_cmd_calib_offset[]				;
extern const uint8_t const_cmd_calib_mag[]					;
extern const uint8_t const_cmd_motors_on[]					;
extern const uint8_t const_cmd_motors_off[]					;
extern const uint8_t const_cmd_save_params[]				;
extern const uint8_t const_cmd_debug_vars_info_3[]	;
extern const uint8_t const_cmd_debug_vars_3[]				;
extern const uint8_t const_cmd_read_adj_vars_cfg[] 	;
extern const uint8_t const_cmd_read_vars_cfg[]			;
extern const uint8_t const_cmd_board_info_ext[]			;
extern const uint8_t const_cmd_calib_acc[]					;
extern const uint8_t const_cmd_calib_gyro[]					;
extern const uint8_t const_cmd_use_defaults[]				;
extern const uint8_t const_cmd_read_params[]				;
extern const uint8_t const_cmd_read_params_3[]			;
extern const uint8_t const_cmd_read_params_ext[]    ;
extern const uint8_t const_cmd_write_params[]				;
extern const uint8_t const_cmd_write_params_3[]			;
extern const uint8_t const_cmd_write_params_ext[]   ;
extern const uint8_t const_cmd_reset[]							;
extern const uint8_t const_cmd_boot_mode_3[]				;
extern const uint8_t const_cmd_calib_bat[]          ;
extern const uint8_t const_cmd_control[]         	  ;
extern const uint8_t const_cmd_trigger_pin[]        ;
extern const uint8_t const_cmd_execute_menu[]   		;
extern const uint8_t const_cmd_helper_data[]      	;
extern const uint8_t const_cmd_get_angles[]					;
extern const uint8_t const_cmd_select_imu[]					;
extern const uint8_t const_cmd_write_profile_names[];
extern const uint8_t const_cmd_set_adj_vars[] 			;
extern const uint8_t const_cmd_auto_pid[] 					;
extern const uint8_t const_cmd_servo_out[]					;
extern const uint8_t const_cmd_i2c_write_reg_buf[]	;
extern const uint8_t const_cmd_i2c_read_reg_buf[]		;
extern const uint8_t const_cmd_write_external_data[];
extern const uint8_t const_cmd_api_virt_ch_control[];
extern const uint8_t const_cmd_write_vars_cfg[]			;
extern const uint8_t const_cmd_eeprom_write[]				;
extern const uint8_t const_cmd_eeprom_read[]				;
extern const uint8_t const_cmd_ahrs_helper[]				;

extern const char rms_err_r[];
extern const char rms_err_p[];
extern const char rms_err_y[];
extern const char freq_r[];
extern const char freq_p[];
extern const char freq_y[];
extern const char enc_raw_r[];
extern const char enc_raw_p[];
extern const char enc_raw_y[];
extern const char imu_temp[];
extern const char f_imu_temp[];
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++FUNCTION PROTOTYPES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t find_debug_var_number (uint8_t * varname);
void alex_mos_get_debug_variables(void);
void send_back_recived_msg(void);
void alexmos_detect_and_init(alex_mos_msg_and_state *alexmos);


uint8_t AlexMosTiltLimiter (cmd_out_control_type *ctrl, float *current_pitch_encoder_angle);
uint8_t sort_alex_mos_message(uint8_t *ch ,uint16_t count,alex_mos_msg_and_state *alexmos);
uint8_t alex_mos_pack_cmd_control(uint8_t *msg, cmd_out_control_type *ctrl);
uint8_t alex_mos_process_char(uint8_t c,alex_mos_msg_and_state *alexmos);

void alexmos_main_processing(void);
void alex_mos_insert_crc(uint8_t *msg);
//void send_control_msg_to_alexmos_if_its_need(uint8_t,cmd_out_control_type*,joystick_t *);
void send_realtime_data_request_to_alexmos_if_its_need(uint8_t ch);
void send_debug_vars_3_request_to_alexmos_if_its_need(uint8_t ch);


uint8_t alex_mos_pack_cmd_board_info   (uint8_t * msg);
uint8_t alex_mos_pack_cmd_board_info_3 (uint8_t * msg);
uint8_t alex_mos_pack_cmd_read_params						(uint8_t * msg);//- request parameters from the board
uint8_t alex_mos_pack_cmd_read_params_3					(uint8_t * msg);//– request parameters from the board
uint8_t alex_mos_pack_cmd_read_params_ext				(uint8_t * msg);//– request extended parameters from the board
uint8_t alex_mos_pack_cmd_write_params						(uint8_t * msg);//- write parameters to board and saves to EEPROM
uint8_t alex_mos_pack_cmd_write_params_3					(uint8_t * msg);//- write parameters to board and saves to EEPROM
uint8_t alex_mos_pack_cmd_write_params_ext				(uint8_t * msg);//– write extended parameters
uint8_t alex_mos_pack_cmd_realtime_data		 			(uint8_t * msg);//- request real-time data, response is CMD_REALTIME_DATA_3
uint8_t alex_mos_pack_cmd_realtime_data_3 				(uint8_t * msg);//- request real-time data, response is CMD_REALTIME_DATA_3
uint8_t alex_mos_pack_cmd_realtime_data_4 				(uint8_t * msg);//– request extended real-time data, response is CMD_REALTIME_DATA_4
uint8_t alex_mos_pack_cmd_reset									(uint8_t * msg);//– reset device
uint8_t alex_mos_pack_cmd_boot_mode_3						(uint8_t * msg);//– enter bootloader mode to upload firmware
uint8_t alex_mos_pack_cmd_script_debug						(uint8_t * msg);
uint8_t alex_mos_pack_cmd_ahrs_helper						(uint8_t * msg , uint8_t mode,uint8_t*gravity_vector,uint8_t*heading_vector);	
//– use provided attitude instead of estimated attitude from main IMU sensor
uint8_t alex_mos_pack_cmd_calb_acc								(uint8_t * msg);	//– calibrate accelerometer
uint8_t alex_mos_pack_cmd_calb_gyro							(uint8_t * msg);	//– calibrate gyroscope
uint8_t alex_mos_pack_cmd_calib_ext_gain					(uint8_t * msg);	//– calibrate EXT_FC gains
uint8_t alex_mos_pack_cmd_calib_use_defaults			(uint8_t * msg);	//– reset to factory defaults
uint8_t alex_mos_pack_cmd_calib_poles						(uint8_t * msg);	//– calibrate poles and direction
uint8_t alex_mos_pack_cmd_calib_offset						(uint8_t * msg);	//– calibrate follow offset
uint8_t alex_mos_pack_cmd_calib_bat							(uint8_t * msg);	//- calibrate battery (voltage sensor)
uint8_t alex_mos_pack_cmd_calib_mag							(uint8_t * msg);	//– run magnetometer calibration

uint8_t alex_mos_pack_cmd_trigger_pin						(uint8_t * msg);	//- trigger output pin
uint8_t alex_mos_pack_cmd_motors_on							(uint8_t * msg);	//- switch motors ON
uint8_t alex_mos_pack_cmd_motors_off							(uint8_t * msg);	//- switch motors OFF
uint8_t alex_mos_pack_cmd_execute_menu						(uint8_t * msg);	//- execute menu command
uint8_t alex_mos_pack_cmd_helper_data						(uint8_t * msg);	//– pass helper data
uint8_t alex_mos_pack_cmd_get_angles 						(uint8_t * msg);	//- Request information about angles and RC control state
uint8_t alex_mos_pack_cmd_select_imu_3						(uint8_t * msg);	//– Select which IMU to configure
uint8_t alex_mos_pack_cmd_read_profile_names_3		(uint8_t * msg);	//– Request profile names stored in EEPROM
uint8_t alex_mos_pack_cmd_write_profile_names_3	(uint8_t * msg);	//– Writes profile names to EEPROM
uint8_t alex_mos_pack_cmd_get_params_3 					(uint8_t * msg);	//– Request information about configurable parameters: type, range, current value
uint8_t alex_mos_pack_cmd_set_adj_vars 					(uint8_t * msg);	//– Change the value of selected parameter(s)
uint8_t alex_mos_pack_cmd_save_params_3					(uint8_t * msg);	//– Saves current params from volatile memory to EEPROM, to the active profile slot.
uint8_t alex_mos_pack_cmd_auto_pid								(uint8_t * msg);	//– Starts automatic PID calibration
uint8_t alex_mos_pack_cmd_servo_out							(uint8_t * msg);	//– Output PWM signal on the specified pins
uint8_t alex_mos_pack_cmd_i2c_write_reg_buf			(uint8_t * msg);	//– writes data to any device connected to I2C line
uint8_t alex_mos_pack_cmd_i2c_read_reg_buf				(uint8_t * msg);	//– requests reading from any device connected to I2C line
uint8_t alex_mos_pack_cmd_debug_vars_info_3			(uint8_t * msg);	//– request information about debug variables
uint8_t alex_mos_pack_cmd_debug_vars_3						(uint8_t * msg);	//– request values of debug variables
uint8_t alex_mos_pack_cmd_write_extern_data_3		(uint8_t * msg);	//– stores any user data to the dedicated area in the EEPROM
uint8_t alex_mos_pack_cmd_read_extern_data_3			(uint8_t * msg);	//– request user data, stored in the EEPROM
uint8_t alex_mos_pack_cmd_api_virt_ch_control		(uint8_t * msg);	//– update a state of 32 virtual channels that named “API_VIRT_CHXX” in the GUI
uint8_t alex_mos_pack_cmd_read_adj_vars_cfg			(uint8_t * msg);	//– request configuration of mapping of control inputs to adjustable
uint8_t alex_mos_pack_cmd_write_adj_vars_cfg			(uint8_t * msg);	//– writes configuration of mapping of control inputs to adjustable variables
uint8_t alex_mos_pack_cmd_eeprom_write						(uint8_t * msg);	//– writes a block of data to EEPROM to specified address
uint8_t alex_mos_pack_cmd_eeprom_read						(uint8_t * msg);	//– request a reading of block of data from EEPROM at the specified address and size.
uint8_t alex_mos_pack_cmd_read_file							(uint8_t * msg);	//– read file from internal filesystem
uint8_t alex_mos_pack_cmd_write_file							(uint8_t * msg);	//– write file to internal filesystem
uint8_t alex_mos_pack_cmd_fs_clear_all						(uint8_t * msg);	//– delete all files from internal filesystem
uint8_t alex_mos_pack_cmd_run_script							(uint8_t * msg);	//– start or stop user-written script


#endif


