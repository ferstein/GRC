#ifndef ER8300_H
#define ER8300_H

#include <stdint.h>

//#ifdef __cplusplus
//extern "C" {
//#endif




typedef enum VISCA_commands:uint32_t
{
    //page 1/6  (sony er-8300 manual)==================================================================================
    AddresSset                     = 0x883001ff,     // 88 30 01 FF                   +|Address setting
    IfClear                        = 0x800001ff,     // 8x 01 00 01 FF,88 01 00 01 FF +|I/F Clear
    CommandCancel                  = 0x008020FF,     // 8x 2p FF                      +|p: Socket No. (=1 or 2)
    PowerOn                        = 0x040002ff,     // 8x 01 04 00 02 FF             +|Power ON
    PowerOff                       = 0x040003ff,     // 8x 01 04 00 03 FF             +|Power OFF
    ZoomStop                       = 0x040700ff,     // 8x 01 04 07 00 FF             +|Stop
    ZoomTele                       = 0x040702ff,     // 8x 01 04 07 02 FF             +|Tele (Standard)
    ZoomWide                       = 0x040703ff,     // 8x 01 04 07 03 FF             +|Wide (Standard)
    ZoomTeleSpeed                  = 0x040720ff,     // 8x 01 04 07 2p FF             +|Tele (Variable)  p=0 (Low) to 7 (High)
    ZoomWideSpeed                  = 0x040730ff,     // 8x 01 04 07 3p FF             +|Wide (Variable)
    ZoomDirect                     = 0x04470000,     // 8x 01 04 47 0p 0q 0r 0s FF    +|Direct pqrs: Zoom Position
    DzoomOn                        = 0x040602ff,     // 8x 01 04 06 02 FF             +|On Digital zoom ON/OFF
    DzoomOff                       = 0x040603ff,     // 8x 01 04 06 03 FF             +|Off
    DzoomCombine                   = 0x043600ff,     // 8x 01 04 36 00 FF             +|Combine Mode Optical/Digital Zoom Combined
    DzoomSeparate                  = 0x043601ff,     // 8x 01 04 36 01 FF             +|Separate Mode Optical/Digital Zoom Separate
    DzoomStop                      = 0x040600ff,     // 8x 01 04 06 00 FF             +|Stop
    DzoomX1_max                    = 0x040610ff,     // 8x 01 04 06 10 FF             +|x1/MAX Magnification Switchover, * Enabled during Separate Mode
    DzoomTele                      = 0x040620ff,     // 8x 01 04 06 2p FF             +|Tele (Variable) p=0 (Low) to 7 (High),
    DzoomWide                      = 0x040630ff,     // 8x 01 04 06 3p FF             +|Enabled Wide (Variable)  during Separate Mode
    DzoomDirect                    = 0x04460000,     // 8x 01 04 46 00 00 0p 0q FF    +|Direct pq: D-Zoom Position, * Enabled during Separate Mode
    FocusAuto                      = 0x043802ff,     // 8x 01 04 38 02 FF             +|Auto Focus AF ON/OFF
    FocusManual                    = 0x043803ff,     // 8x 01 04 38 03 FF             +|Manual Focus
    FocusAuto_manual               = 0x043810ff,     // 8x 01 04 38 10 FF             +|Auto/Manual
    FocusStop                      = 0x040800ff,     // 8x 01 04 08 00 FF             +|Stop
    FocusFarStandard               = 0x040802ff,     // 8x 01 04 08 02 FF             +|Far (Standard)
    FocusNearStandard              = 0x040803ff,     // 8x 01 04 08 03 FF             +|Near(Standard)
    FocusFarVariable               = 0x040820ff,     // 8x 01 04 08 2p FF             +|Far (Variable) p=0 (Low) to 7 (High)
    FocusNearVariable              = 0x040830ff,     // 8x 01 04 08 3p FF             +|Near(Variable)
    FocusDirect                    = 0x04480000,     // 8x 01 04 48 0p 0q 0r 0s FF    +|Direct pqrs: Focus Position
    FocusOnePushTrigger            = 0x041801ff,     // 8x 01 04 18 01 FF             +|One Push AF Trigger
    FocusNearLimit                 = 0x04280000,     // 8x 01 04 28 0p 0q 0r 0s FF    +|pqrs: Focus Near Limit Position
    AFmodeNormal                   = 0x045700ff,     // 8x 01 04 57 00 FF             +|AF Normal  Movement Mode
    AFmodeInterval                 = 0x045701ff,     // 8x 01 04 57 01 FF             +|Interval
    AFmodeZoomTrigger              = 0x045702ff,     // 8x 01 04 57 02 FF             +|Zoom Trigger AF
    AFmodeActiveIntervalTime       = 0x04270000,     // 8x 01 04 27 0p 0q 0r 0s FF    +|Active/Interval Time pq: Movement Time, rs: Interval
    //page 2/6  (sony er-8300 manual)==================================================================================
    SpotFocusOn                    = 0x050802ff,     // 8x 01 05 08 02 FF             +|pq: X (0h to Fh), rs: Y (0h to Fh)
    SpotFocusOff                   = 0x050803ff,     // 8x 01 05 08 03 FF             +|
    SpotFocusPosition              = 0x05680000,     // 8x 01 05 68 0p 0q 0r 0s FF    +|
    AFsensitivityNormal            = 0x045802ff,     // 8x 01 04 58 02 FF             +|Normal AF Sensitivity High/Low
    AFsensitivityLow               = 0x045803ff,     // 8x 01 04 58 03 FF             +|Low
    IRcorrectionStandard           = 0x041100ff,     // 8x 01 04 11 00 FF             +|Standard FOCUS IR compensation data switching
    IRcorrectionIrLight            = 0x041101ff,     // 8x 01 04 11 01 FF             +|IR Light
    ZoomFocus                      = 0x04479900,     // 8x 01 04 47 0p 0q 0r 0s 0t 0u 0v 0w FF  +|pqrs: Zoom Position, tuvw: Focus Position
    InitializeLens                 = 0x041901ff,     // 8x 01 04 19 01 FF             +|Lens Initialization Start
    InitializeCamera               = 0x041903ff,     // 8x 01 04 19 03 FF             +|Camera reset
    WbAuto                         = 0x043500ff,     // 8x 01 04 35 00 FF             +|Normal Auto
    WbIndoor                       = 0x043501ff,     // 8x 01 04 35 01 FF             +|Indoor mode
    WbOutdoor                      = 0x043502ff,     // 8x 01 04 35 02 FF             +|Outdoor mode
    WbOnePush                      = 0x043503ff,     // 8x 01 04 35 03 FF             +|One Push WB mode
    WbAtw                          = 0x043504ff,     // 8x 01 04 35 04 FF             +|Auto Tracing White Balance
    WbManual                       = 0x043505ff,     // 8x 01 04 35 05 FF             +|Manual Control mode
    WbOnePushTrigger               = 0x041005ff,     // 8x 01 04 10 05 FF             +|One Push WB Trigger
    WbOutdoorAuto                  = 0x043506ff,     // 8x 01 04 35 06 FF             +|Outdoor auto
    WbsodiumLampAuto               = 0x043507ff,     // 8x 01 04 35 07 FF             +|Auto including sodium lamp source
    WbsodiumLamp                   = 0x043508ff,     // 8x 01 04 35 08 FF             +|Sodium lamp source fixed mode
    WbsodiumLampOutdoorAuto        = 0x043509ff,     // 8x 01 04 35 09 FF             +|Outdoor auto including sodium lamp source
    RgainReset                     = 0x040300ff,     // 8x 01 04 03 00 FF             +|Reset Manual Control of R Gain
    RgainUp                        = 0x040302ff,     // 8x 01 04 03 02 FF             +|Up
    RgainDown                      = 0x040303ff,     // 8x 01 04 03 03 FF             +|Down
    RgainDirect                    = 0x04430000,     // 8x 01 04 43 00 00 0p 0q FF    +|pq: R Gain
    BgainReset                     = 0x040400ff,     // 8x 01 04 04 00 FF             +|Reset  Manual Control of B Gain
    BgainUp                        = 0x040402ff,     // 8x 01 04 04 02 FF             +|Up
    BgainDown                      = 0x040403ff,     // 8x 01 04 04 03 FF             +|Down
    BgainDirect                    = 0x04440000,     // 8x 01 04 44 00 00 0p 0q FF    +|pq: B Gain
    AEfullAuto                     = 0x043900ff,     // 8x 01 04 39 00 FF             +|Full Auto Automatic Exposure mode
    AEmanual                       = 0x043903ff,     // 8x 01 04 39 03 FF             +|Manual Control mode
    AEshutterPriority              = 0x04390Aff,     // 8x 01 04 39 0A FF             +|Shutter Priority Automatic Exposure mode
    AEirisPriority                 = 0x04390Bff,     // 8x 01 04 39 0B FF             +|Iris Priority Automatic Exposure mode
    AEbright                       = 0x04390Dff,     // 8x 01 04 39 0D FF             +|Bright Mode (Manual control)
    LowLightBasisBrightnessOn      = 0x053902ff,     // 8x 01 05 39 02 FF             +|
    LowLightBasisBrightnessOff     = 0x053903ff,     // 8x 01 05 39 03 FF             +|
    LowLightBasisBrightnessPosition= 0x054900ff,     // 8x 01 05 49 0p FF             +|p: Position
    ShutterReset                   = 0x040A00ff,     // 8x 01 04 0A 00 FF             +|Reset Shutter Setting
    ShutterUp                      = 0x040A02ff,     // 8x 01 04 0A 02 FF             +|Up
    ShutterDown                    = 0x040A03ff,     // 8x 01 04 0A 03 FF             +|Down
    ShutterDirect                  = 0x044A0000,     // 8x 01 04 4A 00 00 0p 0q FF    +|Direct pq: Shutter Position
    MaxShutterLimit                = 0x052a00ff,     // 8x 01 05 2A 00 0p 0q FF       +|pq: High-speed shutter limit
    MinShutterLimit                = 0x052a01ff,     // 8x 01 05 2A 01 0p 0q FF       +|pq: Low-speed shutter limit
    SlowShutterOn                  = 0x045A02ff,     // 8x 01 04 5A 02 FF             +|On Auto Slow Shutter ON/OFF
    SlowShutterOff                 = 0x045A03ff,     // 8x 01 04 5A 03 FF             +|Off
    SlowShutterLimit               = 0x055a0000,     // 8x 01 05 5A 0p 0q FF          +|pq: Slow Shutter Limit
    //page 3/6  (sony er-8300 manual)==================================================================================
    IrisReset                      = 0x040B00ff,     // 8x 01 04 0B 00 FF             +|Reset Iris Setting
    IrisUp                         = 0x040B02ff,     // 8x 01 04 0B 02 FF             +|Up
    IrisDown                       = 0x040B03ff,     // 8x 01 04 0B 03 FF             +|Down
    IrisDirect                     = 0x044B0000,     // 8x 01 04 4B 00 00 0p 0q FF    +|Direct  pq: Iris Position
    GainReset                      = 0x040C00ff,     // 8x 01 04 0C 00 FF             +|Reset Gain Setting
    GainUp                         = 0x040C02ff,     // 8x 01 04 0C 02 FF             +|Up
    GainDown                       = 0x040C03ff,     // 8x 01 04 0C 03 FF             +|Down
    GainDirect                     = 0x044C0000,     // 8x 01 04 4C 00 00 0p 0q FF    +|Direct,pq: Gain Position
    GainLimit                      = 0x042C00ff,     // 8x 01 04 2C 0p FF             +|Gain Limit p: Gain Position
    GainPoint                      = 0x054c0000,     // 8x 01 05 4C 0p 0q FF          +|pq: Gain Point
    BrightReset                    = 0x040D00ff,     // 8x 01 04 0D 00 FF             +|Reset Bright Setting
    BrightUp                       = 0x040D02ff,     // 8x 01 04 0D 02 FF             +|Up
    BrightDown                     = 0x040D03ff,     // 8x 01 04 0D 03 FF             +|Down
    BrightDirect                   = 0x044D0000,     // 8x 01 04 4D 00 00 0p 0q FF    +|Direct,pq: Bright Position
    BacklightOn                    = 0x043302ff,     // 8x 01 04 33 02 FF             +|On Back Light Compensation ON/OFF
    BacklightOff                   = 0x043303ff,     // 8x 01 04 33 03 FF             +|Off
    SpotAEOn                       = 0x045902ff,     // 8x 01 04 33 02 FF             +|On Back Light Compensation ON/OFF
    SpotAEOff                      = 0x045903ff,     // 8x 01 04 33 03 FF             +|Off
    SpotAEPosition                 = 0x04290000,     // 8x 01 04 29 0p 0q 0r 0s FF    +|Position,pq: X (0 to F), rs: Y (0 to F)
    AEresponseDirect               = 0x045D00ff,     // 8x 01 04 5D pp FF             +|Direct,pp: Automatic Exposure Response Setting (01h to 30h),default value: 01
    ExpCompOn                      = 0x043E02ff,     // 8x 01 04 3E 02 FF             +|On Exposure Compensation ON/OFF
    ExpCompOff                     = 0x043E03ff,     // 8x 01 04 3E 03 FF             +|Off
    ExpCompReset                   = 0x040E00ff,     // 8x 01 04 0E 00 FF             +|Reset Exposure Compensation Amount Setting
    ExpCompUp                      = 0x040E02ff,     // 8x 01 04 0E 02 FF             +|Up
    ExpCompDown                    = 0x040E03ff,     // 8x 01 04 0E 03 FF             +|Down
    ExpCompDirect                  = 0x044E0000,     // 8x 01 04 4E 00 00 0p 0q FF    +|pq: ExpComp Position
    VEoff                          = 0x043d03ff,     // 8x 01 04 3D 03 FF             +|Wide-D OFF
    VEon                           = 0x043d06ff,     // 8x 01 04 3D 06 FF             +|VE On
    VEsetParameter                 = 0x042D00ff,     // 8x 01 04 2D 00 0q 0r 0s 00 00 00 00 FF +|q: Display brightness level (0: Dark to 6: Bright)r: Brightness compensation selection (0: Very dark, 1: Dark,2: Standard, 3: Bright)s: Compensation level (0: Low, 1: Mid, 2: High)
    DefogOn                        = 0x04370200,     // 8x 01 04 37 02 00 FF          +|On Defog ON/OFF
    DefogOff                       = 0x04370300,     // 8x 01 04 37 03 00 FF          +|Off
    ApertureReset                  = 0x040200ff,     // 8x 01 04 02 00 FF             +|Reset Aperture Control
    ApertureUp                     = 0x040202ff,     // 8x 01 04 02 02 FF             +|Up
    ApertureDown                   = 0x040203ff,     // 8x 01 04 02 03 FF             +|Down
    ApertureDirect                 = 0x04420000,     // 8x 01 04 42 00 00 0p 0q FF    +|Direct,pq: Aperture Gain (00h to 0Fh)
    ApertureMode                   = 0x05420100,     // 8x 01 05 42 01 0p FF          +|p: Auto (0)/Manual (1) selection
    ApertureBandWidth              = 0x05420200,     // 8x 01 05 42 02 0p FF          +|p: Bandwidth setting,0: default (initial value),1: low bandwidth,2: mid bandwidth,3: wide bandwidth, 4: broad bandwidth
    ApertureCrispening             = 0x05420300,     // 8x 01 05 42 03 0p FF          +|p: Crispening (0h to 7h)
    ApertureHVbalance              = 0x05420400,     // 8x 01 05 42 04 0p FF          +|p: H/V Balance (5h to 9h)
    ApertureBWbalance              = 0x05420500,     // 8x 01 05 42 05 0p FF          +|p: B/W Balance (0h to 4h)
    ApertureLimit                  = 0x05420600,     // 8x 01 05 42 06 0p FF          +|p: Limit (0h to 7h)
    ApertureHighLightDetail        = 0x05420700,     // 8x 01 05 42 07 0p FF          +|p: High light detail (0h to 4h)
    ApertureSuperLow               = 0x05420800,     // 8x 01 05 42 08 0p FF          +|p: Super low emphasis (0h to 7h)
    HighResolutionOn               = 0x045202ff,     // 8x 01 04 52 02 FF             +|On High-Resolusion Mode ON/OFF
    HighResolutionOff              = 0x045203ff,     // 8x 01 04 52 03 FF             +|Off

    //page 4/6  (sony er-8300 manual)==================================================================================
    NoiseRedution                  = 0x045300ff,     // 8x 01 04 53 0p FF             +|p: NR Setting (0: OFF, level 1 to 5)
    StabilizerOn                   = 0x043402ff,     // 8x 01 04 34 02 FF             +|On Stabilizer ON/OFF/HOLD
    StabilizerOff                  = 0x043403ff,     // 8x 01 04 34 03 FF             +|Off
    GammaStandart                  = 0x045B00ff,     // 8x 01 04 5B 00 FF             +|p: Gamma Setting (0: Standard, 1: Straight, 2: Pattern)
    GammaStraight                  = 0x045B01ff,     // 8x 01 04 5B 01 FF             +|
    GammaPattern                   = 0x045B02ff,     // 8x 01 04 5B 02 FF             +|
    GammaPatternSelect             = 0x055b0000,     // 8x 01 05 5B 0p 0q 0r FF       +|pqr: Selection pattern (001h to 200h)
    GammaOffset                    = 0x041e0000,     // 8x 01 04 1E 00 00 00 0s 0t 0u FF  +|s: Polarity offset (0 is plus, 1 is minus)// tu: Offset s=0 (00h to 40h) // Offset s=1 (00h to 40h)
    HighSensitivityOn              = 0x045E02ff,     // 8x 01 04 5E 02 FF             +|On    High Sensitivity mode ON/OFF
    HighSensitivityOff             = 0x045E03ff,     // 8x 01 04 5E 03 FF             +|Off
    LRreverseOn                    = 0x046102ff,     // 8x 01 04 61 02 FF             +|On Mirror Image ON/OFF
    LRreverseOff                   = 0x046103ff,     // 8x 01 04 61 03 FF             +|Off
    FreezeOn                       = 0x046202ff,     // 8x 01 04 62 02 FF             +|On Still Image ON/OFF
    FreezeOff                      = 0x046203ff,     // 8x 01 04 62 03 FF             +|Off
    PictureEffectOff               = 0x046300ff,     // 8x 01 04 63 00 FF             +|Off Picture Effect Setting
    PictureEffectNegart            = 0x046302ff,     // 8x 01 04 63 02 FF             +|Neg.Art
    PictureEffectBw                = 0x046304ff,     // 8x 01 04 63 04 FF             +|Black & White
    PictureFlipOn                  = 0x046602ff,     // 8x 01 04 66 02 FF             +|On    Picture flip ON/OFF
    PictureFlipOff                 = 0x046603ff,     // 8x 01 04 66 03 FF             +|Off
    ICRon                          = 0x040102ff,     // 8x 01 04 01 02 FF             +|On Infrared Mode ON/OFF
    ICRoff                         = 0x040103ff,     // 8x 01 04 01 03 FF             +|Off
    AutoICRon                      = 0x045102ff,     // 8x 01 04 51 02 FF             +|On Auto dark-field mode On/Off
    AutoICRoff                     = 0x045103ff,     // 8x 01 04 51 03 FF             +|Off
    AutoICRthreshold               = 0x04210000,     // 8x 01 04 21 00 00 0p 0q FF    +|Threshold,pq: ICR ON -> OFF Threshold Level
    AutoICRalarmReplyOn            = 0x043102ff,     // 8x 01 04 31 02 FF             +|On Auto ICR switching Alarm ON/OFF Reply y0 07 04 31 03 FF ICR ON -> OFF y0 07 04 31 02 FF,//ICR OFF -> ON
    AutoICRalarmReplyOff           = 0x043103ff,     // 8x 01 04 31 03 FF             +|Off
    MemoryReset                    = 0x043F0000,     // 8x 01 04 3F 00 0p FF          +|Reset,p: Memory Number (=0h to Fh)
    MemorySet                      = 0x043F0100,     // 8x 01 04 3F 01 0p FF          +|Set
    MemoryRecall                   = 0x043F0200,     // 8x 01 04 3F 02 0p FF          +|Recall
    CustomReset                    = 0x043F007f,     // 8x 01 04 3F 00 7F FF          +|Reset Starts up in this mode when the power is turned on.
    CustomSet                      = 0x043F017f,     // 8x 01 04 3F 01 7F FF          +|Set
    CustomRecall                   = 0x043F027f,     // 8x 01 04 3F 02 7F FF          +|Recall
    MemsaveWrite                   = 0x04230000,     // 8x 01 04 23 0X 0p 0q 0r 0s FF +|Write,X: 00 to 07 (Address), total 16 byte pqrs: 0000h to FFFFh (Data)
    DisplayOn                      = 0x041502ff,     // 8x 01 04 15 02 FF             +|On Display ON/OFF (8x 01 06 06 02 FF)
    DisplayOff                     = 0x041503ff,     // 8x 01 04 15 03 FF             +|Off   (8x 01 06 06 03 FF)
    DisplayOnOff                   = 0x041510ff,     // 8x 01 04 15 10 FF             +|On/Off(8x 01 06 06 10 FF)
    MultiLineTitleSet1             = 0x04731000,     // 8x 01 04 73 1L 00 nn pp qq 00 00 00 00 00 00 FF +| l: line number, nn: h-position, pp: color, qq: blink
    MultiLineTitleSet2             = 0x04732000,     // 8x 01 04 73 2L mm nn pp qq rr ss tt uu vv ww FF +| l:line number,mnpqrstuvw: setting of characters (1 to 10)
    MultiLineTitleSet3             = 0x04733000,     // 8x 01 04 73 3L mm nn pp qq rr ss tt uu vv ww FF +| l:line number,mnpqrstuvw: setting of characters (11 to 20)
    MultiLineTitleClear            = 0x047410ff,     // 8x 01 04 74 1p FF             +|p:Title Setting clear (p: 0h to Ah, F= all lines)
    MultiLineTitleOn               = 0x047420ff,     // 8x 01 04 74 2p FF             +|On,p:Title display On/Off (0h to Ah, F= all lines)
    MultiLineTitleOff              = 0x047430ff,     // 8x 01 04 74 3p FF             +|Off
    MuteOn                         = 0x047502ff,     // 8x 01 04 75 02 FF             +|On Muting ON/OFF
    MuteOff                        = 0x047503ff,     // 8x 01 04 75 03 FF             +|Off
    MuteOnOff                      = 0x047510ff,     // 8x 01 04 75 10 FF             +|On/Off

    //page 5/6  (sony eer8300 manual)==================================================================================

    PrivacyZoneSetMask             = 0x04760000,     // 8x 01 04 76 mm nn 0r 0r 0s 0s FF +|mm: Mask Settings,nn 00: Modify, 01: New,rr: W, ss: H
    PrivacyZoneSetMaskTable        = 0x057000ff,     // 8x 01 05 70 0p FF             +|p: Table (0h to 1h)
    PrivacyZoneDisplay             = 0x04770000,     // 8x 01 04 77 pp pp pp pp FF    +|Mask Display ON/OFF, pp pp pp pp: Mask Settings (0: OFF, 1: ON)
    PrivacyZoneSetmaskcolor        = 0x04780000,     // 8x 01 04 78 pp pp pp pp qq rr FF +|pp pp pp pp: Mask Color Settings,qq: Color Setting when 0 is selected,rr: Color Setting when 1 is selected
    PrivacyZoneSetPanTiltAngle     = 0x04790000,     // 8x 01 04 79 0p 0p 0p 0q 0q 0q FF +|Pan/Tilt Angle Settings ppp: Pan qqq: Tilt
    PrivacyZoneSetptzmask          = 0x047B0000,     // 8x 01 04 7B mm 0p 0p 0p 0q 0q 0q 0r 0r 0r 0r FF |Pan/Tilt/Zoom Settings for Mask ppp: Pan, qqq: Tilt, rrrr: Zoom, mm: Mask Settings
    PrivacyZoneOnInterLockMask     = 0x046F0000,     // 8x 01 04 6F mm 0p 0p 0q 0q 0r 0r 0s 0s FF       |mm: Non_Interlock Mask Settings pp: X, q: Y, rr: W, ss: H
    PrivacyZonecenterlineOff       = 0x047C03ff,     // 8x 01 04 7C 03 FF             +|Center Line Display Off
    PrivacyZonecenterlineOn        = 0x047C04ff,     // 8x 01 04 7C 04 FF             +|Center Line Display On
    IDwrite                        = 0x04220000,     // 8x 01 04 22 0p 0q 0r 0s FF    +|pqrs: Camera ID (=0000h to FFFFh)
    MoutionDetectionOn             = 0x041B02ff,     // 8x 01 04 1B 02 FF             +|Motion Detection (MD) On
    MoutionDetectionOff            = 0x041B03ff,     // 8x 01 04 1B 03 FF             +|Off
    MoutionDetectionFunctionSet    = 0x041C0000,     // 8x 01 04 1C 0m 0n 0p 0q 0r 0s FF  +|m: Display mode,n: Detection Frame Set (00h to 0Fh),pq: Threshold Level (00h to FFh),rs: Interval Time set (00h to FFh)
    MoutionDetectionWindowSet      = 0x041D0000,     // 8x 01 04 1D 0m 0p 0q 0r 0s FF +|m: Select Detection Frame (0,1,2,3),p: Start Horizontal Position (00h to 0Fh),q: Start Vertical Position (00h to 07h),
    // r: Stop Horizontal Position (01h to 10h)
    // s: Stop Vertical Position (01h to 08h)*/
    // Reply: y0 07 04 1B 0p FF p: Detection Frame Number
    ZoomPositionReplyOn            = 0x046902ff,     // 8x 01 04 69 02 FF             +|ZoomPosition data Continuous Output On// reply: y0 07 04 69 0p 0p 0q 0q 0q 0q FF  |pp: D-Zoom Position,* 00: When Zoom Mode is Combine,qqqq: Zoom Position
    ZoomPositionReplyOff           = 0x046903ff,     // 8x 01 04 69 03 FF             +|Off
    ZoomPositionReplyIntervalTimeSet= 0x046A0000,     // 8x 01 04 6A 00 00 0p 0p FF   +|pp: Interval Time [V cycle]
    FocusPositionReplyOn           = 0x04160200,     // 8x 01 04 16 02 FF             +|Focus Position data Continuous Output ON reply: y0 07 04 16 00 00 0p 0p 0p 0p FF |pppp: Focus Position
    FocusPositionReplyOff          = 0x04160300,     // 8x 01 04 16 03 FF             +|Off
    FocusPositionReplyIntervalTimeSet= 0x041A0000,     // 8x 01 04 1A 00 00 0p 0p FF  +|pp: Interval Time [V cycle]
    RegisterValue                  = 0x04240000,     // 8x 01 04 24 mm 0p 0p FF       +|mm: Register No. (=00h to 7Fh) pp: Register Value (=00h to FFh)
    ColorEnhanceParameterSet       = 0x04200000,     // 8x 01 04 20 mm 00 pp 40 40 ss 40 40 FF  |mm: Threshold level, pp: Y fixed color for high-intensity, ss: Y fixed color for low-intensity, Each parameter setting 00h to 7Fh
    ColorEnhanceOn                 = 0x045002ff,     // 8x 01 04 50 02 FF             +|Color Enhancement ON
    ColorEnhanceOff                = 0x045003ff,     // 8x 01 04 50 03 FF             +|Off
    //page 6/6  (sony er-8300 manual)==================================================================================
    ChromaSuppress                 = 0x045F00ff,     // 8x 01 04 5F pp FF             +|pp: chroma suppress setting level 00: OFF 01h to 03h: ON (3 levels).effect increases as the level number increases.*/
    ColorGainDirect                = 0x04490000,     // 8x 01 04 49 00 00 00 0p FF    +|p: Color Gain setting 0h (60%) to Eh (200%)
    ColorHueDirect                 = 0x044F0000,     // 8x 01 04 4F 00 00 00 0p FF    +|p: Color Hue setting 0h (-14 degrees) to Eh (+14 degrees)
    ExtendedExposureCompensationReset= 0x041F0E00,   // 8x 01 04 1F 0E 00 00 FF       +|Exposure compensation reset
    ExtendedExposureCompensationUp = 0x041F0E02,     // 8x 01 04 1F 0E 02 pp FF       +|Exposure compensation up   pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    ExtendedExposureCompensationDown=0x041F0e03,     // 8x 01 04 1F 0E 03 pp FF       +|Exposure compensation down pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    ExtendedExposureCompensationDirect= 0x041f4e00,  // 8x 01 04 1F 4E 00 00 0p 0q FF +|Set the exposure compensation to the specified level pq: Level pq=00h to FFh
    ExtendedApertureReset          = 0x04020000,     // 8x 01 04 1F 02 00 00 FF       +|Aperture control reset
    ExtendedApertureUp             = 0x04020200,     // 8x 01 04 1F 02 02 pp FF       +|Aperture control up pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    ExtendedApertureDown           = 0x04020300,     // 8x 01 04 1F 02 03 pp FF       +|Aperture control down pp: Step number pp=00h to 7Fh(However, 00h is the same operation as 01h.)
    ExtendedApertureDirect         = 0x041F4200,     // 8x 01 04 1F 42 00 00 0p 0q FF +|Set the aperture control to the specified level pq: Level pq=00h to FFh
    ExtendedAutoICRonToOffTreshold = 0x041f2100,     // 8x 01 04 1F 21 00 00 0p 0q FF +|pq: ICR ON->OFF threshold when Auto ICR is on pq=00h to FFh
    ExtendedAutoICRonLevel         = 0x041f2101,     // 8x 01 04 1F 21 01 00 0r 0s FF +|pq: On level ICR OFF->ON when Auto ICR is on pq=00h to 1Ch
    ExtendedColorGainDirect        = 0x041f4900,     // 8x 01 04 1F 49 00 00 0p 0q FF +|Color Gain Setting pq: Gain setting level pq=00h (0%) to FFh (200%)
    ExtendedColorHueDirect         = 0x041f4f00,     // 8x 01 04 1F 4F 00 00 0p 0q FF +|Color Hue Setting pq: Phase setting level pq=00h (-14 degrees) to FFh (14 degrees)
    HLCParameterSet                = 0x04140000,     // 8x 01 04 14 0p 0q FF          +|p: HLC level (0: Off, 1: On) q: HLC mask level (0: Off, 1: On)
    ColorBarOff                    = 0x7e047d00,     // 8x 01 7E 04 7D 00 FF          +|
    ColorBar_8_colors              = 0x7e047d01,     // 8x 01 7E 04 7D 01 FF          +|
    ColorBar_7_colors              = 0x7e047d02,     // 8x 01 7E 04 7D 02 FF          +|
    ColorBarGrayScale              = 0x7e047d03,     // 8x 01 7E 04 7D 03 FF          +|
    ElectronicPanTiltOn            = 0x7e060002,     // 8x 01 7E 06 00 02 FF          +|
    ElectronicPanTiltOff           = 0x7E060003,     // 8x 01 7E 06 00 03 FF          +|
    ElectronicPanTiltPosition      = 0x7E062000,     // 8x 01 7E 06 20 00 00 0y 0y 0y 0y 0z 0z 0z 0z FF
    //yyyy: Pan Position, zzzz: Tilt Position
    //*Supplementary explanation:
    //Pan Position is specified in units of 6 pixels and Tilt Position
    //is specified in units of 4.5 pixels (cut off after the decimal
    //point)

} VISCA_commands_t;


