#include "widget.h"
#include "ui_widget.h"
#include <string.h>
#include <math.h>
#include "analogjoystick.h"
#include "gimbalcontrol.h"
#include "CameraControl.h"
#include "er8300.h"

static AnalogJoystick *Joystick;
static GimbalControl *BGC;
static CameraControl *Cam;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                         |Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->showFullScreen();

    Joystick = new AnalogJoystick;
    BGC = new GimbalControl;
    Cam = new CameraControl;

    connect(&this->JoyTimer,SIGNAL(timeout()),this,SLOT(get_joystick_raw_data()));
    this->JoyTimer.start(10);

    connect(&this->BgcTimer,SIGNAL(timeout()),this,SLOT(BgcProcess()));
    this->BgcTimer.start(20);

    connect(&this->CameraTimer,SIGNAL(timeout()),this,SLOT(CameraProcess()));
    this->CameraTimer.start(5);

    for(unsigned int i=0;i<sizeof (Cam->fcber8300->WBmodeTable.Value);i++){
    ui->comboBoxWB->addItem(Cam->fcber8300->WBmodeTable.ModeReadable[i]);}

    for(unsigned int i=0;i<sizeof (Cam->fcber8300->ColorBarTable.Value);i++){
    ui->comboBoxColorBar->addItem(Cam->fcber8300->ColorBarTable.Readable[i]);}

}

void Widget::get_joystick_raw_data(void)
{
    Joystick->Process();

    if(ui->tab_raw->isActiveWindow())
    {
        ui->lcd0_0->display(static_cast<int>(Joystick->State.Out[0]));
        ui->lcd0_1->display(static_cast<int>(Joystick->State.Out[1]));
        ui->lcd0_2->display(static_cast<int>(Joystick->State.Out[2]));
        ui->lcd0_3->display(static_cast<int>(Joystick->State.Out[3]));
        ui->lcd0_4->display(static_cast<int>(Joystick->State.Out[4]));
        ui->lcd0_5->display(static_cast<int>(Joystick->State.Out[5]));
    }
}

void Widget::BgcProcess(void)
{   BGC->ZoomCompensation = 1+(Cam->ZoomMagnification-1)*BGC->ZoomCompensationGain*1.2f;

    //printf("Zoom Compensation is %.3f \n",BGC->ZoomCompensation);

    BGC->ctrl.CONTROL_MODE=SPEED;
    BGC->ctrl.SPEED_YAW =static_cast<int16_t>((Joystick->State.Out[Joystick->Yw]/BGC->ZoomCompensation)+
            Joystick->State.offset[Joystick->Yw]);
    BGC->ctrl.SPEED_PITCH=static_cast<int16_t>((Joystick->State.Out[Joystick->Pt]/BGC->ZoomCompensation)+
            Joystick->State.offset[Joystick->Pt]);
    BGC->ctrl.SPEED_ROLL =static_cast<int16_t>((Joystick->State.Out[Joystick->Rl] +
            Joystick->State.offset[Joystick->Rl]));

    BGC->Process();
    if(BGC->GimbalCtrlEnabled!=0){
        ui->labeGimbCtrl->setText("Gimb ON");
    }
    else{
        ui->labeGimbCtrl->setText("Gimb OFF");
    }
}

void Widget::CameraProcess(void)
{
    //State.Out[i]+=State.offset[i];
    Cam->ZoomJoy     = static_cast<int>((Joystick->State.Out[Joystick->Zm]+Joystick->State.offset[Joystick->Zm])); //LEFT Y  raw[1]
    Cam->FocusPosJoy = static_cast<int>((Joystick->State.Out[Joystick->FP])); //LEFT Z  raw[2]
    Cam->FocusSpeedJoy=static_cast<int>((Joystick->State.Out[Joystick->FS])); //RIGHT Z raw[5]
    Cam->process();

    if(Cam->CamCtrlEnabled!=0){
        ui->labeCamCtrl->setText("Cam ON");
    }
    else{
        ui->labeCamCtrl->setText("Cam OFF");
    }
    char str[10];
    sprintf(str,"ZR %.1f",static_cast<double>(Cam->ZoomMagnification));
    ui->labeZoomRatio->setText(str);

    Cam->fcber8300->FocusPositionToDistanceAndModeFromContext(str);
    ui->labeFocusPos->setText(str);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SliderYawFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Yw]=static_cast<uint8_t>(value);
    ui->lcdYawFluid->display(value);
}

