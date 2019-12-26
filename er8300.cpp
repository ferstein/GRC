#include "er8300.h"
#include <stdio.h>
#include <string.h>
#include "visca_definitions.h"

er8300::er8300()
{
    memset (&Context,0,sizeof (Context));
    memset (&Camera,0, sizeof (Camera));
    memset (&Parser,0, sizeof (Parser));
    memset (&Decoder,0, sizeof(Decoder));
    Camera.camnum=CAM1;
    Parser.ps=WaitHeader;
    Decoder.step = Start;
}

float er8300::ZoomPositionToMagnification(uint32_t position)
{
    int i;
    float opt,dig;

    //if(position==0)return(1);
    if(position<OpticalZoomTable[11]){
        for(i=1;OpticalZoomTable[i]<=position;i++) if(i==12)break;
        opt=i;
        float f = static_cast<float>(position-OpticalZoomTable[i-1]);
        float f1 = static_cast<float>(OpticalZoomTable[i]-OpticalZoomTable[i-1]);
        if(f1>0){opt+=f/f1;}
        dig=1.0f;
    }
    else
    {
        opt=12.0f;
        for(i=1;DigitalZoomCombineModeTable[i]<=position;i++)if(i==12)break;
        dig=i;
        float f = static_cast<float>(position-DigitalZoomCombineModeTable[i-1]);
        float f1 =static_cast<float>(DigitalZoomCombineModeTable[i]-DigitalZoomCombineModeTable[i-1]);
        if(f1>0){dig+=f/f1;}
    }
    return (opt*dig);
}

float er8300::FocusPositionToDistanceAndModeFromContext(char * buf)
{
    int i=1;
    float f;
    char c= 'A';
    const uint16_t FV[14]={0x1000,0x2000,0x3000,0x4000,0x5000,0x6000,0x7000,0x8000,0x9000,0xA000,0xB000,0xC000,0xD000,0xE000};
    const float    FD[14]={40.00f,10.00f,5.000f,3.300f,2.500f,2.000f,1.700f,1.500f,1.000f,0.500f,0.300f,0.150f,0.060f,0.010f};

    if(Context.Focus > FV[13])Context.Focus = FV[13];
    if(Context.Focus < FV[0]) Context.Focus = FV[0];
    while(Context.Focus>=FV[i]){
        i++;
        if (i>=13)break;
    }

    f = FD[i]+ ((FD[i-1]-FD[i]) * (FV[i] - Context.Focus)/(FV[i]-FV[i-1]));

    if(Context.FocusMode == FocusModeTable.Value[1]) c='M';

    if(f>30.00f)sprintf(buf,"F INF %c",c);
    else sprintf(buf,"F%.2f%c",static_cast<double>(f),c);

    return f;
}

