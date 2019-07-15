/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabBar;
    QWidget *tabSpeed;
    QSlider *SliderYawSpeed;
    QSlider *SliderZoomSpeed;
    QSlider *SliderPitchSpeed;
    QSlider *SliderRollSpeed;
    QPushButton *ButRevYaw;
    QLCDNumber *lcdYawSpeed;
    QLCDNumber *lcdPitchSpeed;
    QLCDNumber *lcdRollSpeed;
    QLCDNumber *lcdZoomSpeed;
    QPushButton *ButRevPitch;
    QPushButton *ButRevRoll;
    QPushButton *ButRevZoom;
    QWidget *tabFluid;
    QSlider *SliderZoomFluid;
    QLCDNumber *lcdPitchFluid;
    QSlider *SliderYawFluid;
    QLCDNumber *lcdRollFluid;
    QSlider *SliderRollFluid;
    QSlider *SliderPitchFluid;
    QLCDNumber *lcdZoomFluid;
    QLCDNumber *lcdYawFluid;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *tabOfset;
    QSlider *SliderYawOffset;
    QLabel *label_19;
    QLabel *label_20;
    QLCDNumber *lcdYawOffset;
    QLabel *label_18;
    QLabel *label_17;
    QSlider *SliderRollOffset;
    QLCDNumber *lcdZoomOffset;
    QLCDNumber *lcdRollOffset;
    QSlider *SliderZoomOffset;
    QLCDNumber *lcdPitchOffset;
    QSlider *SliderPitchOffset;
    QWidget *tabZoom;
    QPushButton *ButDzoomOn;
    QPushButton *ButDzoomOff;
    QPushButton *ButDzoomCombine;
    QPushButton *ButDzoomSeparate;
    QSlider *SliderDigitalZoom;
    QSlider *SliderZoomComp;
    QLabel *label_21;
    QLabel *label_22;
    QWidget *tabFocus;
    QSlider *SliderFocusSPSpeed;
    QSlider *SliderFocusPosVolume;
    QPushButton *ButRevFocusSpeed;
    QPushButton *ButRevFocusPosition;
    QLCDNumber *lcdFocusSpeed;
    QLCDNumber *lcdFocusPosVolume;
    QPushButton *ButFocusAuto;
    QPushButton *ButFocusManual;
    QPushButton *ButFocusOneToutch;
    QWidget *tab_raw;
    QLCDNumber *lcd0_4;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *lcd0_3;
    QLCDNumber *lcd0_2;
    QLabel *label_3;
    QLCDNumber *lcd0_5;
    QLabel *label_4;
    QLabel *label_5;
    QLCDNumber *lcd0_0;
    QLCDNumber *lcd0_1;
    QLabel *label_6;
    QPushButton *ButEnCamCtrl;
    QPushButton *ButDisCamCtrl;
    QPushButton *ButEnGimbalCtrl;
    QPushButton *ButDisGimbalCtrl;
    QPushButton *ButCalibrateJoysticks;
    QLabel *labeCamCtrl;
    QLabel *labeGimbCtrl;
    QLabel *labeZoomComp;
    QLabel *labeZoomRatio;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(800, 480));
        Widget->setMaximumSize(QSize(800, 480));
        Widget->setBaseSize(QSize(800, 480));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(85, 85, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        Widget->setPalette(palette);
        Widget->setCursor(QCursor(Qt::BlankCursor));
        tabBar = new QTabWidget(Widget);
        tabBar->setObjectName(QStringLiteral("tabBar"));
        tabBar->setGeometry(QRect(3, 3, 794, 434));
        sizePolicy.setHeightForWidth(tabBar->sizePolicy().hasHeightForWidth());
        tabBar->setSizePolicy(sizePolicy);
        tabBar->setMinimumSize(QSize(794, 434));
        tabBar->setMaximumSize(QSize(794, 474));
        tabBar->setBaseSize(QSize(794, 474));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush2(QColor(85, 0, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        QBrush brush3(QColor(128, 0, 191, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush3);
        QBrush brush4(QColor(106, 0, 159, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush4);
        QBrush brush5(QColor(42, 0, 63, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush5);
        QBrush brush6(QColor(56, 0, 84, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush5);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
        tabBar->setPalette(palette1);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        tabBar->setFont(font);
        tabBar->setCursor(QCursor(Qt::BlankCursor));
        tabSpeed = new QWidget();
        tabSpeed->setObjectName(QStringLiteral("tabSpeed"));
        SliderYawSpeed = new QSlider(tabSpeed);
        SliderYawSpeed->setObjectName(QStringLiteral("SliderYawSpeed"));
        SliderYawSpeed->setGeometry(QRect(330, 10, 421, 81));
        SliderYawSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderYawSpeed->setMinimum(0);
        SliderYawSpeed->setMaximum(100);
        SliderYawSpeed->setValue(90);
        SliderYawSpeed->setOrientation(Qt::Horizontal);
        SliderZoomSpeed = new QSlider(tabSpeed);
        SliderZoomSpeed->setObjectName(QStringLiteral("SliderZoomSpeed"));
        SliderZoomSpeed->setGeometry(QRect(330, 310, 421, 81));
        SliderZoomSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderZoomSpeed->setMaximum(100);
        SliderZoomSpeed->setValue(90);
        SliderZoomSpeed->setOrientation(Qt::Horizontal);
        SliderPitchSpeed = new QSlider(tabSpeed);
        SliderPitchSpeed->setObjectName(QStringLiteral("SliderPitchSpeed"));
        SliderPitchSpeed->setGeometry(QRect(330, 110, 421, 81));
        SliderPitchSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderPitchSpeed->setMaximum(100);
        SliderPitchSpeed->setValue(90);
        SliderPitchSpeed->setOrientation(Qt::Horizontal);
        SliderRollSpeed = new QSlider(tabSpeed);
        SliderRollSpeed->setObjectName(QStringLiteral("SliderRollSpeed"));
        SliderRollSpeed->setGeometry(QRect(330, 210, 421, 81));
        SliderRollSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderRollSpeed->setMaximum(100);
        SliderRollSpeed->setValue(90);
        SliderRollSpeed->setSliderPosition(90);
        SliderRollSpeed->setTracking(false);
        SliderRollSpeed->setOrientation(Qt::Horizontal);
        SliderRollSpeed->setInvertedControls(false);
        SliderRollSpeed->setTickPosition(QSlider::TicksBelow);
        SliderRollSpeed->setTickInterval(14);
        ButRevYaw = new QPushButton(tabSpeed);
        ButRevYaw->setObjectName(QStringLiteral("ButRevYaw"));
        ButRevYaw->setGeometry(QRect(10, 30, 181, 61));
        lcdYawSpeed = new QLCDNumber(tabSpeed);
        lcdYawSpeed->setObjectName(QStringLiteral("lcdYawSpeed"));
        lcdYawSpeed->setGeometry(QRect(220, 30, 81, 61));
        lcdPitchSpeed = new QLCDNumber(tabSpeed);
        lcdPitchSpeed->setObjectName(QStringLiteral("lcdPitchSpeed"));
        lcdPitchSpeed->setGeometry(QRect(220, 120, 81, 61));
        lcdRollSpeed = new QLCDNumber(tabSpeed);
        lcdRollSpeed->setObjectName(QStringLiteral("lcdRollSpeed"));
        lcdRollSpeed->setGeometry(QRect(220, 220, 81, 61));
        lcdZoomSpeed = new QLCDNumber(tabSpeed);
        lcdZoomSpeed->setObjectName(QStringLiteral("lcdZoomSpeed"));
        lcdZoomSpeed->setGeometry(QRect(220, 320, 81, 61));
        ButRevPitch = new QPushButton(tabSpeed);
        ButRevPitch->setObjectName(QStringLiteral("ButRevPitch"));
        ButRevPitch->setGeometry(QRect(10, 120, 181, 61));
        ButRevRoll = new QPushButton(tabSpeed);
        ButRevRoll->setObjectName(QStringLiteral("ButRevRoll"));
        ButRevRoll->setGeometry(QRect(10, 220, 181, 61));
        ButRevZoom = new QPushButton(tabSpeed);
        ButRevZoom->setObjectName(QStringLiteral("ButRevZoom"));
        ButRevZoom->setGeometry(QRect(10, 310, 181, 61));
        tabBar->addTab(tabSpeed, QString());
        tabFluid = new QWidget();
        tabFluid->setObjectName(QStringLiteral("tabFluid"));
        SliderZoomFluid = new QSlider(tabFluid);
        SliderZoomFluid->setObjectName(QStringLiteral("SliderZoomFluid"));
        SliderZoomFluid->setGeometry(QRect(330, 310, 421, 81));
        SliderZoomFluid->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderZoomFluid->setMinimum(1);
        SliderZoomFluid->setMaximum(99);
        SliderZoomFluid->setPageStep(6);
        SliderZoomFluid->setValue(50);
        SliderZoomFluid->setOrientation(Qt::Horizontal);
        lcdPitchFluid = new QLCDNumber(tabFluid);
        lcdPitchFluid->setObjectName(QStringLiteral("lcdPitchFluid"));
        lcdPitchFluid->setGeometry(QRect(220, 120, 81, 61));
        SliderYawFluid = new QSlider(tabFluid);
        SliderYawFluid->setObjectName(QStringLiteral("SliderYawFluid"));
        SliderYawFluid->setGeometry(QRect(330, 10, 421, 81));
        SliderYawFluid->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderYawFluid->setMinimum(1);
        SliderYawFluid->setMaximum(99);
        SliderYawFluid->setSingleStep(1);
        SliderYawFluid->setPageStep(6);
        SliderYawFluid->setValue(50);
        SliderYawFluid->setOrientation(Qt::Horizontal);
        lcdRollFluid = new QLCDNumber(tabFluid);
        lcdRollFluid->setObjectName(QStringLiteral("lcdRollFluid"));
        lcdRollFluid->setGeometry(QRect(220, 220, 81, 61));
        SliderRollFluid = new QSlider(tabFluid);
        SliderRollFluid->setObjectName(QStringLiteral("SliderRollFluid"));
        SliderRollFluid->setGeometry(QRect(330, 210, 421, 81));
        SliderRollFluid->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderRollFluid->setMinimum(1);
        SliderRollFluid->setMaximum(99);
        SliderRollFluid->setPageStep(5);
        SliderRollFluid->setValue(50);
        SliderRollFluid->setSliderPosition(50);
        SliderRollFluid->setTracking(false);
        SliderRollFluid->setOrientation(Qt::Horizontal);
        SliderRollFluid->setInvertedControls(false);
        SliderRollFluid->setTickPosition(QSlider::TicksBelow);
        SliderRollFluid->setTickInterval(14);
        SliderPitchFluid = new QSlider(tabFluid);
        SliderPitchFluid->setObjectName(QStringLiteral("SliderPitchFluid"));
        SliderPitchFluid->setGeometry(QRect(330, 110, 421, 81));
        SliderPitchFluid->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderPitchFluid->setMinimum(1);
        SliderPitchFluid->setMaximum(99);
        SliderPitchFluid->setPageStep(6);
        SliderPitchFluid->setValue(50);
        SliderPitchFluid->setTracking(true);
        SliderPitchFluid->setOrientation(Qt::Horizontal);
        lcdZoomFluid = new QLCDNumber(tabFluid);
        lcdZoomFluid->setObjectName(QStringLiteral("lcdZoomFluid"));
        lcdZoomFluid->setGeometry(QRect(220, 320, 81, 61));
        lcdYawFluid = new QLCDNumber(tabFluid);
        lcdYawFluid->setObjectName(QStringLiteral("lcdYawFluid"));
        lcdYawFluid->setGeometry(QRect(221, 20, 81, 61));
        label_13 = new QLabel(tabFluid);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(50, 20, 131, 61));
        label_14 = new QLabel(tabFluid);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(50, 120, 131, 61));
        label_15 = new QLabel(tabFluid);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(50, 210, 131, 61));
        label_16 = new QLabel(tabFluid);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(40, 310, 131, 61));
        tabBar->addTab(tabFluid, QString());
        tabOfset = new QWidget();
        tabOfset->setObjectName(QStringLiteral("tabOfset"));
        SliderYawOffset = new QSlider(tabOfset);
        SliderYawOffset->setObjectName(QStringLiteral("SliderYawOffset"));
        SliderYawOffset->setGeometry(QRect(310, 10, 421, 81));
        SliderYawOffset->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderYawOffset->setMinimum(-99);
        SliderYawOffset->setMaximum(99);
        SliderYawOffset->setSingleStep(1);
        SliderYawOffset->setPageStep(1);
        SliderYawOffset->setValue(0);
        SliderYawOffset->setOrientation(Qt::Horizontal);
        label_19 = new QLabel(tabOfset);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(30, 320, 141, 61));
        label_20 = new QLabel(tabOfset);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(30, 220, 131, 61));
        lcdYawOffset = new QLCDNumber(tabOfset);
        lcdYawOffset->setObjectName(QStringLiteral("lcdYawOffset"));
        lcdYawOffset->setGeometry(QRect(201, 20, 81, 61));
        label_18 = new QLabel(tabOfset);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(30, 20, 131, 61));
        label_17 = new QLabel(tabOfset);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(30, 120, 151, 61));
        SliderRollOffset = new QSlider(tabOfset);
        SliderRollOffset->setObjectName(QStringLiteral("SliderRollOffset"));
        SliderRollOffset->setGeometry(QRect(310, 210, 421, 81));
        SliderRollOffset->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderRollOffset->setMinimum(-99);
        SliderRollOffset->setMaximum(99);
        SliderRollOffset->setPageStep(1);
        SliderRollOffset->setValue(0);
        SliderRollOffset->setSliderPosition(0);
        SliderRollOffset->setTracking(false);
        SliderRollOffset->setOrientation(Qt::Horizontal);
        SliderRollOffset->setInvertedControls(false);
        SliderRollOffset->setTickPosition(QSlider::TicksBelow);
        SliderRollOffset->setTickInterval(14);
        lcdZoomOffset = new QLCDNumber(tabOfset);
        lcdZoomOffset->setObjectName(QStringLiteral("lcdZoomOffset"));
        lcdZoomOffset->setGeometry(QRect(200, 320, 81, 61));
        lcdRollOffset = new QLCDNumber(tabOfset);
        lcdRollOffset->setObjectName(QStringLiteral("lcdRollOffset"));
        lcdRollOffset->setGeometry(QRect(200, 220, 81, 61));
        SliderZoomOffset = new QSlider(tabOfset);
        SliderZoomOffset->setObjectName(QStringLiteral("SliderZoomOffset"));
        SliderZoomOffset->setGeometry(QRect(310, 310, 421, 81));
        SliderZoomOffset->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderZoomOffset->setMinimum(-99);
        SliderZoomOffset->setMaximum(99);
        SliderZoomOffset->setPageStep(1);
        SliderZoomOffset->setValue(0);
        SliderZoomOffset->setOrientation(Qt::Horizontal);
        lcdPitchOffset = new QLCDNumber(tabOfset);
        lcdPitchOffset->setObjectName(QStringLiteral("lcdPitchOffset"));
        lcdPitchOffset->setGeometry(QRect(200, 120, 81, 61));
        SliderPitchOffset = new QSlider(tabOfset);
        SliderPitchOffset->setObjectName(QStringLiteral("SliderPitchOffset"));
        SliderPitchOffset->setGeometry(QRect(310, 110, 421, 81));
        SliderPitchOffset->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderPitchOffset->setMinimum(-99);
        SliderPitchOffset->setMaximum(99);
        SliderPitchOffset->setPageStep(1);
        SliderPitchOffset->setValue(0);
        SliderPitchOffset->setTracking(true);
        SliderPitchOffset->setOrientation(Qt::Horizontal);
        tabBar->addTab(tabOfset, QString());
        tabZoom = new QWidget();
        tabZoom->setObjectName(QStringLiteral("tabZoom"));
        ButDzoomOn = new QPushButton(tabZoom);
        ButDzoomOn->setObjectName(QStringLiteral("ButDzoomOn"));
        ButDzoomOn->setGeometry(QRect(10, 330, 171, 61));
        ButDzoomOff = new QPushButton(tabZoom);
        ButDzoomOff->setObjectName(QStringLiteral("ButDzoomOff"));
        ButDzoomOff->setGeometry(QRect(200, 330, 181, 61));
        ButDzoomCombine = new QPushButton(tabZoom);
        ButDzoomCombine->setObjectName(QStringLiteral("ButDzoomCombine"));
        ButDzoomCombine->setGeometry(QRect(600, 330, 181, 61));
        ButDzoomSeparate = new QPushButton(tabZoom);
        ButDzoomSeparate->setObjectName(QStringLiteral("ButDzoomSeparate"));
        ButDzoomSeparate->setGeometry(QRect(400, 330, 181, 61));
        SliderDigitalZoom = new QSlider(tabZoom);
        SliderDigitalZoom->setObjectName(QStringLiteral("SliderDigitalZoom"));
        SliderDigitalZoom->setGeometry(QRect(10, 230, 771, 81));
        SliderDigitalZoom->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderDigitalZoom->setMaximum(235);
        SliderDigitalZoom->setSingleStep(1);
        SliderDigitalZoom->setPageStep(10);
        SliderDigitalZoom->setValue(0);
        SliderDigitalZoom->setTracking(true);
        SliderDigitalZoom->setOrientation(Qt::Horizontal);
        SliderZoomComp = new QSlider(tabZoom);
        SliderZoomComp->setObjectName(QStringLiteral("SliderZoomComp"));
        SliderZoomComp->setGeometry(QRect(10, 60, 771, 81));
        SliderZoomComp->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 50px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -10px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderZoomComp->setMaximum(200);
        SliderZoomComp->setSingleStep(1);
        SliderZoomComp->setPageStep(10);
        SliderZoomComp->setValue(100);
        SliderZoomComp->setTracking(true);
        SliderZoomComp->setOrientation(Qt::Horizontal);
        label_21 = new QLabel(tabZoom);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(250, 0, 291, 61));
        label_22 = new QLabel(tabZoom);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(320, 170, 161, 61));
        tabBar->addTab(tabZoom, QString());
        tabFocus = new QWidget();
        tabFocus->setObjectName(QStringLiteral("tabFocus"));
        SliderFocusSPSpeed = new QSlider(tabFocus);
        SliderFocusSPSpeed->setObjectName(QStringLiteral("SliderFocusSPSpeed"));
        SliderFocusSPSpeed->setGeometry(QRect(340, 60, 421, 60));
        SliderFocusSPSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 40px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -5px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderFocusSPSpeed->setMaximum(100);
        SliderFocusSPSpeed->setValue(90);
        SliderFocusSPSpeed->setOrientation(Qt::Horizontal);
        SliderFocusPosVolume = new QSlider(tabFocus);
        SliderFocusPosVolume->setObjectName(QStringLiteral("SliderFocusPosVolume"));
        SliderFocusPosVolume->setGeometry(QRect(340, 170, 421, 60));
        SliderFocusPosVolume->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 40px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 50px;\n"
