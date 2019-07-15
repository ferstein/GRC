#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <QElapsedTimer>
#include <QDebug>
#include "gimbalcontrol.h"
#include "gimbal_defs.h"
#include "serialport.h"

GimbalControl::GimbalControl()
{

    SerialFD = serialport::init("/dev/ttyO2",Baud115200);
    GimbalCtrlEnabled=1;
    ZoomCompensationGain=1.0f;
    ZoomCompensation=1.0f;
}

void GimbalControl::Process(void)
{
    unsigned char buf[20],buf2[40];
    uint8_t len;
    if(GimbalCtrlEnabled!=0){
        len = CmdControlPack(buf);
        write(SerialFD, buf, len);
    }

    len = read(SerialFD,buf2,40);
}

uint8_t GimbalControl::CmdControlPack(uint8_t *msg)
{
    const uint8_t const_cmd_control[]={ 18 ,START,CMD_CONTROL,13};
    memcpy(msg,&const_cmd_control[1],3);
    memcpy(msg+4,&ctrl,const_cmd_control[3]);
    InsertCrc(msg);
    return(const_cmd_control[0]);
}
void GimbalControl::InsertCrc(uint8_t *msg)
{
    uint16_t i,crc = 0;
    msg[3] =  msg[2]+msg[1];
    for(i=4;i<msg[2]+4;i++) {crc += msg[i];};
    msg[i] = (uint8_t)crc;
}
