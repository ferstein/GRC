#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void get_joystick_raw_data(void);
    void BgcProcess(void);
    void CameraProcess(void);
    void on_SliderYawFluid_valueChanged(int value);
    void on_SliderPitchFluid_valueChanged(int value);
    void on_SliderRollFluid_valueChanged(int value);
    void on_SliderZoomFluid_valueChanged(int value);

    void on_ButRevYaw_pressed();

    void on_ButRevPitch_pressed();

    void on_ButRevRoll_pressed();

    void on_ButRevZoom_pressed();

    void on_SliderYawSpeed_valueChanged(int value);

    void on_SliderPitchSpeed_valueChanged(int value);

    void on_SliderRollSpeed_valueChanged(int value);

    void on_SliderZoomSpeed_valueChanged(int value);

    void on_ButRevFocusSpeed_pressed();

    void on_ButRevFocusPosition_pressed();

    void on_SliderFocusSPSpeed_valueChanged(int value);

    void on_SliderFocusPosVolume_valueChanged(int value);

    void on_SliderYawOffset_sliderReleased();

    void on_SliderPitchOffset_sliderReleased();

    void on_SliderYawOffset_valueChanged(int value);

    void on_SliderPitchOffset_valueChanged(int value);

    void on_SliderRollOffset_valueChanged(int value);

    void on_SliderZoomOffset_valueChanged(int value);

    void on_tabBar_currentChanged(int index);

    void on_ButFocusAuto_pressed();

    void on_ButFocusManual_pressed();

    void on_ButFocusOneToutch_pressed();

    void on_ButDzoomOn_clicked();

    void on_ButDzoomOff_clicked();

    void on_ButDzoomSeparate_clicked();

    void on_ButDzoomCombine_clicked();

    void on_SliderDigitalZoom_valueChanged(int value);

    void on_ButEnCamCtrl_clicked();

    void on_ButDisCamCtrl_clicked();

    void on_ButEnGimbalCtrl_clicked();

    void on_ButDisGimbalCtrl_clicked();

    void on_ButCalibrateJoysticks_clicked();

    void on_SliderZoomComp_valueChanged(int value);

private:
    Ui::Widget *ui;
    QTimer JoyTimer;
    QTimer BgcTimer;
    QTimer CameraTimer;
};

#endif // WIDGET_H