typedef enum Inquiry_Command_List:uint32_t
{
    //Inquiry Command List (1/4)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    PowerInq              = 0x04000000,     // 8x 09 04 00 FF , y0 50 02 FF On , y0 50 03 FF Off (Standby)
    ZoomPosInq            = 0x04470000,     // 8x 09 04 47 FF , y0 50 0p 0q 0r 0s FF pqrs: Zoom Position
    DZoomModeInq          = 0x04060000,     // 8x 09 04 06 FF , y0 50 02 FF D-Zoom On , y0 50 03 FF D-Zoom Off
    DZoomC_SModeInq       = 0X04360000,     // 8x 09 04 36 FF , y0 50 00 FF Combine Mode , y0 50 01 FF Separate Mode
    DZoomPosInq           = 0x04460000,     // 8x 09 04 46 FF , y0 50 00 00 0p 0q FF pq: D-Zoom Position
    FocusModeInq          = 0x04380000,     // 8x 09 04 38 FF , y0 50 02 FF Auto Focus , y0 50 03 FF Manual Focus
    FocusPosInq           = 0x04480000,     // 8x 09 04 48 FF , y0 50 0p 0q 0r 0s FF pqrs: Focus Position
    FocusNearLimitInq     = 0x04280000,     // 8x 09 04 28 FF , y0 50 0p 0q 0r 0s FF pqrs: Focus Near Limit Position
    SpotFocusModeInq      = 0x05080000,     // 8x 09 05 08 FF y0 50 02 FF On ,y0 50 03 FF Off
    SpotFocusPosInq       = 0x05680000,     // 8x 09 05 68 FF y0 50 0p 0q 0r 0s FF pq: X, rs: Y
    AFSensitivityInq      = 0x04580000,     // 8x 09 04 58 FF , y0 50 02 FF AF Sensitivity Normal , y0 50 03 FF AF Sensitivity Low
    AFModeInq             = 0x04570000,     // 8x 09 04 57 FF , y0 50 00 FF Normal AF , y0 50 01 FF Interval AF , y0 50 02 FF Zoom Trigger AF
    AFTimeSettingInq      = 0x04270000,     // 8x 09 04 27 FF , y0 50 0p 0q 0r 0s FF pq: Movement Time, rs: Interval
    LowLightBasisBrightnessInq=0x05390000,  // 8x 09 05 39 FF y0 50 02 FF On , y0 50 03 FF Off
    LowLightBasisBrightnessPosInq=0x05490000,//8x 09 05 49 FF y0 50 0p FF p: Position
    IRCorrectionInq       = 0x04110000,     // 8x 09 04 11 FF , y0 50 00 FF Standard, y0 50 01 FF IR Light
    WBModeInq             = 0x04350000,     // 8x 09 04 35 FF
    // y0 50 00 FF Auto
    // y0 50 01 FF Indoor
    // y0 50 02 FF Outdoor
    // y0 50 03 FF One Push WB
    // y0 50 04 FF ATW
    // y0 50 05 FF Manual
    // y0 50 06 FF Outdoor Auto
    // y0 50 07 FF Sodium Lamp Auto
    // y0 50 08 FF Sodium Lamp
    // y0 50 09 FF Sodium Lamp Outdoor Auto*
    RGainInq              = 0x04430000,     //8x 09 04 43 FF , y0 50 00 00 0p 0q FF pq: R Gain
    BGainInq              = 0x04440000,     //8x 09 04 44 FF , y0 50 00 00 0p 0q FF pq: B Gain
    AEModeInq             = 0x04390000,     //8x 09 04 39 FF , y0 50 00 FF Full Autoy0 50 03 FF Manual
    // y0 50 0A FF Shutter Priority , y0 50 0B FF Iris Priority
    // y0 50 0D FF Bright
    ShutterPosInq         = 0x044A0000,     //8x 09 04 4A FF , y0 50 00 00 0p 0q FF pq: Shutter Position
    MaxShutterInq         = 0x052a0000,     //8x 09 05 2A 00 FF y0 50 0p 0q FF pq: High-speed shutter limit
    MinShutterInq         = 0x052a0100,     //8x 09 05 2A 01 FF y0 50 0p 0q FF pq: Low-speed shutter limit
    SlowShutterInq        = 0x045A0000,     //8x 09 04 5A FF , y0 50 02 FF On, y0 50 03 FF Off
    SlowShutterLimitInq   = 0x055a0000,     //8x 09 05 5A FF y0 50 0p 0q FF pq: Slow Shutter Limit
    //Inquiry Command List (2/4)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    IrisPosInq            = 0x044B0000,     //8x 09 04 4B FF , y0 50 00 00 0p 0q FF pq: Iris Position
    GainPosInq            = 0x044C0000,     //8x 09 04 4C FF , y0 50 00 00 0p 0q FF pq: Gain Position
    GainPointInq          = 0x054c0000,     //8x 09 05 4C FF y0 50 0p 0q FF pq: Gain Point
    GainLimitInq          = 0x042C0000,     //8x 09 04 2C FF , y0 50 0q FF p: Gain Limit
    BrightPosInq          = 0x044D0000,     //8x 09 04 4D FF , y0 50 00 00 0p 0q FF pq: Bright Position
    ExpCompModeInq        = 0x043E0000,     //8x 09 04 3E FF , y0 50 02 FF On, y0 50 03 FF Off
    ExpCompPosInq         = 0x044E0000,     //8x 09 04 4E FF , y0 50 00 00 0p 0q FF pq: ExpComp Position
    BackLightModeInq      = 0x04330000,     //8x 09 04 33 FF , y0 50 02 FF On, y0 50 03 FF Off
    SpotAEModeInq         = 0x04590000,     //8x 09 04 59 FF , y0 50 02 FF On , y0 50 03 FF Off
    SpotAEPosInq          = 0x04290000,     //8x 09 04 29 FF , y0 50 0p 0q 0r 0s FF pq: X position, rs: Y position
    VEModeInq             = 0x043D0000,     //8x 09 04 3D FF , y0 50 02 FF On, y0 50 03 FF Off, y0 50 06 FF VE On
    VEParameterInq        = 0x042D0000,     //8x 09 04 2D FF , y0 50 00 0q 0r 0s 0t 0u 00 00 FF
    /*q: Display brightness level (0: Dark to 6: Bright)
                                      r: Brightness compensation selection (0: Very dark,
                                      1: Dark, 2: Standard, 3: Bright)
                                      s: Compensation level (00h: Low, 01h: Mid, 02h: High)
                                      tu: Always 0*/
    AEResponseInq         = 0x045D0000,     //8x 09 04 5D FF , y0 50 pp FF pp: 01h to 30h
    DefogInq              = 0x04370000,     //8x 09 04 37 FF , y0 50 02 00 FF Defog ON , y0 50 03 00 FF Defog OFF
    ApertureInq           = 0x04420000,     //8x 09 04 42 FF , y0 50 00 00 0p 0q FF pq: Aperture Gain
    ApertureModeInq       = 0x05420100,     //8x 09 05 42 01 FF x0 50 0p FF p: Auto (0), Manual (1)
    ApertureBandwidthInq  = 0x05420200,     //8x 09 05 42 02 FF x0 50 0p FF p: Bandwidth
    ApertureCrispeningInq = 0x05420300,     //8x 09 05 42 03 FF x0 50 0p FF p: Crispening
    ApertureHVBalance     = 0x05420400,     //8x 09 05 42 04 FF x0 50 0p FF p: H/V Balance
    ApertureBWBalance     = 0x05420500,     //8x 09 05 42 05 FF x0 50 0p FF p: B/W Balance
    ApertureLimitInq      = 0x05420600,     //8x 09 05 42 06 FF x0 50 0p FF p: Limit
    ApertureHighLightDetailInq=0x05420700,  //8x 09 05 42 07 FF x0 50 0p FF p: High light detail
    ApertureSuperLowInq   = 0x05420800,     //8x 09 05 42 08 FF x0 50 0p FF p: Super low emphasis
    HRModeInq             = 0x04520000,     //8x 09 04 52 FF , y0 50 02 FF On, y0 50 03 FF Off
    NoiseRedutionInq      = 0x04530000,     //8x 09 04 53 FF , y0 50 0p FF Noise Reduction p: 00h to 05h
    NoiseRedution2D3DInq  = 0x05530000,     //8x 09 05 53 FF y0 50 0p 0q FF p: 2D NR Level, q: 3D NR Level
    GammaInq              = 0x045B0000,     //8x 09 04 5B FF , y0 50 0p FF Gamma p: 00h to 04h
    GammaPatternInq       = 0x055b0000,     //8x 09 05 5B FF y0 50 0p 0q 0r FF pqr: Selection pattern
    GammaOffsetInq        = 0x041e0000,     //8x 09 04 1E FF y0 50 00 00 00 0s 0t 0u FF s: Polarity offset (0 is plus, 1 is minus)
    //tu: Offset s=0 (00h to 40h) Offset s=1 (00h to 10h)
    HighSensitivityInq    = 0x045E0000,     //8x 09 04 5E FF , y0 50 02 FF On, y0 50 03 FF Off
    LR_ReverseModeInq     = 0x04610000,     //8x 09 04 61 FF , y0 50 02 FF On, y0 50 03 FF Off

    //Inquiry Command List (3/4)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    FreezeModeInq         = 0x04620000,     //8x 09 04 62 FF , y0 50 02 FF On, y0 50 03 FF Off
    PictureEffectModeInq  = 0x04630000,     //8x 09 04 63 FF , y0 50 00 FF Off, y0 50 02 FF Neg.Art, y0 50 04 FF Black & White
    PictureFlipModeInq    = 0x04660000,     //8x 09 04 66 FF , y0 50 02 FF On, y0 50 03 FF Off
    ICRModeInq            = 0x04010000,     //8x 09 04 01 FF , y0 50 02 FF On, y0 50 03 FF Off
    AutoICRModeInq        = 0x04510000,     //8x 09 04 51 FF , y0 50 02 FF On, y0 50 03 FF Off
    AutoICRThresholdInq   = 0x04210000,     //8x 09 04 21 FF , y0 50 00 00 0p 0q FF pq: ICR ON ? OFF Threshold Level
    AutoICRAlarmReplyInq  = 0x04310000,     //8x 09 04 31 FF , y0 50 02 FF On, y0 50 03 FF Off
    MemoryInq             = 0x043F0000,     //8x 09 04 3F FF , y0 50 pp FF pp: Memory number recalled last
    MemSaveInq            = 0x04230000,     //8x 09 04 23 0X FF , y0 50 0p 0q 0r 0s FF X: 00h to 07h (Address)
    //pqrs: 0000h to FFFFh (Data)
    DisplayModeInq        = 0x04150000,     //8x 09 04 15 FF(8x 09 06 06 FF) , y0 50 02 FF On, y0 50 03 FF Off
    CAM_StabilizerModeInq = 0x04340000,     //8x 09 04 34 FF , y0 05 02 FF On, y0 05 03 FF Off, y0 05 00 FF Hold
    MuteModeInq           = 0x04750000,     //8x 09 04 75 FF , y0 50 02 FF On, y0 50 03 FF Off
    SetMaskTableInq       = 0x05700000,     //8x 09 05 70 FF y0 50 0m FF m: Table
    PrivacyDisplayInq     = 0x04770000,     //8x 09 04 77 FF , y0 50 pp pp pp pp FF pp pp pp pp: Mask Display (0: OFF, 1: ON)
    PrivacyPanTiltInq     = 0x04790000,     //8x 09 04 79 FF , y0 50 0p 0p 0p 0q 0q 0q FF ppp: Pan, qqq: Tilt
    PrivacyPTZInq         = 0x047B0000,     //8x 09 04 7B mm FF , y0 50 0p 0p 0p 0q 0q 0q 0r 0r 0r 0r FF
    //mm: Mask Settings, ppp: Pan, qqq: Tilt, rrrr: Zoom
    PrivacyMonitorInq     = 0x046F0000,     //8x 09 04 6F FF , y0 50 pp pp pp pp FF pp pp pp pp: Mask is displayed now.
    IDInq                 = 0x04220000,     //8x 09 04 22 FF , y0 50 0p 0q 0r 0s FF pqrs: Camera ID
    VersionInq            = 0x00020000,     //8x 09 00 02 FF , y0 50 00 20 mn pq rs tu vw FF
    //mnpq: Model Code (04xx), vw: Socket Number (= 0x02)
    MDModeInq             = 0x041B0000,     //8x 09 04 1B FF , y0 50 02 FF On, y0 50 03 FF Off
    MDFunctionInq         = 0x041C0000,     //8x 09 04 1C FF , y0 50 0m 0n 0p 0q 0r 0s FF m: Display mode
    //n: Detection Frame Set (00h to 0Fh), pq: Threshold Level (00h to FFh)
    //rs: Interval Time set (00h to FFh)
    MDWindowInq           = 0x041D0000,     //8x 09 04 1D 0m FF , y0 50 0p 0q 0r 0s FF m: Select Detection Frame (0, 1, 2, 3)
    //p: Start Horizontal Position (00h to 0Fh), q: Start Vertical Position (00h to 07h)
    //r: Stop Horizontal Position (01h to 10h), s: Stop Vertical Position (01h to 08h)*/
    ContinuousZoomPosReplyModeInq = 0x04690000,//8x 09 04 69 FF , y0 50 02 FF On, y0 50 03 FF Off
    ZoomPosReplyIntervalTimeInq   = 0x046A0000,//8x 09 04 6A FF , y0 50 00 00 0p 0p FF pp: Interval Time
    ContinuousFocusPosReplyModeInq= 0x04160000,//8x 09 04 16 FF , y0 50 02 FF On, y0 50 03 FF Off
    FocusReplyIntervalTimeInq     = 0x041A0000,//8x 09 04 1A FF , y0 50 00 00 0p 0p FF pp: Interval Time
    RegisterValueInq              = 0x04240000,//8x 09 04 24 mm FF , y0 50 0p 0p FF mm: Register No. (= 0x00h to 7Fh)
    //pp: Register Value (= 0x00h to FFh)
    //Inquiry Command List (3/4)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    ColorEnhanceInq       = 0x04200000,     //8x 09 04 20 FF , y0 50 mm 00 pp qq rr ss tt uu FF mm: Threshold level
    //pp: Y fixed color for high-intensity, rstu: ROM version, qq: Cr fixed color for high-intensity
    //rr: Cb fixed color for high-intensity, ss: Y fixed color for low-intensity
    //tt: Cr fixed color for low-intensity, uu: Cb fixed color for low-intensity
    ColorEnhanceModeInq   = 0x04500000,     //8x 09 04 50 FF , y0 50 02 FF On, y0 50 03 FF Off*/
    ChromaSuppressInq     = 0x045F0000,     //8x 09 04 5F FF , y0 50 pp FF pp: Chroma Suppress setting level
    ColorGainInq          = 0x04490000,     //8x 09 04 49 FF , y0 50 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
    ColorHueInq           = 0x044F0000,     //8x 09 04 4F FF , y0 50 00 00 00 0p FF p: Color Hue setting 0h (- 14 degrees) to Eh (+ 14 degrees)
    TempInq               = 0x04680000,     //8x 09 04 68 FF , y0 50 00 00 0p 0q FF pq: Lens Temperature

    ExtendedExpCompPosInq = 0x041f4e00,     //8x 09 04 1F 4E FF y0 50 00 00 0p 0q FF pq: Exposure compensation level pq = 00h to FFh
    ExtendedApertureInq   = 0x041f4200,     //8x 09 04 1F 42 FF y0 50 00 00 0p 0q FF pq: Aperture control level pq=00h to FFh
    ExtendedColorGainInq  = 0x041f4900,     //8x 09 04 1F 49 00 FF y0 50 0p 0q FF pq: Gain setting level, pq: 00h (0%) to FFh (200%)
    ExtendedColorHueInq   = 0x041f4f00,     //8x 09 04 1F 4F 00 FF y0 50 0p 0q FF pq: Phase setting level pq: 00h (-14 degree) to FFh (+14 degree)
    ExtendedAutoICRThresholdInq=0x041f2100, //8x 09 04 1F 21 00 FF y0 50 00 00 0p 0q FF pq: ICR ON→OFF threshold level when Auto ICR
    //pq = 00h to FFh
    ExtendedAutoICROnLevelInq=0x041f2101,   // 8x 09 04 1F 21 01 FF y0 50 00 00 0p 0q FF pq: ICR OFF→ON threshold level when Auto ICR
    //pq = 00h to 1Ch
    HLCInq                = 0x04140000,     //8x 09 04 14 FF y0 50 0p 0q FF p: HLC level (0: Off, 1: On)
    //q: HLC mask level (0: On, 1: Off)
    CAM_ColorBarInq       = 0x7e047d00,     //8x 09 7E 04 7D FF y0 50 00 FF Off  y0 50 01 FF Color bar 100% 8 colors
    // y0 50 02 FF Color bar 75% 7 colors,     y0 50 03 FF Gray scale
    ePTModeInq            = 0x7e060000,     //8x 09 7E 06 00 FF y0 50 02 FF On     y0 50 03 FF Off
    ePTPositionInq        = 0x7e062000,     //8x 09 7E 06 20 FF y0 50 00 00 0y 0y 0y 0y 0z 0z 0z 0z FF
    //yyyy: Pan Position、 zzzz: Tilt Position
    LensControlSystemInquiry=0x7e7e0000,    //8x 09 7E 7E 00 FF
    // y0 50 0z 0z 0z 0z 0n 0n 0p 0p 0p 0p 00 vv uu FF:z - Zoom position, n - focus near limit
    // p focus position, vv bit0-Focus Mode 0: Manual 1: Auto, bit1-Digital Zoom 1: On 0: Off
    // bit2-AF Sensitivity 0: Low,1: Normal;bit3-4 - 0: Normal 1: Interval 2: Zoom Trigger
    // bit5- DZoomMode 0: Combine, 1: Separate
    CameraControlSystemInquiry=0x7e7e0100,  // Command Packet 8x 09 7E 7E 01 FF
    OtherInquiry              =0x7e7e0200,  // Command Packet 8x 09 7E 7E 02 FF
    ExtendedFunction1Query    =0x7e7e0300,  // Command Packet 8x 09 7E 7E 03 FF
    ExtendedFunction2Query    =0x7e7e0400,  // Command Packet 8x 09 7E 7E 04 FF
    ExtendedFunction3Query    =0x7e7e0500,  // Command Packet 8x 09 7E 7E 05 FF
    Inq_none                 = 0x00000000,

}inquiry_command_list_t;

