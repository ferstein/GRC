#include "widget.h"
#include "ui_widget.h"
#include <string.h>
#include "analogJoystick.h"
#include "gimbalcontrol.h"
#include "camera.h"

AnalogJoystick *Joystick;
GimbalControl *BGC;
Camera *Cam;

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
    Cam = new Camera;

    connect(&this->JoyTimer,SIGNAL(timeout()),this,SLOT(get_joystick_raw_data()));
    this->JoyTimer.start(2);

    connect(&this->BgcTimer,SIGNAL(timeout()),this,SLOT(BgcProcess()));
    this->BgcTimer.start(16);

    connect(&this->CameraTimer,SIGNAL(timeout()),this,SLOT(CameraProcess()));
    this->CameraTimer.start(16);
}
void Widget::get_joystick_raw_data(void)
{
    Joystick->Process();

    if(ui->tab_raw->isActiveWindow())
    {
        ui->lcd0_0->display((int)Joystick->State.Out[0]);
        ui->lcd0_1->display((int)Joystick->State.Out[1]);
        ui->lcd0_2->display((int)Joystick->State.Out[2]);
        ui->lcd0_3->display((int)Joystick->State.Out[3]);
        ui->lcd0_4->display((int)Joystick->State.Out[4]);
        ui->lcd0_5->display((int)Joystick->State.Out[5]);
    }
}

void Widget::BgcProcess(void)
{   BGC->ZoomCompensation = 1+(Cam->ZoomMagnification-1)*BGC->ZoomCompensationGain*1.2f;

    //printf("Zoom Compensation is %.3f \n",BGC->ZoomCompensation);

    BGC->ctrl.CONTROL_MODE=SPEED;
    BGC->ctrl.SPEED_YAW  =(Joystick->State.Out[Joystick->Yw]/BGC->ZoomCompensation)+
            Joystick->State.offset[Joystick->Yw];
    BGC->ctrl.SPEED_PITCH=(Joystick->State.Out[Joystick->Pt]/BGC->ZoomCompensation)+
            Joystick->State.offset[Joystick->Pt];
    BGC->ctrl.SPEED_ROLL =(Joystick->State.Out[Joystick->Rl] + Joystick->State.offset[Joystick->Rl]);

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
    Cam->ZoomJoy     = (Joystick->State.Out[Joystick->Zm]+Joystick->State.offset[Joystick->Zm]); //LEFT Y  raw[1]
    Cam->FocusPosJoy = (Joystick->State.Out[Joystick->FP]); //LEFT Z  raw[2]
    Cam->FocusSpeedJoy=(Joystick->State.Out[Joystick->FS]); //RIGHT Z raw[5]
    Cam->process();

    if(Cam->CamCtrlEnabled!=0){
        ui->labeCamCtrl->setText("Cam ON");
    }
    else{
        ui->labeCamCtrl->setText("Cam OFF");
    }
    char str[10];
    sprintf(str,"ZR %.1f",Cam->ZoomMagnification);
    ui->labeZoomRatio->setText(str);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SliderYawFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Yw]=value;
    ui->lcdYawFluid->display(value);
}

void Widget::on_SliderPitchFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Pt]=value;
    ui->lcdPitchFluid->display(value);
}

void Widget::on_SliderRollFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Rl]=value;
    ui->lcdRollFluid->display(value);
}

void Widget::on_SliderZoomFluid_valueChanged(int value)
{
    Joystick->State.FilterKoef[Joystick->Zm]=value;
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
    ui->SliderYawOffset->setValue(Joystick->State.offset[Joystick->Yw]);
    ui->lcdYawOffset->display(ui->SliderYawOffset->value());
    ui->SliderRollOffset->setValue(Joystick->State.offset[Joystick->Rl]);
    ui->lcdRollOffset->display(ui->SliderRollOffset->value());
    ui->SliderPitchOffset->setValue(Joystick->State.offset[Joystick->Pt]);
    ui->lcdPitchOffset->display(ui->SliderPitchOffset->value());
    ui->SliderZoomOffset->setValue(Joystick->State.offset[Joystick->Zm]);
    ui->lcdZoomOffset->display(ui->SliderZoomOffset->value());

    ui->SliderYawSpeed->setValue(Joystick->State.volume[Joystick->Yw]);
    ui->lcdYawSpeed->display(ui->SliderYawSpeed->value());
    ui->SliderRollSpeed->setValue(Joystick->State.volume[Joystick->Rl]);
    ui->lcdRollSpeed->display(ui->SliderRollSpeed->value());
    ui->SliderPitchSpeed->setValue(Joystick->State.volume[Joystick->Pt]);
    ui->lcdPitchSpeed->display(ui->SliderPitchSpeed->value());
    ui->SliderZoomSpeed->setValue(Joystick->State.volume[Joystick->Zm]);
    ui->lcdZoomSpeed->display(ui->SliderZoomSpeed->value());

    ui->SliderYawFluid->setValue(Joystick->State.FilterKoef[Joystick->Yw]);
    ui->lcdYawFluid->display(ui->SliderYawFluid->value());
    ui->SliderRollFluid->setValue(Joystick->State.FilterKoef[Joystick->Rl]);
    ui->lcdRollFluid->display(ui->SliderRollFluid->value());
    ui->SliderPitchFluid->setValue(Joystick->State.FilterKoef[Joystick->Pt]);
    ui->lcdPitchFluid->display(ui->SliderPitchFluid->value());
    ui->SliderZoomFluid->setValue(Joystick->State.FilterKoef[Joystick->Zm]);
    ui->lcdZoomFluid->display(ui->SliderZoomFluid->value());
    index = index-1;
}

void Widget::on_ButFocusAuto_pressed()
{
    Cam->CommandSelector = 3;//Focus Auto
}


void Widget::on_ButFocusManual_pressed()
{
    Cam->CommandSelector = 2;//Focus manual
}

void Widget::on_ButFocusOneToutch_pressed()
{
    Cam->CommandSelector = 4;//Focus One Push;
}

void Widget::on_ButDzoomOn_clicked()
{
    Cam->CommandSelector = 5;    //Digital zoom on
}

void Widget::on_ButDzoomOff_clicked()
{
    Cam->CommandSelector = 6;    //Digital zoom off
}

void Widget::on_ButDzoomSeparate_clicked()
{
    Cam->CommandSelector = 7;    //Digital zoom separate
}

void Widget::on_ButDzoomCombine_clicked()
{
    Cam->CommandSelector = 8;    //Digital zoom combine mode
}

void Widget::on_SliderDigitalZoom_valueChanged(int value)
{
    Cam->DigitalZoomValue = value;
    Cam->CommandSelector = 9;    //Digital zoom direct
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
    BGC->ZoomCompensationGain=((float)(value))/100.0f;
    if(value<=1)ui->labeZoomComp->setText("ZC OFF");
    else ui->labeZoomComp->setText("ZC On");
}