//++++++++++++++++++++++ VISCA MEMBERS FOR FCB_ER8300 +++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int er8300::CommandPack(VISCAPacket_t * VISCA_packet , const VISCACamera_t * cam)
{
    if(cam->camnum > BROADCAST || cam->camnum < CAM1)
        return(VISCA_ERROR_CMD_NOT_EXECUTABLE);
    VISCA_commands_t command = cam->command;

    VISCA_packet->length = 0x06;
    VISCA_packet->bytes[0] = VISCA_HEADER+cam->camnum;
    VISCA_packet->bytes[1] = VISCA_COMMAND;
    VISCA_packet->bytes[2] = (command >> 24)&0xff;
    VISCA_packet->bytes[5] = VISCA_TERMINATOR;
    switch(cam->command)
    {
    case AddresSset: // 88 30 01 FF Address setting
        VISCA_packet->length = 0x04;
        VISCA_packet->bytes[0] = VISCA_BROADCAST;
        VISCA_packet->bytes[1] = (command>>16)&0xff;
        VISCA_packet->bytes[2] = cam->camnum;
        VISCA_packet->bytes[3] = VISCA_TERMINATOR;
        break;
    case IfClear   : // 8x 01 00 01 FF , 88 01 00 01 FF I/F Clear
        VISCA_packet->length = 0x05;
        VISCA_packet->bytes[2] = (command>>8)&0xff;
        VISCA_packet->bytes[3] =  command&0xff;
        VISCA_packet->bytes[4] = VISCA_TERMINATOR;
        break;
    case CommandCancel  : // 8x 2p FF p: Socket No. (=1 or 2)
        if(cam->value<1)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->value>2)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x03;
        VISCA_packet->bytes[1] = (0x20 + cam->value)&0xff;
        VISCA_packet->bytes[2] =  VISCA_TERMINATOR;
        break;
        // Commands 6 bytes with arguments
    case ZoomTeleSpeed :    //Tele (Variable) 8x 01 04 07 2p FF p=0 (Low) to 7 (High)
    case ZoomWideSpeed :    //Wide (Variable) 8x 01 04 07 3p FF
    case DzoomTele     :    //Tele (Variable) 8x 01 04 06 2p FF p=0 (Low) to 7 (High)
    case DzoomWide     :    //Wide (Variable) 8x 01 04 06 3p FF during Separate Mode
    case FocusFarVariable : //Far  (Variable) 8x 01 04 08 2p FF p=0 (Low) to 7 (High)
    case FocusNearVariable: //Near (Variable) 8x 01 04 08 3p FF
    case GainLimit     :    //Gain Limit      8x 01 04 2C 0p FF p: Gain Position
    case NoiseRedution :    //NR Setting      8x 01 04 53 0p FF p: (0: OFF, level 1 to 5)
    case MultiLineTitleClear :             // 8x 01 04 74 1p FF Title Setting clear,p: (p: 0h to Ah, F= all lines)
    case MultiLineTitleOn    :             // 8x 01 04 74 2p FF On ,p:Title display On/Off (0h to Ah, F= all lines)
    case MultiLineTitleOff   :             // 8x 01 04 74 3p FF Off
    case LowLightBasisBrightnessPosition:  // 8x 01 05 49 0p FF
    case PrivacyZoneSetMaskTable:          // 8x 01 05 70 0p FF p: Table (0h to 1h)
        if(cam->value > 0x0f ) return (VISCA_ERROR_CMD_NOT_EXECUTABLE);
        VISCA_packet->bytes[3] = (command >>16)&0xff;
        VISCA_packet->bytes[4] = ((command>>8 )&0xff) + (cam->value&0x0f);
        break;
    case ChromaSuppress      :// 8x 01 04 5F pp FF,pp: chroma suppress setting level
        // 00: OFF 01h to 03h: ON (3 levels).effect increases as the level number increases.
    case AEresponseDirect:    // 8x 01 04 5D pp FF,pp:Automatic Exposure
        // Response Setting (01h to 30h),default value: 01
        VISCA_packet->bytes[3] = (command>>16)&0xff;
        VISCA_packet->bytes[4] = ((command>>8)&0xff) + (cam->value&0xff);
        break;
        // Commands 7 bytes without arguments
    case DefogOn:             // 8x 01 04 37 02 00 FF On Defog ON/OFF
    case DefogOff:            // 8x 01 04 37 03 00 FF Off
    case CustomReset:         // 8x 01 04 3F 00 7F FF Reset Starts up in this mode when the power is turned on.
    case CustomSet:           // 8x 01 04 3F 01 7F FF Set
    case CustomRecall:        // 8x 01 04 3F 02 7F FF Recall
    case ColorBarOff         :// 8x 01 7E 04 7D 00 FF —
    case ColorBar_8_colors   :// 8x 01 7E 04 7D 01 FF
    case ColorBar_7_colors   :// 8x 01 7E 04 7D 02 FF
    case ColorBarGrayScale   :// 8x 01 7E 04 7D 03 FF
    case ElectronicPanTiltOn :// 8x 01 7E 06 00 02 FF
    case ElectronicPanTiltOff:// 8x 01 7E 06 00 03 FF
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >> 8 )&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = VISCA_TERMINATOR;
        break;
        // Commands 7 bytes with one argument
    case ApertureMode           :// 8x 01 05 42 01 0p FF p: Auto (0)/Manual (1) selection
    case ApertureBandWidth      :// 8x 01 05 42 02 0p FF p: Bandwidth setting,0: default (initial value),1: low bandwidth,2: mid bandwidth,3: wide bandwidth, 4: broad bandwidth
    case ApertureCrispening     :// 8x 01 05 42 03 0p FF p: Crispening (0h to 7h)
    case ApertureHVbalance      :// 8x 01 05 42 04 0p FF p: H/V Balance (5h to 9h)
    case ApertureBWbalance      :// 8x 01 05 42 05 0p FF p: B/W Balance (0h to 4h)
    case ApertureLimit          :// 8x 01 05 42 06 0p FF p: Limit (0h to 7h)
    case ApertureHighLightDetail:// 8x 01 05 42 07 0p FF p: High light detail (0h to 4h)
    case ApertureSuperLow       :// 8x 01 05 42 08 0p FF p: Super low emphasis (0h to 7h)
    case MemoryReset :           // 8x 01 04 3F 00 0p FF Reset,p: Memory Number (=0h to Fh)
    case MemorySet   :           // 8x 01 04 3F 01 0p FF Set
    case MemoryRecall:           // 8x 01 04 3F 02 0p FF Recall
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >> 8 )&0xff;
        VISCA_packet->bytes[6] = VISCA_TERMINATOR;
        if(cam->value > 0x0F)  return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        else VISCA_packet->bytes[5] = (cam->value)&0x0f;
        break;
    case SlowShutterLimit:       // 8x 01 05 5A 0p 0q FF |pq: Slow Shutter Limit
    case GainPoint:              // 8x 01 05 4C 0p 0q FF |pq: Gain Point
        if(cam->value>0xff)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (cam->value >> 4 )&0x0f;
        VISCA_packet->bytes[5] = (cam->value      )&0x0f;
        VISCA_packet->bytes[6] = VISCA_TERMINATOR;
        break;
        // Commands 7 bytes with two arguments
    case  HLCParameterSet: // 8x 01 04 14 0p 0q FF p: HLC level (0: Off, 1: On) q: HLC mask level
        if(cam->HLCset.MaskOnOff >0x0f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->HLCset.LevelOnOff>0x01)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (cam->HLCset.LevelOnOff)&0x0f;
        VISCA_packet->bytes[5] = (cam->HLCset.MaskOnOff )&0x0f;
        VISCA_packet->bytes[6] = VISCA_TERMINATOR;
        break;
        //Commands 8 byte argumentless
    case ExtendedExposureCompensationReset: // 8x 01 04 1F 0E 00 00 FF       |Exposure compensation reset
    case ExtendedApertureReset :            // 8x 01 04 1F 02 00 00 FF       |Aperture control reset
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >> 8 )&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;
        //Commands 8 byte with one argument
    case MaxShutterLimit                 :  // 8x 01 05 2A 00 0p 0q FF       |pq: High-speed shutter limit
    case MinShutterLimit                 :  // 8x 01 05 2A 01 0p 0q FF       |pq: Low-speed shutter limit
        if(cam->value>0xff)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >> 8 )&0xff;
        VISCA_packet->bytes[5] = (cam->value>>4)&0x0f;
        VISCA_packet->bytes[6] = (cam->value   )&0x0f;
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;
    case GammaPatternSelect              :  // 8x 01 05 5B 0p 0q 0r FF       |pqr: Selection pattern (001h to 200h)
        if(cam->value>0x200)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (cam->value>>8)&0x0f;
        VISCA_packet->bytes[5] = (cam->value>>4)&0x0f;
        VISCA_packet->bytes[6] = (cam->value   )&0x0f;
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;
    case ExtendedExposureCompensationUp  :  // 8x 01 04 1F 0E 02 pp FF       |Exposure compensation up   pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    case ExtendedExposureCompensationDown:  // 8x 01 04 1F 0E 03 pp FF       |Exposure compensation down pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    case ExtendedApertureUp              :  // 8x 01 04 1F 02 02 pp FF       |Aperture control up pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    case ExtendedApertureDown            :  // 8x 01 04 1F 02 03 pp FF       |Aperture control down pp: Step number pp=00h to 7Fh(However, 00h is the same operation as 01h.)
        if(cam->value>0x7f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = (cam->value   )&0x7f;
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;
        //Commands 8 byte with two arguments
    case RegisterValue:  //8x 01 04 24 mm 0p 0p FF mm: Register No. (=00h to 7Fh)//pp: Register Value (=00h to FFh)
        if(cam->value >0x7f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->value2>0xff)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] =  cam->value & 0xff;
        VISCA_packet->bytes[5] = (cam->value2>>4)&0x0f;
        VISCA_packet->bytes[6] = (cam->value2   )&0x0f;
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;

        // Standart command 9 bytes with arguments
    case PrivacyZoneDisplay:      // 8x 01 04 77 pp pp pp pp FF Mask Display ON/OFF, pp pp pp pp: Mask Settings (0: OFF, 1: ON)
        VISCA_packet->length = 0x09;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = (cam->value   )&0x01;
        VISCA_packet->bytes[8] = VISCA_TERMINATOR;
        break;
    case ZoomDirect:              // 8x 01 04 47 0p 0q 0r 0s FF pqrs: Zoom Position
    case FocusDirect:             // 8x 01 04 48 0p 0q 0r 0s FF pqrs: Focus Position
    case FocusNearLimit:          // 8x 01 04 28 0p 0q 0r 0s FF pqrs: Focus Near Limit Position
    case AFmodeActiveIntervalTime:// 8x 01 04 27 0p 0q 0r 0s FF Movement Time,pqrs: Interval
    case SpotFocusPosition:       // 8x 01 05 68 0p 0q 0r 0s FF
    case IDwrite:                 // 8x 01 04 22 0p 0q 0r 0s FF,pqrs: Camera ID (=0000h to FFFFh)
        VISCA_packet->length = 0x09;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (cam->value>>12)&0x0f;
        VISCA_packet->bytes[5] = (cam->value>> 8)&0x0f;
        VISCA_packet->bytes[6] = (cam->value>> 4)&0x0f;
        VISCA_packet->bytes[7] = (cam->value    )&0x0f;
        VISCA_packet->bytes[8] = VISCA_TERMINATOR;
        break;
    case SpotAEPosition:  // 0x04290000,   8x 01 04 29 0p 0q 0r 0s FF    |Position,pq: X (0 to F), rs: Y (0 to F)
        VISCA_packet->length = 0x09;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (cam->value >> 8 )&0xff;
        VISCA_packet->bytes[5] = (cam->value      )&0x0f;
        VISCA_packet->bytes[6] = (cam->value2>> 8 )&0xff;
        VISCA_packet->bytes[7] = (cam->value2     )&0x0f;
        VISCA_packet->bytes[8] = VISCA_TERMINATOR;
        break;
    case DzoomDirect:             // 8x 01 04 46 00 00 0p 0q FF pq:   D-Zoom Position
    case RgainDirect:             // 8x 01 04 43 00 00 0p 0q FF R Gain,pq:
    case BgainDirect:             // 8x 01 04 44 00 00 0p 0q FF B Gain,pq:
    case ShutterDirect:           // 8x 01 04 4A 00 00 0p 0q FF Direct,pq: Shutter Position
    case IrisDirect:              // 8x 01 04 4B 00 00 0p 0q FF Direct,pq: Iris Position
    case GainDirect:              // 8x 01 04 4C 00 00 0p 0q FF Direct,pq: Gain Position
    case BrightDirect:            // 8x 01 04 4D 00 00 0p 0q FF Direct,pq: Bright Position
    case ExpCompDirect:           // 8x 01 04 4E 00 00 0p 0q FF Direct,pq: ExpComp Position
    case ApertureDirect:          // 8x 01 04 42 00 00 0p 0q FF Direct,pq: Aperture Gain
    case AutoICRthreshold:        // 8x 01 04 21 00 00 0p 0q FF Threshold,pq: ICR ON -> OFF Threshold Level
    case ZoomPositionReplyIntervalTimeSet:      // 8x 01 04 6A 00 00 0p 0p FF pp: Interval Time [V cycle]
    case FocusPositionReplyIntervalTimeSet:     // 8x 01 04 1A 00 00 0p 0p FF pp: Interval Time [V cycle]
        if(cam->value>0xff)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x09;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = (cam->value>> 4)&0x0f;
        VISCA_packet->bytes[7] = (cam->value    )&0x0f;
        VISCA_packet->bytes[8] = VISCA_TERMINATOR;
        break;
    case ColorGainDirect:         // 8x 01 04 49 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
    case ColorHueDirect:          // 8x 01 04 4F 00 00 00 0p FF p: Color Hue setting 0h (-14 degrees) to Eh (+14 degrees)
        if(cam->value>0x0E)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x09;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = (cam->value   )&0x0f;
        VISCA_packet->bytes[8] = VISCA_TERMINATOR;
        break;

        //Special command with 10 bytes and 5 arguments
    case MoutionDetectionWindowSet://0x041D0000 // 8x 01 04 1D 0m 0p 0q 0r 0s FF |
        if(cam->MD_WindowSet.DetectionFrameNumber>3)return VISCA_ERROR_CMD_NOT_EXECUTABLE;// m: Select Detection Frame (0,1,2,3),
        if(cam->MD_WindowSet.StartHposition>0x0f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;   // p: Start Horizontal Position (00h to 0Fh),
        if(cam->MD_WindowSet.StartVposition>0x07)return VISCA_ERROR_CMD_NOT_EXECUTABLE;   // q: Start Vertical Position (00h to 07h),
        if(cam->MD_WindowSet.StopHposition>0x08)return VISCA_ERROR_CMD_NOT_EXECUTABLE;    // r: Stop Horizontal Position (01h to 10h)
        if(cam->MD_WindowSet.StopHposition<0x01)return VISCA_ERROR_CMD_NOT_EXECUTABLE;    // s: Stop Vertical Position (01h to 08h)*/
        if(cam->MD_WindowSet.StopVposition>0x08)return VISCA_ERROR_CMD_NOT_EXECUTABLE;    // Reply: y0 07 04 1B 0p FF p: Detection Frame Number
        if(cam->MD_WindowSet.StopVposition<0x01)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x0A;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = cam->MD_WindowSet.DetectionFrameNumber;
        VISCA_packet->bytes[5] = cam->MD_WindowSet.StartHposition;
        VISCA_packet->bytes[6] = cam->MD_WindowSet.StartVposition;
        VISCA_packet->bytes[7] = cam->MD_WindowSet.StopHposition;
        VISCA_packet->bytes[8] = cam->MD_WindowSet.StopVposition;
        VISCA_packet->bytes[9] = VISCA_TERMINATOR;
        break;
        //Special command with 10 bytes and 2 arguments
    case MemsaveWrite:  //8x 01 04 23 0X 0p 0q 0r 0s FF //X: 00 to 07 (Address), total 16 byte ,pqrs: 0000h to FFFFh (Data)
        if(cam->value>0x07)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x0A;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] =  cam->value  & 0x07;
        VISCA_packet->bytes[5] = (cam->value2 & 0xF000)>>12;
        VISCA_packet->bytes[6] = (cam->value2 & 0x0F00)>>8 ;
        VISCA_packet->bytes[7] = (cam->value2 & 0x00F0)>>4 ;
        VISCA_packet->bytes[8] =  cam->value2 & 0x000F     ;
        VISCA_packet->bytes[9] = VISCA_TERMINATOR;
        break;
    case ExtendedAutoICRonToOffTreshold:      // 8x 01 04 1F 21 00 00 0p 0q FF pq: ICR ON->OFF threshold when Auto ICR is on pq=00h to FFh
    case ExtendedAutoICRonLevel:              // 8x 01 04 1F 21 01 00 0r 0s FF pq: On level ICR OFF->ON when Auto ICR is on pq=00h to 1Ch
    case ExtendedExposureCompensationDirect : // 8x 01 04 1F 4E 00 00 0p 0q FF  //Set the exposure compensation to the specified level pq: Level pq=00h to FFh
    case ExtendedApertureDirect :             // 8x 01 04 1F 42 00 00 0p 0q FF  //Set the aperture control to the specified level pq: Level pq=00h to FFh
    case ExtendedColorGainDirect:             // 8x 01 04 1F 49 00 00 0p 0q FF |Color Gain Setting pq: Gain setting level pq=00h (0%) to FFh (200%)
    case ExtendedColorHueDirect :             // 8x 01 04 1F 4F 00 00 0p 0q FF |Color Hue Setting pq: Phase setting level pq=00h (-14 degrees) to FFh (14 degrees)
        if(cam->value>0xff)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x0A;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = (cam->value & 0x00F0)>>4 ;
        VISCA_packet->bytes[8] =  cam->value & 0x000F     ;
        VISCA_packet->bytes[9] = VISCA_TERMINATOR;
        break;
        // 11 byte commands
    case GammaOffset:                //0x041e0000, 8x 01 04 1E 00 00 00 0s 0t 0u FF
        //s: Polarity offset (0 is plus, 1 is minus)
        // tu: Offset s=0 (00h to 40h) // Offset s=1 (00h to 40h)
        if(cam->value>1)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->value2>0x40)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x0b;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = (command      )&0xff;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = cam->value & 0x01;
        VISCA_packet->bytes[8] = (cam->value2 & 0x00f0)>>4;
        VISCA_packet->bytes[9] = (cam->value2 & 0x000f);
        VISCA_packet->bytes[10] = VISCA_TERMINATOR;
        break;
    case PrivacyZoneSetMask:         //0x04760000, 8x 01 04 76 mm nn 0r 0r 0s 0s FF  |mm: Mask Settings,nn 00: Modify, 01: New,rr: W, ss: H
    case PrivacyZoneSetmaskcolor:    //0x04780000, 8x 01 04 78 pp pp pp pp qq rr FF  |pp pp pp pp: Mask Color Settings,qq: Color Setting when 0 is selected,rr: Color Setting when 1 is selected
    case PrivacyZoneSetPanTiltAngle: //0x04790000, 8x 01 04 79 0p 0p 0p 0q 0q 0q FF  |Pan/Tilt Angle Settings ppp: Pan qqq: Tilt
    case MoutionDetectionFunctionSet://0x041C0000, 8x 01 04 1C 0m 0n 0p 0q 0r 0s FF  |m: Display mode,n: Detection Frame Set (00h to 0Fh),pq: Threshold Level (00h to FFh),rs: Interval Time set (00h to FFh)
        //FIXME: We do not use this function
        return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        //    break;
        //Special command 13 bytes and 3 arguments
    case VEsetParameter:   // 8x 01 04 2D 00 0q 0r 0s 00 00 00 00 FF
        /*q: Display brightness level (0: Dark to 6: Bright)
                             r: Brightness compensation selection (0: Very dark, 1: Dark,2: Standard, 3: Bright)
                             s: Compensation level (0: Low, 1: Mid, 2: High)*/
        if(cam->VEset.Brightness>6)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->VEset.BrightnessComp>3)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->VEset.BrightnessCompLevel>2)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->length = 0x0b;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >>  8)&0xff;
        VISCA_packet->bytes[5] = cam->VEset.Brightness;
        VISCA_packet->bytes[6] = cam->VEset.BrightnessComp;
        VISCA_packet->bytes[7] = cam->VEset.BrightnessCompLevel;
        VISCA_packet->bytes[8] = 0x00;
        VISCA_packet->bytes[9] = 0x00;
        VISCA_packet->bytes[10] = 0x00;
        VISCA_packet->bytes[11] = 0x00;
        VISCA_packet->bytes[12] = VISCA_TERMINATOR;
        break;
    case ZoomFocus://CAM_ZoomFocus Direct 8x 01 04 47 0p 0q 0r 0s 0t 0u 0v 0w FF
        //pqrs: Zoom Position , tuvw: Focus Position
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (cam->value & 0xf000)>>12;
        VISCA_packet->bytes[5] = (cam->value & 0x0f00)>>8;
        VISCA_packet->bytes[6] = (cam->value & 0x00f0)>>4;
        VISCA_packet->bytes[7] = (cam->value & 0x000f);
        VISCA_packet->bytes[8] = (cam->value2 & 0xf000)>>12;
        VISCA_packet->bytes[9] = (cam->value2 & 0x0f00)>>8;
        VISCA_packet->bytes[10] =(cam->value2 & 0x00f0)>>4;
        VISCA_packet->bytes[11] =(cam->value2 & 0x000f   );
        VISCA_packet->bytes[12] = VISCA_TERMINATOR;
        break;
        // Titles
    case MultiLineTitleSet1: // 8x 01 04 73 1L 00 nn pp qq 00 00 00 00 00 00 FF, //l: line number, nn: h-position, pp: color, qq: blink
        VISCA_packet->length = 0x10;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = ((command&0xff00)>>8) + (cam->title.line & 0x0F);
        VISCA_packet->bytes[5] = command&0xff;
        VISCA_packet->bytes[6] = cam->title.hposition;
        VISCA_packet->bytes[7] = cam->title.color;
        VISCA_packet->bytes[8] = cam->title.blink;
        VISCA_packet->bytes[9]  = 0x00;
        VISCA_packet->bytes[10] = 0x00;
        VISCA_packet->bytes[11] = 0x00;
        VISCA_packet->bytes[12] = 0x00;
        VISCA_packet->bytes[13] = 0x00;
        VISCA_packet->bytes[14] = 0x00;
        VISCA_packet->bytes[15] = VISCA_TERMINATOR;
        break;

    case MultiLineTitleSet2: // 8x 01 04 73 2L mm nn pp qq rr ss tt uu vv ww FF, //L: line number,mnpqrstuvw: setting of characters (1 to 10)
    case MultiLineTitleSet3: // 8x 01 04 73 3L mm nn pp qq rr ss tt uu vv ww FF, //L: line number,mnpqrstuvw: setting of characters (11 to 20)
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = ((command&0xff00)>>8) + (cam->title.line & 0x0F);
        uint8_t ttlcnt;
        for(ttlcnt = 0 ;ttlcnt<10;ttlcnt++)
        {
            VISCA_packet->bytes[5+ttlcnt] = cam->title.chars[ttlcnt];
        }
        VISCA_packet->bytes[15] = VISCA_TERMINATOR;
        break;
    case  ColorEnhanceParameterSet:// 8x 01 04 20 mm 00 pp 40 40 ss 40 40 FF
        // mm: Threshold level,
        // pp: Y fixed color for high-intensity,
        // ss: Y fixed color for low-intensity,
        // Each parameter setting 00h to 7Fh
        if(cam->ColorEnhanceSet.ThresholdLevel>0x7f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->ColorEnhanceSet.YfixedColorHighIntensity>0x7f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        if(cam->ColorEnhanceSet.YfixedColorLowIntensity>0x7f)return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = cam->ColorEnhanceSet.ThresholdLevel;
        VISCA_packet->bytes[5] = 0x00;
        VISCA_packet->bytes[6] = cam->ColorEnhanceSet.YfixedColorHighIntensity;
        VISCA_packet->bytes[7] = 0x40;
        VISCA_packet->bytes[8] = 0x40;
        VISCA_packet->bytes[9]  = cam->ColorEnhanceSet.YfixedColorLowIntensity;
        VISCA_packet->bytes[10] = 0x40;
        VISCA_packet->bytes[11] = 0x40;
        VISCA_packet->bytes[12] = VISCA_TERMINATOR;
        break;
        // 14 byte 5 args
    case PrivacyZoneOnInterLockMask:// 8x 01 04 6F mm 0p 0p 0q 0q 0r 0r 0s 0s FF       |mm: Non_Interlock Mask Settings pp: X, q: Y, rr: W, ss: H
        return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        //FIXME: We do not use this command
        //break;
    case PrivacyZoneSetptzmask:     // 8x 01 04 7B mm 0p 0p 0p 0q 0q 0q 0r 0r 0r 0r FF |Pan/Tilt/Zoom Settings for Mask ppp: Pan, qqq: Tilt, rrrr: Zoom, mm: Mask Settings
        return VISCA_ERROR_CMD_NOT_EXECUTABLE;
        //FIXME: We do not use this command
        //break;
    case ElectronicPanTiltPosition: //0x7E062000  8x 01 7E 06 20 00 00 0y 0y 0y 0y 0z 0z 0z 0z FF
        //yyyy: Pan Position, zzzz: Tilt Position
        //*Supplementary explanation:
        //Pan Position is specified in units of 6 pixels and Tilt Position
        //is specified in units of 4.5 pixels (cut off after the decimal point)
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >> 8)&0xff;
        VISCA_packet->bytes[5] = 0x00;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = (cam->PTset.PanPosition & 0xf000)>>12;
        VISCA_packet->bytes[8] = (cam->PTset.PanPosition & 0x0f00)>>8;
        VISCA_packet->bytes[9]  =(cam->PTset.PanPosition & 0x00f0)>>4;
        VISCA_packet->bytes[10] =(cam->PTset.PanPosition & 0x000f);
        VISCA_packet->bytes[11] =(cam->PTset.TiltPosition & 0xf000)>>12;
        VISCA_packet->bytes[12] =(cam->PTset.TiltPosition & 0x0f00)>>8;
        VISCA_packet->bytes[13] =(cam->PTset.TiltPosition & 0x00f0)>>4;
        VISCA_packet->bytes[14] =(cam->PTset.TiltPosition & 0x000f);
        VISCA_packet->bytes[15] = VISCA_TERMINATOR;
        break;
        //Standart command 6 bytes without arguments
    case PowerOn :
    case PowerOff:
    case ZoomStop:
    case ZoomTele:
    case ZoomWide:
    case DzoomOn :
    case DzoomOff:
    case DzoomCombine:
    case DzoomSeparate:
    case DzoomStop:
    case DzoomX1_max:
    case FocusAuto:
    case FocusManual:
    case FocusAuto_manual:
    case FocusStop:
    case FocusFarStandard:
    case FocusNearStandard:
    case FocusOnePushTrigger:
    case AFmodeNormal:
    case AFmodeInterval:
    case AFmodeZoomTrigger:
    case SpotFocusOn:
    case SpotFocusOff:
    case AFsensitivityNormal:
    case AFsensitivityLow:
    case IRcorrectionStandard:
    case IRcorrectionIrLight:
    case InitializeLens:
    case InitializeCamera:
    case WbAuto:
    case WbIndoor:
    case WbOutdoor:
    case WbOnePush:
    case WbAtw:
    case WbManual:
    case WbOnePushTrigger:
    case WbOutdoorAuto:
    case WbsodiumLampAuto:
    case WbsodiumLamp:
    case WbsodiumLampOutdoorAuto:
    case RgainReset:
    case RgainUp:
    case RgainDown :
    case BgainReset:
    case BgainUp   :
    case BgainDown :
    case AEfullAuto:
    case AEmanual  :
    case AEshutterPriority:
    case AEirisPriority:
    case AEbright:
    case LowLightBasisBrightnessOn:
    case LowLightBasisBrightnessOff:
    case ShutterReset  :
    case ShutterUp     :
    case ShutterDown   :
    case SlowShutterOn :
    case SlowShutterOff:
    case IrisReset     :
    case IrisUp        :
    case IrisDown      :
    case GainReset     :
    case GainUp        :
    case GainDown      :
    case BrightReset   :
    case BrightUp      :
    case BrightDown    :
    case BacklightOn   :
    case BacklightOff  :
    case SpotAEOn      :
    case SpotAEOff     :
    case ExpCompOn     :
    case ExpCompOff    :
    case ExpCompReset  :
    case ExpCompUp     :
    case ExpCompDown   :
    case VEoff         :
    case VEon          :
    case ApertureReset :
    case ApertureUp    :
    case ApertureDown  :
    case HighResolutionOn :
    case HighResolutionOff:
    case StabilizerOn :
    case StabilizerOff:
    case GammaStandart:
    case GammaStraight:
    case GammaPattern :
    case HighSensitivityOn :
    case HighSensitivityOff:
    case LRreverseOn :
    case LRreverseOff:
    case FreezeOn    :
    case FreezeOff   :
    case PictureEffectOff:
    case PictureEffectNegart:
    case PictureEffectBw:
    case PictureFlipOn :
    case PictureFlipOff:
    case ICRon :
    case ICRoff:
    case AutoICRon :
    case AutoICRoff:
    case AutoICRalarmReplyOn  :
    case AutoICRalarmReplyOff :
    case DisplayOn   :
    case DisplayOff  :
    case DisplayOnOff:
    case MuteOn      :
    case MuteOff     :
    case MuteOnOff   :
    case PrivacyZonecenterlineOff:
    case PrivacyZonecenterlineOn :
    case MoutionDetectionOn:
    case MoutionDetectionOff:
    case ZoomPositionReplyOn  :
    case ZoomPositionReplyOff :
    case FocusPositionReplyOn :
    case FocusPositionReplyOff:
    case ColorEnhanceOn       :
    case ColorEnhanceOff      :
        VISCA_packet->bytes[3] = (command >> 16)&0xff;
        VISCA_packet->bytes[4] = (command >> 8 )&0xff;
        break;
    default:
        return VISCA_ERROR_CMD_NOT_EXECUTABLE;
    }
    return (VISCA_SUCCESS);
}