typedef enum _VISCA_CAM
{
    CAM1=1,
    CAM2=2,
    CAM3=3,
    CAM4=4,
    CAM5=5,
    CAM6=6,
    CAM7=7,
    BROADCAST = 8,
} VISCA_Cam_t;

typedef struct _VISCA_packet
{
    uint8_t length;
    uint8_t bytes[32];

} VISCAPacket_t;

typedef enum Generic{
    On = 0x02,
    Off= 0x03,
}Generic_t;

/* TITLE STRUCTURE */
typedef struct _VISCA_title
{
    uint8_t line;
    uint8_t hposition;
    uint8_t color;
    uint8_t blink;
    uint8_t chars[10];

} VISCATitleData_t;

typedef struct _MD_Window{
    uint8_t DetectionFrameNumber;// m: Select Detection Frame (0,1,2,3),
    uint8_t StartHposition;      // p: Start Horizontal Position (00h to 0Fh),
    uint8_t StartVposition;      // q: Start Vertical Position (00h to 07h),
    uint8_t StopHposition;       // r: Stop Horizontal Position (01h to 10h)
    uint8_t StopVposition;       // s: Stop Vertical Position (01h to 08h)*/
}MD_Window_t;

typedef     struct VisibilityEnhancer{//(CAM_VE)
    uint8_t  Mode;
    uint8_t  Brightness;
    uint8_t  BrightnessComp;
    uint8_t  BrightnessCompLevel;
}VisibilityEnhancer_t;

