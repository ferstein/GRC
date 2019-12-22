#ifndef ER8300_H
#define ER8300_H
#include <stdint.h>
#include "libvisca.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Generic{
    On = 0x02,
    Off= 0x03,
}Generic_t;


typedef struct CameraContext {
    Generic_t  Power;
    uint16_t Zoom;
    uint8_t  DZoomMode;
    uint8_t  DzoomOnOffClear;
    uint8_t  DZoom;
    uint8_t  FocusMode;
    uint16_t Focus;
    uint8_t  AFMode;
    uint8_t  AFSensitivity;
    uint8_t  FocusSpotMode;
    uint8_t  FocusSpotXposition;
    uint8_t  FocusSpotYposition;
    uint8_t  IRCorrection;
    uint8_t  WBmode;
    uint8_t  GainRed;
    uint8_t  GainBlue;
    uint8_t  AutoExposureMode;
    uint8_t  LowLightBasisBrightness;
    uint8_t  LowLightBasisBrightnessOnOff;
    uint8_t  Shutter;
    uint8_t  ShutterLimitMax;
    uint8_t  ShutterLimitMin;
    uint8_t  SlowShutterOnOff;
    uint8_t  SlowShutterLimit;
    uint8_t  Iris;
    uint8_t  Gain;
    uint8_t  Bright;
    uint8_t  ExposureCompensationOnOff;
    uint8_t  ExposureCompensation;
    uint8_t  ExposureCompensationExtended;//Must be enabled from register 0x5F bit 0
    uint8_t  BackLightCompensationOnOff;
    uint8_t  AutoExposureSpotXposition;
    uint8_t  AutoExposureSpotYposition;
    uint8_t  AutoExposureResponse;
    struct VisibilityEnhancer{//(CAM_VE)
        uint8_t  Mode;
        uint8_t  Brightness;
        uint8_t  BrightnessComp;
        uint8_t  BrightnessCompLevel;
    };
    uint8_t  DefogOnOff;
    struct  Aperture{
        uint8_t Level;
        uint8_t LevelExtended;//Must be enabled from register 0x5F bit 1
        uint8_t Mode;
        uint8_t BandWidth;
        uint8_t Crispening;
        uint8_t HVbalance;
        uint8_t BWbalance;
        uint8_t Limit;
        uint8_t HighLightDetail;
        uint8_t SuperLow;

    };
    uint8_t  HiResolutionOnOff;
    struct NoiseRedution{
        uint8_t  Level;
        uint8_t  Level2D;
        uint8_t  Level3D;
    };
    struct Gamma{
        uint8_t  Mode;
        uint16_t Pattern;
        int8_t   Offset;
    };
    Generic_t HighSensitivity;
    struct Picture{
        Generic_t LR_Reverse;
        Generic_t Freeze;
        Generic_t PictureFlip;
        uint8_t   BlackAndWgite;
    };
    struct ICR{//IR Cut-Filter
        Generic_t ICROnOff;
        Generic_t AutoICROnOff;
        Generic_t AlarmReply;
        uint8_t ExtendedONtoOfftreshold;//Must be enabled from register 0x5F bit 3
        uint8_t ExtendedOnLevel;//Must be enabled from register 0x5F bit 3
    };
    uint8_t Memory;//TODO: 16 presets of camera parameters, this place must be edited
    Generic_t Display;
    VISCATitleData_t MultiLineTitle;
    Generic_t Mute;
    uint16_t CamId;
    //CAM_PrivacyZone
    //CAM_MD (Motion detection
    struct ContinuousZoomPosReply{
        Generic_t OnOff;
        uint8_t IntervalTime;
    };
    struct ContinuousFocusPosReply{
        Generic_t OnOff;
        uint8_t IntervalTime;
    };
    uint8_t RegistersValue[12];
    struct ColorEnhance{
        uint8_t ThresholdLevel;
        uint8_t YfixedColorHighIntensity;
        uint8_t YfixedColorLowIntensity;
        Generic_t OnOff;
    };
    uint8_t ChromaSuppress;
    uint8_t ColorGain;
    uint8_t ColorHue;
    uint8_t ColorGainExtended;//Must be enabled from register 0x5F bit 2
    uint8_t ColorHueExtended; //Must be enabled from register 0x5F bit 2
    struct HLC{
        bool OnOff;
        bool Mask;
    };
    uint8_t ColorBar;
    struct ElectronicPanTilt{
        Generic_t OnOff;
        uint16_t PanPosition;  //in 6 pixels resolution
        uint16_t TiltPosition; //in 4.5 pixels resolution
    };



}CameraContext_t;