"    margin: -5px 0 ; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}"));
        SliderFocusPosVolume->setMaximum(100);
        SliderFocusPosVolume->setValue(90);
        SliderFocusPosVolume->setOrientation(Qt::Horizontal);
        ButRevFocusSpeed = new QPushButton(tabFocus);
        ButRevFocusSpeed->setObjectName(QStringLiteral("ButRevFocusSpeed"));
        ButRevFocusSpeed->setGeometry(QRect(30, 60, 181, 61));
        ButRevFocusPosition = new QPushButton(tabFocus);
        ButRevFocusPosition->setObjectName(QStringLiteral("ButRevFocusPosition"));
        ButRevFocusPosition->setGeometry(QRect(30, 170, 181, 61));
        lcdFocusSpeed = new QLCDNumber(tabFocus);
        lcdFocusSpeed->setObjectName(QStringLiteral("lcdFocusSpeed"));
        lcdFocusSpeed->setGeometry(QRect(230, 60, 81, 61));
        lcdFocusPosVolume = new QLCDNumber(tabFocus);
        lcdFocusPosVolume->setObjectName(QStringLiteral("lcdFocusPosVolume"));
        lcdFocusPosVolume->setGeometry(QRect(230, 170, 81, 61));
        ButFocusAuto = new QPushButton(tabFocus);
        ButFocusAuto->setObjectName(QStringLiteral("ButFocusAuto"));
        ButFocusAuto->setGeometry(QRect(30, 280, 181, 61));
        ButFocusManual = new QPushButton(tabFocus);
        ButFocusManual->setObjectName(QStringLiteral("ButFocusManual"));
        ButFocusManual->setGeometry(QRect(310, 280, 181, 61));
        ButFocusOneToutch = new QPushButton(tabFocus);
        ButFocusOneToutch->setObjectName(QStringLiteral("ButFocusOneToutch"));
        ButFocusOneToutch->setGeometry(QRect(580, 280, 181, 61));
        tabBar->addTab(tabFocus, QString());
        tab_raw = new QWidget();
        tab_raw->setObjectName(QStringLiteral("tab_raw"));
        lcd0_4 = new QLCDNumber(tab_raw);
        lcd0_4->setObjectName(QStringLiteral("lcd0_4"));
        lcd0_4->setGeometry(QRect(650, 120, 140, 80));
        label = new QLabel(tab_raw);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 0, 81, 20));
        label_2 = new QLabel(tab_raw);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 100, 81, 20));
        lcd0_3 = new QLCDNumber(tab_raw);
        lcd0_3->setObjectName(QStringLiteral("lcd0_3"));
        lcd0_3->setGeometry(QRect(650, 20, 140, 80));
        lcd0_2 = new QLCDNumber(tab_raw);
        lcd0_2->setObjectName(QStringLiteral("lcd0_2"));
        lcd0_2->setGeometry(QRect(10, 220, 140, 80));
        label_3 = new QLabel(tab_raw);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 200, 81, 20));
        lcd0_5 = new QLCDNumber(tab_raw);
        lcd0_5->setObjectName(QStringLiteral("lcd0_5"));
        lcd0_5->setGeometry(QRect(650, 220, 140, 80));
        label_4 = new QLabel(tab_raw);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(680, 0, 91, 20));
        label_5 = new QLabel(tab_raw);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(680, 100, 91, 20));
        lcd0_0 = new QLCDNumber(tab_raw);
        lcd0_0->setObjectName(QStringLiteral("lcd0_0"));
        lcd0_0->setGeometry(QRect(10, 20, 140, 80));
        lcd0_1 = new QLCDNumber(tab_raw);
        lcd0_1->setObjectName(QStringLiteral("lcd0_1"));
        lcd0_1->setGeometry(QRect(10, 120, 140, 80));
        label_6 = new QLabel(tab_raw);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(680, 200, 91, 20));
        ButEnCamCtrl = new QPushButton(tab_raw);
        ButEnCamCtrl->setObjectName(QStringLiteral("ButEnCamCtrl"));
        ButEnCamCtrl->setGeometry(QRect(170, 30, 171, 61));
        ButDisCamCtrl = new QPushButton(tab_raw);
        ButDisCamCtrl->setObjectName(QStringLiteral("ButDisCamCtrl"));
        ButDisCamCtrl->setGeometry(QRect(460, 30, 171, 61));
        ButEnGimbalCtrl = new QPushButton(tab_raw);
        ButEnGimbalCtrl->setObjectName(QStringLiteral("ButEnGimbalCtrl"));
        ButEnGimbalCtrl->setGeometry(QRect(170, 110, 171, 61));
        ButDisGimbalCtrl = new QPushButton(tab_raw);
        ButDisGimbalCtrl->setObjectName(QStringLiteral("ButDisGimbalCtrl"));
        ButDisGimbalCtrl->setGeometry(QRect(460, 110, 171, 61));
        ButCalibrateJoysticks = new QPushButton(tab_raw);
        ButCalibrateJoysticks->setObjectName(QStringLiteral("ButCalibrateJoysticks"));
        ButCalibrateJoysticks->setGeometry(QRect(310, 330, 171, 61));
        tabBar->addTab(tab_raw, QString());
        labeCamCtrl = new QLabel(Widget);
        labeCamCtrl->setObjectName(QStringLiteral("labeCamCtrl"));
        labeCamCtrl->setGeometry(QRect(10, 443, 81, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush9(QColor(106, 104, 100, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        labeCamCtrl->setPalette(palette2);
        QFont font1;
        font1.setPointSize(12);
        labeCamCtrl->setFont(font1);
        labeCamCtrl->setFrameShape(QFrame::Box);
        labeGimbCtrl = new QLabel(Widget);
        labeGimbCtrl->setObjectName(QStringLiteral("labeGimbCtrl"));
        labeGimbCtrl->setGeometry(QRect(100, 443, 81, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        labeGimbCtrl->setPalette(palette3);
        labeGimbCtrl->setFont(font1);
        labeGimbCtrl->setFrameShape(QFrame::Box);
        labeZoomComp = new QLabel(Widget);
        labeZoomComp->setObjectName(QStringLiteral("labeZoomComp"));
        labeZoomComp->setGeometry(QRect(190, 443, 81, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        labeZoomComp->setPalette(palette4);
        labeZoomComp->setFont(font1);
        labeZoomComp->setFrameShape(QFrame::Box);
        labeZoomRatio = new QLabel(Widget);
        labeZoomRatio->setObjectName(QStringLiteral("labeZoomRatio"));
        labeZoomRatio->setGeometry(QRect(280, 443, 81, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        labeZoomRatio->setPalette(palette5);
        labeZoomRatio->setFont(font1);
        labeZoomRatio->setFrameShape(QFrame::Box);

        retranslateUi(Widget);

        tabBar->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        ButRevYaw->setText(QApplication::translate("Widget", "YAW REVERSE", Q_NULLPTR));
        ButRevPitch->setText(QApplication::translate("Widget", "PITCH REVERSE", Q_NULLPTR));
        ButRevRoll->setText(QApplication::translate("Widget", "ROLL REVERSE", Q_NULLPTR));
        ButRevZoom->setText(QApplication::translate("Widget", "ZOOM REVERSE", Q_NULLPTR));
        tabBar->setTabText(tabBar->indexOf(tabSpeed), QApplication::translate("Widget", "SPEED", Q_NULLPTR));
        label_13->setText(QApplication::translate("Widget", "YAW FLUID", Q_NULLPTR));
        label_14->setText(QApplication::translate("Widget", "PITCH FLUID", Q_NULLPTR));
        label_15->setText(QApplication::translate("Widget", "ROLL FLUID", Q_NULLPTR));
        label_16->setText(QApplication::translate("Widget", "ZOOM FLUID", Q_NULLPTR));
        tabBar->setTabText(tabBar->indexOf(tabFluid), QApplication::translate("Widget", "FLUID", Q_NULLPTR));
        label_19->setText(QApplication::translate("Widget", "ZOOM OFFSET", Q_NULLPTR));
        label_20->setText(QApplication::translate("Widget", "ROLL OFFSET", Q_NULLPTR));
        label_18->setText(QApplication::translate("Widget", "YAW OFFSET", Q_NULLPTR));
        label_17->setText(QApplication::translate("Widget", "PITCH OFFSET", Q_NULLPTR));
        tabBar->setTabText(tabBar->indexOf(tabOfset), QApplication::translate("Widget", "OFSET", Q_NULLPTR));
        ButDzoomOn->setText(QApplication::translate("Widget", "DZOOM ON", Q_NULLPTR));
        ButDzoomOff->setText(QApplication::translate("Widget", "DZOOM OFF", Q_NULLPTR));
        ButDzoomCombine->setText(QApplication::translate("Widget", "COMBINE", Q_NULLPTR));
        ButDzoomSeparate->setText(QApplication::translate("Widget", "SEPARATE", Q_NULLPTR));
        label_21->setText(QApplication::translate("Widget", "ZOOM COMPENSATION GAIN", Q_NULLPTR));
        label_22->setText(QApplication::translate("Widget", "DIGITAL ZOOM", Q_NULLPTR));
        tabBar->setTabText(tabBar->indexOf(tabZoom), QApplication::translate("Widget", "ZOOM", Q_NULLPTR));
        ButRevFocusSpeed->setText(QApplication::translate("Widget", "SPEED REVRSE", Q_NULLPTR));
        ButRevFocusPosition->setText(QApplication::translate("Widget", "POSIT REVERSE", Q_NULLPTR));
        ButFocusAuto->setText(QApplication::translate("Widget", "AUTO", Q_NULLPTR));
        ButFocusManual->setText(QApplication::translate("Widget", "MANUAL", Q_NULLPTR));
        ButFocusOneToutch->setText(QApplication::translate("Widget", "ONE TOUTCH", Q_NULLPTR));
        tabBar->setTabText(tabBar->indexOf(tabFocus), QApplication::translate("Widget", "FOCUS", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "LEFT X", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "LEFT Y", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "LEFT Z", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "RIGHT X", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "RIGHT Y", Q_NULLPTR));
        label_6->setText(QApplication::translate("Widget", "RIGHT Z", Q_NULLPTR));
        ButEnCamCtrl->setText(QApplication::translate("Widget", "CAM CTRL ON", Q_NULLPTR));
        ButDisCamCtrl->setText(QApplication::translate("Widget", "CAM CTRL OFF", Q_NULLPTR));
        ButEnGimbalCtrl->setText(QApplication::translate("Widget", "GIMB CTRL ON", Q_NULLPTR));
        ButDisGimbalCtrl->setText(QApplication::translate("Widget", "GIMB CTRL OFF", Q_NULLPTR));
        ButCalibrateJoysticks->setText(QApplication::translate("Widget", "Calib. Joysticks", Q_NULLPTR));
        tabBar->setTabText(tabBar->indexOf(tab_raw), QApplication::translate("Widget", "RAW", Q_NULLPTR));
        labeCamCtrl->setText(QApplication::translate("Widget", "Cam ON", Q_NULLPTR));
        labeGimbCtrl->setText(QApplication::translate("Widget", "Gimb ON", Q_NULLPTR));
        labeZoomComp->setText(QApplication::translate("Widget", "ZC ON", Q_NULLPTR));
        labeZoomRatio->setText(QApplication::translate("Widget", "ZR", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
