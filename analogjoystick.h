#ifndef ANALOGJOYSTICK_H
#define ANALOGJOYSTICK_H
#include <stdint.h>
struct JoystickState
{
    uint8_t FilterKoef[8];
    int16_t raw[8][10];
    uint8_t rawIndex;
    double rmsRaw[8];
    float rawFiltred[8];
    float center[8];
    float deadZone[8];
    float Out[8];
    float volume[8];
    uint8_t rev[8];
    float offset[8];

};

class AnalogJoystick
{
public:
    AnalogJoystick();
    ~AnalogJoystick();
    JoystickState State;
    void Init();
    void Process(void);
    void CalibrateZeros();
    int8_t Yw;
    int8_t Pt;
    int8_t Rl;
    int8_t Zm;
    int8_t FS;
    int8_t FP;

private:
    void ReadRaw();
    void ApplyValueAndOffset();
};

#endif // ANALOGJOYSTICK_H