class er8300
{
public:
    er8300();
    CameraContext_t CameraContext;

private:
    struct ColorBarTable{
        const unsigned char Value[0x04]=
        {0x00,0x01,0x02,0x03,};
        const char Readable[0x04][16]=
        {"Off","On 8 colors","On 7 colors","On Gray scale"};

        struct ColorGainTable{
            const unsigned char Value[0x0f]=
            {0x00,0x01,0x02,0x03,0x04,0x05,0x06,
             0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e};
            const char Readable[0x0f][6]=
            {"60 %","70 %","80 %","90 %","100%","110%","120%",
             "130%","140%","150%","160%","170%","180%","190%","200%"};
        };

        struct ColorHueTable{
            const unsigned char Value[0x0f]=
            {0x00,0x01,0x02,0x03,0x04,0x05,0x06,
             0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e};
            const char Readable[0x0f][7]=
            {"-14deg","-12deg","-10deg","-8 deg","-6 deg","-4 deg","-2 deg",
             " 0 deg"," 2 deg"," 4 deg"," 6 deg"," 8 deg","10 deg","12 deg","14 deg"};
        };

        const char ShutterSpeed59_94Table[22][8]={
            "1/1    ","1/2    ","1/4    ","1/8    ","1/15   ","1/30   ","1/60   ",
            "1/90   ","1/100  ","1/125  ","1/180  ","1/250  ","1/350  ","1/500  ",
            "1/725  ","1/1000 ","1/1500 ","1/2000 ","1/3000 ","1/4000 ","1/6000 ",
            "1/10000"};

        const char ShutterSpeed_50Table[22][8]={
            "1/1    ","1/2    ","1/3    ","1/6    ","1/12   ","1/25   ","1/50   ",
            "1/75   ","1/100  ","1/120  ","1/150  ","1/215  ","1/300  ","1/425  ",
            "1/600  ","1/1000 ","1/1250 ","1/1750 ","1/2500 ","1/3500 ","1/6000 ",
            "1/10000"};

        const char IrisTable [18][6]={
            "CLOSE","F22","F20","F18","F16","F14","F11","F9.6","F8",
            "F6.8","F5.6","F4.8","F4","F3.4","F2.8","F2.4","F2","F1.8"};

        const char GainTable[17][6]={
            //0D to 10 can be set only when the high-sensitivity mode is ON.
            "     ",
            "0  dB","3  dB","6  dB","9  dB","12 dB","15 dB","18 dB","21 dB",
            "24 dB","27 dB","30 dB","33 dB","36 dB","39 dB","42 dB","45 dB",};