int ViscaInquiryCommandPack(VISCAPacket_t * VISCA_packet, VISCACamera_t * camera )
{
    VISCA_packet->bytes[0] = VISCA_HEADER+camera->camnum;
    VISCA_packet->bytes[1] = VISCA_INQUIRY;

    switch(camera->inquiry){
    //Standart camera 1  5 bytes inqiry
    case VersionInq:           //         8x 09 00 02 FF
    case PowerInq  :           //         8x 09 04 00 FF
    case ZoomPosInq:           //         8x 09 04 47 FF
    case DZoomModeInq:         //         8x 09 04 06 FF
    case DZoomC_SModeInq:      //         8x 09 04 36 FF
    case DZoomPosInq:          //         8x 09 04 46 FF
    case FocusModeInq:         //         8x 09 04 38 FF
    case FocusPosInq:          //         8x 09 04 48 FF
    case FocusNearLimitInq:    //         8x 09 04 28 FF
    case AFSensitivityInq:     //         8x 09 04 58 FF
    case AFModeInq:            //         8x 09 04 57 FF
    case AFTimeSettingInq:     //         8x 09 04 27 FF
    case IRCorrectionInq:      //         8x 09 04 11 FF
    case WBModeInq:            //         8x 09 04 35 FF
    case RGainInq :            //         8x 09 04 43 FF
    case BGainInq :            //         8x 09 04 44 FF
    case AEModeInq:            //         8x 09 04 39 FF
    case ShutterPosInq:        //         8x 09 04 4A FF
    case SlowShutterInq:       //         8x 09 04 5A FF
    case IrisPosInq      :     //         8x 09 04 4B FF
    case GainPosInq      :     //         8x 09 04 4C FF
    case GainLimitInq    :     //         8x 09 04 2C FF
    case BrightPosInq    :     //         8x 09 04 4D FF
    case ExpCompModeInq  :     //         8x 09 04 3E FF
    case ExpCompPosInq   :     //         8x 09 04 4E FF
    case BackLightModeInq:     //         8x 09 04 33 FF
    case SpotAEModeInq   :     //         8x 09 04 59 FF
    case SpotAEPosInq    :     //         8x 09 04 29 FF
    case VEModeInq       :     //         8x 09 04 3D FF
    case VEParameterInq  :     //         8x 09 04 2D FF
    case AEResponseInq   :     //         8x 09 04 5D FF
    case DefogInq        :     //         8x 09 04 37 FF
    case ApertureInq     :     //         8x 09 04 42 FF
    case HRModeInq       :     //         8x 09 04 52 FF
    case NoiseRedutionInq:     //         8x 09 04 53 FF
    case GammaInq        :     //         8x 09 04 5B FF
    case GammaOffsetInq  :     //         8x 09 04 1E FF
    case HighSensitivityInq:   //         8x 09 04 5E FF
    case LR_ReverseModeInq :   //         8x 09 04 61 FF
    case FreezeModeInq   :     //         8x 09 04 62 FF
    case PictureEffectModeInq: //         8x 09 04 63 FF
    case PictureFlipModeInq:   //         8x 09 04 66 FF
    case ICRModeInq        :   //         8x 09 04 01 FF
    case AutoICRModeInq    :   //         8x 09 04 51 FF
    case AutoICRThresholdInq:  //         8x 09 04 21 FF
    case AutoICRAlarmReplyInq: //         8x 09 04 31 FF
    case MemoryInq         :   //         8x 09 04 3F FF
    case DisplayModeInq       ://         8x 09 04 15 FF (8x 09 06 06 FF)
    case CAM_StabilizerModeInq://         8x 09 04 34 FF
    case MuteModeInq          ://         8x 09 04 75 FF
    case PrivacyDisplayInq    ://         8x 09 04 77 FF
    case PrivacyPanTiltInq    ://         8x 09 04 79 FF
    case PrivacyMonitorInq    ://         8x 09 04 6F FF
    case IDInq                ://         8x 09 04 22 FF
    case ColorEnhanceModeInq:  //         8x 09 04 50 FF
    case ChromaSuppressInq  :  //         8x 09 04 5F FF
    case ColorGainInq       :  //         8x 09 04 49 FF
    case ColorHueInq        :  //         8x 09 04 4F FF
    case TempInq            :  //         8x 09 04 68 FF
    case MDModeInq:            //         8x 09 04 1B FF
    case MDFunctionInq:        //         8x 09 04 1C FF
    case ContinuousZoomPosReplyModeInq: //8x 09 04 69 FF
    case ZoomPosReplyIntervalTimeInq:   //8x 09 04 6A FF
    case ContinuousFocusPosReplyModeInq://8x 09 04 16 FF
    case FocusReplyIntervalTimeInq:     //8x 09 04 1A FF
    case ColorEnhanceInq:      //         8x 09 04 20 FF
    case HLCInq:               //         8x 09 04 14 FF
        // 5 bytes inqiry with 0x05 category
    case SpotFocusModeInq:             // 8x 09 05 08 FF
    case SpotFocusPosInq:              // 8x 09 05 68 FF
    case LowLightBasisBrightnessInq:   // 8x 09 05 39 FF
    case LowLightBasisBrightnessPosInq:// 8x 09 05 49 FF
    case SlowShutterLimitInq:          // 8x 09 05 5A FF
    case GainPointInq    :             // 8x 09 05 4C FF
    case NoiseRedution2D3DInq :        // 8x 09 05 53 FF
    case GammaPatternInq      :        // 8x 09 05 5B FF
    case SetMaskTableInq:              // 8x 09 05 70 FF
        VISCA_packet->length = 0x05;
        VISCA_packet->bytes[2] = (camera->inquiry&0xff000000)>>24;
        VISCA_packet->bytes[3] = (camera->inquiry&0x00ff0000)>>16;
        VISCA_packet->bytes[4] = VISCA_TERMINATOR;
        break;
        // 6 bytes inqiry with 0x04 category
    case ExtendedExpCompPosInq:        // 8x 09 04 1F 4E FF
    case ExtendedApertureInq:          // 8x 09 04 1F 42 FF
        // 6 bytes inqiry 0x05 category
    case MaxShutterInq      :          // 8x 09 05 2A 00 FF
    case MinShutterInq      :          // 8x 09 05 2A 01 FF
    case ApertureModeInq :             // 8x 09 05 42 01 FF
    case ApertureBandwidthInq :        // 8x 09 05 42 02 FF
    case ApertureCrispeningInq:        // 8x 09 05 42 03 FF
    case ApertureHVBalance    :        // 8x 09 05 42 04 FF
    case ApertureBWBalance    :        // 8x 09 05 42 05 FF
    case ApertureLimitInq     :        // 8x 09 05 42 06 FF
    case ApertureHighLightDetailInq:   // 8x 09 05 42 07 FF
    case ApertureSuperLowInq  :        // 8x 09 05 42 08 FF
        // 6 bytes inqiry 0x7e category
    case CAM_ColorBarInq:              // 8x 09 7E 04 7D FF
    case ePTModeInq:                   // 8x 09 7E 06 00 FF
    case ePTPositionInq:               // 8x 09 7E 06 20 FF
    case LensControlSystemInquiry:     // 8x 09 7E 7E 00 FF
    case CameraControlSystemInquiry:   // 8x 09 7E 7E 01 FF
    case MiscInquiry              :    // 8x 09 7E 7E 02 FF
    case ExtendedFunction1Query    :   // 8x 09 7E 7E 03 FF
    case ExtendedFunction2Query    :   // 8x 09 7E 7E 04 FF
    case ExtendedFunction3Query    :   // 8x 09 7E 7E 05 FF
        VISCA_packet->length = 0x06;
        VISCA_packet->bytes[2] = (camera->inquiry&0xff000000)>>24;
        VISCA_packet->bytes[3] = (camera->inquiry&0x00ff0000)>>16;
        VISCA_packet->bytes[4] = (camera->inquiry&0x0000ff00)>>8;
        VISCA_packet->bytes[5] = VISCA_TERMINATOR;
        break;
        // 7 bytes inqiry with 0x04 category
    case ExtendedColorGainInq:       //0x1f49,   8x 09 04 1F 49 00 FF
    case ExtendedColorHueInq:        //0x1f4f,   8x 09 04 1F 4F 00 FF
    case ExtendedAutoICRThresholdInq://0x1f21,   8x 09 04 1F 21 00 FF
    case ExtendedAutoICROnLevelInq:  //0x1f2101, 8x 09 04 1F 21 01 FF
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[2] = (camera->inquiry&0xff000000)>>24;
        VISCA_packet->bytes[3] = (camera->inquiry&0x00ff0000)>>16;
        VISCA_packet->bytes[4] = (camera->inquiry&0x0000ff00)>>8;
        VISCA_packet->bytes[5] =  camera->inquiry&0x000000ff;
        VISCA_packet->bytes[6] = VISCA_TERMINATOR;
        break;

        // 6 bytes inqiry with 0x04 category and args
    case PrivacyPTZInq:        //0x7B,   8x 09 04 7B mm FF
    case RegisterValueInq:     //0x24,   8x 09 04 24 mm FF
    case MDWindowInq:          //0x1D,   8x 09 04 1D 0m FF
    case MemSaveInq:           //0x2300, 8x 09 04 23 0X FF
        VISCA_packet->length = 0x06;
        VISCA_packet->bytes[2] = (camera->inquiry&0xff000000)>>24;
        VISCA_packet->bytes[3] = (camera->inquiry&0x00ff0000)>>16;
        VISCA_packet->bytes[4] =  camera->inquiryArgument;
        VISCA_packet->bytes[5] = VISCA_TERMINATOR;
        break;
    default: return VISCA_ERROR_CMD_NOT_EXECUTABLE;
    }
    return 0;
}