void Widget::on_SliderPitchFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Pt]=static_cast<uint8_t>(value);
    ui->lcdPitchFluid->display(value);
}

void Widget::on_SliderRollFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Rl]=static_cast<uint8_t>(value);
    ui->lcdRollFluid->display(value);
}

void Widget::on_SliderZoomFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Zm]=static_cast<uint8_t>(value);
    ui->lcdZoomFluid->display(value);
}


void Widget::on_ButRevYaw_pressed()
{
    if(Joystick->State.rev[Joystick->Yw]==0) Joystick->State.rev[Joystick->Yw]=0xff;
    else Joystick->State.rev[Joystick->Yw]=0;
}

void Widget::on_ButRevPitch_pressed()
{
    if(Joystick->State.rev[Joystick->Pt]==0) Joystick->State.rev[Joystick->Pt]=0xff;
    else Joystick->State.rev[Joystick->Pt]=0;
}

void Widget::on_ButRevRoll_pressed()
{
    if(Joystick->State.rev[Joystick->Rl]==0) Joystick->State.rev[Joystick->Rl]=0xff;
    else Joystick->State.rev[Joystick->Rl]=0;
}

void Widget::on_ButRevZoom_pressed()
{
    if(Joystick->State.rev[Joystick->Zm]==0) Joystick->State.rev[Joystick->Zm]=0xff;
    else Joystick->State.rev[Joystick->Zm]=0;
}

void Widget::on_SliderYawSpeed_valueChanged(int value)
{
    Joystick->State.volume[Joystick->Yw]=value;
    ui->lcdYawSpeed->display(value);
}

void Widget::on_SliderPitchSpeed_valueChanged(int value)
{
    Joystick->State.volume[Joystick->Pt]=value;
    ui->lcdPitchSpeed->display(value);
}

void Widget::on_SliderRollSpeed_valueChanged(int value)
{
    Joystick->State.volume[Joystick->Rl]=value;
    ui->lcdRollSpeed->display(value);
}

void Widget::on_SliderZoomSpeed_valueChanged(int value)
{
    Joystick->State.volume[Joystick->Zm]=value;
    ui->lcdZoomSpeed->display(value);
}

void Widget::on_ButRevFocusSpeed_pressed()
{
    if(Joystick->State.rev[Joystick->FS]==0) Joystick->State.rev[Joystick->FS]=0xff;
    else Joystick->State.rev[Joystick->FS]=0;
}

void Widget::on_ButRevFocusPosition_pressed()
{
    if(Joystick->State.rev[Joystick->FP]==0) Joystick->State.rev[Joystick->FP]=0xff;
    else Joystick->State.rev[Joystick->FP]=0;
}

void Widget::on_SliderFocusSPSpeed_valueChanged(int value)
{
    Joystick->State.volume[Joystick->FS]=value;
    ui->lcdFocusSpeed->display(value);
}

void Widget::on_SliderFocusPosVolume_valueChanged(int value)
{
    Joystick->State.volume[Joystick->FP]=value;
    ui->lcdFocusPosVolume->display(value);
}

//void Widget::on_tabOFSET_tabBarClicked(int index){}
void Widget::on_SliderYawOffset_sliderReleased(){}
void Widget::on_SliderPitchOffset_sliderReleased(){}

void Widget::on_SliderYawOffset_valueChanged(int value)
{
    Joystick->State.offset[Joystick->Yw]=value;
    ui->lcdYawOffset->display(value);
}

void Widget::on_SliderPitchOffset_valueChanged(int value)
{
    Joystick->State.offset[Joystick->Pt]=value;
    ui->lcdPitchOffset->display(value);
}

void Widget::on_SliderRollOffset_valueChanged(int value)
{
    Joystick->State.offset[Joystick->Rl]=value;
    ui->lcdRollOffset->display(value);
}

