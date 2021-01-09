/********************************************************************************
** Form generated from reading UI file 'systemset.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSET_H
#define UI_SYSTEMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_systemSet
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QPushButton *btnClose;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_screen;
    QToolButton *toolButton_screen;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_downed;
    QToolButton *toolButton_download;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QLineEdit *lineEdit_face;
    QToolButton *toolButton_Face;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_AutoSnap;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSet;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QLineEdit *lineEdit_Length;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QComboBox *combox_StartDriver;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QComboBox *combox_EndDriver;
    QCheckBox *checkBoxCycle;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btnRecordSet;
    QWidget *tab_3;
    QGridLayout *gridLayout_7;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_Prew;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *btnpreSet;
    QWidget *tab_4;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QComboBox *comboBox_Alarm;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *checkBox_Voice;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox_Prety;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_9;
    QLineEdit *lineEdit_Alarm;
    QToolButton *btnAlarmOpen;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_18;
    QPushButton *btnAlarmSet;

    void setupUi(QWidget *systemSet)
    {
        if (systemSet->objectName().isEmpty())
            systemSet->setObjectName(QStringLiteral("systemSet"));
        systemSet->resize(806, 441);
        systemSet->setMaximumSize(QSize(1000, 800));
        gridLayout_2 = new QGridLayout(systemSet);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_7 = new QLabel(systemSet);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(12);
        label_7->setFont(font);

        horizontalLayout_5->addWidget(label_7);

        btnClose = new QPushButton(systemSet);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        horizontalLayout_5->addWidget(btnClose);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        tabWidget = new QTabWidget(systemSet);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QFont font1;
        font1.setPointSize(14);
        tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_screen = new QLineEdit(tab);
        lineEdit_screen->setObjectName(QStringLiteral("lineEdit_screen"));

        horizontalLayout->addWidget(lineEdit_screen);

        toolButton_screen = new QToolButton(tab);
        toolButton_screen->setObjectName(QStringLiteral("toolButton_screen"));

        horizontalLayout->addWidget(toolButton_screen);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_downed = new QLineEdit(tab);
        lineEdit_downed->setObjectName(QStringLiteral("lineEdit_downed"));

        horizontalLayout_2->addWidget(lineEdit_downed);

        toolButton_download = new QToolButton(tab);
        toolButton_download->setObjectName(QStringLiteral("toolButton_download"));

        horizontalLayout_2->addWidget(toolButton_download);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);

        lineEdit_face = new QLineEdit(tab);
        lineEdit_face->setObjectName(QStringLiteral("lineEdit_face"));

        horizontalLayout_3->addWidget(lineEdit_face);

        toolButton_Face = new QToolButton(tab);
        toolButton_Face->setObjectName(QStringLiteral("toolButton_Face"));

        horizontalLayout_3->addWidget(toolButton_Face);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkBox_AutoSnap = new QCheckBox(tab);
        checkBox_AutoSnap->setObjectName(QStringLiteral("checkBox_AutoSnap"));

        horizontalLayout_7->addWidget(checkBox_AutoSnap);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        btnSet = new QPushButton(tab);
        btnSet->setObjectName(QStringLiteral("btnSet"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/SystemSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSet->setIcon(icon1);

        horizontalLayout_7->addWidget(btnSet);


        gridLayout->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_8->addWidget(label_3);

        lineEdit_Length = new QLineEdit(groupBox);
        lineEdit_Length->setObjectName(QStringLiteral("lineEdit_Length"));

        horizontalLayout_8->addWidget(lineEdit_Length);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);


        gridLayout_3->addLayout(horizontalLayout_8, 0, 0, 1, 2);

        horizontalSpacer_6 = new QSpacerItem(83, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        combox_StartDriver = new QComboBox(groupBox);
        combox_StartDriver->setObjectName(QStringLiteral("combox_StartDriver"));

        horizontalLayout_9->addWidget(combox_StartDriver);


        gridLayout_3->addLayout(horizontalLayout_9, 1, 0, 2, 2);

        horizontalSpacer_7 = new QSpacerItem(83, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 1, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(83, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 2, 2, 2, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_10->addWidget(label_5);

        combox_EndDriver = new QComboBox(groupBox);
        combox_EndDriver->setObjectName(QStringLiteral("combox_EndDriver"));

        horizontalLayout_10->addWidget(combox_EndDriver);


        gridLayout_3->addLayout(horizontalLayout_10, 3, 0, 1, 2);

        checkBoxCycle = new QCheckBox(groupBox);
        checkBoxCycle->setObjectName(QStringLiteral("checkBoxCycle"));

        gridLayout_3->addWidget(checkBoxCycle, 4, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(87, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 4, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(83, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 5, 3, 1, 1);

        btnRecordSet = new QPushButton(groupBox);
        btnRecordSet->setObjectName(QStringLiteral("btnRecordSet"));
        btnRecordSet->setIcon(icon1);

        gridLayout_3->addWidget(btnRecordSet, 5, 4, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_7 = new QGridLayout(tab_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        widget = new QWidget(tab_3);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        checkBox_Prew = new QCheckBox(widget);
        checkBox_Prew->setObjectName(QStringLiteral("checkBox_Prew"));

        horizontalLayout_4->addWidget(checkBox_Prew);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_5->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget, 0, 0, 1, 2);

        horizontalSpacer_13 = new QSpacerItem(152, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_13, 1, 0, 1, 1);

        btnpreSet = new QPushButton(tab_3);
        btnpreSet->setObjectName(QStringLiteral("btnpreSet"));
        btnpreSet->setIcon(icon1);

        gridLayout_7->addWidget(btnpreSet, 1, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_6 = new QGridLayout(tab_4);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_12->addWidget(label_8);

        comboBox_Alarm = new QComboBox(tab_4);
        comboBox_Alarm->setObjectName(QStringLiteral("comboBox_Alarm"));
        comboBox_Alarm->setMinimumSize(QSize(120, 0));

        horizontalLayout_12->addWidget(comboBox_Alarm);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_14);


        gridLayout_6->addLayout(horizontalLayout_12, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        checkBox_Voice = new QCheckBox(tab_4);
        checkBox_Voice->setObjectName(QStringLiteral("checkBox_Voice"));

        horizontalLayout_13->addWidget(checkBox_Voice);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_15);


        gridLayout_6->addLayout(horizontalLayout_13, 1, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        checkBox_Prety = new QCheckBox(tab_4);
        checkBox_Prety->setObjectName(QStringLiteral("checkBox_Prety"));

        horizontalLayout_14->addWidget(checkBox_Prety);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_16);


        gridLayout_6->addLayout(horizontalLayout_14, 2, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_15->addWidget(label_9);

        lineEdit_Alarm = new QLineEdit(tab_4);
        lineEdit_Alarm->setObjectName(QStringLiteral("lineEdit_Alarm"));

        horizontalLayout_15->addWidget(lineEdit_Alarm);

        btnAlarmOpen = new QToolButton(tab_4);
        btnAlarmOpen->setObjectName(QStringLiteral("btnAlarmOpen"));

        horizontalLayout_15->addWidget(btnAlarmOpen);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_17);


        gridLayout_6->addLayout(horizontalLayout_15, 3, 0, 1, 2);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_18);

        btnAlarmSet = new QPushButton(tab_4);
        btnAlarmSet->setObjectName(QStringLiteral("btnAlarmSet"));
        btnAlarmSet->setIcon(icon1);

        horizontalLayout_16->addWidget(btnAlarmSet);


        gridLayout_6->addLayout(horizontalLayout_16, 4, 1, 1, 1);

        tabWidget->addTab(tab_4, QString());

        gridLayout_2->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(systemSet);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(systemSet);
    } // setupUi

    void retranslateUi(QWidget *systemSet)
    {
        systemSet->setWindowTitle(QApplication::translate("systemSet", "systemSet", Q_NULLPTR));
        label_7->setText(QApplication::translate("systemSet", "  \347\263\273\347\273\237\350\256\276\347\275\256", Q_NULLPTR));
        btnClose->setText(QString());
        label->setText(QApplication::translate("systemSet", "\346\212\223\345\233\276\350\267\257\345\276\204\357\274\232    ", Q_NULLPTR));
        toolButton_screen->setText(QApplication::translate("systemSet", "...", Q_NULLPTR));
        label_2->setText(QApplication::translate("systemSet", "\344\270\213\350\275\275\350\267\257\345\276\204\357\274\232    ", Q_NULLPTR));
        toolButton_download->setText(QApplication::translate("systemSet", "...", Q_NULLPTR));
        label_10->setText(QApplication::translate("systemSet", "\344\272\272\350\204\270\345\233\276\347\211\207\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        toolButton_Face->setText(QApplication::translate("systemSet", "...", Q_NULLPTR));
        checkBox_AutoSnap->setText(QApplication::translate("systemSet", "\350\207\252\345\212\250\345\274\200\345\220\257\346\212\223\346\213\215", Q_NULLPTR));
        btnSet->setText(QApplication::translate("systemSet", "\350\256\276\347\275\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("systemSet", "\350\267\257\345\276\204\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("systemSet", "\346\234\254\345\234\260\345\275\225\345\203\217\345\217\202\346\225\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("systemSet", "\345\275\225\345\203\217\346\226\207\344\273\266\351\225\277\345\272\246", Q_NULLPTR));
        label_6->setText(QApplication::translate("systemSet", "\345\210\206", Q_NULLPTR));
        label_4->setText(QApplication::translate("systemSet", "\345\275\225\345\203\217\345\274\200\345\247\213\351\251\261\345\212\250\345\231\250", Q_NULLPTR));
        label_5->setText(QApplication::translate("systemSet", "\345\275\225\345\203\217\347\273\223\346\235\237\351\251\261\345\212\250\345\231\250", Q_NULLPTR));
        checkBoxCycle->setText(QApplication::translate("systemSet", "\345\276\252\347\216\257\350\246\206\347\233\226", Q_NULLPTR));
        btnRecordSet->setText(QApplication::translate("systemSet", "\350\256\276\347\275\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("systemSet", "\346\234\254\345\234\260\345\275\225\345\203\217", Q_NULLPTR));
        checkBox_Prew->setText(QApplication::translate("systemSet", "\345\220\257\345\212\250\346\227\266\350\207\252\345\212\250\346\201\242\345\244\215\344\270\212\344\270\200\346\254\241\351\200\200\345\207\272\345\256\242\346\210\267\347\253\257\347\232\204\351\242\204\350\247\210\347\225\214\351\235\242", Q_NULLPTR));
        btnpreSet->setText(QApplication::translate("systemSet", "\350\256\276\347\275\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("systemSet", "\351\242\204\350\247\210\350\256\276\347\275\256", Q_NULLPTR));
        label_8->setText(QApplication::translate("systemSet", "\346\212\245\350\255\246\346\272\220", Q_NULLPTR));
        comboBox_Alarm->clear();
        comboBox_Alarm->insertItems(0, QStringList()
         << QApplication::translate("systemSet", "\346\212\245\350\255\246\350\276\223\345\205\245", Q_NULLPTR)
         << QApplication::translate("systemSet", "\347\247\273\345\212\250\346\212\245\350\255\246", Q_NULLPTR)
         << QApplication::translate("systemSet", "\350\247\206\351\242\221\344\270\242\345\244\261", Q_NULLPTR)
         << QApplication::translate("systemSet", "\347\241\254\347\233\230\346\215\237\345\235\217", Q_NULLPTR)
         << QApplication::translate("systemSet", "\345\221\212\350\255\246\350\256\276\345\244\207", Q_NULLPTR)
         << QApplication::translate("systemSet", "\351\201\256\346\214\241\346\212\245\350\255\246", Q_NULLPTR)
         << QApplication::translate("systemSet", "\344\272\256\345\272\246\345\274\202\345\270\270", Q_NULLPTR)
         << QApplication::translate("systemSet", "\350\247\206\351\242\221\345\274\202\345\270\270", Q_NULLPTR)
         << QApplication::translate("systemSet", "\350\266\212\347\225\214\344\276\246\346\265\213", Q_NULLPTR)
         << QApplication::translate("systemSet", "\345\214\272\345\237\237\345\205\245\344\276\265", Q_NULLPTR)
         << QApplication::translate("systemSet", "\351\242\234\350\211\262\345\274\202\345\270\270", Q_NULLPTR)
         << QApplication::translate("systemSet", "\345\243\260\351\237\263\345\274\202\345\270\270", Q_NULLPTR)
         << QApplication::translate("systemSet", "\351\201\227\347\225\231\347\211\251", Q_NULLPTR)
        );
        checkBox_Voice->setText(QApplication::translate("systemSet", "\345\243\260\351\237\263\346\217\220\351\206\222", Q_NULLPTR));
        checkBox_Prety->setText(QApplication::translate("systemSet", "\351\207\215\345\244\215\346\222\255\346\224\276\345\243\260\351\237\263", Q_NULLPTR));
        label_9->setText(QApplication::translate("systemSet", "\345\243\260\351\237\263\346\226\207\344\273\266", Q_NULLPTR));
        btnAlarmOpen->setText(QApplication::translate("systemSet", "\346\265\217\350\247\210...", Q_NULLPTR));
        btnAlarmSet->setText(QApplication::translate("systemSet", "\350\256\276\347\275\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("systemSet", "\345\221\212\350\255\246\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class systemSet: public Ui_systemSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSET_H