int er8300::ProcessMesages (uint8_t *buf,int len)
{
    int i = 0;
    while (i< len)
    {
        switch (Parser.ps){
        case WaitHeader :
            Parser.index=0;
            if(buf[i]==(8+Camera.camnum)<<4 || buf[i]==0x88)
            {
                Parser.ps=WaitTerminator;
                Parser.msg[Parser.index]=buf[i];
            }
            break;
        case WaitTerminator:
            Parser.index++;
            if(Parser.index>sizeof(Parser.msg))
            {
                Parser.index = 0;
                Parser.ps = WaitHeader;
                Parser.ErrorCounter++;
                break;
            }

            Parser.msg[Parser.index]=buf[i];
            if(buf[i]==0xff)
            {
                Decoder.len = Parser.index;
                Decoder.msg = Parser.msg;
                DecodeMessage();
                Parser.ps = WaitHeader;
            }
            break;
        }
        i++;
    }
    return(0);
}

int er8300::DecodeMessage(void)
{
    if(Decoder.len<3){
        Decoder.Error++;
        return -1;
    }
    if(Decoder.len == 3)
        // Acknowledge || Completion || Network Change X0 38 FF
    {
        switch(Decoder.msg[1]&0xf0){
        case VISCA_RESPONSE_ACK:      //0x40
            break;
        case VISCA_RESPONSE_COMPLETED://0x50
            break;
        default:
            if(Decoder.msg[1]==0x38)
                break;
        }
    }
    else
        //len > 3  Error || Inquiry or Address Set 88 30 01 FF  88 30 02 FF Returned the device address to +1.
    {
        switch (Decoder.msg[1]&0xf0){
        case VISCA_RESPONSE_ERROR:    //0x60
            break;
        case VISCA_RESPONSE_ADDRESS:  //0x30
            break;
        case VISCA_RESPONSE_INQIRY:   //0x50
            DecodeInquiry();
            break;
        }
    }

    return 0;
}

