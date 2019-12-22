#include "CameraControl.h"
#include "serialport.h"
#include "ConsoleEscSequ.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <chrono>
#include <cinttypes>
using namespace std;
using namespace std::chrono;

CameraControl::CameraControl()
{
    fcber8300=new er8300;
    printf ("Opening camera control serial port! \n");
    fcber8300->Camera.fd=serial.init("/dev/ttyO4",Baud115200);
    if(fcber8300->Camera.fd>0){
        printf("Camera serial opened ...initialization %i \n",fcber8300->Camera.fd);

        CamCtrlEnabled=1;
        ProSt=SendCommands;
        isOnline = false;
        RespondTimeShtamp=0;
    }
    else{

        perror("Camera serial error :");
        exit (EXIT_FAILURE);
    }

}
CameraControl::~CameraControl()
{
    close(fcber8300->Camera.fd);
    delete fcber8300;
}

void CameraControl::Init(void)
{

}

void CameraControl::ZoomSpeedPackAndSend( VISCACamera_t * Cam){
    int r;
    int ZoomSpeed = static_cast<int>(fabs(ZoomJoy/40));
    if(ZoomSpeed>7)ZoomSpeed=7;
    Cam->value=static_cast<int16_t>(ZoomSpeed);
    if(ZoomJoy>1) {Cam->command=ZoomTeleSpeed;
    }
    else{
        if(ZoomJoy<-1){Cam->command=ZoomWideSpeed;
        }
        else {Cam->command=ZoomStop;
        }
    }
    fcber8300->CommandPack(&visca_paket,Cam);
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    Cam->TimeSend = ms.count();
    r=write(Cam->fd,&visca_paket.bytes,visca_paket.length);
    if(r<0)printf("\033[0;31m %lli:Zoom send error ! %i\033[0m\n",Cam->TimeSend ,r);
}

void CameraControl::FocusPackAndSend( VISCACamera_t * Cam){
    static volatile int FocusPosManualMode=0;
    static volatile int FocusPosEx=0;
    int r;
    if(fcber8300->Context.FocusMode == fcber8300->FocusModeTable.Value[1]){//if focus is in manual mode
        FocusPosManualMode+=FocusSpeedJoy/20;
        FocusPosEx= FocusPosManualMode+FocusPosJoy*4;

        if(FocusPosManualMode<0x1000)FocusPosManualMode=0x1000;
        if(FocusPosManualMode>0xE000)FocusPosManualMode=0xE000;

        if(FocusPosEx<0x1000)FocusPosEx=0x1000;
        if(FocusPosEx>0xE000)FocusPosEx=0xE000;
        Cam->command=FocusDirect;
        Cam->value = static_cast<int16_t>(FocusPosEx);
        fcber8300->CommandPack(&visca_paket,Cam);
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        Cam->TimeSend = ms.count();
        r = write(Cam->fd,&visca_paket.bytes,visca_paket.length);
        if(r<0)printf("\033[0;31m %lli:Focus send error ! %i\033[0m\n",Cam->TimeSend,r);
    }
}
int CameraControl::CbCommadSemndWrespond( VISCACamera_t * Cam){
    int r = 0,len=0;
    if(!isOnline)return -2;
    if(Cam == nullptr)return -3;
    if(Cam->command == 0)return -4;
    unsigned char cbuf[64];

    ProSt = MuteHighPriorityCommands;

    r = fcber8300->CommandPack(&visca_paket,Cam);
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    Cam->TimeSend = ms.count();
    while(Cam->TimeSend < ms.count()-50);
    len = read(Cam->fd,&cbuf,63);
    ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    r = write(Cam->fd,&visca_paket.bytes,visca_paket.length);
    while(Cam->TimeSend < ms.count()-300){
        len = read(Cam->fd,&cbuf,63);
        if(len > 0 ){
            //TODO: parse buf
        }
    }

    if(r<0) printf("\033[0;31m %lli:Camera command send error ! %i\033[0m\n",Cam->TimeSend,r);
    ProSt = SendCommands;
    return r;
}

void CameraControl::process(void)
{
    static volatile long long int IdleTimeStamp = 0;
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    switch(ProSt){
    case SendCommands:
    {
        if(CamCtrlEnabled!=0){
            ZoomSpeedPackAndSend(&fcber8300->Camera);
            FocusPackAndSend(&fcber8300->Camera);//printf("\033[0;35m%lli:Camera write event \033[0m\n",CamS1.TimeSend);
        }
        ProSt=WaitAckAndComplition;
    }break;
    case WaitAckAndComplition:
    {
        int len = read(fcber8300->Camera.fd,&buf,30);
        if(len>0)
        {// printf("\033[0;32m%lli:Camera read %i bytes\033[0m\n",ms.count(),len);
            isOnline=true;
            RespondTimeShtamp=ms.count();
            //TODO: PARSER MUST BE Here for Zoom and Focus position parsing
            ProSt=SendCommands;
        }
        else
        {// printf("\033[0;31m%lli :Camera read empty or error %i \033[0m\n",ms.count(),len);
            if(RespondTimeShtamp < ms.count()-4000)
            {
                isOnline=false;
                printf("\033[0;31m %lli:Camera not respond ! \033[0m\n",ms.count());
                ProSt=SendCommands;
            }
            if(fcber8300->Camera.TimeSend < ms.count()-41)
            {
                ProSt=SendCommands;
            }
        }
    }break;
    case MuteHighPriorityCommands:
    {
        if(IdleTimeStamp == 0)
        {
            IdleTimeStamp = ms.count();
            printf("\033[0;35m%lli:CAMERA HIGH PRIORITY COMMAND MUTEX MODE ACTIVATED! \033[0m\r\n",IdleTimeStamp);
        }
        else if(IdleTimeStamp < ms.count()-3000)
        {
            printf("\033[0;35m%lli:CAMERA TIMEOUT OF MUTEX MODE NOW IS NORMAL MODE!\033[0m\r\n",IdleTimeStamp);
            IdleTimeStamp=0;
            ProSt=SendCommands;
        }
    }break;
    default:
    {
        ProSt=SendCommands;
    }break;
    }

    //ViscaParseBuf ((uint8_t*)buf,len ,&viscaParser,&CamS1);
    //ZoomMagnification=( ZoomMagnification*0.8 ) + (0.2* fcber8300->ZoomPositionToMagnification(CamS1.ZoomPosition));

}

void CameraControl::VprintError (int err,long long int time) {
    printf(COLOR_TEXT_RED);
    switch(buf[2]){
    case 1:   printf("%lld:VISCA Message length error %i \n",time,err);break;
    case 2:   printf("%lld:VISCA Syntax Error %i \n",time,err);break;
    case 3:   printf("%lld:VISCA Command buffer full %i \n",time,err);break;
    case 4:   printf("%lld:VISCA Command cancelled %i \n",time,err);break;
    case 5:   printf("%lld:VISCA No socket %i \n",time,err);break;
    case 0x41:printf("%lld:VISCA No socketCommand not executable %i \n",time,err);break;
    default:  printf("%lld:Zoom VISCA Unknown error %i \n",time,err);break;
    }
    printf(COLOR_RESET);
}