typedef  struct  Aperture{
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
}Aperture_t;

typedef struct NoiseRedution{
    uint8_t  Level;
    uint8_t  Level2D;
    uint8_t  Level3D;
}NoiseRedution_t;
typedef  struct Gamma{
    uint8_t  Mode;
    uint16_t Pattern;
    int8_t   Offset;
}Gamma_t;

typedef struct PictureEffect{
    Generic_t LR_Reverse;
    Generic_t Freeze;
    Generic_t PictureFlip;
    uint8_t   BlackAndWgite;
}PictureEffect_t;

typedef  struct ICR{//IR Cut-Filter
    Generic_t ICROnOff;
    Generic_t AutoICROnOff;
    Generic_t AlarmReply;
    uint8_t ExtendedONtoOfftreshold;//Must be enabled from register 0x5F bit 3
    uint8_t ExtendedOnLevel;//Must be enabled from register 0x5F bit 3
}ICR_t;

typedef struct ContinuousZoomPosReply{
    Generic_t OnOff;
    uint8_t IntervalTime;
}ContinuousZoomPosReply_t;

typedef struct ContinuousFocusPosReply{
    Generic_t OnOff;
    uint8_t IntervalTime;
}ContinuousFocusPosReply_t;

typedef struct ColorEnhance{
    uint8_t ThresholdLevel;
    uint8_t YfixedColorHighIntensity;
    uint8_t YfixedColorLowIntensity;
    Generic_t OnOff;
} ColorEnhance_t;