        struct GainLimitTables{
            const unsigned char Value[9]=
            {0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x04,};
            const char HS_Off[9][6]=
            {"33 dB","30 dB","27 dB","24 dB","21 dB","18 dB","15 dB","12 dB","9  dB"};
            const char HS_On[9][6]=
            {"45 dB","42 dB","39 dB","36 dB","33 dB","30 dB","27 dB","24 dB","21 dB"};
        };
        struct BrightTable{
            //1D to 20 can be set only when the high-sensitivity mode is ON.
            const unsigned char Value[29]={
                0x20,0x1F,0x1E,0x1D,0x1C,0x1B,0x1A,0x19,0x18,0x17,
                0x16,0x15,0x14,0x13,0x12,0x11,0x10,0x0F,0x0E,0x0D,
                0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x00      };
            const char Iris[29][6]={
                "F1.8","F1.8","F1.8","F1.8","F1.8","F1.8","F1.8","F1.8","F1.8","F1.8",
                "F1.8","F1.8","F1.8","F1.8","F1.8","F1.8","F2  ","F2.4","F2.8","F3.4",
                "F4  ","F4.8","F5.6","F6.8","F8  ","F9.6","F11 ","F14 ","CLOSE"      };
            const char Gain[29][6]={
                "45 dB","42 dB","39 dB","36 dB","33 dB","30 dB","27 dB","24 dB","21 dB","18 dB",
                "15 dB","12 dB","9 dB ","6 dB ","3 dB ","0 dB ","0 dB ","0 dB ","0 dB ","0 dB ",
                "0 dB ","0 dB ","0 dB ","0 dB ","0 dB ","0 dB ","0 dB ","0 dB ","0 dB ",};
        };

        struct ExposureCompensationTable{
            const unsigned char Value[15]={
                0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00};
            const char ReadableValue[15][5]={
                "+7","+6","+5","+4","+3","+2","+1","0 ","−1","−2","−3","−4","−5","−6","−7"};
            const char Gain[15][11]={
                "+10.5 dB","+9 dB   ","+7.5 dB ","+6 dB   ","+4.5 dB ","+3 dB   ","+1.5 dB ",
                "0 dB    ","−1.5 dB ","−3 dB   ","−4.5 dB ","−6 dB   ","−7.5 dB ","−9 dB   ",
                "-10.5 dB" };
        };

        const uint16_t OpticalZoomTable [12]={
            /* 1× */0x0000,/* 2× */0x1970,/* 3× */0x249C,/* 4× */0x2B5F,
            /* 5× */0x3020,/* 6× */0x33C4,/* 7× */0x36B7,/* 8× */0x392F,
            /* 9× */0x3B4D,/* 10×*/0x3D1E,/* 11×*/0x3EAD,/* 12× */0x4000};

        const uint16_t DigitalZoomCombineModeTable [12]={
            /* 1× */0x4000,/* 2× */0x6000,/* 3× */0x6A80,/* 4× */0x7000,
            /* 5× */0x7300,/* 6× */0x7540,/* 7× */0x76C0,/* 8× */0x7800,
            /* 9× */0x78C0,/* 10×*/0x7980,/* 11×*/0x7A00,/* 12×*/0x7AC0};

        const uint8_t DigitalZoomSeparateModeTable [12]={
            /*1× */0x00,/*2× */0x80,/*3× */0xAA,/*4× */0xC0,/*5× */0xCC,
            /*6× */0xD5,/*7× */0xDB,/*8× */0xE0,/*9× */0xE3,/*10×*/0xE6,
            /*11×*/0xE8,/*12×*/0xEB                                    };

        struct GenericStateTable{
            const uint8_t Value[3]={0x00,0x02,0x03};
            const char ModeReadable[3][8]={
                "Stop","On","Off"};
        };

        struct ApertureModeTable{
            const uint8_t Value[2]={0x00,0x01};
            const char ModeReadable[2][8]={
                "Auto","Manual"};
        };

        struct ApertureBandWidthTable{
            const uint8_t Value[5]={0x00,0x01,0x02,0x03,0x04,};
            const char ModeReadable[5][16]={
                "Default        ",
                "Low bandwidth  ",
                "Mid bandwidth  ",
                "Wide bandwidth ",
                "Broad bandwidth",};
        };

        struct NoiseRedutionTable{
            const uint8_t Value[7]={0x00,0x01,0x02,0x03,0x04,0x05,0x07};
            const char ModeReadable[7][16]={
                "Off",
                "Level 1",
                "Level 2",
                "Level 3",
                "Level 4",
                "Level 5",
                "Manual 2D/3D"};
        };
        struct GammaSettingTable{
            const uint8_t Value[7]={0x00,0x01,0x02};
            const char ModeReadable[7][16]={
                "Standard","Straight","Pattern"};
        };

