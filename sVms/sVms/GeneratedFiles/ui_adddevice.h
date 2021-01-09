/********************************************************************************
** Form generated from reading UI file 'adddevice.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDEVICE_H
#define UI_ADDDEVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddDevice
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QRadioButton *radioButton_name;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QPushButton *btnClose;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Name;
    QLineEdit *lineEdit_Name;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_Usr;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineEdit_Port;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QComboBox *comboBox_Type;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSure;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *radioButton_paragr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Addr;
    QLineEdit *lineEdit_Addr;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_Pwd;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QComboBox *comboBox_ChannelNo;

    void setupUi(QWidget *AddDevice)
    {
        if (AddDevice->objectName().isEmpty())
            AddDevice->setObjectName(QStringLiteral("AddDevice"));
        AddDevice->resize(354, 555);
        AddDevice->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(AddDevice);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(AddDevice);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        radioButton_name = new QRadioButton(groupBox);
        radioButton_name->setObjectName(QStringLiteral("radioButton_name"));

        gridLayout->addWidget(radioButton_name, 1, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout_6->addWidget(label_2);

        btnClose = new QPushButton(groupBox);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        horizontalLayout_6->addWidget(btnClose);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_Name = new QLabel(groupBox);
        label_Name->setObjectName(QStringLiteral("label_Name"));
        label_Name->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(label_Name);

        lineEdit_Name = new QLineEdit(groupBox);
        lineEdit_Name->setObjectName(QStringLiteral("lineEdit_Name"));
        lineEdit_Name->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(lineEdit_Name);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_Usr = new QLineEdit(groupBox);
        lineEdit_Usr->setObjectName(QStringLiteral("lineEdit_Usr"));
        lineEdit_Usr->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(lineEdit_Usr);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));

        horizontalLayout_3->addWidget(label_4);

        lineEdit_Port = new QLineEdit(groupBox);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(lineEdit_Port);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(label_8);

        comboBox_Type = new QComboBox(groupBox);
        comboBox_Type->setObjectName(QStringLiteral("comboBox_Type"));
        comboBox_Type->setMinimumSize(QSize(0, 30));

        horizontalLayout_7->addWidget(comboBox_Type);


        gridLayout->addLayout(horizontalLayout_7, 7, 0, 1, 4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        btnSure = new QPushButton(groupBox);
        btnSure->setObjectName(QStringLiteral("btnSure"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSure->sizePolicy().hasHeightForWidth());
        btnSure->setSizePolicy(sizePolicy);
        btnSure->setMaximumSize(QSize(16777215, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSure->setIcon(icon1);

        horizontalLayout_10->addWidget(btnSure);

        horizontalSpacer_2 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        btnCancel = new QPushButton(groupBox);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy1);
        btnCancel->setMaximumSize(QSize(16777215, 30));
        btnCancel->setIcon(icon);

        horizontalLayout_10->addWidget(btnCancel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_10, 9, 0, 1, 4);

        radioButton_paragr = new QRadioButton(groupBox);
        radioButton_paragr->setObjectName(QStringLiteral("radioButton_paragr"));

        gridLayout->addWidget(radioButton_paragr, 1, 3, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_Addr = new QLabel(groupBox);
        label_Addr->setObjectName(QStringLiteral("label_Addr"));
        label_Addr->setMinimumSize(QSize(80, 0));

        horizontalLayout_2->addWidget(label_Addr);

        lineEdit_Addr = new QLineEdit(groupBox);
        lineEdit_Addr->setObjectName(QStringLiteral("lineEdit_Addr"));
        lineEdit_Addr->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(lineEdit_Addr);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(80, 0));

        horizontalLayout_5->addWidget(label_6);

        lineEdit_Pwd = new QLineEdit(groupBox);
        lineEdit_Pwd->setObjectName(QStringLiteral("lineEdit_Pwd"));
        lineEdit_Pwd->setMinimumSize(QSize(0, 30));
        lineEdit_Pwd->setEchoMode(QLineEdit::Password);

        horizontalLayout_5->addWidget(lineEdit_Pwd);


        gridLayout->addLayout(horizontalLayout_5, 6, 0, 1, 4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_8->addWidget(label_9);

        comboBox_ChannelNo = new QComboBox(groupBox);
        comboBox_ChannelNo->setObjectName(QStringLiteral("comboBox_ChannelNo"));
        comboBox_ChannelNo->setMinimumSize(QSize(0, 30));

        horizontalLayout_8->addWidget(comboBox_ChannelNo);


        gridLayout->addLayout(horizontalLayout_8, 8, 0, 1, 4);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(AddDevice);

        QMetaObject::connectSlotsByName(AddDevice);
    } // setupUi

    void retranslateUi(QWidget *AddDevice)
    {
        AddDevice->setWindowTitle(QApplication::translate("AddDevice", "AddDevice", Q_NULLPTR));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("AddDevice", "\346\267\273\345\212\240\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        radioButton_name->setText(QApplication::translate("AddDevice", "IP\345\237\237\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddDevice", "\346\267\273\345\212\240\350\256\276\345\244\207", Q_NULLPTR));
        btnClose->setText(QString());
        label_Name->setText(QApplication::translate("AddDevice", "\350\256\276\345\244\207\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("AddDevice", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("AddDevice", "\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("AddDevice", "\346\221\204\345\203\217\345\244\264\347\261\273\345\236\213\357\274\232", Q_NULLPTR));
        comboBox_Type->clear();
        comboBox_Type->insertItems(0, QStringList()
         << QApplication::translate("AddDevice", "\346\257\224\345\257\271\346\234\272", Q_NULLPTR)
         << QApplication::translate("AddDevice", "\346\212\223\346\213\215\346\234\272", Q_NULLPTR)
         << QApplication::translate("AddDevice", "\351\227\250\347\246\201\346\234\272", Q_NULLPTR)
         << QApplication::translate("AddDevice", "\346\221\204\345\203\217\346\234\272", Q_NULLPTR)
        );
        btnSure->setText(QApplication::translate("AddDevice", "\347\241\256\345\256\232", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("AddDevice", "\345\217\226\346\266\210", Q_NULLPTR));
        radioButton_paragr->setText(QApplication::translate("AddDevice", "IP\346\256\265", Q_NULLPTR));
        label_Addr->setText(QApplication::translate("AddDevice", "IP/UUID\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("AddDevice", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("AddDevice", "\351\200\232\351\201\223\346\225\260\357\274\232", Q_NULLPTR));
        comboBox_ChannelNo->clear();
        comboBox_ChannelNo->insertItems(0, QStringList()
         << QApplication::translate("AddDevice", "1", Q_NULLPTR)
         << QApplication::translate("AddDevice", "4", Q_NULLPTR)
         << QApplication::translate("AddDevice", "8", Q_NULLPTR)
         << QApplication::translate("AddDevice", "9", Q_NULLPTR)
         << QApplication::translate("AddDevice", "16", Q_NULLPTR)
         << QApplication::translate("AddDevice", "32", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class AddDevice: public Ui_AddDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDEVICE_H