typedef struct HLC{
    uint8_t Level; //HLC level (0: Off, 1: On)
    uint8_t Mask;  //HLC mask level
}HLC_t;

typedef struct ElectronicPanTilt{
    Generic_t OnOff;
    uint16_t PanPosition;  //in 6 pixels resolution
    uint16_t TiltPosition; //in 4.5 pixels resolution
}ElectronicPanTilt_t;

typedef struct CameraContext {
    Generic_t  Power;
    uint16_t Zoom;
    uint8_t  DZoomMode;
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
    uint8_t  DefogOnOff;
    VisibilityEnhancer_t VE;
    Aperture_t Aperture;
    uint8_t  HiResolutionOnOff;
    NoiseRedution_t NR;
    Gamma_t Gamma;
    Generic_t HighSensitivity;
    PictureEffect_t PE;
    ICR_t ICR;
    uint8_t Memory;//TODO: 16 presets of camera parameters, this place must be edited
    Generic_t Display;
    VISCATitleData_t MultiLineTitle;
    Generic_t Mute;
    uint16_t CamId;
    //FIXME:
    //CAM_PrivacyZone
    //CAM_MD (Motion detection
    ContinuousZoomPosReply_t ZoomPosReply;
    ContinuousFocusPosReply_t FocusPosReply;
    uint8_t RegistersValue[12];
    ColorEnhance_t ColorEnhance;
    uint8_t ChromaSuppress;
    uint8_t ColorGain;
    uint8_t ColorHue;
    uint8_t ColorGainExtended;//Must be enabled from register 0x5F bit 2
    uint8_t ColorHueExtended; //Must be enabled from register 0x5F bit 2
    HLC_t HLC;
    uint8_t ColorBar;
    ElectronicPanTilt_t EPT;

}CameraContext_t;