        struct DZoomModeTable{
            const uint8_t Value[2]={0x00,0x01};
            const char ModeReadable[2][10]={"Combine","Saeparate"};
        };

        struct FocusModeTable{
            const uint8_t Value[3]={0x02,0x03};
            const char ModeReadable[3][12]={
                "Auto","Manual"};
        };

        struct AutoFocusModeTable{
            const uint8_t Value[3]={0x00,0x01,0x02};
            const char ModeReadable[3][16]={
                "Normal AF","Interval AF","Zoom Trigger AF"};
        };
        struct AFSensitivityTable{
            const uint8_t Value[2]={0x02,0x03};
            const char ModeReadable[2][16]={
                "Normal","Low"};
        };

        struct IRCorrectionTable{
            const uint8_t Value[2]={0x00,0x01};
            const char ModeReadable[2][16]={
                "Standard","IR Light"};
        };

        struct WBmodeTable{
            const uint8_t Value[12]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
            const char ModeReadable[10][20]={
                "Auto               ",
                "Indoor             ",
                "Outdoor            ",
                "One Push           ",
                "Auto Trace         ",
                "Manual             ",
                "Outdoor            ",
                "Sodium Lamp Auto   ",
                "Sodium Lamp fixed  ",
                "Sodium Lamp Outdoor",
            };
        };

        struct AutoExposureModeTable{
            const uint8_t Value[12]={0x00,0x03,0x0A,0x0B,0x0D};
            const char ModeReadable[5][20]={
                "Auto            ",
                "Manual          ",
                "Shutter Priority",
                "Iris Priority   ",
                "Bright          ",
            };
        };


        struct FocusNearLimitTable{
            const uint16_t Value[14]={
                0x1000,0x2000,0x3000,0x4000,0x5000,0x6000,0x7000,
                0x8000,0x9000,0xA000,0xB000,0xC000,0xD000,0xE000,      };
            const char DistanceReadable[14][9]={ //30 cm is initial setting
                                                 "Over Inf","10 m    ","5 m     ","3.3 m   ","2.5 m   ",
                                                 "2 m     ","1.7 m   ","1.5 m   ","1 m     ","50 cm   ",
                                                 "30 cm   ","15 cm   ","6 cm    ","1 cm    "            };
            const float Distance[14]={
                1e12f,10.0f,5.0f,3.3f,2.5f,2.0f,1.7f,1.5f,1.0f,0.5f,
                0.3f,0.15f,0.06f,0.01f                                 };
        };

        struct WideTeleLimitTable{
            const uint8_t Value[17]={
                0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
                0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xFF         };
            const uint16_t ZoomPositionWideLimit[17]={
                0x0000,0x01EE,0x03DD,0x05CC,0x07BB,0x09A9,0x0B98,0x0D87,
                0x0F76,0x1165,0x1353,0x1542,0x1731,0x1920,0x1B0F,0x1CFD,
                0x1ECD                                                 };
            const float ZoomRatioWideLimit[17]={
                1.00f,1.05f,1.09f,1.15f,1.20f,1.26f,1.33f,1.40f,1.48f,
                1.56f,1.65f,1.75f,1.86f,1.98f,2.11f,2.26f,2.41f        };
            const uint16_t ZoomPositionTeleLimit[17]={
                0x4000,0x3E11,0x3C22,0x3A33,0x3844,0x3656,0x3467,0x3278,
                0x3089,0x2E9A,0x2CAC,0x2ABD,0x28CE,0x26DF,0x24F0,0x2302,
                0x2132                                                 };
            const float ZoomRatioTeleLimit[17]={
                12.00f,10.59f,9.440f,8.460f,7.610f,6.860f,6.200f,5.620f,
                5.100f,4.650f,4.240f,3.890f,3.570f,3.290f,3.040f,2.820f,
                2.630f                                                 };
        };