void Widget::on_SliderZoomOffset_valueChanged(int value)
{
    Joystick->State.offset[Joystick->Zm]=value;
    ui->lcdZoomOffset->display(value);
}

void Widget::on_tabBar_currentChanged(int index)
{
    ui->SliderYawOffset->setValue(static_cast<int>(Joystick->State.offset[Joystick->Yw]));
    ui->lcdYawOffset->display(ui->SliderYawOffset->value());
    ui->SliderRollOffset->setValue(static_cast<int>(Joystick->State.offset[Joystick->Rl]));
    ui->lcdRollOffset->display(ui->SliderRollOffset->value());
    ui->SliderPitchOffset->setValue(static_cast<int>(Joystick->State.offset[Joystick->Pt]));
    ui->lcdPitchOffset->display(ui->SliderPitchOffset->value());
    ui->SliderZoomOffset->setValue(static_cast<int>(Joystick->State.offset[Joystick->Zm]));
    ui->lcdZoomOffset->display(ui->SliderZoomOffset->value());

    ui->SliderYawSpeed->setValue(static_cast<int>(Joystick->State.volume[Joystick->Yw]));
    ui->lcdYawSpeed->display(ui->SliderYawSpeed->value());
    ui->SliderRollSpeed->setValue(static_cast<int>(Joystick->State.volume[Joystick->Rl]));
    ui->lcdRollSpeed->display(ui->SliderRollSpeed->value());
    ui->SliderPitchSpeed->setValue(static_cast<int>(Joystick->State.volume[Joystick->Pt]));
    ui->lcdPitchSpeed->display(ui->SliderPitchSpeed->value());
    ui->SliderZoomSpeed->setValue(static_cast<int>(Joystick->State.volume[Joystick->Zm]));
    ui->lcdZoomSpeed->display(ui->SliderZoomSpeed->value());

    ui->SliderYawFluid->setValue(static_cast<int>(Joystick->State.FilterKoef[Joystick->Yw]));
    ui->lcdYawFluid->display(ui->SliderYawFluid->value());
    ui->SliderRollFluid->setValue(static_cast<int>(Joystick->State.FilterKoef[Joystick->Rl]));
    ui->lcdRollFluid->display(ui->SliderRollFluid->value());
    ui->SliderPitchFluid->setValue(static_cast<int>(Joystick->State.FilterKoef[Joystick->Pt]));
    ui->lcdPitchFluid->display(ui->SliderPitchFluid->value());
    ui->SliderZoomFluid->setValue(static_cast<int>(Joystick->State.FilterKoef[Joystick->Zm]));
    ui->lcdZoomFluid->display(ui->SliderZoomFluid->value());
    index = index-1;
}

void Widget::on_ButFocusAuto_pressed()
{

    Cam->fcber8300->Camera.command = FocusAuto;//Focus Auto
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
    Cam->fcber8300->Context.FocusMode = Cam->fcber8300->FocusModeTable.Value[0];
}
void Widget::on_ButFocusManual_pressed()
{
     Cam->fcber8300->Camera.command = FocusManual;//Focus manual
     if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
     Cam->fcber8300->Context.FocusMode = Cam->fcber8300->FocusModeTable.Value[1];
}

void Widget::on_ButFocusOneToutch_pressed()
{
    Cam->fcber8300->Camera.command = FocusOnePushTrigger;//Focus One Push
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
}

void Widget::on_ButDzoomOn_clicked()
{
    Cam->fcber8300->Camera.command = DzoomOn;//DZoom on
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
    Cam->fcber8300->Context.DZoomMode = Cam->fcber8300->DZoomModeTable.Value[2];//Digital zoom on
}

void Widget::on_ButDzoomOff_clicked()
{
    Cam->fcber8300->Camera.command = DzoomOff;//DZoom off
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
    Cam->fcber8300->Context.DZoomMode = Cam->fcber8300->DZoomModeTable.Value[3];//Digital zoom off
}

