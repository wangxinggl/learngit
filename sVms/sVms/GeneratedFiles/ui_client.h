/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "animationbutton.h"
#include "cpumemorylabel.h"

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QAction *screenAction;
    QAction *videoAction;
    QAction *logAction;
    QAction *exitAction;
    QAction *yuntaiAction;
    QAction *action1024_768;
    QAction *action1280_1024;
    QAction *action1440_900;
    QAction *maxAction;
    QAction *equipmentAction;
    QAction *userAction;
    QAction *faceAction;
    QAction *logSearchAction;
    QAction *systemAction;
    QAction *playBackAction;
    QAction *lockAction;
    QAction *MapAction;
    QAction *eyeAction;
    QAction *skinAaction;
    QAction *aboutAction;
    QAction *preViewAction;
    QAction *AlarmLogAction;
    QAction *previewAction;
    QAction *actionHomePage;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QPushButton *btnMenu_Max;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Close;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_Operator;
    AnimationButton *widget_user;
    QLabel *label_5;
    AnimationButton *widget_face;
    QLabel *label_6;
    AnimationButton *widget_equiment;
    QLabel *label_8;
    AnimationButton *widget_Log;
    QLabel *label_9;
    QLabel *label_Config;
    AnimationButton *widget_Prew;
    QLabel *label_10;
    AnimationButton *widget_PlayBack;
    QLabel *label_11;
    AnimationButton *widget_set;
    QLabel *label_12;
    AnimationButton *widget_DevicePara;
    QLabel *label_13;
    QPushButton *btnSetLanguage;
    CpuMemoryLabel *labCPUMemory;

    void setupUi(QMainWindow *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QStringLiteral("ClientClass"));
        ClientClass->resize(1027, 820);
        screenAction = new QAction(ClientClass);
        screenAction->setObjectName(QStringLiteral("screenAction"));
        videoAction = new QAction(ClientClass);
        videoAction->setObjectName(QStringLiteral("videoAction"));
        logAction = new QAction(ClientClass);
        logAction->setObjectName(QStringLiteral("logAction"));
        exitAction = new QAction(ClientClass);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("\351\200\200\345\207\272");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral(":/res/SoftIcon/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        exitAction->setIcon(icon);
        yuntaiAction = new QAction(ClientClass);
        yuntaiAction->setObjectName(QStringLiteral("yuntaiAction"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/PZTControl.png"), QSize(), QIcon::Normal, QIcon::Off);
        yuntaiAction->setIcon(icon1);
        action1024_768 = new QAction(ClientClass);
        action1024_768->setObjectName(QStringLiteral("action1024_768"));
        action1280_1024 = new QAction(ClientClass);
        action1280_1024->setObjectName(QStringLiteral("action1280_1024"));
        action1440_900 = new QAction(ClientClass);
        action1440_900->setObjectName(QStringLiteral("action1440_900"));
        maxAction = new QAction(ClientClass);
        maxAction->setObjectName(QStringLiteral("maxAction"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/SoftIcon/Max.png"), QSize(), QIcon::Normal, QIcon::Off);
        maxAction->setIcon(icon2);
        equipmentAction = new QAction(ClientClass);
        equipmentAction->setObjectName(QStringLiteral("equipmentAction"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/SoftIcon/EaimentSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        equipmentAction->setIcon(icon3);
        userAction = new QAction(ClientClass);
        userAction->setObjectName(QStringLiteral("userAction"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/SoftIcon/UserSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        userAction->setIcon(icon4);
        faceAction = new QAction(ClientClass);
        faceAction->setObjectName(QStringLiteral("faceAction"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/SoftIcon/faceSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        faceAction->setIcon(icon5);
        logSearchAction = new QAction(ClientClass);
        logSearchAction->setObjectName(QStringLiteral("logSearchAction"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/SoftIcon/LogSearch.png"), QSize(), QIcon::Normal, QIcon::Off);
        logSearchAction->setIcon(icon6);
        systemAction = new QAction(ClientClass);
        systemAction->setObjectName(QStringLiteral("systemAction"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/res/SoftIcon/SystemSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        systemAction->setIcon(icon7);
        playBackAction = new QAction(ClientClass);
        playBackAction->setObjectName(QStringLiteral("playBackAction"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/res/SoftIcon/VideoPlayBack.png"), QSize(), QIcon::Normal, QIcon::Off);
        playBackAction->setIcon(icon8);
        lockAction = new QAction(ClientClass);
        lockAction->setObjectName(QStringLiteral("lockAction"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/res/SoftIcon/Lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        lockAction->setIcon(icon9);
        MapAction = new QAction(ClientClass);
        MapAction->setObjectName(QStringLiteral("MapAction"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/res/SoftIcon/Map.png"), QSize(), QIcon::Normal, QIcon::Off);
        MapAction->setIcon(icon10);
        eyeAction = new QAction(ClientClass);
        eyeAction->setObjectName(QStringLiteral("eyeAction"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Client/res/eye.ico"), QSize(), QIcon::Normal, QIcon::Off);
        eyeAction->setIcon(icon11);
        skinAaction = new QAction(ClientClass);
        skinAaction->setObjectName(QStringLiteral("skinAaction"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/res/SoftIcon/Skin.png"), QSize(), QIcon::Normal, QIcon::Off);
        skinAaction->setIcon(icon12);
        aboutAction = new QAction(ClientClass);
        aboutAction->setObjectName(QStringLiteral("aboutAction"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/res/SoftIcon/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        aboutAction->setIcon(icon13);
        preViewAction = new QAction(ClientClass);
        preViewAction->setObjectName(QStringLiteral("preViewAction"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/res/SoftIcon/Prew.png"), QSize(), QIcon::Normal, QIcon::Off);
        preViewAction->setIcon(icon14);
        AlarmLogAction = new QAction(ClientClass);
        AlarmLogAction->setObjectName(QStringLiteral("AlarmLogAction"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/res/SoftIcon/AlarmLog.png"), QSize(), QIcon::Normal, QIcon::Off);
        AlarmLogAction->setIcon(icon15);
        previewAction = new QAction(ClientClass);
        previewAction->setObjectName(QStringLiteral("previewAction"));
        previewAction->setCheckable(true);
        QIcon icon16;
        iconThemeName = QString::fromUtf8("\344\270\273\351\242\204\350\247\210");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon16 = QIcon::fromTheme(iconThemeName);
        } else {
            icon16.addFile(QStringLiteral(":/Client/res/Preview_48px_1093402_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        }
        previewAction->setIcon(icon16);
        previewAction->setIconVisibleInMenu(true);
        previewAction->setPriority(QAction::NormalPriority);
        actionHomePage = new QAction(ClientClass);
        actionHomePage->setObjectName(QStringLiteral("actionHomePage"));
        centralWidget = new QWidget(ClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setMaximumSize(QSize(16777215, 30));
        label_3->setStyleSheet(QStringLiteral("font: 20pt \"Microsoft JhengHei\";"));

        gridLayout->addWidget(label_3, 0, 1, 2, 1);

        horizontalSpacer = new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(0, 30));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/res/SoftIcon/logo.png")));
        label_2->setScaledContents(true);

        gridLayout->addWidget(label_2, 0, 0, 2, 1);

        btnMenu_Max = new QPushButton(centralWidget);
        btnMenu_Max->setObjectName(QStringLiteral("btnMenu_Max"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
        btnMenu_Max->setSizePolicy(sizePolicy);
        btnMenu_Max->setMinimumSize(QSize(30, 30));
        btnMenu_Max->setMaximumSize(QSize(30, 30));
        btnMenu_Max->setFocusPolicy(Qt::NoFocus);
        btnMenu_Max->setStyleSheet(QStringLiteral(""));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/res/SoftIcon/+.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Max->setIcon(icon17);
        btnMenu_Max->setIconSize(QSize(25, 25));

        gridLayout->addWidget(btnMenu_Max, 0, 6, 1, 1);

        btnMenu_Min = new QPushButton(centralWidget);
        btnMenu_Min->setObjectName(QStringLiteral("btnMenu_Min"));
        sizePolicy.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy);
        btnMenu_Min->setMinimumSize(QSize(30, 30));
        btnMenu_Min->setMaximumSize(QSize(30, 30));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/res/SoftIcon/-.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Min->setIcon(icon18);
        btnMenu_Min->setIconSize(QSize(25, 25));

        gridLayout->addWidget(btnMenu_Min, 0, 5, 1, 1);

        btnMenu_Close = new QPushButton(centralWidget);
        btnMenu_Close->setObjectName(QStringLiteral("btnMenu_Close"));
        sizePolicy.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy);
        btnMenu_Close->setMinimumSize(QSize(30, 30));
        btnMenu_Close->setMaximumSize(QSize(30, 30));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);
        btnMenu_Close->setStyleSheet(QStringLiteral(""));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Close->setIcon(icon19);
        btnMenu_Close->setIconSize(QSize(25, 25));

        gridLayout->addWidget(btnMenu_Close, 0, 7, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setStyleSheet(QLatin1String("QTabBar::tab{width:175;height:34\n"
";font: 13pt \"Microsoft YaHei UI\";}\n"
"\n"
""));
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_Operator = new QLabel(tab);
        label_Operator->setObjectName(QStringLiteral("label_Operator"));
        label_Operator->setGeometry(QRect(10, 20, 951, 23));
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_Operator->setFont(font);
        label_Operator->setStyleSheet(QStringLiteral("background-color: rgb(58, 58, 58);"));
        label_Operator->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        widget_user = new AnimationButton(tab);
        widget_user->setObjectName(QStringLiteral("widget_user"));
        widget_user->setGeometry(QRect(350, 290, 151, 141));
        widget_user->setMinimumSize(QSize(151, 141));
        widget_user->setMaximumSize(QSize(151, 141));
        label_5 = new QLabel(widget_user);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 120, 151, 21));
        label_5->setMinimumSize(QSize(151, 21));
        label_5->setMaximumSize(QSize(151, 21));
        label_5->setAlignment(Qt::AlignCenter);
        widget_face = new AnimationButton(tab);
        widget_face->setObjectName(QStringLiteral("widget_face"));
        widget_face->setGeometry(QRect(590, 70, 151, 141));
        widget_face->setMinimumSize(QSize(151, 141));
        widget_face->setMaximumSize(QSize(151, 141));
        label_6 = new QLabel(widget_face);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(0, 120, 151, 21));
        label_6->setMinimumSize(QSize(151, 21));
        label_6->setMaximumSize(QSize(151, 21));
        label_6->setAlignment(Qt::AlignCenter);
        widget_equiment = new AnimationButton(tab);
        widget_equiment->setObjectName(QStringLiteral("widget_equiment"));
        widget_equiment->setGeometry(QRect(110, 290, 151, 141));
        widget_equiment->setMinimumSize(QSize(151, 141));
        widget_equiment->setMaximumSize(QSize(151, 141));
        label_8 = new QLabel(widget_equiment);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 120, 151, 21));
        label_8->setMinimumSize(QSize(151, 21));
        label_8->setMaximumSize(QSize(151, 21));
        label_8->setAlignment(Qt::AlignCenter);
        widget_Log = new AnimationButton(tab);
        widget_Log->setObjectName(QStringLiteral("widget_Log"));
        widget_Log->setGeometry(QRect(830, 290, 151, 141));
        widget_Log->setMinimumSize(QSize(151, 141));
        widget_Log->setMaximumSize(QSize(151, 141));
        label_9 = new QLabel(widget_Log);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(0, 120, 151, 21));
        label_9->setMinimumSize(QSize(151, 21));
        label_9->setMaximumSize(QSize(151, 21));
        label_9->setAlignment(Qt::AlignCenter);
        label_Config = new QLabel(tab);
        label_Config->setObjectName(QStringLiteral("label_Config"));
        label_Config->setGeometry(QRect(10, 250, 951, 23));
        label_Config->setFont(font);
        label_Config->setStyleSheet(QStringLiteral("background-color: rgb(58, 58, 58);"));
        label_Config->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        widget_Prew = new AnimationButton(tab);
        widget_Prew->setObjectName(QStringLiteral("widget_Prew"));
        widget_Prew->setGeometry(QRect(110, 70, 151, 141));
        widget_Prew->setMinimumSize(QSize(151, 141));
        widget_Prew->setMaximumSize(QSize(151, 141));
        label_10 = new QLabel(widget_Prew);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(0, 120, 151, 21));
        label_10->setMaximumSize(QSize(151, 21));
        label_10->setAlignment(Qt::AlignCenter);
        widget_PlayBack = new AnimationButton(tab);
        widget_PlayBack->setObjectName(QStringLiteral("widget_PlayBack"));
        widget_PlayBack->setGeometry(QRect(350, 70, 151, 141));
        widget_PlayBack->setMinimumSize(QSize(151, 141));
        widget_PlayBack->setMaximumSize(QSize(151, 141));
        label_11 = new QLabel(widget_PlayBack);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(0, 120, 151, 21));
        label_11->setMinimumSize(QSize(151, 21));
        label_11->setMaximumSize(QSize(151, 21));
        label_11->setAlignment(Qt::AlignCenter);
        widget_set = new AnimationButton(tab);
        widget_set->setObjectName(QStringLiteral("widget_set"));
        widget_set->setGeometry(QRect(590, 290, 151, 141));
        widget_set->setMinimumSize(QSize(151, 141));
        widget_set->setMaximumSize(QSize(151, 141));
        label_12 = new QLabel(widget_set);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(0, 120, 151, 21));
        label_12->setMinimumSize(QSize(151, 21));
        label_12->setMaximumSize(QSize(151, 21));
        label_12->setAlignment(Qt::AlignCenter);
        widget_DevicePara = new AnimationButton(tab);
        widget_DevicePara->setObjectName(QStringLiteral("widget_DevicePara"));
        widget_DevicePara->setGeometry(QRect(110, 480, 151, 141));
        widget_DevicePara->setMinimumSize(QSize(151, 141));
        widget_DevicePara->setMaximumSize(QSize(151, 141));
        label_13 = new QLabel(widget_DevicePara);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(0, 120, 151, 21));
        label_13->setMinimumSize(QSize(151, 21));
        label_13->setMaximumSize(QSize(151, 21));
        label_13->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 3, 0, 1, 8);

        btnSetLanguage = new QPushButton(centralWidget);
        btnSetLanguage->setObjectName(QStringLiteral("btnSetLanguage"));
        sizePolicy.setHeightForWidth(btnSetLanguage->sizePolicy().hasHeightForWidth());
        btnSetLanguage->setSizePolicy(sizePolicy);
        btnSetLanguage->setMaximumSize(QSize(30, 30));
        btnSetLanguage->setStyleSheet(QStringLiteral("QPushButton::menu-indicator{image:none;}"));
        btnSetLanguage->setIconSize(QSize(30, 30));

        gridLayout->addWidget(btnSetLanguage, 0, 4, 1, 1);

        labCPUMemory = new CpuMemoryLabel(centralWidget);
        labCPUMemory->setObjectName(QStringLiteral("labCPUMemory"));
        labCPUMemory->setMinimumSize(QSize(140, 15));
        labCPUMemory->setMaximumSize(QSize(200, 10));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(8);
        labCPUMemory->setFont(font1);
        labCPUMemory->setAutoFillBackground(false);
        labCPUMemory->setFrameShape(QFrame::NoFrame);
        labCPUMemory->setScaledContents(true);
        labCPUMemory->setAlignment(Qt::AlignCenter);
        labCPUMemory->setWordWrap(true);

        gridLayout->addWidget(labCPUMemory, 0, 3, 1, 1);

        ClientClass->setCentralWidget(centralWidget);

        retranslateUi(ClientClass);

        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ClientClass)
    {
        ClientClass->setWindowTitle(QApplication::translate("ClientClass", "Client", Q_NULLPTR));
        screenAction->setText(QApplication::translate("ClientClass", "\346\212\223\345\233\276\346\226\207\344\273\266", Q_NULLPTR));
        videoAction->setText(QApplication::translate("ClientClass", "\350\247\206\351\242\221\346\226\207\344\273\266", Q_NULLPTR));
        logAction->setText(QApplication::translate("ClientClass", "\346\227\245\345\277\227\346\226\207\344\273\266", Q_NULLPTR));
        exitAction->setText(QApplication::translate("ClientClass", "\351\200\200\345\207\272", Q_NULLPTR));
        yuntaiAction->setText(QApplication::translate("ClientClass", "\344\272\221\345\217\260\346\216\247\345\210\266", Q_NULLPTR));
        action1024_768->setText(QApplication::translate("ClientClass", "1024*768", Q_NULLPTR));
        action1280_1024->setText(QApplication::translate("ClientClass", "1280*1024", Q_NULLPTR));
        action1440_900->setText(QApplication::translate("ClientClass", "1440*900", Q_NULLPTR));
        maxAction->setText(QApplication::translate("ClientClass", "\346\234\200\345\244\247\345\214\226", Q_NULLPTR));
        equipmentAction->setText(QApplication::translate("ClientClass", "\350\256\276\345\244\207\347\256\241\347\220\206", Q_NULLPTR));
        userAction->setText(QApplication::translate("ClientClass", "\347\224\250\346\210\267\347\256\241\347\220\206", Q_NULLPTR));
        faceAction->setText(QApplication::translate("ClientClass", "\344\272\272\350\204\270\347\256\241\347\220\206", Q_NULLPTR));
        logSearchAction->setText(QApplication::translate("ClientClass", "\346\227\245\345\277\227\346\220\234\347\264\242", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        logSearchAction->setToolTip(QApplication::translate("ClientClass", "\350\256\276\345\244\207\346\227\245\345\277\227", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        systemAction->setText(QApplication::translate("ClientClass", "\347\263\273\347\273\237\350\256\276\347\275\256", Q_NULLPTR));
        playBackAction->setText(QApplication::translate("ClientClass", "\350\247\206\351\242\221\346\221\230\350\246\201\345\233\236\346\224\276", Q_NULLPTR));
        lockAction->setText(QApplication::translate("ClientClass", "\345\212\240\351\224\201", Q_NULLPTR));
        MapAction->setText(QApplication::translate("ClientClass", "\347\224\265\345\255\220\345\234\260\345\233\276", Q_NULLPTR));
        eyeAction->setText(QApplication::translate("ClientClass", "\351\223\272\345\271\263\351\242\204\350\247\210", Q_NULLPTR));
        skinAaction->setText(QApplication::translate("ClientClass", "\345\210\207\346\215\242\347\232\256\350\202\244", Q_NULLPTR));
        aboutAction->setText(QApplication::translate("ClientClass", "\345\205\263\344\272\216", Q_NULLPTR));
        preViewAction->setText(QApplication::translate("ClientClass", "\351\242\204\350\247\210", Q_NULLPTR));
        AlarmLogAction->setText(QApplication::translate("ClientClass", "\345\221\212\350\255\246\346\227\245\345\277\227", Q_NULLPTR));
        previewAction->setText(QApplication::translate("ClientClass", "\346\231\272\350\203\275\350\257\206\345\210\253", Q_NULLPTR));
        actionHomePage->setText(QApplication::translate("ClientClass", "\351\246\226\351\241\265", Q_NULLPTR));
        label_3->setText(QApplication::translate("ClientClass", "sVMS2000", Q_NULLPTR));
        label_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Max->setToolTip(QApplication::translate("ClientClass", "\346\234\200\345\244\247\345\214\226", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnMenu_Max->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Min->setToolTip(QApplication::translate("ClientClass", "\346\234\200\345\260\217\345\214\226", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnMenu_Min->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("ClientClass", "\345\205\263\351\227\255", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        label_Operator->setText(QApplication::translate("ClientClass", "\346\223\215\344\275\234", Q_NULLPTR));
        label_5->setText(QApplication::translate("ClientClass", "\347\224\250\346\210\267\347\256\241\347\220\206", Q_NULLPTR));
        label_6->setText(QApplication::translate("ClientClass", "\344\272\272\350\204\270\347\256\241\347\220\206", Q_NULLPTR));
        label_8->setText(QApplication::translate("ClientClass", "\350\256\276\345\244\207\347\256\241\347\220\206", Q_NULLPTR));
        label_9->setText(QApplication::translate("ClientClass", "\346\227\245\345\277\227", Q_NULLPTR));
        label_Config->setText(QApplication::translate("ClientClass", "\351\205\215\347\275\256", Q_NULLPTR));
        label_10->setText(QApplication::translate("ClientClass", "\351\242\204\350\247\210", Q_NULLPTR));
        label_11->setText(QApplication::translate("ClientClass", "\350\247\206\351\242\221\345\233\236\346\224\276", Q_NULLPTR));
        label_12->setText(QApplication::translate("ClientClass", "\350\256\276\347\275\256", Q_NULLPTR));
        label_13->setText(QApplication::translate("ClientClass", "\350\256\276\345\244\207\351\205\215\347\275\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ClientClass", "\351\246\226\351\241\265", Q_NULLPTR));
        btnSetLanguage->setText(QString());
        labCPUMemory->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