        struct TemperatureConvertionTable{
            const uint8_t Value[8]={0xFB,0x00,0x0A,0x14,0x1E,0x28,0x32,0x3C,};
            const int8_t MinTemperature[8]={-8,-3, 7,17,27,37,47,57};
            const int8_t MaxTemperature[8]={-2, 3,13,23,33,43,53,63};
        };

        typedef const struct RegisterSettings{
            uint8_t InitialSettings;
            uint8_t RegisterNum;
            char RegisterName[32];
            uint8_t NumPossibleValues;
            uint8_t PossibleValues[20];
            char ValuesDescription[20][120];
        }Registercontent_t;

        Registercontent_t RegSettings[12]=
        {
            {//0
             .InitialSettings=0x00,
             .RegisterNum=0x00,
             {"Camera BaudRate"},
             .NumPossibleValues=5,
             .PossibleValues={0x00,0x01,0x02,0x03,0x04},
             .ValuesDescription={"9600 bps","19200 bps ","38400 bps ","57600 bps ","115200 bps",},},
            {//1
             .InitialSettings=0x00,
             .RegisterNum=0x60,
             "Digital Output",
             .NumPossibleValues=2,
             .PossibleValues={0x00,0x01},
             .ValuesDescription={"YUV","RGB"},},
            {//2
             .InitialSettings=0x1D,
             .RegisterNum=0x72,
             "Monitoring Mode",
             .NumPossibleValues=12,
             .PossibleValues={0x1D,0x1E,0x13,0x14,0x01,0x04,0x06,0x08,0x09,0x0C,0x0E,0x11},
             .ValuesDescription={
                 "System:QFHD (3840 × 2160)29.97p\nOutput: 3840 × 2160 29.97p\n1920 × 1080 59.94p\nWhen electronic pan/tilt is ON.",
                 "System:QFHD (3840 × 2160)25p   \nOutput: 3840 × 2160 25p   \n1920 × 1080 50p   \nWhen electronic pan/tilt is ON.",
                 "System: FHD (1920 × 1080)59.94p\nOutput: 1920 × 1080 59.94p",
                 "System: FHD (1920 × 1080)50p\nOutput: 1920 × 1080 50p",
                 "System: FHD (1920 × 1080)59.94i\nOutput: 1920 × 1080 59.94i",
                 "System: FHD (1920 × 1080)50i   \nOutput: 1920 × 1080 50i",
                 "System: FHD (1920 × 1080)29.97p\nOutput: 1920 × 1080 59.94p",
                 "System: FHD (1920 × 1080)25p   \nOutput: 1920 × 1080 50p",
                 "System:  HD (1280 × 720)59.94p \nOutput: 1280 × 720 59.94p",
                 "System:  HD (1280 × 720)50p    \nOutput: 1280 × 720 50p",
                 "System:  HD (1280 × 720)29.97p \nOutput: 1280 × 720 59.94p",
                 "System:  HD (1280 × 720) 25p   \nOutput: 1280 × 720 50p",     },},
            {//3
             .InitialSettings=0x00,
             .RegisterNum=0x75,
             "Low Delay Mode",
             .NumPossibleValues=2,
             .PossibleValues={0x00,0x01},
             .ValuesDescription={"Normal Mode","Low Delay Mode"},},
            {//4
             .InitialSettings=0x00,
             .RegisterNum=0x50,
             "Zoom Limit Wide",
             .NumPossibleValues=255,
             .PossibleValues={0x00,0x00,0x00,0x00,0x00,0x00},
             .ValuesDescription={"Wide Limit 0 - Disabled, 0xff(dec255) - maximum limit)"},},
            {//5
             .InitialSettings=0x00,
             .RegisterNum=0x51,
             "Zoom Limit Tele",
             .NumPossibleValues=255,
             .PossibleValues={0x00,0x00,0x00,0x00,0x00,0x00},
             .ValuesDescription={"Tele Limit 0 - Disabled, 0xff(dec255) - maximum limit)"},},
            {//6
             .InitialSettings=0xEB,
             .RegisterNum=0x52,
             "Digital Zoom Max",
             .NumPossibleValues=0xEB,
             .PossibleValues={0x00,0x00,0x00,0x00,0x00,0x00},
             .ValuesDescription={"Max. digital zoom ratio = 256 ÷ (256-Value)"},},
            {//7
             .InitialSettings=0x00,
             .RegisterNum=0x53,
             "StableZoom",
             .NumPossibleValues=0x2,
             .PossibleValues={0x00,0x01,0x00},
             .ValuesDescription={"StableZoom Off","StableZoom On"},},
            {//8
             .InitialSettings=0x01,
             .RegisterNum=0x54,
             "FocusTrace@ZoomDirect",
             .NumPossibleValues=0x2,
             .PossibleValues={0x00,0x01,0x00},
             .ValuesDescription={"FocusTrace@ZoomDirect Off","FocusTrace@ZoomDirect On"},},
            {//9
             .InitialSettings=0x00,
             .RegisterNum=0x55,
             "FocusOffset@DomeCover",
             .NumPossibleValues=0xFF,
             .PossibleValues={0x00,0x00,0x00,0x00,0x00,0x00},
             .ValuesDescription={"FocusOffset@DomeCover 0 - Off, 0xff(dec255) - Max"},},
            {//10
             .InitialSettings=0x00,
             .RegisterNum=0x5F,
             "Extended Mode (bitmask)",
             .NumPossibleValues=0x0F,
             .PossibleValues={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F},
             .ValuesDescription={
                 "All extended functions is Off",                                                       //0
                 "Exposure compensation Extended 256 levels On",                                        //1
                 "Aperture Extended 256 levels On",                                                     //2
                 "Exposure compensation Extended 256 levels On\nAperture Extended 256 levels On",       //3
                 "Color Gain/Hue Extended 256 levels On",                                               //4
                 "Color Gain/Hue Extended 256 levels On,\nExposure compensation Extended 256 levels On",//5
                 "Color Gain/Hue Extended 256 levels On,\nAperture Extended 256 levels On",             //6
                 "Color Gain/Hue Extended 256 levels On,\nAperture Extended 256 levels On,\nExposure compensation Extended 256 levels On",//7
                 "Auto ICR Off setting enable On/Off",                                              //8
                 "Auto ICR Off setting enable On/Off,\nExposure compensation Extended 256 levels On",//9
                 "Auto ICR Off setting enable On/Off,\nAperture Extended 256 levels On",             //10 = 8+2
                 "Auto ICR Off setting enable On/Off,\nAperture Extended 256 levels On,\nExposure compensation Extended 256 levels On",//11 = 8+2+1
                 "Auto ICR Off setting enable On/Off,\nColor Gain/Hue Extended 256 levels On",       //12=8+4
                 "Auto ICR Off setting enable On/Off,\nColor Gain/Hue Extended 256 levels On,\nExposure compensation Extended 256 levels On",//13=8+4+1
                 "Auto ICR Off setting enable On/Off,\nColor Gain/Hue Extended 256 levels On,\nAperture Extended 256 levels On",//14=8+4+2
                 "Auto ICR Off On/Off,\nColor Gain/Hue Extended On,\nAperture Extended On,\nExposure compensation Extended  On",//15=8+4+2+1
             },},
        };