/* CAMERA STRUCTURE */
// This structure used only for packing and sending parameters to the camera
// After acknowelage or inquire respond Camera context structure must be filled
// And used for displayng values in GUI or anywhere !
typedef struct _VISCA_camera
{
    int fd; //Serial port file descriptor
    VISCA_Cam_t camnum;
    VISCA_commands_t command;
    int16_t value;
    int16_t value2;
    inquiry_command_list_t inquiry;
    uint8_t                inquiryArgument;
    long long TimeSend;

    VISCATitleData_t title;
    MD_Window_t MD_WindowSet;
    VisibilityEnhancer_t VEset;
    ColorEnhance_t ColorEnhanceSet;
    HLC_t HLCset;
    ElectronicPanTilt_t PTset;

} VISCACamera_t;




class er8300
{
private:
    enum PS:uint8_t{WaitHeader = 0,WaitReply,WaitInqiry,WaitStop,}ps;

public:
    er8300();
    float ZoomPositionToMagnification(uint32_t position);
    float FocusPositionToDistanceAndModeFromContext(char * buf);
    int CommandPack(VISCAPacket_t * VISCA_packet , const VISCACamera_t * camera);
    int InquiryPack(VISCAPacket_t * VISCA_packet , const VISCACamera_t * camera);
    int ParseBuf( uint8_t *buf,uint8_t len);

