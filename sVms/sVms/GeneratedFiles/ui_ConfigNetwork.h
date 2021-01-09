/********************************************************************************
** Form generated from reading UI file 'ConfigNetwork.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGNETWORK_H
#define UI_CONFIGNETWORK_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigNetwork
{
public:
    QPushButton *btnSave;
    QPushButton *btnUpGrade;
    QPushButton *btnClose;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_PRIMARYDNS;
    QPushButton *btnDNSSave;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *lineEdit_SECONDARYDNS;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_NETIPMASK;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLineEdit *lineEdit_MAC1;
    QLabel *label_11;
    QLineEdit *lineEdit_MAC2;
    QLabel *label_12;
    QLineEdit *lineEdit_MAC3;
    QLabel *label_13;
    QLineEdit *lineEdit_MAC4;
    QLabel *label_14;
    QLineEdit *lineEdit_MAC5;
    QLabel *label_15;
    QLineEdit *lineEdit_MAC6;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLineEdit *lineEdit_TCPPORT;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_NETGATEWAY;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_NETIP;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QLineEdit *lineEdit_HTTPPORT;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnIPSave;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_NETCARD;
    QCheckBox *checkBox_DHCPEnable;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_Downed;
    QCheckBox *checkBox_HIGHTLOADDOWN;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_chuanshu;
    QComboBox *comboBox_TRANSFERPOLICY;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnDownSave;

    void setupUi(QWidget *ConfigNetwork)
    {
        if (ConfigNetwork->objectName().isEmpty())
            ConfigNetwork->setObjectName(QStringLiteral("ConfigNetwork"));
        ConfigNetwork->resize(706, 509);
        btnSave = new QPushButton(ConfigNetwork);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(200, 460, 75, 23));
        btnUpGrade = new QPushButton(ConfigNetwork);
        btnUpGrade->setObjectName(QStringLiteral("btnUpGrade"));
        btnUpGrade->setGeometry(QRect(300, 460, 75, 23));
        btnClose = new QPushButton(ConfigNetwork);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(670, 10, 30, 30));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnClose->sizePolicy().hasHeightForWidth());
        btnClose->setSizePolicy(sizePolicy);
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));
        groupBox = new QGroupBox(ConfigNetwork);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 150, 541, 82));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(label_6);

        lineEdit_PRIMARYDNS = new QLineEdit(groupBox);
        lineEdit_PRIMARYDNS->setObjectName(QStringLiteral("lineEdit_PRIMARYDNS"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_PRIMARYDNS->sizePolicy().hasHeightForWidth());
        lineEdit_PRIMARYDNS->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(lineEdit_PRIMARYDNS);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        btnDNSSave = new QPushButton(groupBox);
        btnDNSSave->setObjectName(QStringLiteral("btnDNSSave"));

        gridLayout->addWidget(btnDNSSave, 0, 1, 2, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(80, 0));
        label_7->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_6->addWidget(label_7);

        lineEdit_SECONDARYDNS = new QLineEdit(groupBox);
        lineEdit_SECONDARYDNS->setObjectName(QStringLiteral("lineEdit_SECONDARYDNS"));
        sizePolicy1.setHeightForWidth(lineEdit_SECONDARYDNS->sizePolicy().hasHeightForWidth());
        lineEdit_SECONDARYDNS->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(lineEdit_SECONDARYDNS);


        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(ConfigNetwork);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 240, 541, 211));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_NETIPMASK = new QLineEdit(groupBox_2);
        lineEdit_NETIPMASK->setObjectName(QStringLiteral("lineEdit_NETIPMASK"));
        sizePolicy1.setHeightForWidth(lineEdit_NETIPMASK->sizePolicy().hasHeightForWidth());
        lineEdit_NETIPMASK->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_NETIPMASK);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(80, 0));
        label_8->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(label_8);

        lineEdit_MAC1 = new QLineEdit(groupBox_2);
        lineEdit_MAC1->setObjectName(QStringLiteral("lineEdit_MAC1"));
        lineEdit_MAC1->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_MAC1->sizePolicy().hasHeightForWidth());
        lineEdit_MAC1->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_MAC1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_7->addWidget(label_11);

        lineEdit_MAC2 = new QLineEdit(groupBox_2);
        lineEdit_MAC2->setObjectName(QStringLiteral("lineEdit_MAC2"));
        lineEdit_MAC2->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_MAC2->sizePolicy().hasHeightForWidth());
        lineEdit_MAC2->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_MAC2);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_7->addWidget(label_12);

        lineEdit_MAC3 = new QLineEdit(groupBox_2);
        lineEdit_MAC3->setObjectName(QStringLiteral("lineEdit_MAC3"));
        lineEdit_MAC3->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_MAC3->sizePolicy().hasHeightForWidth());
        lineEdit_MAC3->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_MAC3);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_7->addWidget(label_13);

        lineEdit_MAC4 = new QLineEdit(groupBox_2);
        lineEdit_MAC4->setObjectName(QStringLiteral("lineEdit_MAC4"));
        lineEdit_MAC4->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_MAC4->sizePolicy().hasHeightForWidth());
        lineEdit_MAC4->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_MAC4);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_7->addWidget(label_14);

        lineEdit_MAC5 = new QLineEdit(groupBox_2);
        lineEdit_MAC5->setObjectName(QStringLiteral("lineEdit_MAC5"));
        lineEdit_MAC5->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_MAC5->sizePolicy().hasHeightForWidth());
        lineEdit_MAC5->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_MAC5);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_7->addWidget(label_15);

        lineEdit_MAC6 = new QLineEdit(groupBox_2);
        lineEdit_MAC6->setObjectName(QStringLiteral("lineEdit_MAC6"));
        lineEdit_MAC6->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_MAC6->sizePolicy().hasHeightForWidth());
        lineEdit_MAC6->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(lineEdit_MAC6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(80, 0));
        label_9->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_8->addWidget(label_9);

        lineEdit_TCPPORT = new QLineEdit(groupBox_2);
        lineEdit_TCPPORT->setObjectName(QStringLiteral("lineEdit_TCPPORT"));
        sizePolicy1.setHeightForWidth(lineEdit_TCPPORT->sizePolicy().hasHeightForWidth());
        lineEdit_TCPPORT->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(lineEdit_TCPPORT);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_8, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(label_4);

        lineEdit_NETGATEWAY = new QLineEdit(groupBox_2);
        lineEdit_NETGATEWAY->setObjectName(QStringLiteral("lineEdit_NETGATEWAY"));
        sizePolicy1.setHeightForWidth(lineEdit_NETGATEWAY->sizePolicy().hasHeightForWidth());
        lineEdit_NETGATEWAY->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(lineEdit_NETGATEWAY);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(80, 0));
        label_2->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_NETIP = new QLineEdit(groupBox_2);
        lineEdit_NETIP->setObjectName(QStringLiteral("lineEdit_NETIP"));
        sizePolicy1.setHeightForWidth(lineEdit_NETIP->sizePolicy().hasHeightForWidth());
        lineEdit_NETIP->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_NETIP);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(80, 0));
        label_10->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(label_10);

        lineEdit_HTTPPORT = new QLineEdit(groupBox_2);
        lineEdit_HTTPPORT->setObjectName(QStringLiteral("lineEdit_HTTPPORT"));
        sizePolicy1.setHeightForWidth(lineEdit_HTTPPORT->sizePolicy().hasHeightForWidth());
        lineEdit_HTTPPORT->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(lineEdit_HTTPPORT);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_9, 5, 0, 1, 1);

        btnIPSave = new QPushButton(groupBox_2);
        btnIPSave->setObjectName(QStringLiteral("btnIPSave"));

        gridLayout_2->addWidget(btnIPSave, 5, 1, 1, 1);

        groupBox_3 = new QGroupBox(ConfigNetwork);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(40, 50, 541, 98));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(80, 0));
        label->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(label);

        comboBox_NETCARD = new QComboBox(groupBox_3);
        comboBox_NETCARD->setObjectName(QStringLiteral("comboBox_NETCARD"));
        sizePolicy.setHeightForWidth(comboBox_NETCARD->sizePolicy().hasHeightForWidth());
        comboBox_NETCARD->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox_NETCARD);

        checkBox_DHCPEnable = new QCheckBox(groupBox_3);
        checkBox_DHCPEnable->setObjectName(QStringLiteral("checkBox_DHCPEnable"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_DHCPEnable->sizePolicy().hasHeightForWidth());
        checkBox_DHCPEnable->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(checkBox_DHCPEnable);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_Downed = new QLabel(groupBox_3);
        label_Downed->setObjectName(QStringLiteral("label_Downed"));
        label_Downed->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_10->addWidget(label_Downed);

        checkBox_HIGHTLOADDOWN = new QCheckBox(groupBox_3);
        checkBox_HIGHTLOADDOWN->setObjectName(QStringLiteral("checkBox_HIGHTLOADDOWN"));

        horizontalLayout_10->addWidget(checkBox_HIGHTLOADDOWN);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_10, 1, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_chuanshu = new QLabel(groupBox_3);
        label_chuanshu->setObjectName(QStringLiteral("label_chuanshu"));
        label_chuanshu->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_11->addWidget(label_chuanshu);

        comboBox_TRANSFERPOLICY = new QComboBox(groupBox_3);
        comboBox_TRANSFERPOLICY->setObjectName(QStringLiteral("comboBox_TRANSFERPOLICY"));
        comboBox_TRANSFERPOLICY->setMinimumSize(QSize(100, 0));

        horizontalLayout_11->addWidget(comboBox_TRANSFERPOLICY);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);


        gridLayout_3->addLayout(horizontalLayout_11, 2, 0, 1, 1);

        btnDownSave = new QPushButton(groupBox_3);
        btnDownSave->setObjectName(QStringLiteral("btnDownSave"));

        gridLayout_3->addWidget(btnDownSave, 1, 1, 1, 1);


        retranslateUi(ConfigNetwork);

        QMetaObject::connectSlotsByName(ConfigNetwork);
    } // setupUi

    void retranslateUi(QWidget *ConfigNetwork)
    {
        ConfigNetwork->setWindowTitle(QApplication::translate("ConfigNetwork", "ConfigNetwork", Q_NULLPTR));
        btnSave->setText(QApplication::translate("ConfigNetwork", "\344\277\235\345\255\230\351\205\215\347\275\256", Q_NULLPTR));
        btnUpGrade->setText(QApplication::translate("ConfigNetwork", "\346\233\264\346\226\260", Q_NULLPTR));
        btnClose->setText(QString());
        groupBox->setTitle(QApplication::translate("ConfigNetwork", "DNS\346\234\215\345\212\241\345\231\250", Q_NULLPTR));
        label_6->setText(QApplication::translate("ConfigNetwork", "      \351\246\226\345\205\210DNS", Q_NULLPTR));
        btnDNSSave->setText(QApplication::translate("ConfigNetwork", "\344\277\235\345\255\230", Q_NULLPTR));
        label_7->setText(QApplication::translate("ConfigNetwork", "      \345\244\207\347\224\250DNS", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("ConfigNetwork", "IP", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConfigNetwork", "     \345\255\220\347\275\221\346\216\251\347\240\201", Q_NULLPTR));
        label_8->setText(QApplication::translate("ConfigNetwork", "          MAC", Q_NULLPTR));
        label_11->setText(QApplication::translate("ConfigNetwork", ":", Q_NULLPTR));
        label_12->setText(QApplication::translate("ConfigNetwork", ":", Q_NULLPTR));
        label_13->setText(QApplication::translate("ConfigNetwork", ":", Q_NULLPTR));
        label_14->setText(QApplication::translate("ConfigNetwork", ":", Q_NULLPTR));
        label_15->setText(QApplication::translate("ConfigNetwork", ":", Q_NULLPTR));
        label_9->setText(QApplication::translate("ConfigNetwork", "      TCP\347\253\257\345\217\243", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConfigNetwork", "     \351\273\230\350\256\244\347\275\221\345\205\263", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConfigNetwork", "       IP\345\234\260\345\235\200", Q_NULLPTR));
        label_10->setText(QApplication::translate("ConfigNetwork", "     HTTP\347\253\257\345\217\243", Q_NULLPTR));
        btnIPSave->setText(QApplication::translate("ConfigNetwork", "\344\277\235\345\255\230", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("ConfigNetwork", "         \347\275\221\345\215\241", Q_NULLPTR));
        comboBox_NETCARD->clear();
        comboBox_NETCARD->insertItems(0, QStringList()
         << QApplication::translate("ConfigNetwork", "\346\234\211\347\272\277\347\275\221\345\215\241", Q_NULLPTR)
        );
        checkBox_DHCPEnable->setText(QApplication::translate("ConfigNetwork", "\350\207\252\345\212\250\350\216\267\345\217\226IP\345\234\260\345\235\200", Q_NULLPTR));
        label_Downed->setText(QApplication::translate("ConfigNetwork", "\347\275\221\347\273\234\351\253\230\351\200\237\344\270\213\350\275\275", Q_NULLPTR));
        checkBox_HIGHTLOADDOWN->setText(QString());
        label_chuanshu->setText(QApplication::translate("ConfigNetwork", "\347\275\221\347\273\234\344\274\240\350\276\223\347\255\226\347\225\245", Q_NULLPTR));
        comboBox_TRANSFERPOLICY->clear();
        comboBox_TRANSFERPOLICY->insertItems(0, QStringList()
         << QApplication::translate("ConfigNetwork", "\350\207\252\351\200\202\345\272\224", Q_NULLPTR)
         << QApplication::translate("ConfigNetwork", "\347\224\273\350\264\250\344\274\230\345\205\210", Q_NULLPTR)
         << QApplication::translate("ConfigNetwork", "\346\265\201\347\225\205\344\274\230\345\205\210", Q_NULLPTR)
        );
        btnDownSave->setText(QApplication::translate("ConfigNetwork", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigNetwork: public Ui_ConfigNetwork {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGNETWORK_H
