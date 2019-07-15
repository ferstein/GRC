#include "analogjoystick.h"
#include "SimpleGPIO.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
int Inited = 0;
AnalogJoystick::AnalogJoystick()
{
     Init();
}
AnalogJoystick::~AnalogJoystick()
{

}

void AnalogJoystick::Init()
{
    printf("Start of Joystick Init ");
    for(int i=0;i<6;i++)
    {
        State.FilterKoef[i]=80;
        State.center[i]=2048;
        State.deadZone[i]=8;
        State.rawFiltred[i]=2048;
        State.Out[i]=0;
        State.volume[i] = 100;
        State.offset[i] = 0;
        State.rev[i]=1;
        for(int k=0;k<10;k++) {State.raw[i][k]=2048;}
        State.rmsRaw[i]=2048;

        Yw= 3;//RIGHT X
        Pt= 4;//RIGHT Y
        FS= 5;//RIGHT Z
        Rl= 0;//LEFT X
        Zm= 1;//LEFT Y
        FP= 2;//LEFT Z

    }

    State.rawIndex=0;
    CalibrateZeros();
    Inited=0xffff;

}

void AnalogJoystick::Process(void)
{   if(Inited){
    ReadRaw();
    ApplyValueAndOffset();
    }
    else{
        Init();
    }
}
void AnalogJoystick::CalibrateZeros()
{
    printf("Start of Joystick  calibration \n");
    int i,j;
    for(i=0;i<1000;i++)
    {
        ReadRaw();
        for(j=0;j<6;j++)
        {
            State.Out[j]=0;
            State.center[j] = (State.center[j]*0.8f + State.rawFiltred[j]*0.2f);
            printf("Calibration %i : %.2f \n",j,State.center[j]);
        }
    }
printf("Calibration of Joystick finished \n");
}
void AnalogJoystick::ReadRaw()
{
    State.raw[0][State.rawIndex]=analog_read(AIN5);//LEFT X
    State.raw[1][State.rawIndex]=analog_read(AIN4);//LEFT Y
    State.raw[2][State.rawIndex]=analog_read(AIN3);//LEFT Z
    State.raw[3][State.rawIndex]=analog_read(AIN0);//RIGHT X
    State.raw[4][State.rawIndex]=analog_read(AIN2);//RIGHT Y
    State.raw[5][State.rawIndex]=analog_read(AIN1);//RIGHT Z
    State.rawIndex++;
    if(State.rawIndex>=10){
        State.rawIndex=0;

        for(int i=0;i<6;i++)
        {
            State.rmsRaw[i]=0;
            for(int j = 0;j<10;j++)
            {
                State.rmsRaw[i] += (State.raw[i][j] *  State.raw[i][j]);
            }
            State.rmsRaw[i]/=10;
            State.rmsRaw[i]=sqrt(State.rmsRaw[i]);

            State.rawFiltred[i]=(State.rawFiltred[i]*State.FilterKoef[i]);
            State.rawFiltred[i]+=State.rmsRaw[i]*(float)(100-State.FilterKoef[i]);
            State.rawFiltred[i]/=100.0f;
        }
    }
}
void AnalogJoystick::ApplyValueAndOffset()
{
    int i;
    float v;
    for(i=0;i<6;i++)
    {
        v=State.rawFiltred[i]-State.center[i];
        //deadZones
        if(fabs(v)<State.deadZone[i])State.Out[i]=0;
        else{
            if(v>0 && v>State.deadZone[i]){
                State.Out[i]=v-State.deadZone[i];}
            if(v<0 && -v>State.deadZone[i]){
                State.Out[i]=v+State.deadZone[i];
            }
        }
        // Volume
        State.Out[i]= (State.Out[i]*State.volume[i])/100;
        // Reverses
        if(State.rev[i])State.Out[i]*=-1;
        // Offsets
        //State.Out[i]+=State.offset[i];

        //printf("Joystick channel %i: raw %i,  Center %i, Volume %i \n",i,State.raw[i],State.center[i],State.volume[i]);
    }
}