        struct ValueLimits {
            const uint8_t AFActiveTimeMin = 0x00;
            const uint8_t AFActiveTimeMax = 0xFF;
            const uint8_t AFIntervalTimeMin = 0x00;
            const uint8_t AFIntervalTimeMax = 0xFF;

            const uint8_t SpotFocus_X_positionMin = 0x00;
            const uint8_t SpotFocus_X_positionMax = 0x0F;
            const uint8_t SpotFocus_Y_positionMin = 0x00;
            const uint8_t SpotFocus_Y_positionMax = 0x0F;

            const uint8_t SpotAE_X_positionMin = 0x00;
            const uint8_t SpotAE_X_positionMax = 0x0F;
            const uint8_t SpotAE_Y_positionMin = 0x00;
            const uint8_t SpotAE_Y_positionMax = 0x0F;



            const uint8_t RGainMin = 0x00;
            const uint8_t RGainMax = 0xFF;
            const uint8_t BGainMin = 0x00;
            const uint8_t BGainMax = 0xFF;

            const uint8_t VisibilityEnhancerBrightnessMin=0;
            const uint8_t VisibilityEnhancerBrightnessMax=0x06;
            const uint8_t VisibilityEnhancerBrightnessCompMin=0;
            const uint8_t VisibilityEnhancerBrightnessCompMax=0x03;
            const uint8_t VisibilityEnhancerBrightnessCompLevelMin=0;
            const uint8_t VisibilityEnhancerBrightnessCompLevelMax=0x02;

