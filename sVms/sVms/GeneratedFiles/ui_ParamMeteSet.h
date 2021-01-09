/********************************************************************************
** Form generated from reading UI file 'ParamMeteSet.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMMETESET_H
#define UI_PARAMMETESET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamMeteSet
{
public:
    QLabel *label_20;
    QPushButton *btnSave;
    QPushButton *btnUpdate;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_Enable;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QCheckBox *checkBox_Time1;
    QTimeEdit *timeEdit_Start1;
    QLabel *label_36;
    QTimeEdit *timeEdit_End1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QCheckBox *checkBox_Time2;
    QTimeEdit *timeEdit_Start2;
    QLabel *label_37;
    QTimeEdit *timeEdit_End2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_SENSITIVITY;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *comboBox_SNAPMODE;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_MAXSNAPNUM;
    QComboBox *comboBox_MAXSNAPNUM;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_FASTSNAPFRAMECOUNT;
    QLineEdit *lineEdit_FASTSNAPFRAMECOUNT;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_SNAPCOUNT;
    QComboBox *comboBox_SNAPCOUNT;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_INTERERAITIME;
    QLineEdit *lineEdit_INTERERAITIME;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_INTERERAIFRAME;
    QLineEdit *lineEdit_INTERERAIFRAME;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_INTERERAIFRAME_GATE;
    QLineEdit *lineEdit_INTERERAIFRAME_GATE;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_16;
    QLineEdit *lineEdit_FACESIZE;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_18;
    QLineEdit *lineEdit_MAXFACESIZE;
    QLabel *label_19;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_21;
    QComboBox *comboBox_SNAPSCENE;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_22;
    QComboBox *comboBox_FACETRACKING;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_23;
    QComboBox *comboBox_FTPENABLE;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_24;
    QComboBox *comboBox_PRIVATEUP;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_SERVERIP;
    QLineEdit *lineEdit_SERVERIP;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_SERVERPORT;
    QLineEdit *lineEdit_SERVERPORT;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_27;
    QComboBox *comboBox_PICMODE;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_29;
    QLineEdit *lineEdit_FACEPICQUAL;
    QLabel *label_30;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_31;
    QLineEdit *lineEdit_FRAMEPICQUAL;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_32;
    QComboBox *comboBox_FACEPICNAME;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_CUSTOMNAME;
    QLineEdit *lineEdit_CUSTOMNAME;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_34;
    QLineEdit *lineEdit_EXTENDVAULE;
    QLabel *label_35;
    QPushButton *btnClose;

    void setupUi(QDialog *ParamMeteSet)
    {
        if (ParamMeteSet->objectName().isEmpty())
            ParamMeteSet->setObjectName(QStringLiteral("ParamMeteSet"));
        ParamMeteSet->resize(1020, 616);
        label_20 = new QLabel(ParamMeteSet);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(400, 540, 261, 16));
        btnSave = new QPushButton(ParamMeteSet);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(400, 580, 75, 23));
        btnUpdate = new QPushButton(ParamMeteSet);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));
        btnUpdate->setGeometry(QRect(600, 580, 75, 23));
        layoutWidget = new QWidget(ParamMeteSet);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 40, 451, 481));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_Enable = new QCheckBox(layoutWidget);
        checkBox_Enable->setObjectName(QStringLiteral("checkBox_Enable"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_Enable->sizePolicy().hasHeightForWidth());
        checkBox_Enable->setSizePolicy(sizePolicy);
        checkBox_Enable->setMinimumSize(QSize(10, 0));

        verticalLayout->addWidget(checkBox_Enable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(155, 0));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        checkBox_Time1 = new QCheckBox(layoutWidget);
        checkBox_Time1->setObjectName(QStringLiteral("checkBox_Time1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_Time1->sizePolicy().hasHeightForWidth());
        checkBox_Time1->setSizePolicy(sizePolicy1);
        checkBox_Time1->setMaximumSize(QSize(15, 16777215));

        horizontalLayout->addWidget(checkBox_Time1);

        timeEdit_Start1 = new QTimeEdit(layoutWidget);
        timeEdit_Start1->setObjectName(QStringLiteral("timeEdit_Start1"));
        sizePolicy.setHeightForWidth(timeEdit_Start1->sizePolicy().hasHeightForWidth());
        timeEdit_Start1->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(timeEdit_Start1);

        label_36 = new QLabel(layoutWidget);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setMaximumSize(QSize(20, 16777215));

        horizontalLayout->addWidget(label_36);

        timeEdit_End1 = new QTimeEdit(layoutWidget);
        timeEdit_End1->setObjectName(QStringLiteral("timeEdit_End1"));
        sizePolicy.setHeightForWidth(timeEdit_End1->sizePolicy().hasHeightForWidth());
        timeEdit_End1->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(timeEdit_End1);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(155, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        checkBox_Time2 = new QCheckBox(layoutWidget);
        checkBox_Time2->setObjectName(QStringLiteral("checkBox_Time2"));
        sizePolicy1.setHeightForWidth(checkBox_Time2->sizePolicy().hasHeightForWidth());
        checkBox_Time2->setSizePolicy(sizePolicy1);
        checkBox_Time2->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_2->addWidget(checkBox_Time2);

        timeEdit_Start2 = new QTimeEdit(layoutWidget);
        timeEdit_Start2->setObjectName(QStringLiteral("timeEdit_Start2"));
        sizePolicy.setHeightForWidth(timeEdit_Start2->sizePolicy().hasHeightForWidth());
        timeEdit_Start2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(timeEdit_Start2);

        label_37 = new QLabel(layoutWidget);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_2->addWidget(label_37);

        timeEdit_End2 = new QTimeEdit(layoutWidget);
        timeEdit_End2->setObjectName(QStringLiteral("timeEdit_End2"));
        sizePolicy.setHeightForWidth(timeEdit_End2->sizePolicy().hasHeightForWidth());
        timeEdit_End2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(timeEdit_End2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(190, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        comboBox_SENSITIVITY = new QComboBox(layoutWidget);
        comboBox_SENSITIVITY->setObjectName(QStringLiteral("comboBox_SENSITIVITY"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_SENSITIVITY->sizePolicy().hasHeightForWidth());
        comboBox_SENSITIVITY->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(comboBox_SENSITIVITY);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(190, 0));
        label_5->setMaximumSize(QSize(110, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_5);

        comboBox_SNAPMODE = new QComboBox(layoutWidget);
        comboBox_SNAPMODE->setObjectName(QStringLiteral("comboBox_SNAPMODE"));
        sizePolicy2.setHeightForWidth(comboBox_SNAPMODE->sizePolicy().hasHeightForWidth());
        comboBox_SNAPMODE->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(comboBox_SNAPMODE);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_MAXSNAPNUM = new QLabel(layoutWidget);
        label_MAXSNAPNUM->setObjectName(QStringLiteral("label_MAXSNAPNUM"));
        label_MAXSNAPNUM->setMinimumSize(QSize(190, 0));
        label_MAXSNAPNUM->setMaximumSize(QSize(110, 16777215));
        label_MAXSNAPNUM->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_MAXSNAPNUM);

        comboBox_MAXSNAPNUM = new QComboBox(layoutWidget);
        comboBox_MAXSNAPNUM->setObjectName(QStringLiteral("comboBox_MAXSNAPNUM"));
        sizePolicy2.setHeightForWidth(comboBox_MAXSNAPNUM->sizePolicy().hasHeightForWidth());
        comboBox_MAXSNAPNUM->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(comboBox_MAXSNAPNUM);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_FASTSNAPFRAMECOUNT = new QLabel(layoutWidget);
        label_FASTSNAPFRAMECOUNT->setObjectName(QStringLiteral("label_FASTSNAPFRAMECOUNT"));
        label_FASTSNAPFRAMECOUNT->setMinimumSize(QSize(190, 0));
        label_FASTSNAPFRAMECOUNT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_FASTSNAPFRAMECOUNT);

        lineEdit_FASTSNAPFRAMECOUNT = new QLineEdit(layoutWidget);
        lineEdit_FASTSNAPFRAMECOUNT->setObjectName(QStringLiteral("lineEdit_FASTSNAPFRAMECOUNT"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_FASTSNAPFRAMECOUNT->sizePolicy().hasHeightForWidth());
        lineEdit_FASTSNAPFRAMECOUNT->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(lineEdit_FASTSNAPFRAMECOUNT);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_6->addWidget(label_9);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_SNAPCOUNT = new QLabel(layoutWidget);
        label_SNAPCOUNT->setObjectName(QStringLiteral("label_SNAPCOUNT"));
        label_SNAPCOUNT->setMinimumSize(QSize(190, 0));
        label_SNAPCOUNT->setMaximumSize(QSize(110, 16777215));
        label_SNAPCOUNT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_SNAPCOUNT);

        comboBox_SNAPCOUNT = new QComboBox(layoutWidget);
        comboBox_SNAPCOUNT->setObjectName(QStringLiteral("comboBox_SNAPCOUNT"));
        sizePolicy2.setHeightForWidth(comboBox_SNAPCOUNT->sizePolicy().hasHeightForWidth());
        comboBox_SNAPCOUNT->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(comboBox_SNAPCOUNT);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_INTERERAITIME = new QLabel(layoutWidget);
        label_INTERERAITIME->setObjectName(QStringLiteral("label_INTERERAITIME"));
        label_INTERERAITIME->setMinimumSize(QSize(190, 0));
        label_INTERERAITIME->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_INTERERAITIME);

        lineEdit_INTERERAITIME = new QLineEdit(layoutWidget);
        lineEdit_INTERERAITIME->setObjectName(QStringLiteral("lineEdit_INTERERAITIME"));
        sizePolicy3.setHeightForWidth(lineEdit_INTERERAITIME->sizePolicy().hasHeightForWidth());
        lineEdit_INTERERAITIME->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(lineEdit_INTERERAITIME);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_8->addWidget(label_11);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_INTERERAIFRAME = new QLabel(layoutWidget);
        label_INTERERAIFRAME->setObjectName(QStringLiteral("label_INTERERAIFRAME"));
        label_INTERERAIFRAME->setMinimumSize(QSize(190, 0));
        label_INTERERAIFRAME->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_INTERERAIFRAME);

        lineEdit_INTERERAIFRAME = new QLineEdit(layoutWidget);
        lineEdit_INTERERAIFRAME->setObjectName(QStringLiteral("lineEdit_INTERERAIFRAME"));
        sizePolicy3.setHeightForWidth(lineEdit_INTERERAIFRAME->sizePolicy().hasHeightForWidth());
        lineEdit_INTERERAIFRAME->setSizePolicy(sizePolicy3);

        horizontalLayout_9->addWidget(lineEdit_INTERERAIFRAME);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_9->addWidget(label_13);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_INTERERAIFRAME_GATE = new QLabel(layoutWidget);
        label_INTERERAIFRAME_GATE->setObjectName(QStringLiteral("label_INTERERAIFRAME_GATE"));
        label_INTERERAIFRAME_GATE->setMinimumSize(QSize(190, 0));
        label_INTERERAIFRAME_GATE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_INTERERAIFRAME_GATE);

        lineEdit_INTERERAIFRAME_GATE = new QLineEdit(layoutWidget);
        lineEdit_INTERERAIFRAME_GATE->setObjectName(QStringLiteral("lineEdit_INTERERAIFRAME_GATE"));
        sizePolicy3.setHeightForWidth(lineEdit_INTERERAIFRAME_GATE->sizePolicy().hasHeightForWidth());
        lineEdit_INTERERAIFRAME_GATE->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(lineEdit_INTERERAIFRAME_GATE);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_10->addWidget(label_15);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(190, 0));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_16);

        lineEdit_FACESIZE = new QLineEdit(layoutWidget);
        lineEdit_FACESIZE->setObjectName(QStringLiteral("lineEdit_FACESIZE"));
        sizePolicy3.setHeightForWidth(lineEdit_FACESIZE->sizePolicy().hasHeightForWidth());
        lineEdit_FACESIZE->setSizePolicy(sizePolicy3);

        horizontalLayout_11->addWidget(lineEdit_FACESIZE);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_11->addWidget(label_17);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(190, 0));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_18);

        lineEdit_MAXFACESIZE = new QLineEdit(layoutWidget);
        lineEdit_MAXFACESIZE->setObjectName(QStringLiteral("lineEdit_MAXFACESIZE"));
        sizePolicy3.setHeightForWidth(lineEdit_MAXFACESIZE->sizePolicy().hasHeightForWidth());
        lineEdit_MAXFACESIZE->setSizePolicy(sizePolicy3);

        horizontalLayout_12->addWidget(lineEdit_MAXFACESIZE);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_12->addWidget(label_19);


        verticalLayout->addLayout(horizontalLayout_12);

        layoutWidget1 = new QWidget(ParamMeteSet);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(560, 80, 381, 441));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_21 = new QLabel(layoutWidget1);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setMinimumSize(QSize(155, 0));
        label_21->setMaximumSize(QSize(155, 16777215));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_21);

        comboBox_SNAPSCENE = new QComboBox(layoutWidget1);
        comboBox_SNAPSCENE->setObjectName(QStringLiteral("comboBox_SNAPSCENE"));
        sizePolicy2.setHeightForWidth(comboBox_SNAPSCENE->sizePolicy().hasHeightForWidth());
        comboBox_SNAPSCENE->setSizePolicy(sizePolicy2);

        horizontalLayout_13->addWidget(comboBox_SNAPSCENE);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_22 = new QLabel(layoutWidget1);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setMinimumSize(QSize(155, 0));
        label_22->setMaximumSize(QSize(155, 16777215));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_22);

        comboBox_FACETRACKING = new QComboBox(layoutWidget1);
        comboBox_FACETRACKING->setObjectName(QStringLiteral("comboBox_FACETRACKING"));
        sizePolicy2.setHeightForWidth(comboBox_FACETRACKING->sizePolicy().hasHeightForWidth());
        comboBox_FACETRACKING->setSizePolicy(sizePolicy2);

        horizontalLayout_14->addWidget(comboBox_FACETRACKING);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_23 = new QLabel(layoutWidget1);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setMinimumSize(QSize(155, 0));
        label_23->setMaximumSize(QSize(155, 16777215));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_23);

        comboBox_FTPENABLE = new QComboBox(layoutWidget1);
        comboBox_FTPENABLE->setObjectName(QStringLiteral("comboBox_FTPENABLE"));
        sizePolicy2.setHeightForWidth(comboBox_FTPENABLE->sizePolicy().hasHeightForWidth());
        comboBox_FTPENABLE->setSizePolicy(sizePolicy2);

        horizontalLayout_15->addWidget(comboBox_FTPENABLE);


        verticalLayout_2->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_24 = new QLabel(layoutWidget1);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setMinimumSize(QSize(155, 0));
        label_24->setMaximumSize(QSize(155, 16777215));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(label_24);

        comboBox_PRIVATEUP = new QComboBox(layoutWidget1);
        comboBox_PRIVATEUP->setObjectName(QStringLiteral("comboBox_PRIVATEUP"));
        sizePolicy2.setHeightForWidth(comboBox_PRIVATEUP->sizePolicy().hasHeightForWidth());
        comboBox_PRIVATEUP->setSizePolicy(sizePolicy2);

        horizontalLayout_16->addWidget(comboBox_PRIVATEUP);


        verticalLayout_2->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_SERVERIP = new QLabel(layoutWidget1);
        label_SERVERIP->setObjectName(QStringLiteral("label_SERVERIP"));
        label_SERVERIP->setMinimumSize(QSize(155, 0));
        label_SERVERIP->setMaximumSize(QSize(155, 16777215));
        label_SERVERIP->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(label_SERVERIP);

        lineEdit_SERVERIP = new QLineEdit(layoutWidget1);
        lineEdit_SERVERIP->setObjectName(QStringLiteral("lineEdit_SERVERIP"));
        sizePolicy3.setHeightForWidth(lineEdit_SERVERIP->sizePolicy().hasHeightForWidth());
        lineEdit_SERVERIP->setSizePolicy(sizePolicy3);

        horizontalLayout_17->addWidget(lineEdit_SERVERIP);


        verticalLayout_2->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_SERVERPORT = new QLabel(layoutWidget1);
        label_SERVERPORT->setObjectName(QStringLiteral("label_SERVERPORT"));
        label_SERVERPORT->setMinimumSize(QSize(155, 0));
        label_SERVERPORT->setMaximumSize(QSize(155, 16777215));
        label_SERVERPORT->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_18->addWidget(label_SERVERPORT);

        lineEdit_SERVERPORT = new QLineEdit(layoutWidget1);
        lineEdit_SERVERPORT->setObjectName(QStringLiteral("lineEdit_SERVERPORT"));
        sizePolicy3.setHeightForWidth(lineEdit_SERVERPORT->sizePolicy().hasHeightForWidth());
        lineEdit_SERVERPORT->setSizePolicy(sizePolicy3);

        horizontalLayout_18->addWidget(lineEdit_SERVERPORT);


        verticalLayout_2->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_27 = new QLabel(layoutWidget1);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setMinimumSize(QSize(155, 0));
        label_27->setMaximumSize(QSize(155, 16777215));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(label_27);

        comboBox_PICMODE = new QComboBox(layoutWidget1);
        comboBox_PICMODE->setObjectName(QStringLiteral("comboBox_PICMODE"));
        sizePolicy2.setHeightForWidth(comboBox_PICMODE->sizePolicy().hasHeightForWidth());
        comboBox_PICMODE->setSizePolicy(sizePolicy2);

        horizontalLayout_19->addWidget(comboBox_PICMODE);

        label_28 = new QLabel(layoutWidget1);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_19->addWidget(label_28);


        verticalLayout_2->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_29 = new QLabel(layoutWidget1);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setMinimumSize(QSize(155, 0));
        label_29->setMaximumSize(QSize(155, 16777215));
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_20->addWidget(label_29);

        lineEdit_FACEPICQUAL = new QLineEdit(layoutWidget1);
        lineEdit_FACEPICQUAL->setObjectName(QStringLiteral("lineEdit_FACEPICQUAL"));
        sizePolicy3.setHeightForWidth(lineEdit_FACEPICQUAL->sizePolicy().hasHeightForWidth());
        lineEdit_FACEPICQUAL->setSizePolicy(sizePolicy3);

        horizontalLayout_20->addWidget(lineEdit_FACEPICQUAL);

        label_30 = new QLabel(layoutWidget1);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_20->addWidget(label_30);


        verticalLayout_2->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_31 = new QLabel(layoutWidget1);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setMinimumSize(QSize(155, 0));
        label_31->setMaximumSize(QSize(155, 16777215));
        label_31->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_21->addWidget(label_31);

        lineEdit_FRAMEPICQUAL = new QLineEdit(layoutWidget1);
        lineEdit_FRAMEPICQUAL->setObjectName(QStringLiteral("lineEdit_FRAMEPICQUAL"));
        sizePolicy3.setHeightForWidth(lineEdit_FRAMEPICQUAL->sizePolicy().hasHeightForWidth());
        lineEdit_FRAMEPICQUAL->setSizePolicy(sizePolicy3);

        horizontalLayout_21->addWidget(lineEdit_FRAMEPICQUAL);


        verticalLayout_2->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_32 = new QLabel(layoutWidget1);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setMinimumSize(QSize(155, 0));
        label_32->setMaximumSize(QSize(155, 16777215));
        label_32->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_22->addWidget(label_32);

        comboBox_FACEPICNAME = new QComboBox(layoutWidget1);
        comboBox_FACEPICNAME->setObjectName(QStringLiteral("comboBox_FACEPICNAME"));
        sizePolicy2.setHeightForWidth(comboBox_FACEPICNAME->sizePolicy().hasHeightForWidth());
        comboBox_FACEPICNAME->setSizePolicy(sizePolicy2);

        horizontalLayout_22->addWidget(comboBox_FACEPICNAME);


        verticalLayout_2->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_CUSTOMNAME = new QLabel(layoutWidget1);
        label_CUSTOMNAME->setObjectName(QStringLiteral("label_CUSTOMNAME"));
        label_CUSTOMNAME->setMinimumSize(QSize(155, 0));
        label_CUSTOMNAME->setMaximumSize(QSize(155, 16777215));
        label_CUSTOMNAME->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_23->addWidget(label_CUSTOMNAME);

        lineEdit_CUSTOMNAME = new QLineEdit(layoutWidget1);
        lineEdit_CUSTOMNAME->setObjectName(QStringLiteral("lineEdit_CUSTOMNAME"));
        sizePolicy3.setHeightForWidth(lineEdit_CUSTOMNAME->sizePolicy().hasHeightForWidth());
        lineEdit_CUSTOMNAME->setSizePolicy(sizePolicy3);

        horizontalLayout_23->addWidget(lineEdit_CUSTOMNAME);


        verticalLayout_2->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_34 = new QLabel(layoutWidget1);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setMinimumSize(QSize(155, 0));
        label_34->setMaximumSize(QSize(155, 16777215));
        label_34->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_24->addWidget(label_34);

        lineEdit_EXTENDVAULE = new QLineEdit(layoutWidget1);
        lineEdit_EXTENDVAULE->setObjectName(QStringLiteral("lineEdit_EXTENDVAULE"));
        sizePolicy3.setHeightForWidth(lineEdit_EXTENDVAULE->sizePolicy().hasHeightForWidth());
        lineEdit_EXTENDVAULE->setSizePolicy(sizePolicy3);

        horizontalLayout_24->addWidget(lineEdit_EXTENDVAULE);

        label_35 = new QLabel(layoutWidget1);
        label_35->setObjectName(QStringLiteral("label_35"));

        horizontalLayout_24->addWidget(label_35);


        verticalLayout_2->addLayout(horizontalLayout_24);

        btnClose = new QPushButton(ParamMeteSet);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(970, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        retranslateUi(ParamMeteSet);

        QMetaObject::connectSlotsByName(ParamMeteSet);
    } // setupUi

    void retranslateUi(QDialog *ParamMeteSet)
    {
        ParamMeteSet->setWindowTitle(QApplication::translate("ParamMeteSet", "ParamMeteSet", Q_NULLPTR));
        label_20->setText(QApplication::translate("ParamMeteSet", "\347\224\261\345\255\227\346\257\215\345\222\214\346\225\260\345\255\227\347\273\204\346\210\220,1-15\345\255\227\347\254\246\357\274\214\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", Q_NULLPTR));
        btnSave->setText(QApplication::translate("ParamMeteSet", "\344\277\235\345\255\230", Q_NULLPTR));
        btnUpdate->setText(QApplication::translate("ParamMeteSet", "\346\233\264\346\226\260", Q_NULLPTR));
        checkBox_Enable->setText(QApplication::translate("ParamMeteSet", "\345\274\200\345\205\263", Q_NULLPTR));
        label->setText(QApplication::translate("ParamMeteSet", "      \345\270\203\351\230\262\346\227\266\351\227\264\346\256\2651", Q_NULLPTR));
        checkBox_Time1->setText(QString());
        label_36->setText(QApplication::translate("ParamMeteSet", "---", Q_NULLPTR));
        label_2->setText(QApplication::translate("ParamMeteSet", "      \345\270\203\351\230\262\346\227\266\351\227\264\346\256\2652", Q_NULLPTR));
        checkBox_Time2->setText(QString());
        label_37->setText(QApplication::translate("ParamMeteSet", "---", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParamMeteSet", "            \347\201\265\346\225\217\345\272\246", Q_NULLPTR));
        label_4->setText(QApplication::translate("ParamMeteSet", "[0 - 10]", Q_NULLPTR));
        label_5->setText(QApplication::translate("ParamMeteSet", "          \346\212\223\346\213\215\346\250\241\345\274\217", Q_NULLPTR));
        label_MAXSNAPNUM->setText(QApplication::translate("ParamMeteSet", "      \346\234\200\345\244\247\346\212\223\346\213\215\346\254\241\346\225\260", Q_NULLPTR));
        label_FASTSNAPFRAMECOUNT->setText(QApplication::translate("ParamMeteSet", "      \345\277\253\351\200\237\346\212\223\346\213\215\345\270\247\346\225\260", Q_NULLPTR));
        label_9->setText(QApplication::translate("ParamMeteSet", "[10 - 1500]", Q_NULLPTR));
        label_SNAPCOUNT->setText(QApplication::translate("ParamMeteSet", "          \346\212\223\346\213\215\346\254\241\346\225\260", Q_NULLPTR));
        label_INTERERAITIME->setText(QApplication::translate("ParamMeteSet", "          \351\227\264\351\232\224\346\227\266\351\227\264", Q_NULLPTR));
        label_11->setText(QApplication::translate("ParamMeteSet", "[1 - 30S]", Q_NULLPTR));
        label_INTERERAIFRAME->setText(QApplication::translate("ParamMeteSet", "\351\227\264\351\232\224\345\270\247\346\225\260(\351\227\264\351\232\224\346\212\223\346\213\215)", Q_NULLPTR));
        label_13->setText(QApplication::translate("ParamMeteSet", "[10 - 1500]", Q_NULLPTR));
        label_INTERERAIFRAME_GATE->setText(QApplication::translate("ParamMeteSet", "\351\227\264\351\232\224\345\270\247\346\225\260(\345\215\225\344\272\272\346\250\241\345\274\217)", Q_NULLPTR));
        label_15->setText(QApplication::translate("ParamMeteSet", "[10 - 1500]", Q_NULLPTR));
        label_16->setText(QApplication::translate("ParamMeteSet", "  \344\272\272\350\204\270\350\257\206\345\210\253\346\234\200\345\260\217\345\203\217\347\264\240", Q_NULLPTR));
        label_17->setText(QApplication::translate("ParamMeteSet", "[30 - 300]", Q_NULLPTR));
        label_18->setText(QApplication::translate("ParamMeteSet", "  \344\272\272\350\204\270\350\257\206\345\210\253\346\234\200\345\244\247\345\203\217\347\264\240", Q_NULLPTR));
        label_19->setText(QApplication::translate("ParamMeteSet", "[300 - 500]", Q_NULLPTR));
        label_21->setText(QApplication::translate("ParamMeteSet", "            \345\234\272\346\231\257\346\212\223\346\213\215", Q_NULLPTR));
        label_22->setText(QApplication::translate("ParamMeteSet", "          \344\272\272\350\204\270\350\267\237\350\270\252\346\241\206", Q_NULLPTR));
        label_23->setText(QApplication::translate("ParamMeteSet", "             FTP\344\270\212\344\274\240", Q_NULLPTR));
        label_24->setText(QApplication::translate("ParamMeteSet", "        \347\247\201\346\234\211\345\215\217\350\256\256\344\270\212\344\274\240", Q_NULLPTR));
        label_SERVERIP->setText(QApplication::translate("ParamMeteSet", "          \346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", Q_NULLPTR));
        label_SERVERPORT->setText(QApplication::translate("ParamMeteSet", "          \346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", Q_NULLPTR));
        label_27->setText(QApplication::translate("ParamMeteSet", "        \345\233\276\347\211\207\344\270\212\344\274\240\346\240\274\345\274\217", Q_NULLPTR));
        label_28->setText(QApplication::translate("ParamMeteSet", "[1 - 99]", Q_NULLPTR));
        label_29->setText(QApplication::translate("ParamMeteSet", "    \344\272\272\350\204\270\345\233\276\347\211\207\347\274\226\347\240\201\350\264\250\351\207\217", Q_NULLPTR));
        label_30->setText(QApplication::translate("ParamMeteSet", "[1 - 99]", Q_NULLPTR));
        label_31->setText(QApplication::translate("ParamMeteSet", "      \345\216\237\345\233\276\347\211\207\347\274\226\347\240\201\350\264\250\351\207\217", Q_NULLPTR));
        label_32->setText(QApplication::translate("ParamMeteSet", "          \344\272\272\350\204\270\345\233\276\347\211\207\345\220\215", Q_NULLPTR));
        label_CUSTOMNAME->setText(QApplication::translate("ParamMeteSet", "          \350\207\252\345\256\232\344\271\211\345\211\215\347\274\200", Q_NULLPTR));
        label_34->setText(QApplication::translate("ParamMeteSet", "\344\272\272\350\204\270\345\221\250\350\276\271\345\214\272\345\237\237\346\211\251\345\261\225\347\263\273\346\225\260", Q_NULLPTR));
        label_35->setText(QApplication::translate("ParamMeteSet", "[0 - 10]", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ParamMeteSet: public Ui_ParamMeteSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMMETESET_H