void Widget::on_ButDzoomSeparate_clicked()
{
    Cam->fcber8300->Camera.command = DzoomSeparate;//Digital zoom separate
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
    Cam->fcber8300->Context.DZoomMode = Cam->fcber8300->DZoomModeTable.Value[1];
}

void Widget::on_ButDzoomCombine_clicked()
{

    Cam->fcber8300->Camera.command = DzoomCombine;//Digital zoom combine mode
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
    Cam->fcber8300->Context.DZoomMode = Cam->fcber8300->DZoomModeTable.Value[0];
}

void Widget::on_SliderDigitalZoom_valueChanged(int value)
{
    if(Cam->fcber8300->Context.DZoomMode != Cam->fcber8300->DZoomModeTable.Value[3] ){ //If Dzoom  is not Off
        Cam->fcber8300->Camera.value = static_cast<int16_t>(value);
        Cam->fcber8300->Camera.command = DzoomDirect;    //Digital zoom direct
        if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
        Cam->fcber8300->Context.DZoom=static_cast<uint8_t>(value);
    }
}

void Widget::on_ButEnCamCtrl_clicked()
{
    Cam->CamCtrlEnabled=1;
}

void Widget::on_ButDisCamCtrl_clicked()
{
    Cam->CamCtrlEnabled=0;
}


void Widget::on_ButEnGimbalCtrl_clicked()
{
    BGC->GimbalCtrlEnabled = 1;
}

void Widget::on_ButDisGimbalCtrl_clicked()
{
    BGC->GimbalCtrlEnabled = 0;
}

void Widget::on_ButCalibrateJoysticks_clicked()
{
    Joystick->CalibrateZeros();
}

void Widget::on_SliderZoomComp_valueChanged(int value)
{
    BGC->ZoomCompensationGain=(static_cast<float>(value))/100.0f;
    if(value<=1)ui->labeZoomComp->setText("ZC OFF");
    else ui->labeZoomComp->setText("ZC On");
}

void Widget::on_tabBar_tabBarClicked(int index)
{
    switch(index)
    {
    case 0:{// Speed tab

    }break;
    case 1:{//Fluid tab

    }break;
    case 2:{//Offset tab

    }break;
    case 3:{//Zoom tab

    }break;
    case 4:{//Focus tab

    }break;
    case 5:{//Raw nab

    }break;
    case 6:{//color tab
        ui->comboBoxWB->setCurrentIndex( Cam->fcber8300->Context.WBmode);
    }break;
    case 7:{//Exposure tab

    }break;
    default: break;
    }
}


void Widget::on_comboBoxWB_currentIndexChanged(int index)
{
    switch(index){
    case 0:Cam->fcber8300->Camera.command = WbAuto;break;
    case 1:Cam->fcber8300->Camera.command = WbIndoor;break;
    case 2:Cam->fcber8300->Camera.command = WbOutdoor;break;
    case 3:Cam->fcber8300->Camera.command = WbOnePush;break;
    case 4:Cam->fcber8300->Camera.command = WbAtw;break;
    case 5:Cam->fcber8300->Camera.command = WbManual;break;
    case 6:Cam->fcber8300->Camera.command = WbOutdoorAuto;break;
    case 7:Cam->fcber8300->Camera.command = WbsodiumLampAuto;break;
    case 9:Cam->fcber8300->Camera.command = WbsodiumLamp;break;
    case 10:Cam->fcber8300->Camera.command= WbsodiumLampOutdoorAuto;break;
    default: printf("UI ERROR : Bed WB Index %i \r\n",index);return;
    }
    if(Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera)<0)return;
    Cam->fcber8300->Context.WBmode = index & 0xff;
}

void Widget::on_ButWBonePushTrigger_clicked()
{
    Cam->fcber8300->Camera.command = WbOnePushTrigger;
    Cam->CbCommadSemndWrespond(&Cam->fcber8300->Camera);
}

void Widget::on_comboBoxColorBar_currentIndexChanged(int index)
{
    switch(index){
    case 0:break;
    case 1:break;
    case 2:break;
    case 3:break;
    default: printf("UI ERROR : Bed Color Bar  Index %i \r\n",index);return;

    }
}