            const uint8_t ApertureControlLevelMin = 0x00;
            const uint8_t ApertureControlLevelMax = 0x0F;
            const uint8_t ApertureCrispeningMin = 0x00;
            const uint8_t ApertureCrispeningMax = 0x07;
            const uint8_t ApertureHVbalanceMin = 0x05;
            const uint8_t ApertureHVbalanceMax = 0x09;
            const uint8_t ApertureBWbalanceMin = 0x00;
            const uint8_t ApertureBWbalanceMax = 0x04;
            const uint8_t ApertureLimitMax = 0x00;
            const uint8_t ApertureLimitMin = 0x07;
            const uint8_t ApertureHighLightDetailMin = 0x00;
            const uint8_t ApertureHighLightDetailMax = 0x04;
            const uint8_t ApertureSuperLowMin = 0x00;
            const uint8_t ApertureSuperLowMax = 0x07;

            const uint8_t NoiseRedution2DlevelMin = 0x00;
            const uint8_t NoiseRedution2DlevelMax = 0x05;
            const uint8_t NoiseRedution3DlevelMin = 0x00;
            const uint8_t NoiseRedution3DlevelMax = 0x05;

            const uint8_t AutoExposureResponseMin = 0x01;
            const uint8_t AutoExposureResponseMax = 0x30;

            const uint16_t GammaPatternMin = 0x001;
            const uint16_t GammaPatternMax = 0x200;
            const int8_t  GammaOffsetMin = -0x40;
            const int8_t  GammaOffsetMax =  0x40;


            const uint8_t AutoICROnOffThresholdLevelMin = 0x00;
            const uint8_t AutoICROnOffThresholdLevelMax = 0xFF;
            const uint8_t MDThresholdLevelMin = 0x00;
            const uint8_t MDThresholdLevelMax = 0xFF;
            const uint8_t MDIntervalTimeMin   = 0x00;
            const uint8_t MDIntervalTimeMax   = 0xFF;
            const uint8_t MDSetHorizontalPositionMin = 0x00;
            const uint8_t MDSetHorizontalPositionMax = 0x10;
            const uint8_t MDSetVerticalPositionMin = 0x00;
            const uint8_t MDSetVerticalPositionMax = 0x08;
            const uint8_t ChromaSuppressSettingLevelMin = 0x00;
            const uint8_t ChromaSuppressSettingLevelMax = 0x03;
            const uint8_t ColorGainSettingLevelMin = 0x00;
            const uint8_t ColorGainSettingLevelMax = 0x0E;
            const uint8_t ColorHueSettingLevelMin = 0x00;
            const uint8_t ColorHueSettingLevelMax = 0x0E;
            const uint8_t ColorEnhancementThresholdLevelMin = 0x00;
            const uint8_t ColorEnhancementThresholdLevelMax = 0x7F;
            const uint8_t ColorEnhancement_Y_fixedColorMin = 0x00;
            const uint8_t ColorEnhancement_Y_fixedColorMax = 0x7F;
        };
    };
};


#ifdef __cplusplus
} /* closing brace for extern "C" */

#endif

#endif // ER8300_H