int er8300::DecodeInquiry(void)
{
    uint8_t *msg = Decoder.msg;
    if(msg==nullptr)return (-1);
    switch(Camera.inquiry){
    case Inq_none:
        return 0;
    case PowerInq          :
        //y0 50 02 FF On ,
        //y0 50 03 FF Off (Standby)
        Context.Power=msg[2];
        break;
    case ZoomPosInq        :
        //y0 50 0p 0q 0r 0s FF pqrs: Zoom Position
        Context.Zoom = static_cast<uint16_t>(msg[5]+(msg[4]<<4)+(msg[3]<<8)+(msg[2]<<12));
        break;
    case DZoomModeInq      :
        //y0 50 02 FF D-Zoom On ,
        //y0 50 03 FF D-Zoom Off
        Context.DZoomOnOff=static_cast<Generic_t>( msg[2]);
        break;
    case DZoomC_SModeInq   :
        //y0 50 00 FF Combine Mode ,
        //y0 50 01 FF Separate Mode
        Context.DZoomMode=msg[2];
        break;
    case DZoomPosInq       :
        //y0 50 00 00 0p 0q FF pq: D-Zoom Position
        Context.DZoom =(msg[5]+(msg[4]<<4))&0xff;
        break;
    case FocusModeInq      :
        //y0 50 02 FF Auto Focus , y0 50 03 FF Manual Focus
        Context.FocusMode=msg[2];
        break;
    case FocusPosInq       :
        //y0 50 0p 0q 0r 0s FF pqrs: Focus Position
        Context.Focus = static_cast<uint16_t>(msg[5]+(msg[4]<<4)+(msg[3]<<8)+(msg[2]<<12));
        break;
    case FocusNearLimitInq :
        //y0 50 0p 0q 0r 0s FF pqrs: Focus Near Limit Position
         Context.FocusNearLimit = static_cast<uint16_t>(msg[5]+(msg[4]<<4)+(msg[3]<<8)+(msg[2]<<12));
        break;
    case SpotFocusModeInq  :
        //y0 50 02 FF On ,
        //y0 50 03 FF Off
        Context.FocusSpotMode = msg[2];
        break;
    case SpotFocusPosInq   :
        //y0 50 0p 0q 0r 0s FF pq: X, rs: Y
        Context.FocusSpotXposition = static_cast<uint8_t>((msg[2]<<4)+(msg[3]));
        Context.FocusSpotYposition = static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case AFSensitivityInq  :
        //y0 50 02 FF AF Sensitivity Normal ,
        //y0 50 03 FF AF Sensitivity Low
        Context.AFSensitivity=msg[2];
        break;
    case AFModeInq         :
        //y0 50 00 FF Normal AF ,
        //y0 50 01 FF Interval AF ,
        //y0 50 02 FF Zoom Trigger AF
        Context.AFMode=msg[2];
        break;
    case AFTimeSettingInq  :
        //y0 50 0p 0q 0r 0s FF pq: Movement Time, rs: Interval
        Context.AFtime     = static_cast<uint8_t>((msg[2]<<4)+ msg[3]);
        Context.AFinterval = static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case LowLightBasisBrightnessInq:
        //y0 50 02 FF On , y0 50 03 FF Off
        Context.LowLightBasisBrightnessOnOff=msg[2];
        break;
    case LowLightBasisBrightnessPosInq:
        //y0 50 0p FF p: Position
        Context.LowLightBasisBrightness=msg[2];
        break;
    case IRCorrectionInq :
        //y0 50 00 FF Standard, y0 50 01 FF IR Light
        Context.IRCorrection=msg[2];
        break;
    case WBModeInq :
        // y0 50 00 FF Auto,y0 50 01 FF Indoor,y0 50 02 FF Outdoor,y0 50 03 FF One Push WB
        // y0 50 04 FF ATW,y0 50 05 FF Manual,y0 50 06 FF Outdoor Auto,y0 50 07 FF Sodium Lamp Auto
        // y0 50 08 FF Sodium Lamp,y0 50 09 FF Sodium Lamp Outdoor Auto
        Context.WBmode=msg[2];
        break;
    case RGainInq    :
        //y0 50 00 00 0p 0q FF pq: R Gain
        Context.GainRed =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case BGainInq    :
        //y0 50 00 00 0p 0q FF pq: B Gain
        Context.GainBlue =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case AEModeInq   :
        // y0 50 00 FF Full Autoy0 50 03 FF Manual
        // y0 50 0A FF Shutter Priority , y0 50 0B FF Iris Priority
        // y0 50 0D FF Bright
        Context.AutoExposureMode=msg[2];
        break;
    case ShutterPosInq        :
        //y0 50 00 00 0p 0q FF pq: Shutter Position
        Context.Shutter =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case MaxShutterInq        :
        //y0 50 0p 0q FF pq: High-speed shutter limit
        Context.ShutterLimitMax =  static_cast<uint8_t>((msg[2]<<4)+ msg[3]);
        break;
    case MinShutterInq        :
        //y0 50 0p 0q FF pq: Low-speed shutter limit
        Context.ShutterLimitMin =  static_cast<uint8_t>((msg[2]<<4)+ msg[3]);
        break;
    case SlowShutterInq       :
        //y0 50 02 FF On, y0 50 03 FF Off
        Context.SlowShutterOnOff = msg[2];
        break;
    case SlowShutterLimitInq  :
        //y0 50 0p 0q FF pq: Slow Shutter Limit
        Context.SlowShutterLimit =  static_cast<uint8_t>((msg[2]<<4)+ msg[3]);
        break;
    case IrisPosInq           :
        //y0 50 00 00 0p 0q FF pq: Iris Position
        Context.Iris =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case GainPosInq           :
        //y0 50 00 00 0p 0q FF pq: Gain Position
        Context.Gain =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case GainPointInq         :
        //y0 50 0p 0q FF pq: Gain Point
        Context.GainPoint =  static_cast<uint8_t>((msg[2]<<4)+ msg[3]);
        break;
    case GainLimitInq         :
        //y0 50 0q FF p: Gain Limit
        Context.GainLimit =  msg[2];
        break;
    case BrightPosInq         :
        //y0 50 00 00 0p 0q FF pq: Bright Position
        Context.Bright =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case ExpCompModeInq       :
        //y0 50 02 FF On, y0 50 03 FF Off
        Context.ExposureCompensationOnOff = msg[2];
        break;
    case ExpCompPosInq        :
        //y0 50 00 00 0p 0q FF pq: ExpComp Position
        Context.ExposureCompensation =  static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case BackLightModeInq     :
        //y0 50 02 FF On, y0 50 03 FF Off
        Context.BackLightCompensationOnOff = msg[2];
        break;
    case SpotAEModeInq        :
        //y0 50 02 FF On , y0 50 03 FF Off
        Context.SpotAEMode = static_cast<Generic_t>( msg[2]);
        break;
    case SpotAEPosInq         :
        //y0 50 0p 0q 0r 0s FF pq: X position, rs: Y position
        Context.SpotAEPositionX = static_cast<uint8_t>((msg[2]<<4)+ msg[3]);
        Context.SpotAEPositionY = static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case VEModeInq            :
        //y0 50 02 FF On,
        //y0 50 03 FF Off,
        //y0 50 06 FF VE On
        Context.VE.Mode = static_cast<Generic_t>( msg[2]);
        break;
    case VEParameterInq       :
        // y0 50 00 0q 0r 0s 0t 0u 00 00 FF
        // q: Display brightness level (0: Dark to 6: Bright)
        // r: Brightness compensation selection (0: Very dark,// 1: Dark, 2: Standard, 3: Bright)
        // s: Compensation level (00h: Low, 01h: Mid, 02h: High)
        // tu: Always 0
        Context.VE.Brightness = msg[3];
        Context.VE.BrightnessComp = msg[4];
        Context.VE.BrightnessCompLevel = msg[5];
        break;
    case AEResponseInq         :
        //y0 50 pp FF pp: 01h to 30h
        Context.AEresponse = msg[2];
        break;
    case DefogInq              :
        //y0 50 02 00 FF Defog ON , y0 50 03 00 FF Defog OFF
        Context.DefogOnOff = msg[2];
        break;
    case ApertureInq           :
        //y0 50 00 00 0p 0q FF pq: Aperture Gain
        Context.Aperture.Level = static_cast<uint8_t>((msg[4]<<4)+ msg[5]);
        break;
    case ApertureModeInq       :
        //x0 50 0p FF p: Auto (0), Manual (1)
        Context.Aperture.Mode = msg[2];
        break;
    case ApertureBandwidthInq  :
        //x0 50 0p FF p: Bandwidth
        Context.Aperture.BandWidth = msg[2];
        break;
    case ApertureCrispeningInq :
        //x0 50 0p FF p: Crispening
        Context.Aperture.Crispening = msg[2];
        break;
    case ApertureHVBalance     :
        //x0 50 0p FF p: H/V Balance
        Context.Aperture.HVbalance = msg[2];
        break;
    case ApertureBWBalance     :
        //x0 50 0p FF p: B/W Balance
        Context.Aperture.BWbalance = msg[2];
        break;
    case ApertureLimitInq      :
        //x0 50 0p FF p: Limit
        Context.Aperture.Limit = msg[2];
        break;
    case ApertureHighLightDetailInq:
        //x0 50 0p FF p: High light detail
        Context.Aperture.HighLightDetail = msg[2];
        break;
    case ApertureSuperLowInq   :
        //x0 50 0p FF p: Super low emphasis
        Context.Aperture.SuperLow = msg[2];
        break;
    case HRModeInq             :
        //y0 50 02 FF On, y0 50 03 FF Off
        Context.HiResolutionOnOff = msg[2];
        break;
    case NoiseRedutionInq      :
        //y0 50 0p FF Noise Reduction p: 00h to 05h
        Context.NR.Level = msg[2];
        break;
    case NoiseRedution2D3DInq  :
        //y0 50 0p 0q FF p: 2D NR Level, q: 3D NR Level
        Context.NR.Level2D = msg[2];
        Context.NR.Level3D = msg[3];
        break;
    case GammaInq              :
        //y0 50 0p FF Gamma p: 00h to 04h
        Context.Gamma.Mode = msg[2];
        break;
    case GammaPatternInq       :
        //y0 50 0p 0q 0r FF pqr: Selection pattern
        Context.Gamma.Pattern = static_cast<uint16_t>(((msg[2]<<8) + (msg[3]<<4) + msg[4]));
        break;
    case GammaOffsetInq        :
        //y0 50 00 00 00 0s 0t 0u FF
        //s: Polarity offset (0 is plus, 1 is minus)
        //tu: Offset s=0 (00h to 40h) Offset s=1 (00h to 10h)
        Context.Gamma.Offset = static_cast<int8_t>((msg[6]<<4) + msg[7]);
        if(msg[5]!=0)Context.Gamma.Offset*=-1;
        break;
    case HighSensitivityInq    :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
         Context.HighSensitivity =static_cast<Generic_t>(msg[2]);
        break;
    case LR_ReverseModeInq     :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
        Context.PE.LR_Reverse =static_cast<Generic_t>(msg[2]);
        break;
    case FreezeModeInq         :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
        Context.PE.Freeze =static_cast<Generic_t>(msg[2]);
        break;
    case PictureEffectModeInq  :
        //y0 50 00 FF Off,
        //y0 50 02 FF Neg.Art,
        //y0 50 04 FF Black & White
        Context.PE.BlackAndWhite =static_cast<uint8_t>(msg[2]);
        break;
    case PictureFlipModeInq    :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
        Context.PE.Flip =static_cast<Generic_t>(msg[2]);
        break;
    case ICRModeInq            :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
        Context.ICR.ICROnOff =static_cast<Generic_t>(msg[2]);
        break;
    case AutoICRModeInq        :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
        Context.ICR.AutoICROnOff =static_cast<Generic_t>(msg[2]);
        break;
    case AutoICRThresholdInq   :
        //y0 50 00 00 0p 0q FF pq: ICR ON -> OFF Threshold Level
         Context.ICR.AutoICROnOff =static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case AutoICRAlarmReplyInq  :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
         Context.ICR.AlarmReply =static_cast<Generic_t>(msg[2]);
        break;
    case MemoryInq             :
        //y0 50 pp FF pp: Memory number recalled last
        Context.MemoryAddress=static_cast<uint8_t>(msg[2]);
        break;
    case MemSaveInq            :
        //8x 09 04 23 0X FF ,
        //y0 50 0p 0q 0r 0s FF pqrs: 0000h to FFFFh (Data),X: 00h to 07h (Address)
         Context.MemoryData = static_cast<uint16_t>((msg[2]<<12)+(msg[3]<<8)+(msg[4]<<4)+msg[5]);
        break;
    case DisplayModeInq        :
        //y0 50 02 FF On,
        //y0 50 03 FF Off
         Context.Display =static_cast<Generic_t>(msg[2]);
        break;
    case CAM_StabilizerModeInq :
        //y0 05 02 FF On,
        //y0 05 03 FF Off,
        //y0 05 00 FF Hold
         Context.Stabilizer =static_cast<uint8_t>(msg[2]);
        break;
    case MuteModeInq:
        //y0 50 02 FF On, y0 50 03 FF Off
         Context.Mute =static_cast<Generic_t>(msg[2]);
        break;
    case SetMaskTableInq:
        //y0 50 0m FF m: Table
        Context.MaskTableNum =static_cast<uint8_t>(msg[2]);
        break;
    case PrivacyDisplayInq:
        //y0 50 pp pp pp pp FF pp pp pp pp: Mask Display (0: OFF, 1: ON)
        //TODO: we dont use this
        break;
    case PrivacyPanTiltInq:
        //y0 50 0p 0p 0p 0q 0q 0q FF ppp: Pan, qqq: Tilt
        //TODO: we dont use this
        break;
    case PrivacyPTZInq:
        //y0 50 0p 0p 0p 0q 0q 0q 0r 0r 0r 0r FF
        //mm: Mask Settings, ppp: Pan, qqq: Tilt, rrrr: Zoom
        //TODO: we dont use this
        break;
    case PrivacyMonitorInq:
        //y0 50 pp pp pp pp FF pp pp pp pp: Mask is displayed now.
        //TODO: we dont use this
        break;
    case IDInq:
        //y0 50 0p 0q 0r 0s FF pqrs: Camera ID
        Context.ID = static_cast<uint16_t>((msg[2]<<12)+(msg[3]<<8)+(msg[4]<<4)+msg[5]);
        break;
    case VersionInq:
        //y0 50 00 20 mn pq rs tu vw FF
        //mnpq: Model Code (04xx), vw: Socket Number (= 0x02)
        Context.Model = static_cast<uint16_t>((msg[4]<<4)+msg[5]);
        Context.ModelAdditional = static_cast<uint16_t>((msg[6]<<4)+msg[7]);
        break;
    case MDModeInq:
        //y0 50 02 FF On,
        //0 50 03 FF Off
        //TODO: we dont use this
        break;
    case MDFunctionInq:
        //y0 50 0m 0n 0p 0q 0r 0s FF m: Display mode
        //n: Detection Frame Set (00h to 0Fh), pq: Threshold Level (00h to FFh)
        //rs: Interval Time set (00h to FFh)
        //TODO: we dont use this
        break;
    case MDWindowInq:
        //y0 50 0p 0q 0r 0s FF m: Select Detection Frame (0, 1, 2, 3)
        //p: Start Horizontal Position (00h to 0Fh), q: Start Vertical Position (00h to 07h)
        //r: Stop Horizontal Position (01h to 10h), s: Stop Vertical Position (01h to 08h)*/
        //TODO: we dont use this
        break;
    case ContinuousZoomPosReplyModeInq :
        //y0 50 02 FF On, y0 50 03 FF Off
        Context.ZoomPosReply.OnOff = static_cast<Generic_t>(msg[2]);
        break;
    case ZoomPosReplyIntervalTimeInq   :
        //y0 50 00 00 0p 0p FF pp: Interval Time
        Context.ZoomPosReply.IntervalTime = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case ContinuousFocusPosReplyModeInq:
        //y0 50 02 FF On, y0 50 03 FF Off
        Context.FocusPosReply.OnOff = static_cast<Generic_t>(msg[2]);
        break;
    case FocusReplyIntervalTimeInq:
        //y0 50 00 00 0p 0p FF pp: Interval Time
        Context.FocusPosReply.IntervalTime = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case RegisterValueInq:
        //y0 50 0p 0p FF mm: Register No. (= 0x00h to 7Fh)
        //pp: Register Value (= 0x00h to FFh)
        if(Camera.inquiryArgument<=0x7f)
             Context.RegistersValue[Camera.inquiryArgument]= static_cast<uint8_t>((msg[2]<<4)+msg[3]);
        break;
    case ColorEnhanceInq:
        // y0 50 mm 00 pp 40 40 ss 40 40 FF
        // mm: Threshold level
        // pp: Y fixed color for high-intensity
        // ss: Y fixed color for low-intensity
        Context.ColorEnhance.ThresholdLevel =  static_cast<Generic_t>(msg[2]);
        Context.ColorEnhance.YfixedColorHighIntensity =  (msg[4]);
        Context.ColorEnhance.YfixedColorLowIntensity =   (msg[7]);
        break;
    case ColorEnhanceModeInq   :
        //y0 50 02 FF On, y0 50 03 FF Off*/
         Context.ColorEnhance.OnOff =  static_cast<Generic_t>(msg[2]);
        break;
    case ChromaSuppressInq     :
        //y0 50 pp FF pp: Chroma Suppress setting level
        Context.ChromaSuppress =  static_cast<uint8_t>(msg[2]);
        break;
    case ColorGainInq          :
        //y0 50 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
        Context.ColorGain =  static_cast<uint8_t>(msg[5]);
        break;
    case ColorHueInq           :
        //y0 50 00 00 00 0p FF p: Color Hue setting 0h (- 14 degrees) to Eh (+ 14 degrees)
        Context.ColorHue =  static_cast<uint8_t>(msg[5]);
        break;
    case TempInq               :
        //y0 50 00 00 0p 0q FF pq: Lens Temperature
        Context.LensTemperature = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case ExtendedExpCompPosInq :
        //y0 50 00 00 0p 0q FF pq: Exposure compensation level pq = 00h to FFh
        Context.ExposureCompensationExtended = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case ExtendedApertureInq   :
        //y0 50 00 00 0p 0q FF pq: Aperture control level pq=00h to FFh
        Context.Aperture.LevelExtended = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case ExtendedColorGainInq  :
        //y0 50 0p 0q FF pq: Gain setting level, pq: 00h (0%) to FFh (200%)
        Context.ColorGainExtended = static_cast<uint8_t>((msg[2]<<4)+msg[3]);
        break;
    case ExtendedColorHueInq   :
        //y0 50 0p 0q FF pq: Phase setting level pq: 00h (-14 degree) to FFh (+14 degree)
        Context.ColorHueExtended = static_cast<uint8_t>((msg[2]<<4)+msg[3]);
        break;
    case ExtendedAutoICRThresholdInq:
        //y0 50 00 00 0p 0q FF pq: ICR ON→OFF threshold level when Auto ICR
        //pq = 00h to FFh
        Context.ICR.ExtendedOnOfftreshold = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case ExtendedAutoICROnLevelInq:
        //y0 50 00 00 0p 0q FF pq: ICR OFF→ON threshold level when Auto ICR
        //pq = 00h to 1Ch
        Context.ICR.ExtendedOffOnLevel = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        break;
    case HLCInq:
        //y0 50 0p 0q FF p: HLC level (0: Off, 1: On)
        //q: HLC mask level (0: On, 1: Off)
        Context.HLC.LevelOnOff = static_cast<Generic_t>(msg[2]);
        Context.HLC.MaskOnOff  = static_cast<Generic_t>(msg[3]);
        break;
    case CAM_ColorBarInq       :
        // y0 50 00 FF Off
        // y0 50 01 FF Color bar 100% 8 colors
        // y0 50 02 FF Color bar 75% 7 colors,
        // y0 50 03 FF Gray scale
        Context.ColorBar = msg[2];
        break;
    case ePTModeInq:
        //y0 50 02 FF On
        //y0 50 03 FF Off
        Context.EPT.OnOff = static_cast<Generic_t>(msg[2]);
        break;
    case ePTPositionInq:
        //y0 50 00 00 0y 0y 0y 0y 0z 0z 0z 0z FF
        //yyyy: Pan Position、 zzzz: Tilt Position
        Context.EPT.PanPosition  = static_cast<uint16_t>((msg[4]<<12) + (msg[5]<<8) + (msg[6 ]<<4) + msg[7 ]);
        Context.EPT.TiltPosition = static_cast<uint16_t>((msg[8]<<12) + (msg[9]<<8) + (msg[10]<<4) + msg[11]);
        break;
    case LensControlSystemInquiry:
        // y0 50 0z 0z 0z 0z 0n 0n 0p 0p 0p 0p 00 vv uu FF:z - Zoom position, n - focus near limit
        // p focus position, vv bit0-Focus Mode 0: Manual 1: Auto, bit1-Digital Zoom 1: On 0: Off
        // bit2-AF Sensitivity 0: Low,1: Normal;bit3-4 - 0: Normal 1: Interval 2: Zoom Trigger
        // bit5- DZoomMode 0: Combine, 1: Separate
        Context.Zoom = static_cast<uint16_t>((msg[2]<<12)+(msg[3]<<8)+(msg[4]<<4)+msg[5]);
        Context.FocusNearLimit = static_cast<uint16_t>((msg[6]<<4)+msg[7]);
        Context.Focus = static_cast<uint16_t>((msg[8]<<12)+(msg[9]<<8)+(msg[10]<<4)+msg[11]);
        Context.DZoomMode = (msg[13]&0x20)>>4;
        if(msg[13]&0x02) Context.DZoomOnOff=Generic::On;
        else Context.DZoomOnOff=Generic::Off;
        Context.AFMode = (msg[13]&0x18)>>3;
        if(msg[13]&0x04) Context.AFSensitivity = 0x03;
        else  Context.AFSensitivity = 0x02;
        break;
    case CameraControlSystemInquiry:
        Context.GainRed = static_cast<uint8_t>((msg[2]<<4)+msg[3]);
        Context.GainBlue = static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        Context.WBmode = static_cast<uint8_t>(msg[6]);
        Context.Aperture.Level =static_cast<uint8_t>(msg[7]);
        Context.AutoExposureMode = static_cast<uint8_t>(msg[8]);
        if(msg[9]&0x20)Context.HiResolutionOnOff = Generic::On;
        else Context.HiResolutionOnOff = Generic::Off;
        if(msg[9]&0x10)Context.VE.Mode = Generic::On;
        else Context.VE.Mode = Generic::Off;
        if(msg[9]&0x08)Context.SpotAEMode = Generic::On;
        else Context.SpotAEMode = Generic::Off;
        if(msg[9]&0x04)Context.BackLightCompensationOnOff = Generic::On;
        else Context.BackLightCompensationOnOff = Generic::Off;
        if(msg[9]&0x02)Context.ExposureCompensationOnOff = Generic::On;
        else Context.ExposureCompensationOnOff = Generic::Off;
        if(msg[9]&0x01)Context.SlowShutterOnOff = Generic::On;
        else Context.SlowShutterOnOff = Generic::Off;

        Context.Shutter = msg[10];
        Context.Iris = msg[11];
        Context.Gain = msg[12];
        Context.Bright = msg[13];
        Context.ExposureCompensation=msg[14];
        break;
    case MiscInquiry              :
        if(msg[2]&0x08)Context.ICR.AlarmReply = Generic::On;
        else Context.ICR.AlarmReply = Generic::Off;
        if(msg[2]&0x04)Context.ICR.AutoICROnOff = Generic::On;
        else Context.ICR.AutoICROnOff = Generic::Off;
        if(msg[2]&0x01)Context.Power = Generic::On;
        else Context.Power = Generic::Off;

        if(msg[3]&0x40)Context.Stabilizer = Generic::On;
        else Context.Stabilizer = Generic::Off;
        if(msg[3]&0x10)Context.ICR.ICROnOff = Generic::On;
        else Context.ICR.ICROnOff = Generic::Off;
        if(msg[3]&0x08)Context.PE.Freeze = Generic::On;
        else Context.PE.Freeze = Generic::Off;
        if(msg[3]&0x04)Context.PE.LR_Reverse = Generic::On;
        else Context.PE.LR_Reverse = Generic::Off;

        //if(msg[4]&0x20)Context.PZ.OnOff= Generic::On;
        //else Context.PZ.OnOff = Generic::Off;
        if(msg[4]&0x10)Context.Mute= Generic::On;
        else Context.Mute = Generic::Off;
        if(msg[4]&0x08)Context.MultiLineTitle.OnOff= Generic::On;
        else Context.MultiLineTitle.OnOff = Generic::Off;
        if(msg[4]&0x04)Context.Display= Generic::On;
        else Context.Display = Generic::Off;
        Context.PE.Mode = msg[5];
        Context.ID= static_cast<uint16_t>((msg[8]<<12)+(msg[9]<<8)+(msg[10]<<4)+msg[11]);

        if(msg[12]&0x10)Context.MemoryProvided = Generic::On;
        else Context.MemoryProvided = Generic::Off;

        if(msg[12]&0x04)Context.ICR.Provided= Generic::On;
        else Context.ICR.Provided = Generic::Off;

        if(msg[12]&0x02)Context.StabiliserProvided= Generic::On;
        else Context.StabiliserProvided = Generic::Off;

        if(msg[12]&0x01)Context.System= VideoSystem::VIDEO_50_25;
        else Context.System= VideoSystem::VIDEO_59_94__29_97;

        break;
    case ExtendedFunction1Query    :
        Context.DZoom = static_cast<uint8_t>((msg[2]<<4)+msg[3]);
        Context.AFtime= static_cast<uint8_t>((msg[4]<<4)+msg[5]);
        Context.AFinterval = static_cast<uint8_t>((msg[6]<<4)+msg[7]);
        Context.SpotAEPositionX = msg[8];
        Context.SpotAEPositionY = msg[9];
        //if(msg[10]&0x04)Context.MD.OnOff = Generic::On;
        //else Context.MD.OnOff = Generic::Off;
        if(msg[10]&0x01)Context.PE.E_Flip = Generic::On;
        else Context.PE.E_Flip = Generic::Off;
        Context.ColorGain = (msg[11]&0x78)>>3;
        //
        Context.AEresponse=msg[12];
        //TODO: Bed camera documentation Context.Gamma.Offset = (msg[13]&70)>>4;
        if(msg[13]&0x08)Context.HighSensitivity = Generic::On;
        else Context.HighSensitivity = Generic::Off;

        Context.NR.Level = msg[13]&0x07;
        Context.ChromaSuppress = (msg[14]&0x70)>>4;
        Context.GainLimit = msg[14]&0x0f;
        break;
    case ExtendedFunction2Query:
        if(msg[2]&0x02)Context.VE.Mode = Generic::On;
        else Context.VE.Mode = Generic::Off;
        //FIXME: Tomorrow  !!!
        1

        break;
    case ExtendedFunction3Query    :
        Context.ColorHue = msg[2];
        break;
    //default:
    }
    Camera.inquiry=Inq_none;
    Camera.inquiryArgument=0;
    return 0;
}


