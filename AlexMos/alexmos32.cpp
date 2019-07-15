#include "stdint.h"
#include <string.h>
#include "alexmos32.h"

// оманды , которые можно определить в виде строковых констант , то есть команды без дополнительных параметров , или с 
//параметрами которые можно перечислить или продублировать , короче которые строго определены и нет необходимости пересчитывать 
//контрольные суммы , отправл€ютс€ через указатель
// Ќулевой лемент буффера содержит количество байт дл€ передачи всего сообщени€ ,
//сам  при том не передаетс€ 
/*    0                                                                       */
//first byte(index = 0) - this string length not include him to the message
/*      1          2            3              4               5          6    */
//start - 0x3e//cmd id//body data size//header checksum//body data//bodychecksum//
const uint8_t const_cmd_board_info[]		 ={6,START,CMD_BOARD_INFO,1,CMD_BOARD_INFO+1,0,0};									//Ц request board and firmware information
const uint8_t const_cmd_board_info3[]		 ={6,START,CMD_BOARD_INFO_3,1,CMD_BOARD_INFO_3+1,0,0};							//- request additional board information
const uint8_t const_cmd_real_time_data[]	 ={6,START,CMD_REALTIME_DATA,1,CMD_REALTIME_DATA+1,0,0};
const uint8_t const_cmd_real_time_data_3[]	 ={6,START,CMD_REALTIME_DATA_3,1,CMD_REALTIME_DATA_3+1,0,0};
const uint8_t const_cmd_real_time_data_4[]	 ={6,START,CMD_REALTIME_DATA_4,1,CMD_REALTIME_DATA_4+1,0,0};
const uint8_t const_cmd_read_profile_names[] ={6,START,CMD_READ_PROFILE_NAMES,1,CMD_READ_PROFILE_NAMES+1,0,0};
const uint8_t const_cmd_read_i2c_reg_buf[]	 ={6,START,CMD_I2C_READ_REG_BUF,1,CMD_I2C_READ_REG_BUF+1,0,0};
const uint8_t const_cmd_read_external_data[] ={6,START,CMD_READ_EXTERNAL_DATA,1,CMD_READ_EXTERNAL_DATA+1,0,0};
const uint8_t const_cmd_calib_ext_gain[]	 ={6,START,CMD_CALIB_EXT_GAIN,1,CMD_CALIB_EXT_GAIN+1,0,0};
const uint8_t const_cmd_calib_poles[]		 ={6,START,CMD_CALIB_POLES,1,CMD_CALIB_POLES+1,0,0};
const uint8_t const_cmd_calib_offset[]		 ={6,START,CMD_CALIB_OFFSET,1,CMD_CALIB_OFFSET+1,0,0};
const uint8_t const_cmd_motors_on[]			 ={6,START,CMD_MOTORS_ON,1,CMD_MOTORS_ON+1,0,0};
const uint8_t const_cmd_calib_mag[]			 ={6,START,CMD_CALIB_MAG,1,CMD_CALIB_MAG+1,0,0};
const uint8_t const_cmd_motors_off[]		 ={6,START,CMD_MOTORS_OFF,1,CMD_MOTORS_OFF+1,0,0};
const uint8_t const_cmd_save_params[]		 ={6,START,CMD_SAVE_PARAMS_3,1,CMD_SAVE_PARAMS_3+1,0,0};
const uint8_t const_cmd_debug_vars_info_3[]	 ={6,START,CMD_DEBUG_VARS_INFO_3,1,CMD_DEBUG_VARS_INFO_3+1,0,0};
const uint8_t const_cmd_debug_vars_3[]		 ={6,START,CMD_DEBUG_VARS_3 ,1,CMD_DEBUG_VARS_3+1,0,0};
const uint8_t const_cmd_read_adj_vars_cfg[]  ={6,START,CMD_READ_ADJ_VARS_CFG,1,CMD_READ_ADJ_VARS_CFG+1,0,0 };
const uint8_t const_cmd_read_params[]		 ={6,START,CMD_READ_PARAMS    ,0x01,CMD_READ_PARAMS    +0x01,0x00,0x00};
const uint8_t const_cmd_read_params_3[]		 ={6,START,CMD_READ_PARAMS_3  ,0x01,CMD_READ_PARAMS_3  +0x01,0x00,0x00};
const uint8_t const_cmd_read_params_ext[]    ={6,START,CMD_READ_PARAMS_EXT,0x01,CMD_READ_PARAMS_EXT+0x01,0x00,0x00};
const uint8_t const_cmd_board_info_ext[]     ={7 ,START,CMD_BOARD_INFO,2,CHSUM,0x00,0x00,0x00};
const uint8_t const_cmd_calib_acc[]			 ={17,START,CMD_CALIB_ACC ,0x0c,CHSUM,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,CHSUM};
const uint8_t const_cmd_calib_gyro[]         ={17,START,CMD_CALIB_GYRO,0x0c,CHSUM,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,CHSUM};
const uint8_t const_cmd_use_defaults[]       ={6 ,START,CMD_USE_DEFAULTS,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_write_params[]       ={6 ,START,CMD_WRITE_PARAMS    ,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_write_params_3[]     ={6 ,START,CMD_WRITE_PARAMS_3  ,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_write_params_ext[]   ={6 ,START,CMD_WRITE_PARAMS_EXT,0x01,CHSUM,0x00,CHSUM};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const uint8_t const_cmd_reset[]				 ={  8 ,START,CMD_RESET,3};
const uint8_t const_cmd_boot_mode_3[]		 ={  8 ,START,CMD_BOOT_MODE_3,3};
const uint8_t const_cmd_calib_bat[]          ={  7 ,START,CMD_WRITE_PARAMS_EXT,0x02};
const uint8_t const_cmd_control[]         	 ={ 18 ,START,CMD_CONTROL,13};
const uint8_t const_cmd_trigger_pin[]        ={  7 ,START,CMD_TRIGGER_PIN,2};
const uint8_t const_cmd_execute_menu[]   	 ={  6 ,START,CMD_EXECUTE_MENU,1};
const uint8_t const_cmd_helper_data[]      	 ={ 15 ,START,CMD_HELPER_DATA,10};
const uint8_t const_cmd_get_angles[]		 ={  6 ,START,CMD_GET_ANGLES,1};
const uint8_t const_cmd_select_imu[]		 ={  6 ,START,CMD_SELECT_IMU_3,1};
const uint8_t const_cmd_write_profile_names[]={245 ,START,CMD_HELPER_DATA,240};
const uint8_t const_cmd_set_adj_vars[] 		 ={ 16 ,START,CMD_SET_ADJ_VARS,11};
const uint8_t const_cmd_auto_pid[]		     ={ 24 ,START,CMD_AUTO_PID,19};
const uint8_t const_cmd_servo_out[]			 ={ 21 ,START,CMD_SERVO_OUT,16};
const uint8_t const_cmd_i2c_write_reg_buf[]	 ={ 0  ,START,CMD_I2C_WRITE_REG_BUF,4 }; //¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_i2c_read_reg_buf[]	 ={ 0  ,START,CMD_I2C_READ_REG_BUF ,4 }; //¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_write_external_data[]={ 132,START,CMD_WRITE_EXTERNAL_DATA,128};
const uint8_t const_cmd_api_virt_ch_control[]={ 71 ,START,CMD_API_VIRT_CH_CONTROL,64 };
const uint8_t const_cmd_write_vars_cfg[]	 ={ 93 ,START,CMD_WRITE_ADJ_VARS_CFG,88};
const uint8_t const_cmd_eeprom_write[]		 ={  4 ,START,CMD_EEPROM_WRITE,0};//¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_eeprom_read[]		 ={  4 ,START,CMD_EEPROM_READ,0}; //¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_ahrs_helper[]		 ={ 30 ,START,CMD_AHRS_HELPER,25};

//‘унции копировани€ строчных констант в строчную переменнную , вставки параметров  и  контрольных сум.
uint8_t alex_mos_pack_cmd_board_info(uint8_t * msg)
{
    memcpy(msg ,&const_cmd_board_info[1],const_cmd_board_info[0]);
    return (const_cmd_board_info[0]);
}
uint8_t alex_mos_pack_cmd_board_info_3(uint8_t * msg)
{
    memcpy(msg ,&const_cmd_board_info3[1],const_cmd_board_info3[0]);
    return (const_cmd_board_info3[0]);
}
uint8_t alex_mos_pack_cmd_realtime_data(uint8_t * msg)
//- request real-time data, response is CMD_REALTIME_DATA_3
{
    memcpy(msg ,&const_cmd_real_time_data[1],const_cmd_real_time_data[0]);
    return (const_cmd_real_time_data[0]);
}
uint8_t alex_mos_pack_cmd_realtime_data_3(uint8_t * msg)
//- request real-time data, response is CMD_REALTIME_DATA_3
{
    memcpy(msg ,&const_cmd_real_time_data_3[1],const_cmd_real_time_data_3[0]);
    return (const_cmd_real_time_data_3[0]);
}
uint8_t alex_mos_pack_cmd_realtime_data_4(uint8_t * msg)
//Ц request extended real-time data, response is CMD_REALTIME_DATA_4
{
    memcpy(msg ,&const_cmd_real_time_data_4[1],const_cmd_real_time_data_4[0]);
    return (const_cmd_real_time_data_4[0]);
}
uint8_t alex_mos_pack_cmd_read_params(uint8_t * msg )//- request parameters from the board
{
    memcpy(msg ,&const_cmd_read_params[1],const_cmd_read_params[0]);
    return (const_cmd_read_params[0]);
}
uint8_t alex_mos_pack_cmd_read_params_3(uint8_t * msg)//Ц request parameters from the board
{
    memcpy(msg ,&const_cmd_read_params_3[1],const_cmd_read_params_3[0]);
    return (const_cmd_read_params_3[0]);
}
uint8_t alex_mos_pack_cmd_read_params_ext(uint8_t * msg)//Ц request extended parameters from the board
{
    memcpy(msg ,&const_cmd_read_params_ext[1],const_cmd_read_params_ext[0]);
    return (const_cmd_read_params_ext[0]);
}
uint8_t alex_mos_pack_cmd_write_params(uint8_t * msg)//- write parameters to board and saves to EEPROM
{
    memcpy(msg ,&const_cmd_write_params[1],const_cmd_write_params[0]);
    return (const_cmd_write_params[0]);
}
uint8_t alex_mos_pack_cmd_write_params_3(uint8_t * msg)//- write parameters to board and saves to EEPROM
{
    memcpy(msg ,&const_cmd_write_params_3[1],const_cmd_write_params_3[0]);
    return(const_cmd_write_params_3[0]);
}
uint8_t alex_mos_pack_cmd_write_params_ext(uint8_t * msg)//Ц write extended parameters
{
    memcpy(msg ,&const_cmd_write_params_ext[1],const_cmd_write_params_ext[0]);
    return(const_cmd_write_params_ext[0]);
}
uint8_t alex_mos_pack_cmd_reset(uint8_t * msg)//Ц reset device
{
    memcpy(msg ,&const_cmd_reset[1],const_cmd_reset[0]);
    return(const_cmd_reset[0]);
}
uint8_t alex_mos_pack_cmd_boot_mode_3(uint8_t * msg)//Ц enter bootloader mode to upload firmware
{
    memcpy(msg ,&const_cmd_boot_mode_3[1],const_cmd_boot_mode_3[0]);
    return(const_cmd_boot_mode_3[0]);
}
//Ц control alex_mos_pack movement
uint8_t alex_mos_pack_cmd_control(uint8_t *msg, cmd_out_control_type *ctrl)
{
    //const uint8_t const_cmd_control[]         	  ={ 18 ,START,CMD_CONTROL,13};
    memcpy(msg,&const_cmd_control[1],3);
    memcpy(msg+4,ctrl,const_cmd_control[3]);
    alex_mos_insert_crc(msg);
    return(const_cmd_control[0]);
}	
/*
uint8_t alex_mos_pack_cmd_calib_ext_gain					(uint8_t * msg);	//Ц calibrate EXT_FC gains
uint8_t alex_mos_pack_cmd_calib_use_defaults			(uint8_t * msg);	//Ц reset to factory defaults
uint8_t alex_mos_pack_cmd_calib_poles						(uint8_t * msg);	//Ц calibrate poles and direction
uint8_t alex_mos_pack_cmd_calib_offset						(uint8_t * msg);	//Ц calibrate follow offset
uint8_t alex_mos_pack_cmd_calib_bat							(uint8_t * msg);	//- calibrate battery (voltage sensor)
uint8_t alex_mos_pack_cmd_calib_mag							(uint8_t * msg);	//Ц run magnetometer calibration

uint8_t alex_mos_pack_cmd_trigger_pin						(uint8_t * msg);	//- trigger output pin
uint8_t alex_mos_pack_cmd_motors_on							(uint8_t * msg);	//- switch motors ON
uint8_t alex_mos_pack_cmd_motors_off							(uint8_t * msg);	//- switch motors OFF
uint8_t alex_mos_pack_cmd_execute_menu						(uint8_t * msg);	//- execute menu command
uint8_t alex_mos_pack_cmd_helper_data						(uint8_t * msg);	//Ц pass helper data
uint8_t alex_mos_pack_cmd_get_angles 						(uint8_t * msg);	//- Request information about angles and RC control state
uint8_t alex_mos_pack_cmd_select_imu_3						(uint8_t * msg);	//Ц Select which IMU to configure
uint8_t alex_mos_pack_cmd_read_profile_names_3		(uint8_t * msg);	//Ц Request profile names stored in EEPROM
uint8_t alex_mos_pack_cmd_write_profile_names_3	(uint8_t * msg);	//Ц Writes profile names to EEPROM
uint8_t alex_mos_pack_cmd_get_params_3 					(uint8_t * msg);	//Ц Request information about configurable parameters: type, range, current value
uint8_t alex_mos_pack_cmd_set_adj_vars 					(uint8_t * msg);	//Ц Change the value of selected parameter(s)
uint8_t alex_mos_pack_cmd_save_params_3					(uint8_t * msg);	//Ц Saves current params from volatile memory to EEPROM, to the active profile slot.
uint8_t alex_mos_pack_cmd_auto_pid								(uint8_t * msg);	//Ц Starts automatic PID calibration
uint8_t alex_mos_pack_cmd_servo_out							(uint8_t * msg);	//Ц Output PWM signal on the specified pins
uint8_t alex_mos_pack_cmd_i2c_write_reg_buf			(uint8_t * msg);	//Ц writes data to any device connected to I2C line
uint8_t alex_mos_pack_cmd_i2c_read_reg_buf				(uint8_t * msg);	//Ц requests reading from any device connected to I2C line
uint8_t alex_mos_pack_cmd_debug_vars_info_3			(uint8_t * msg);	//Ц request information about debug variables
uint8_t alex_mos_pack_cmd_debug_vars_3						(uint8_t * msg);	//Ц request values of debug variables
uint8_t alex_mos_pack_cmd_write_extern_data_3		(uint8_t * msg);	//Ц stores any user data to the dedicated area in the EEPROM
uint8_t alex_mos_pack_cmd_read_extern_data_3			(uint8_t * msg);	//Ц request user data, stored in the EEPROM
uint8_t alex_mos_pack_cmd_api_virt_ch_control		(uint8_t * msg);	//Ц update a state of 32 virtual channels that named УAPI_VIRT_CHXXФ in the GUI
uint8_t alex_mos_pack_cmd_read_adj_vars_cfg			(uint8_t * msg);	//Ц request configuration of mapping of control inputs to adjustable
uint8_t alex_mos_pack_cmd_write_adj_vars_cfg			(uint8_t * msg);	//Ц writes configuration of mapping of control inputs to adjustable variables
uint8_t alex_mos_pack_cmd_eeprom_write						(uint8_t * msg);	//Ц writes a block of data to EEPROM to specified address
uint8_t alex_mos_pack_cmd_eeprom_read						(uint8_t * msg);	//Ц request a reading of block of data from EEPROM at the specified address and size.
uint8_t alex_mos_pack_cmd_read_file							(uint8_t * msg);	//Ц read file from internal filesystem
uint8_t alex_mos_pack_cmd_write_file							(uint8_t * msg);	//Ц write file to internal filesystem
uint8_t alex_mos_pack_cmd_fs_clear_all						(uint8_t * msg);	//Ц delete all files from internal filesystem
uint8_t alex_mos_pack_cmd_run_script							(uint8_t * msg);	//Ц start or stop user-written script
*/
enum {STATE_WAIT, STATE_GOT_MARKER, STATE_GOT_ID, STATE_GOT_LEN, STATE_GOT_HEADER, STATE_GOT_DATA } state;

// Debug variable names (use for findig needed variable and position of 
// this variable debus vars struct )

const char rms_err_r[] ={0x09,'R','M','S','_','E','R','R','_','R'};
const char rms_err_p[] ={0x09,'R','M','S','_','E','R','R','_','P'};
const char rms_err_y[] ={0x09,'R','M','S','_','E','R','R','_','Y'};
const char freq_r[]    ={0x06,'F','R','E','Q','_','R'};
const char freq_p[]    ={0x06,'F','R','E','Q','_','P'};
const char freq_y[]    ={0x06,'F','R','E','Q','_','Y'};
const char enc_raw_r[] ={0x09,'E','N','C','_','R','A','W','_','R'};
const char enc_raw_p[] ={0x09,'E','N','C','_','R','A','W','_','P'};
const char enc_raw_y[] ={0x09,'E','N','C','_','R','A','W','_','Y'};
const char imu_temp[]  ={0x08,'I','M','U','_','T','E','M','P'};
const char f_imu_temp[]={0x0A,'F','_','I','M','U','_','T','E','M','P'};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ѕарсинг сообщений
uint8_t alex_mos_process_char(uint8_t c, alex_mos_msg_and_state *alexmos) {
    switch(alexmos->parsing_step)
    {
    case STATE_WAIT:
        if(c == START)
        {
            alexmos->start= c;
            alexmos->parsing_step = STATE_GOT_MARKER;
        }
        else
        {
            //onParseError();
        }
        break;
    case STATE_GOT_MARKER:
        alexmos->command_id = c;
        alexmos->parsing_step = STATE_GOT_ID;
        break;
    case STATE_GOT_ID:
        alexmos->data_size = c;
        alexmos->parsing_step = STATE_GOT_LEN;
        break;
    case STATE_GOT_LEN:
        alexmos->header_cheksum = alexmos->command_id + alexmos->data_size;
        if (c == alexmos->header_cheksum
                && alexmos->data_size <= 250) // checksum and size ok
        {

            if(alexmos->data_size== 0)
            {
                alexmos->parsing_step = STATE_GOT_DATA;
            }
            else
            {
                alexmos->parsing_step = STATE_GOT_HEADER;
                alexmos->uint8_ptr  = (uint8_t*)&alexmos->msg_union;
            }
        }
        else
        {
            alexmos->onParseError++;
            alexmos->parsing_step = STATE_WAIT;
        }
        alexmos->body_cheksum = 0;
        break;
    case STATE_GOT_HEADER:
        if(alexmos->data_size == 0)
        {
            alexmos->parsing_step = STATE_GOT_DATA;
            break;
        }
        if((alexmos->uint8_ptr - (uint8_t*)&alexmos->msg_union)>250)
        {
            alexmos->parsing_step = STATE_WAIT;
            alexmos->onParseError++;
            break;
        }
        *alexmos->uint8_ptr = c;
        alexmos->uint8_ptr ++;
        alexmos->body_cheksum += c;
        if(alexmos->data_size ==
                (alexmos->uint8_ptr - (uint8_t*)&alexmos->msg_union))
            alexmos->parsing_step = STATE_GOT_DATA;
        break;
    case STATE_GOT_DATA:
        alexmos->parsing_step = STATE_WAIT;
        if(c == alexmos->body_cheksum) // checksum ok
        {
            return 1;
        }
        else
        {
            alexmos->onParseError++;
        }
        break;
    default :
        alexmos->parsing_step = STATE_WAIT;
        break;
    }
    return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t sort_alex_mos_message(uint8_t *ch ,uint16_t count,alex_mos_msg_and_state *alexmos)
{
 //   uint8_t i,j,k,n,typ;
    uint16_t symbols;
    uint8_t * c_ptr_src, *c_ptr_dst;
    for(symbols=0;symbols< count;symbols++)
    {
        if(alex_mos_process_char(ch[symbols],alexmos))
        {
            switch (alexmos->command_id)
            {
            case CMD_BOARD_INFO :
            {
                break;
            }
            case CMD_BOARD_INFO_3 :
            {
                break;
            }
            case CMD_READ_PARAMS :
            {
                break;
            }
            case CMD_READ_PARAMS_EXT :
            {
                break;
            }
            case CMD_REALTIME_DATA_3 :
            {
                break;
            }
            case CMD_REALTIME_DATA_4 :
            {/*
                gimbal.cam_angle_roll  = alexmos->msg_union.real_time_data_4.FRAME_CAM_ANGLE_ROLL  * ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit;
                gimbal.cam_angle_pitch = alexmos->msg_union.real_time_data_4.FRAME_CAM_ANGLE_PITCH * ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit;
                gimbal.cam_angle_yaw   = alexmos->msg_union.real_time_data_4.FRAME_CAM_ANGLE_YAW   * ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit;

                gimbal.angle_yaw   =  alexmos->msg_union.real_time_data_4.ANGLE_YAW;
                gimbal.angle_pitch =  alexmos->msg_union.real_time_data_4.ANGLE_PITCH;
                gimbal.angle_roll  =  alexmos->msg_union.real_time_data_4.ANGLE_ROLL;
                */
                break;
            }
            case CMD_CONFIRM :
            {
                break;
            }
            case CMD_ERROR :

                break;

            case CMD_GET_ANGLES :
            {
                break;
            }
            case CMD_READ_PROFILE_NAMES :
            {
                break;
            }
            case CMD_I2C_READ_REG_BUF :
            {
                break;
            }
            case CMD_AUTO_PID :
            {
                break;
            }
                /*______________________________________________________________________*/
            case CMD_DEBUG_VARS_INFO_3 :

            {
                /*// decoding to alexmos_debug_vars struct
                if(alexmos->msg_union.debug_vars_info_3.debug_vars_num > 20)
                    alexmos->msg_union.debug_vars_info_3.debug_vars_num=20;
                alexmos_debug_vars.vars_count =
                        alexmos->msg_union.debug_vars_info_3.debug_vars_num;
                j=0;k=0;
                for(i=0;i<alexmos_debug_vars.vars_count;i++)
                {
                    n=0;
                    while(n <= alexmos->msg_union.debug_vars_info_3.debug_vars[j])
                    {//Copy current variable name while copy index < lenthf  of var name
                        alexmos_debug_vars.var[i].name[n]
                                = alexmos->msg_union.debug_vars_info_3.debug_vars[k];
                        k++;n++;
                    }
                    //copy type
                    alexmos_debug_vars.var[i].type
                            = alexmos->msg_union.debug_vars_info_3.debug_vars[k];
                    k += 3;
                    j=k;
                }

                alexmos->enc_pitch_dvar_no = find_debug_var_number ((uint8_t *) enc_raw_p);
                alexmos->enc_roll_dvar_no  = find_debug_var_number ((uint8_t *) enc_raw_r);
                alexmos->enc_yaw_dvar_no   = find_debug_var_number ((uint8_t *) enc_raw_y);
                */
                break;
            }
                /*______________________________________________________________________*/
            case CMD_DEBUG_VARS_3 :
            {
                /*
                c_ptr_src = alexmos->msg_union.debug_vars_3;
                for (i=0;i<alexmos_debug_vars.vars_count;i++)
                {
                    typ = alexmos_debug_vars.var[i].type &~ 0xf0;
                    switch(typ)
                    {
                    case VAR_TYPE_UINT8 :
                    case VAR_TYPE_INT8 :
                        alexmos_debug_vars.var[i].value = (uint8_t)*c_ptr_src;
                        c_ptr_src++;
                        break;
                    case VAR_TYPE_UINT16 :
                    case VAR_TYPE_INT16 :
                        alexmos_debug_vars.var[i].value = 0;
                        c_ptr_dst = (uint8_t *)&alexmos_debug_vars.var[i].value;
                        *c_ptr_dst = *c_ptr_src;
                        c_ptr_dst++;
                        c_ptr_src++;
                        *c_ptr_dst = *c_ptr_src;
                        c_ptr_src++;
                        break;
                    case VAR_TYPE_UINT32 :
                    case VAR_TYPE_INT32 :
                    case VAR_TYPE_FLOAT :
                        alexmos_debug_vars.var[i].value = 0;
                        c_ptr_dst = (uint8_t *)&alexmos_debug_vars.var[i].value;
                        *c_ptr_dst = *c_ptr_src;
                        c_ptr_dst++;
                        c_ptr_src++;
                        *c_ptr_dst = *c_ptr_src;
                        c_ptr_src++;
                        c_ptr_dst++;
                        *c_ptr_dst = *c_ptr_src;
                        c_ptr_dst++;
                        c_ptr_src++;
                        *c_ptr_dst = *c_ptr_src;
                        c_ptr_src++;
                        break;


                    }
                }

                if(gimbal.enc_roll_dvar_no  < 20)
                gimbal.enc_roll = alexmos_debug_vars.var[gimbal.enc_roll_dvar_no].value  &~ 0xC000;
                gimbal.enc_roll = 0;
                if(gimbal.enc_pitch_dvar_no < 20)
                    gimbal.enc_pitch = alexmos_debug_vars.var[gimbal.enc_pitch_dvar_no].value;// &~ 0xC000 ;
                if(gimbal.enc_pitch_dvar_no < 20)
                    gimbal.enc_yaw = alexmos_debug_vars.var[gimbal.enc_yaw_dvar_no].value;// &~ 0xC000 ;

                alexmos_debug_vars.DR = 0xff;
*/
                break;
            }
                //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            case CMD_READ_EXTERNAL_DATA :
            {
                break;
            }
            case CMD_READ_ADJ_VARS_CFG :
            {
                break;
            }
            case CMD_RESET :
            {
                break;
            }
            case CMD_EEPROM_READ :
            {
                break;
            }
            case CMD_READ_FILE :
            {
                break;
            }
            case CMD_SCRIPT_DEBUG :
            {
                break;
            }
            case CMD_AHRS_HELPER :
            {
                break;
            }
            default :
            {

            }
            }
            return(alexmos->command_id);
        }

    }
    return(0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* 
 Function check alexmos_debug_vars struct for equals of debug variables
 and charsters located in memory  position varname
 lengts of data is located in first byte of names in alexmos_debug_vars struct.
 funcion returns variable number of first equals names , and 0xff in struct not
 contain names same with incoming charster set */

uint8_t find_debug_var_number (uint8_t * varname)
{/*
    uint8_t i,j,equals;
    for(i=0; i<alexmos_debug_vars.vars_count ;i++)
    {
        equals=0;
        for(j=1; j <= alexmos_debug_vars.var[i].name[0];j++)
        {
            if(varname[j] == alexmos_debug_vars.var[i].name[j])
            {
                equals++;
            }
            else break;
        }
        if(equals == alexmos_debug_vars.var[i].name[0]) return(i);
    }*/
    return(0xff);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void alexmos_detect_and_init(alex_mos_msg_and_state *alexmos)
{
    /*
    //gimbal.kp_p = parameter_RW[GIMB_PosContYawP].v.float32;
    //gimbal.kp_y = parameter_RW[GIMB_PosContPitP].v.float32;

    uint8_t attempts,speeds;
    if(parameter_RW[SERIAL_1_PROTOCO].v.i8 == SERIAL_PROTOCOL_ALEXMOS) alexmos->serport = 1;
    else if(parameter_RW[SERIAL_2_PROTOCO].v.i8 == SERIAL_PROTOCOL_ALEXMOS) alexmos->serport = 2;
    else if(parameter_RW[SERIAL_3_PROTOCO].v.i8 == SERIAL_PROTOCOL_ALEXMOS) alexmos->serport = 3;
    else if(parameter_RW[SERIAL_4_PROTOCO].v.i8 == SERIAL_PROTOCOL_ALEXMOS) alexmos->serport = 4;
    else if(parameter_RW[SERIAL_5_PROTOCO].v.i8 == SERIAL_PROTOCOL_ALEXMOS) alexmos->serport = 5;
    else
    {
        alexmos->serport = 0;
        alexmos->detected = 0;
        return;
    }

    volatile uint32_t  timer = time_boot + 4000;
    const uint32_t serial_speeds[6]={256000,115200,57600,38400,19200,9600};
    while(timer > time_boot){};
    //Check all avialable speeds of serial serial_port
    for (speeds=0;speeds<6;speeds++)
    {
        while(serial_port[alexmos->serport].tx.bysy)serial_port[alexmos->serport].tx.bysy--;
        SetSerialPortSpeed(alexmos->serport ,serial_speeds[speeds]);
        // 5 attempts with 100 msec waiting for answer
        for(attempts=5;attempts>0;attempts--)
        {
            send_msg_pointer(alexmos->serport,(uint8_t*)&const_cmd_board_info[1],const_cmd_board_info[0]);
            timer = time_boot + 500;
            while(timer > time_boot){};
            {
                get_serial_rx_buffer_state(alexmos->serport);
                if(sort_alex_mos_message(alexmos->serport) && alexmos->command_id==CMD_BOARD_INFO)
                {// Recived correct answer !!!!!!!!!
                    LEDOn(LED7);
                    alexmos->detected = 1;
                    return;
                }
            }
        }
    }
    LEDOff(LED7);
    alexmos->detected = 0;
    */
    alexmos->detected = 0xff;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void alex_mos_get_debug_variables(void)
{
    /*
    uint8_t attempts;
    volatile uint32_t timer;
    for(attempts=0;attempts < 3;attempts++)
    {
        if(send_msg_pointer(alexmos->serport,(uint8_t*)&const_cmd_debug_vars_info_3[1],
                            const_cmd_debug_vars_info_3[0])>=0)
        {
            timer = time_boot + 200;
        }
        while(timer > time_boot);
        get_serial_rx_buffer_state(alexmos->serport);
        if( sort_alex_mos_message(alexmos->serport)&& alexmos->command_id==CMD_DEBUG_VARS_INFO_3)
        {
            attempts=0x10;
            alexmos->detected |= 0x0f;
            break;
        }
    }
    get_serial_rx_buffer_state(alexmos->serport);
    sort_alex_mos_message(alexmos->serport);
    */
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void send_back_recived_msg(void)
{
    /*
    alexmos->total_bytes = alexmos->data_size + 5;
    alex_mos_insert_crc(&alexmos->total_bytes);
    send_msg_pointer(alexmos->serport, &alexmos->total_bytes+1,alexmos->total_bytes);
    */
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void alexmos_main_processing(void)
{

        //send_realtime_data_request_to_alexmos_if_its_need(alexmos->serport);
        //send_debug_vars_3_request_to_alexmos_if_its_need(alexmos->serport);
        //sort_alex_mos_message(alexmos->serport);
        //send_control_msg_to_alexmos_if_its_need(alexmos->serport,&alex_mos_ctrl_msg,&Joystick);

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void send_debug_vars_3_request_to_alexmos_if_its_need(uint8_t ch){
    /*
    static volatile uint32_t dv3timer = 0;
    if(dv3timer <= time_boot)
    {
        if(send_msg_pointer(alexmos->serport, (uint8_t* )&const_cmd_debug_vars_3[1],
                            const_cmd_debug_vars_3[0]) >= 0 )
        {
            dv3timer = time_boot+alex_mos_getting_angles_interval;
        }
    }
    */
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void	send_realtime_data_request_to_alexmos_if_its_need(uint8_t ch)
{
/*
    static volatile uint32_t alex_mos_getting_angles_timer = 0;
    if (alex_mos_getting_angles_timer <= time_boot)
    {
        if(send_msg_pointer(ch, (uint8_t* )&const_cmd_real_time_data_4[1],
                            const_cmd_real_time_data_4[0])>=0)
        {
            alex_mos_getting_angles_timer=time_boot+alex_mos_getting_angles_interval;
        }
    }
*/
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void mode_manual_worker(void)
{
 /*   //if joystick channel defined to gimbal channel then put control signals
    alex_mos_ctrl_msg.CONTROL_MODE = ALEX_MOS_CONTROL_MODE_SPEED;
    if(parameter_RO[GIMB_YAW_RCCH ].v.i8 > 0 && parameter_RO[GIMB_YAW_RCCH ].v.i8 <=8)
        alex_mos_ctrl_msg.SPEED_YAW   = Joystick.ch[parameter_RO[GIMB_YAW_RCCH ].v.i8].out;
    else
        alex_mos_ctrl_msg.SPEED_YAW   = 0;
    if(parameter_RO[GIMB_PITCH_RCCH ].v.i8 > 0 && parameter_RO[GIMB_PITCH_RCCH ].v.i8 <=8)
        alex_mos_ctrl_msg.SPEED_PITCH = Joystick.ch[parameter_RO[GIMB_PITCH_RCCH].v.i8].out;
    else alex_mos_ctrl_msg.SPEED_PITCH = 0;
    if(parameter_RO[GIMB_ROLL_RCCH ].v.i8 > 0 && parameter_RO[GIMB_ROLL_RCCH ].v.i8 <=8)
        alex_mos_ctrl_msg.SPEED_ROLL = Joystick.ch[parameter_RO[GIMB_ROLL_RCCH].v.i8].out;
    else
        alex_mos_ctrl_msg.SPEED_ROLL = 0;
 */
}
void mode_geolck_worker(void)
{
/*    alex_mos_ctrl_msg.CONTROL_MODE = ALEX_MOS_CONTROL_MODE_SPEED;
    if (Joystick.lost == 0)
    {
        geo_manual_calculation (
                    &current_GPS_data.lat, &current_GPS_data.lon,
                    &mount_control.input_a,&mount_control.input_b,
                    Joystick.ch[parameter_RW[GIMB_YAW_RCCH  ].v.i8].owotrim,  // Joystick channels defined as Yaw and Pitch
                -Joystick.ch[parameter_RW[GIMB_PITCH_RCCH].v.i8].owotrim,  // without trimming for drift of geoppoint cancelation
                parameter_RW[GEOLOCK_JOY_KOEF].v.f32);
    }
    //Set lense to needed position referenced as GPS data (WGS86)
    find_needed_gimbal_adj_angle_geo (&current_lense_coordinates,&CurrentAttitude,&gimbal,
                                      &current_GPS_data,&mount_control,&alex_mos_ctrl_msg.SPEED_YAW,&alex_mos_ctrl_msg.SPEED_PITCH);

*/}

void mode_ptz_position_worker(void)
{
    //alex_mos_ctrl_msg.CONTROL_MODE = ALEX_MOS_CONTROL_MODE_SPEED;
    //Set gimbal to NED angles
    //find_needed_gimbal_adj_angle_ptz(&gimbal,&CurrentAttitude,//Current UAV attitude
    //                                 &alex_mos_ctrl_msg.SPEED_YAW, &alex_mos_ctrl_msg.SPEED_PITCH);
}

void mode_ptz_speed_worker(void)
{
    /*
    alex_mos_ctrl_msg.CONTROL_MODE = ALEX_MOS_CONTROL_MODE_SPEED;
    if(ptz_speed.timeout_ms > time_boot)
    {
        alex_mos_ctrl_msg.SPEED_YAW = ptz_speed.yaw_speed*400.0f;
        alex_mos_ctrl_msg.SPEED_PITCH = ptz_speed.pitch_speed*400.0f;
        alex_mos_ctrl_msg.SPEED_ROLL = 0;
    }
    else
    {
        alex_mos_ctrl_msg.SPEED_YAW = 0;
        alex_mos_ctrl_msg.SPEED_PITCH = 0;
        alex_mos_ctrl_msg.SPEED_ROLL = 0;
        //gimbal.mode = MANUAL;
    }
    */
}
void mode_target_lock_worker(void)
{
    /*
    float x,y,mulx=1,muly=1;
    int zr=camEO.ZoomRatio;

    if (gimbal.ActiveCamNO == LWIR)
    {
        zr= camLWIR.ZoomRatio;
        mulx=parameter_RW[TRK_LWIR_X_MULTP].v.f32;
        muly=parameter_RW[TRK_LWIR_Y_MULTP].v.f32;
    }

    alex_mos_ctrl_msg.CONTROL_MODE = ALEX_MOS_CONTROL_MODE_SPEED;
    if(target_lock_calculator(zr,&x,&y) >= 0)
    {
        if(parameter_RW[TRK_REVERSE_OUTX].v.u8 !=0){ x *=-1;}
        if(parameter_RW[TRK_REVERSE_OUTY].v.u8 !=0){ y *=-1;}

        alex_mos_ctrl_msg.SPEED_YAW   = x*mulx;
        alex_mos_ctrl_msg.SPEED_PITCH = y*muly;

    }
    else{
        alex_mos_ctrl_msg.SPEED_YAW   = 0;
        alex_mos_ctrl_msg.SPEED_PITCH = 0;
        gimbal.mode = MANUAL;
        stop_target_tracking();
    }
    alex_mos_ctrl_msg.SPEED_ROLL  = 0;
    */

}

void send_control_msg_to_alexmos_if_its_need(uint8_t ch, cmd_out_control_type *ctrl,joystick_t *j )
{
    static volatile uint32_t alex_mos_sending_control_timer =0;
    uint16_t len;

    if (alex_mos_sending_control_timer <= time_boot)
    {
        switch ((uint8_t)gimbal.mode)
        {
        case MANUAL:      mode_manual_worker();break;
        case GEOLOCK:     mode_geolck_worker();break;
        case GOTO_SPEED:   mode_ptz_speed_worker();break;
        case GOTO_POSITION:mode_ptz_position_worker();break;
        case TARGETLOCK: mode_target_lock_worker();break;
        case PARKED:break;
        case POWER_OFF:break;
        case NONE:gimbal.mode=MANUAL;
        default:;
        }
        uint8_t lim = AlexMosTiltLimiter (&alex_mos_ctrl_msg ,&current_lense_coordinates.EncoderAnglePitch);
        if(gimbal.mode == TARGETLOCK && lim !=0)
        {
            alex_mos_ctrl_msg.SPEED_PITCH = 0;
            alex_mos_ctrl_msg.SPEED_YAW = 0;
            stop_target_tracking();
        }
        if (gimbal.mode != POWER_OFF)
        {
            len = alex_mos_pack_cmd_control((uint8_t*)&serial_port[ch].tx.data[0] ,ctrl);
            if(send_msg(ch,len)>=0){
                alex_mos_sending_control_timer =time_boot +  alex_mos_sending_control_interval;
            }
        }
    }
}

uint8_t AlexMosTiltLimiter (cmd_out_control_type *ctrl ,float *current_pitch_encoder_angle)
{
    /*
    static volatile float pita;
    //pita = -(360.0f - *current_pitch_encoder_angle * RADIANS_TO_DEGREES );
    pita = fmod((*current_pitch_encoder_angle * RADIANS_TO_DEGREES),360.0f);
    if(  parameter_RW[GIMB_PITCH_LIM_P].v.f32 != 0
         && pita >= parameter_RW[GIMB_PITCH_LIM_P].v.f32
         && ctrl->SPEED_PITCH <= 0)
    {
        ctrl->SPEED_PITCH = 1;
        return 0x0f;
    }
    if(parameter_RW[GIMB_PITCH_LIM_N].v.f32 !=0
            && pita <= parameter_RW[GIMB_PITCH_LIM_N].v.f32
            && ctrl->SPEED_PITCH >= 0)
    {
        ctrl->SPEED_PITCH = -1;
        return 0xf0;
    }
    */

    return 0;
} 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ‘унц1€ коп1ю3 заголовок пов1домленн€ з *src_sring в *dst_sring , всього коп1ю3тьс€ чотири байти
void copy_message_header(const uint8_t *src_sring, uint8_t *dst_sring)
{
    uint8_t copy_index_i;
    for(copy_index_i=0;copy_index_i<4;copy_index_i++)
    {
        dst_sring[copy_index_i]= src_sring[copy_index_i];
    }
}	

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//‘ункци€ вставл€ет контрольные суммы , в протоколе их две , в нужные места указаного буфера
void alex_mos_insert_crc(uint8_t *msg)
{
    uint16_t i,crc = 0;
    msg[3] =  msg[2]+msg[1];
    for(i=4;i<msg[2]+4;i++) {crc += msg[i];};
    msg[i] = (uint8_t)crc;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++






