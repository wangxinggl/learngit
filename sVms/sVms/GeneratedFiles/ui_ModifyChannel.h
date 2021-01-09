/********************************************************************************
** Form generated from reading UI file 'ModifyChannel.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYCHANNEL_H
#define UI_MODIFYCHANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModifyChannel
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_Num;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_Name;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnSure;
    QPushButton *btnCancel;

    void setupUi(QWidget *ModifyChannel)
    {
        if (ModifyChannel->objectName().isEmpty())
            ModifyChannel->setObjectName(QStringLiteral("ModifyChannel"));
        ModifyChannel->resize(429, 187);
        gridLayout = new QGridLayout(ModifyChannel);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(7, 7, 7, 7);
        horizontalSpacer = new QSpacerItem(386, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 3);

        btnClose = new QPushButton(ModifyChannel);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
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

        gridLayout->addWidget(btnClose, 0, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(ModifyChannel);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label);

        lineEdit_Num = new QLineEdit(ModifyChannel);
        lineEdit_Num->setObjectName(QStringLiteral("lineEdit_Num"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_Num->sizePolicy().hasHeightForWidth());
        lineEdit_Num->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lineEdit_Num);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(ModifyChannel);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_Name = new QLineEdit(ModifyChannel);
        lineEdit_Name->setObjectName(QStringLiteral("lineEdit_Name"));
        sizePolicy1.setHeightForWidth(lineEdit_Name->sizePolicy().hasHeightForWidth());
        lineEdit_Name->setSizePolicy(sizePolicy1);
        lineEdit_Name->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(lineEdit_Name);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 4);

        horizontalSpacer_4 = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        btnSure = new QPushButton(ModifyChannel);
        btnSure->setObjectName(QStringLiteral("btnSure"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnSure->sizePolicy().hasHeightForWidth());
        btnSure->setSizePolicy(sizePolicy2);
        btnSure->setMinimumSize(QSize(80, 30));

        gridLayout->addWidget(btnSure, 2, 1, 1, 1);

        btnCancel = new QPushButton(ModifyChannel);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy2.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy2);
        btnCancel->setMinimumSize(QSize(80, 0));
        btnCancel->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(btnCancel, 2, 2, 1, 2);


        retranslateUi(ModifyChannel);

        QMetaObject::connectSlotsByName(ModifyChannel);
    } // setupUi

    void retranslateUi(QWidget *ModifyChannel)
    {
        ModifyChannel->setWindowTitle(QApplication::translate("ModifyChannel", "ModifyChannel", Q_NULLPTR));
        btnClose->setText(QString());
        label->setText(QApplication::translate("ModifyChannel", "    \351\200\232\351\201\223\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("ModifyChannel", "    \351\200\232\351\201\223\345\220\215", Q_NULLPTR));
        btnSure->setText(QApplication::translate("ModifyChannel", "\347\241\256\345\256\232", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("ModifyChannel", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ModifyChannel: public Ui_ModifyChannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYCHANNEL_H
