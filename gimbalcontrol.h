#ifndef GIMBALCONTROL_H
#define GIMBALCONTROL_H
#include <stdint.h>

#define t1u uint8_t
#define t1s int8_t
#define t2u uint16_t
#define t2s int16_t
#define t4f float
#define t4s int32_t
#define t4u uint32_t

#pragma pack(push,1)

enum ControlMode:uint8_t
{
    NO_CONTROL  =0,
    SPEED       =1,
    ANGLE       =2,
    SPEED_ANGLE =3,
    RC          =4,
    ANGLE_REL_FRAME=5,
    RC_HIGH_RES=6,
    HIGH_RES_SPEED=(1<<7)+1,
};

struct controlStruct
//control gimbal movement
{
  ControlMode CONTROL_MODE; //  1u
  t2s SPEED_ROLL; //  2s
  t2s ANGLE_ROLL; //  2s
  t2s SPEED_PITCH; //  2s
  t2s ANGLE_PITCH; //  2s
  t2s SPEED_YAW; //  2s
  t2s ANGLE_YAW; //  2s
};


#pragma pack(pop)

class GimbalControl
{
public:
    unsigned int GimbalCtrlEnabled;
    GimbalControl();
    void Process(void);
    controlStruct ctrl;
    float ZoomCompensation;
    float ZoomCompensationGain;
private:
    void InsertCrc(uint8_t *msg);
    uint8_t CmdControlPack(uint8_t *msg);
    int SerialFD;
};

#endif // GIMBALCONTROL_H