    CameraContext_t Context;
    VISCACamera_t Camera;

    struct _ColorBarTable{
        const unsigned char Value[0x04]=
        {0x00,0x01,0x02,0x03,};
        const char Readable[0x04][16]=
        {"Off","On 8 colors","On 7 colors","On Gray scale"};
    }ColorBarTable;

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

    struct _GenericStateTable_{
        const uint8_t Value[3]={0x00,0x02,0x03};
        const char ModeReadable[3][8]={
            "Stop","On","Off"};
    }GenericStateTable;

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

    struct _DZoomModeTable{
        const uint8_t Value[5]={0x00,0x01,0x02,0x03,0x04};
        const char ModeReadable[5][10]={"Combine","Saeparate","On","Off","SuperRes"};
    }DZoomModeTable;

    struct _FocusModeTable{
        const uint8_t Value[3]={0x02,0x03};
        const char ModeReadable[3][12]={
            "Auto","Manual"};
    }FocusModeTable;

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

    struct _WBmodeTable{
        const uint8_t Value[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
        const char ModeReadable[10][20]={
            "Auto               ",
            "Indoor             ",
            "Outdoor            ",
            "One Push  WB       ",
            "Auto Trace WB      ",
            "Manual             ",
            "Outdoor Auto       ",
            "Sodium Lamp Auto   ",
            "Sodium Lamp fixed  ",
            "Sodium Lamp Outdoor",
        };
    }WBmodeTable;

