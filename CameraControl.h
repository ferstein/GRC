#ifndef CAMERA_H
#define CAMERA_H
#include "serialport.h"
#include "er8300.h"
#include <stdint.h>
class CameraControl
{
public:
    CameraControl();
    ~CameraControl();
    unsigned int CamCtrlEnabled;
    int ZoomJoy;
    int FocusPosJoy;
    int FocusSpeedJoy;
    float ZoomMagnification; //from camera

    void process(void);
    er8300 *fcber8300;
//    VISCACamera_t CamS0; //Used for GUI commands
    int  CbCommadSemndWrespond( VISCACamera_t * Cam);
private:

    serialport serial;
  //  int fd;

    enum {SendCommands=1,WaitAckAndComplition,MuteHighPriorityCommands,Idle}ProSt;
    int Csocket; //Sockets and errors containers
    char buf[64];
    bool isOnline;
    long long int RespondTimeShtamp;
//    VISCACamera_t CamS1;  //This is one camera, CamS1 same CamS2 but different sockets for advanced VISCA routing and speed
    VISCAPacket_t visca_paket;
    //visca_parser_state_t  viscaParser;

    void Init(void);
    void ZoomSpeedPackAndSend( VISCACamera_t *);
    void FocusPackAndSend( VISCACamera_t * Cam);
    void VprintError (int err,long long int time);


};

#endif // CAMERA_H
