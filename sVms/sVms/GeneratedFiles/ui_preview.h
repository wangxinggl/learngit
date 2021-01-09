/********************************************************************************
** Form generated from reading UI file 'preview.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEW_H
#define UI_PREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreView
{
public:
    QGridLayout *gridLayout_8;
    QWidget *widget_Manage;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_Search;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QPushButton *btnExtendDown;
    QWidget *widget_Ptz;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *nPTZSpeed;
    QPushButton *m_btnPtzUp;
    QPushButton *m_btnPtzAuto;
    QPushButton *m_btnPtzLeft;
    QPushButton *m_btnPtzDown;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *m_btnPtzFocus_A;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *m_btnPtzFocus_S;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *m_btnPtzZoom_A;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *m_btnPtzZoom_S;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *m_btnPtzApe_A;
    QLabel *label_16;
    QLabel *label_17;
    QPushButton *m_btnPtzApe_S;
    QPushButton *m_btnPtzRight;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QPushButton *PtzLight;
    QPushButton *PtzPreset;
    QPushButton *PtzRain;
    QPushButton *PtzRecall;
    QWidget *widget_main;
    QGridLayout *gridLayout_main;
    QSpacerItem *horizontalSpacer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClearUnrec;
    QPushButton *btnSet;
    QLabel *label;
    QPushButton *btnClearRec;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QPushButton *btnExtendLeft;

    void setupUi(QWidget *PreView)
    {
        if (PreView->objectName().isEmpty())
            PreView->setObjectName(QStringLiteral("PreView"));
        PreView->resize(1266, 863);
        gridLayout_8 = new QGridLayout(PreView);
        gridLayout_8->setSpacing(0);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        widget_Manage = new QWidget(PreView);
        widget_Manage->setObjectName(QStringLiteral("widget_Manage"));
        widget_Manage->setMinimumSize(QSize(238, 0));
        widget_Manage->setMaximumSize(QSize(250, 16777215));
        gridLayout_2 = new QGridLayout(widget_Manage);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        lineEdit_Search = new QLineEdit(widget_Manage);
        lineEdit_Search->setObjectName(QStringLiteral("lineEdit_Search"));

        gridLayout_2->addWidget(lineEdit_Search, 0, 0, 1, 1);

        treeWidget = new QTreeWidget(widget_Manage);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMinimumSize(QSize(235, 0));
        treeWidget->setMaximumSize(QSize(230, 16777215));

        gridLayout_2->addWidget(treeWidget, 1, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(widget_Manage);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMaximumSize(QSize(16777215, 20));
        label_3->setStyleSheet(QStringLiteral(""));
        label_3->setFrameShape(QFrame::Box);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        btnExtendDown = new QPushButton(widget_Manage);
        btnExtendDown->setObjectName(QStringLiteral("btnExtendDown"));
        sizePolicy1.setHeightForWidth(btnExtendDown->sizePolicy().hasHeightForWidth());
        btnExtendDown->setSizePolicy(sizePolicy1);
        btnExtendDown->setMaximumSize(QSize(18, 16777215));
        btnExtendDown->setStyleSheet(QStringLiteral("QPushButton{border:none}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/xia.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExtendDown->setIcon(icon);

        horizontalLayout_2->addWidget(btnExtendDown);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        widget_Ptz = new QWidget(widget_Manage);
        widget_Ptz->setObjectName(QStringLiteral("widget_Ptz"));
        sizePolicy1.setHeightForWidth(widget_Ptz->sizePolicy().hasHeightForWidth());
        widget_Ptz->setSizePolicy(sizePolicy1);
        widget_Ptz->setMinimumSize(QSize(0, 370));
        widget_Ptz->setMaximumSize(QSize(250, 16777215));
        layoutWidget = new QWidget(widget_Ptz);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 280, 231, 24));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        nPTZSpeed = new QSlider(layoutWidget);
        nPTZSpeed->setObjectName(QStringLiteral("nPTZSpeed"));
        nPTZSpeed->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(nPTZSpeed);

        m_btnPtzUp = new QPushButton(widget_Ptz);
        m_btnPtzUp->setObjectName(QStringLiteral("m_btnPtzUp"));
        m_btnPtzUp->setGeometry(QRect(40, 0, 150, 150));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_btnPtzUp->sizePolicy().hasHeightForWidth());
        m_btnPtzUp->setSizePolicy(sizePolicy2);
        m_btnPtzUp->setMinimumSize(QSize(150, 150));
        m_btnPtzUp->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/PTZMax.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/PTZBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/PTZsBlue.png);}"));
        m_btnPtzUp->setFlat(true);
        m_btnPtzAuto = new QPushButton(widget_Ptz);
        m_btnPtzAuto->setObjectName(QStringLiteral("m_btnPtzAuto"));
        m_btnPtzAuto->setGeometry(QRect(40, 0, 150, 150));
        sizePolicy2.setHeightForWidth(m_btnPtzAuto->sizePolicy().hasHeightForWidth());
        m_btnPtzAuto->setSizePolicy(sizePolicy2);
        m_btnPtzAuto->setMinimumSize(QSize(150, 150));
        m_btnPtzAuto->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/PTZMax.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/PTZBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/PTZsBlue.png);}\n"
""));
        m_btnPtzAuto->setFlat(true);
        m_btnPtzLeft = new QPushButton(widget_Ptz);
        m_btnPtzLeft->setObjectName(QStringLiteral("m_btnPtzLeft"));
        m_btnPtzLeft->setGeometry(QRect(40, 0, 150, 150));
        sizePolicy2.setHeightForWidth(m_btnPtzLeft->sizePolicy().hasHeightForWidth());
        m_btnPtzLeft->setSizePolicy(sizePolicy2);
        m_btnPtzLeft->setMinimumSize(QSize(150, 150));
        m_btnPtzLeft->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/PTZMax.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/PTZBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/PTZsBlue.png);}"));
        m_btnPtzLeft->setFlat(true);
        m_btnPtzDown = new QPushButton(widget_Ptz);
        m_btnPtzDown->setObjectName(QStringLiteral("m_btnPtzDown"));
        m_btnPtzDown->setGeometry(QRect(40, 0, 150, 150));
        sizePolicy2.setHeightForWidth(m_btnPtzDown->sizePolicy().hasHeightForWidth());
        m_btnPtzDown->setSizePolicy(sizePolicy2);
        m_btnPtzDown->setMinimumSize(QSize(150, 150));
        m_btnPtzDown->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/PTZMax.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/PTZBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/PTZsBlue.png);}\n"
""));
        m_btnPtzDown->setFlat(true);
        layoutWidget1 = new QWidget(widget_Ptz);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 160, 231, 37));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_8->setSpacing(15);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        m_btnPtzFocus_A = new QPushButton(layoutWidget1);
        m_btnPtzFocus_A->setObjectName(QStringLiteral("m_btnPtzFocus_A"));
        sizePolicy1.setHeightForWidth(m_btnPtzFocus_A->sizePolicy().hasHeightForWidth());
        m_btnPtzFocus_A->setSizePolicy(sizePolicy1);
        m_btnPtzFocus_A->setMinimumSize(QSize(35, 35));
        m_btnPtzFocus_A->setMaximumSize(QSize(35, 35));
        m_btnPtzFocus_A->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/AddHui.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/AddBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/AddsBlue.png);}"));
        m_btnPtzFocus_A->setIconSize(QSize(35, 35));
        m_btnPtzFocus_A->setAutoRepeat(true);

        horizontalLayout_8->addWidget(m_btnPtzFocus_A);

        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(20, 20));
        label_12->setMaximumSize(QSize(20, 20));
        label_12->setStyleSheet(QStringLiteral("border-image: url(:/res/PTZPro/bainbeipro.png);"));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setScaledContents(true);
        label_12->setWordWrap(false);

        horizontalLayout_8->addWidget(label_12);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(20, 20));
        label_13->setMaximumSize(QSize(20, 20));
        label_13->setStyleSheet(QStringLiteral("border-image: url(:/res/PTZPro/bainbei.png);"));
        label_13->setFrameShape(QFrame::Panel);

        horizontalLayout_8->addWidget(label_13);

        m_btnPtzFocus_S = new QPushButton(layoutWidget1);
        m_btnPtzFocus_S->setObjectName(QStringLiteral("m_btnPtzFocus_S"));
        sizePolicy1.setHeightForWidth(m_btnPtzFocus_S->sizePolicy().hasHeightForWidth());
        m_btnPtzFocus_S->setSizePolicy(sizePolicy1);
        m_btnPtzFocus_S->setMinimumSize(QSize(35, 35));
        m_btnPtzFocus_S->setMaximumSize(QSize(35, 35));
        m_btnPtzFocus_S->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/DelHui.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/DelBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/DelsBlue.png);}"));
        m_btnPtzFocus_S->setIconSize(QSize(35, 35));
        m_btnPtzFocus_S->setAutoRepeat(true);

        horizontalLayout_8->addWidget(m_btnPtzFocus_S);

        layoutWidget2 = new QWidget(widget_Ptz);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 200, 231, 37));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_9->setSpacing(15);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        m_btnPtzZoom_A = new QPushButton(layoutWidget2);
        m_btnPtzZoom_A->setObjectName(QStringLiteral("m_btnPtzZoom_A"));
        sizePolicy1.setHeightForWidth(m_btnPtzZoom_A->sizePolicy().hasHeightForWidth());
        m_btnPtzZoom_A->setSizePolicy(sizePolicy1);
        m_btnPtzZoom_A->setMinimumSize(QSize(35, 35));
        m_btnPtzZoom_A->setMaximumSize(QSize(35, 35));
        m_btnPtzZoom_A->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/AddHui.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/AddBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/AddsBlue.png);}"));
        m_btnPtzZoom_A->setIconSize(QSize(35, 35));
        m_btnPtzZoom_A->setAutoRepeat(true);

        horizontalLayout_9->addWidget(m_btnPtzZoom_A);

        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMinimumSize(QSize(20, 20));
        label_14->setMaximumSize(QSize(20, 20));
        label_14->setStyleSheet(QStringLiteral("border-image: url(:/res/PTZPro/guangquanpro.png);"));
        label_14->setFrameShape(QFrame::Panel);

        horizontalLayout_9->addWidget(label_14);

        label_15 = new QLabel(layoutWidget2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(20, 20));
        label_15->setMaximumSize(QSize(20, 20));
        label_15->setStyleSheet(QStringLiteral("border-image: url(:/res/PTZPro/guangquan.png);"));
        label_15->setFrameShape(QFrame::Panel);

        horizontalLayout_9->addWidget(label_15);

        m_btnPtzZoom_S = new QPushButton(layoutWidget2);
        m_btnPtzZoom_S->setObjectName(QStringLiteral("m_btnPtzZoom_S"));
        sizePolicy1.setHeightForWidth(m_btnPtzZoom_S->sizePolicy().hasHeightForWidth());
        m_btnPtzZoom_S->setSizePolicy(sizePolicy1);
        m_btnPtzZoom_S->setMinimumSize(QSize(35, 35));
        m_btnPtzZoom_S->setMaximumSize(QSize(35, 35));
        m_btnPtzZoom_S->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/DelHui.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/DelBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/DelsBlue.png);}"));
        m_btnPtzZoom_S->setIconSize(QSize(35, 35));
        m_btnPtzZoom_S->setAutoRepeat(true);

        horizontalLayout_9->addWidget(m_btnPtzZoom_S);

        layoutWidget3 = new QWidget(widget_Ptz);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 240, 231, 37));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_10->setSpacing(15);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        m_btnPtzApe_A = new QPushButton(layoutWidget3);
        m_btnPtzApe_A->setObjectName(QStringLiteral("m_btnPtzApe_A"));
        sizePolicy1.setHeightForWidth(m_btnPtzApe_A->sizePolicy().hasHeightForWidth());
        m_btnPtzApe_A->setSizePolicy(sizePolicy1);
        m_btnPtzApe_A->setMinimumSize(QSize(35, 35));
        m_btnPtzApe_A->setMaximumSize(QSize(35, 35));
        m_btnPtzApe_A->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/AddHui.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/AddBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/AddsBlue.png);}"));
        m_btnPtzApe_A->setIconSize(QSize(35, 35));
        m_btnPtzApe_A->setAutoRepeat(true);

        horizontalLayout_10->addWidget(m_btnPtzApe_A);

        label_16 = new QLabel(layoutWidget3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(20, 20));
        label_16->setMaximumSize(QSize(20, 20));
        label_16->setStyleSheet(QStringLiteral("border-image: url(:/res/PTZPro/jujiaopro.png);"));
        label_16->setFrameShape(QFrame::Panel);

        horizontalLayout_10->addWidget(label_16);

        label_17 = new QLabel(layoutWidget3);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(20, 20));
        label_17->setMaximumSize(QSize(20, 20));
        label_17->setStyleSheet(QStringLiteral("border-image: url(:/res/PTZPro/jujiao.png);"));
        label_17->setFrameShape(QFrame::Panel);

        horizontalLayout_10->addWidget(label_17);

        m_btnPtzApe_S = new QPushButton(layoutWidget3);
        m_btnPtzApe_S->setObjectName(QStringLiteral("m_btnPtzApe_S"));
        sizePolicy1.setHeightForWidth(m_btnPtzApe_S->sizePolicy().hasHeightForWidth());
        m_btnPtzApe_S->setSizePolicy(sizePolicy1);
        m_btnPtzApe_S->setMinimumSize(QSize(35, 35));
        m_btnPtzApe_S->setMaximumSize(QSize(35, 35));
        m_btnPtzApe_S->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/DelHui.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/DelBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/DelsBlue.png);}"));
        m_btnPtzApe_S->setIconSize(QSize(35, 35));
        m_btnPtzApe_S->setAutoRepeat(true);

        horizontalLayout_10->addWidget(m_btnPtzApe_S);

        m_btnPtzRight = new QPushButton(widget_Ptz);
        m_btnPtzRight->setObjectName(QStringLiteral("m_btnPtzRight"));
        m_btnPtzRight->setGeometry(QRect(40, 1, 150, 150));
        sizePolicy2.setHeightForWidth(m_btnPtzRight->sizePolicy().hasHeightForWidth());
        m_btnPtzRight->setSizePolicy(sizePolicy2);
        m_btnPtzRight->setMinimumSize(QSize(150, 150));
        m_btnPtzRight->setMaximumSize(QSize(150, 150));
        m_btnPtzRight->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/PTZMax.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/PTZBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/PTZsBlue.png);}"));
        m_btnPtzRight->setFlat(true);
        groupBox = new QGroupBox(widget_Ptz);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 310, 221, 53));
        groupBox->setStyleSheet(QStringLiteral("QWidget{background-color:DimGrey;border-top-left-radius:15px;border-top-right-radius:15px;border-bottom-left-radius:15px;border-bottom-right-radius:15px}"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        PtzLight = new QPushButton(groupBox);
        PtzLight->setObjectName(QStringLiteral("PtzLight"));
        PtzLight->setMinimumSize(QSize(35, 35));
        PtzLight->setMaximumSize(QSize(35, 35));
        PtzLight->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/light.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/lightBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/lightsBlue.png);}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/PTZ/Light.png"), QSize(), QIcon::Normal, QIcon::Off);
        PtzLight->setIcon(icon1);
        PtzLight->setIconSize(QSize(20, 20));
        PtzLight->setAutoRepeat(true);

        gridLayout_5->addWidget(PtzLight, 0, 0, 1, 1);

        PtzPreset = new QPushButton(groupBox);
        PtzPreset->setObjectName(QStringLiteral("PtzPreset"));
        PtzPreset->setMinimumSize(QSize(35, 35));
        PtzPreset->setMaximumSize(QSize(35, 35));
        PtzPreset->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/yuzhi.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/yuzhiBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/yuzhisBlue.png);}"));
        PtzPreset->setIconSize(QSize(20, 20));
        PtzPreset->setAutoRepeat(true);

        gridLayout_5->addWidget(PtzPreset, 0, 1, 1, 1);

        PtzRain = new QPushButton(groupBox);
        PtzRain->setObjectName(QStringLiteral("PtzRain"));
        PtzRain->setMinimumSize(QSize(35, 35));
        PtzRain->setMaximumSize(QSize(35, 35));
        PtzRain->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/Brush.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/BrushBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/BrushsBlue.png);}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/PTZ/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        PtzRain->setIcon(icon2);
        PtzRain->setIconSize(QSize(20, 20));
        PtzRain->setAutoRepeat(true);

        gridLayout_5->addWidget(PtzRain, 0, 2, 1, 1);

        PtzRecall = new QPushButton(groupBox);
        PtzRecall->setObjectName(QStringLiteral("PtzRecall"));
        PtzRecall->setMinimumSize(QSize(35, 35));
        PtzRecall->setMaximumSize(QSize(35, 35));
        PtzRecall->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/res/PTZPro/diaoyong.png);}\n"
"QPushButton:hover{border-image: url(:/res/PTZPro/diaoyongBlue.png);}\n"
"QPushButton:pressed{border-image: url(:/res/PTZPro/diaoyongsBlue.png);}"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/PTZ/Recall.png"), QSize(), QIcon::Normal, QIcon::Off);
        PtzRecall->setIcon(icon3);
        PtzRecall->setIconSize(QSize(20, 20));
        PtzRecall->setAutoRepeat(true);

        gridLayout_5->addWidget(PtzRecall, 0, 3, 1, 1);


        gridLayout_2->addWidget(widget_Ptz, 3, 0, 1, 2);

        treeWidget->raise();
        widget_Ptz->raise();
        lineEdit_Search->raise();

        gridLayout_8->addWidget(widget_Manage, 0, 0, 1, 1);

        widget_main = new QWidget(PreView);
        widget_main->setObjectName(QStringLiteral("widget_main"));
        gridLayout_main = new QGridLayout(widget_main);
        gridLayout_main->setSpacing(6);
        gridLayout_main->setContentsMargins(11, 11, 11, 11);
        gridLayout_main->setObjectName(QStringLiteral("gridLayout_main"));
        gridLayout_main->setHorizontalSpacing(3);
        gridLayout_main->setVerticalSpacing(0);
        gridLayout_main->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(68, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_main->addItem(horizontalSpacer, 0, 4, 1, 1);

        scrollArea = new QScrollArea(widget_main);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(240, 0));
        scrollArea->setMaximumSize(QSize(240, 16777215));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 238, 841));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 0, 600);

        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_main->addWidget(scrollArea, 1, 3, 3, 4);

        scrollArea_2 = new QScrollArea(widget_main);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy3);
        scrollArea_2->setMaximumSize(QSize(16777215, 150));
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1319, 131));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 1300, -1);

        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_main->addWidget(scrollArea_2, 3, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(679, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_main->addItem(horizontalSpacer_2, 2, 1, 1, 1);

        btnClearUnrec = new QPushButton(widget_main);
        btnClearUnrec->setObjectName(QStringLiteral("btnClearUnrec"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnClearUnrec->sizePolicy().hasHeightForWidth());
        btnClearUnrec->setSizePolicy(sizePolicy4);
        btnClearUnrec->setMaximumSize(QSize(20, 20));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/SoftIcon/Clear1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearUnrec->setIcon(icon4);

        gridLayout_main->addWidget(btnClearUnrec, 2, 2, 1, 1);

        btnSet = new QPushButton(widget_main);
        btnSet->setObjectName(QStringLiteral("btnSet"));
        sizePolicy4.setHeightForWidth(btnSet->sizePolicy().hasHeightForWidth());
        btnSet->setSizePolicy(sizePolicy4);
        btnSet->setMaximumSize(QSize(20, 20));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/SoftIcon/SystemSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSet->setIcon(icon5);

        gridLayout_main->addWidget(btnSet, 0, 5, 1, 1);

        label = new QLabel(widget_main);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));

        gridLayout_main->addWidget(label, 0, 3, 1, 1);

        btnClearRec = new QPushButton(widget_main);
        btnClearRec->setObjectName(QStringLiteral("btnClearRec"));
        sizePolicy4.setHeightForWidth(btnClearRec->sizePolicy().hasHeightForWidth());
        btnClearRec->setSizePolicy(sizePolicy4);
        btnClearRec->setMaximumSize(QSize(20, 20));
        btnClearRec->setIcon(icon4);

        gridLayout_main->addWidget(btnClearRec, 0, 6, 1, 1);

        label_2 = new QLabel(widget_main);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_main->addWidget(label_2, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);

        gridLayout_main->addLayout(gridLayout, 0, 0, 2, 3);


        gridLayout_8->addWidget(widget_main, 0, 3, 1, 1);

        btnExtendLeft = new QPushButton(PreView);
        btnExtendLeft->setObjectName(QStringLiteral("btnExtendLeft"));
        sizePolicy.setHeightForWidth(btnExtendLeft->sizePolicy().hasHeightForWidth());
        btnExtendLeft->setSizePolicy(sizePolicy);
        btnExtendLeft->setMaximumSize(QSize(10, 16777215));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/SoftIcon/zou.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExtendLeft->setIcon(icon6);
        btnExtendLeft->setIconSize(QSize(12, 12));

        gridLayout_8->addWidget(btnExtendLeft, 0, 1, 1, 1);

        btnExtendLeft->raise();
        widget_main->raise();
        widget_Manage->raise();

        retranslateUi(PreView);

        QMetaObject::connectSlotsByName(PreView);
    } // setupUi

    void retranslateUi(QWidget *PreView)
    {
        PreView->setWindowTitle(QApplication::translate("PreView", "PreView", Q_NULLPTR));
        lineEdit_Search->setPlaceholderText(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("PreView", "\350\256\276\345\244\207\347\256\241\347\220\206\344\270\255\345\277\203", Q_NULLPTR));
        label_3->setText(QApplication::translate("PreView", "\344\272\221\345\217\260\346\216\247\345\210\266", Q_NULLPTR));
        btnExtendDown->setText(QString());
        label_4->setText(QApplication::translate("PreView", "\351\200\237\345\272\246", Q_NULLPTR));
        m_btnPtzUp->setText(QString());
        m_btnPtzAuto->setText(QString());
        m_btnPtzLeft->setText(QString());
        m_btnPtzDown->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnPtzFocus_A->setToolTip(QApplication::translate("PreView", "\345\217\230\345\200\215", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_btnPtzFocus_A->setText(QString());
        label_12->setText(QString());
        label_13->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnPtzFocus_S->setToolTip(QApplication::translate("PreView", "\345\217\230\345\200\215", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_btnPtzFocus_S->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnPtzZoom_A->setToolTip(QApplication::translate("PreView", "\345\205\211\345\234\210", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_btnPtzZoom_A->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnPtzZoom_S->setToolTip(QApplication::translate("PreView", "\345\205\211\345\234\210", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_btnPtzZoom_S->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnPtzApe_A->setToolTip(QApplication::translate("PreView", "\350\201\232\347\204\246", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_btnPtzApe_A->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_btnPtzApe_S->setToolTip(QApplication::translate("PreView", "\350\201\232\347\204\246", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        m_btnPtzApe_S->setText(QString());
        m_btnPtzRight->setText(QString());
        groupBox->setTitle(QString());
        PtzLight->setText(QString());
        PtzPreset->setText(QString());
        PtzRain->setText(QString());
        PtzRecall->setText(QString());
        btnClearUnrec->setText(QString());
        btnSet->setText(QString());
        label->setText(QApplication::translate("PreView", "\345\256\236\346\227\266\345\221\212\350\255\246", Q_NULLPTR));
        btnClearRec->setText(QString());
        label_2->setText(QApplication::translate("PreView", "\345\256\236\346\227\266\346\212\223\346\213\215", Q_NULLPTR));
        btnExtendLeft->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PreView: public Ui_PreView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEW_H