    struct _AutoExposureModeTable{
        const uint8_t Value[12]={0x00,0x03,0x0A,0x0B,0x0D};
        const char ModeReadable[5][20]={
            "Auto            ",
            "Manual          ",
            "Shutter Priority",
            "Iris Priority   ",
            "Bright          ",
        };
    }AutoExposureModeTable;


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

    struct _WideTeleLimitTable{
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
    }WideTeleLimitTable;

    struct _TemperatureConvertionTable{
        const uint8_t Value[8]={0xFB,0x00,0x0A,0x14,0x1E,0x28,0x32,0x3C,};
        const int8_t MinTemperature[8]={-8,-3, 7,17,27,37,47,57};
        const int8_t MaxTemperature[8]={-2, 3,13,23,33,43,53,63};
    }TemperatureConvertionTable;

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
        /*0*/{0x00,0x00,"Camera BaudRate",5,{0x00,0x01,0x02,0x03,0x04},{"9600 bps","19200 bps ","38400 bps ","57600 bps ","115200 bps",},},
        /*1*/{0x00,0x60,"Digital Output" ,2,{0x00,0x01},{"YUV","RGB"},},
        /*2*/{0x1D,0x72,"Monitoring Mode",12,{0x1D,0x1E,0x13,0x14,0x01,0x04,0x06,0x08,0x09,0x0C,0x0E,0x11},
              {
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
        /*3*/{0x00,0x75,"Low Delay Mode",2,{0x00,0x01},{"Normal Mode","Low Delay Mode"},},
        /*4*/{0x00,0x50,"Zoom Limit Wide",255,{0x00,0x00,0x00,0x00,0x00,0x00},{"Wide Limit 0 - Disabled, 0xff(dec255) - maximum limit)"},},
        /*5*/{0x00,0x51,"Zoom Limit Tele",255,{0x00,0x00,0x00,0x00,0x00,0x00},{"Tele Limit 0 - Disabled, 0xff(dec255) - maximum limit)"},},
        /*6*/{0xEB,0x52,"Digital Zoom Max",0xEB,{0x00,0x00,0x00,0x00,0x00,0x00},{"Max. digital zoom ratio = 256 ÷ (256-Value)"},},
        /*7*/{0x00,0x53,"StableZoom",0x2,{0x00,0x01,0x00},{"StableZoom Off","StableZoom On"},},
        /*8*/{0x01,0x54,"FocusTrace@ZoomDirect",0x2,{0x00,0x01,0x00},{"FocusTrace@ZoomDirect Off","FocusTrace@ZoomDirect On"},},
        /*9*/{0x00,0x55,"FocusOffset@DomeCover",0xFF,{0x00,0x00,0x00,0x00,0x00,0x00},{"FocusOffset@DomeCover 0 - Off, 0xff(dec255) - Max"},},
        /*10*/{0x00,0x5F,"Extended Mode (bitmask)",0x0F,{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F},
               {
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

    struct _ValueLimits {
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
    }ValueLimits;

};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#ifdef __cplusplus
//} /* closing brace for extern "C" */
//#endif
#endif // ER8300_H


