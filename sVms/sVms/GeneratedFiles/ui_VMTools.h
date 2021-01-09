/********************************************************************************
** Form generated from reading UI file 'VMTools.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VMTOOLS_H
#define UI_VMTOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_VMTools
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cameraBtn;
    QPushButton *btnClose;
    QPushButton *recordBtn;
    QPushButton *talkBtn;
    QPushButton *soundBtn;
    QLabel *label_IP;
    QLabel *label_Num;

    void setupUi(QDialog *VMTools)
    {
        if (VMTools->objectName().isEmpty())
            VMTools->setObjectName(QStringLiteral("VMTools"));
        VMTools->setWindowModality(Qt::ApplicationModal);
        VMTools->resize(407, 17);
        VMTools->setMinimumSize(QSize(0, 17));
        VMTools->setMaximumSize(QSize(16777215, 20));
        VMTools->setWindowOpacity(0.3);
        VMTools->setStyleSheet(QStringLiteral(""));
        VMTools->setModal(false);
        gridLayout = new QGridLayout(VMTools);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 4, 3);
        horizontalSpacer = new QSpacerItem(300, 11, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        cameraBtn = new QPushButton(VMTools);
        cameraBtn->setObjectName(QStringLiteral("cameraBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraBtn->sizePolicy().hasHeightForWidth());
        cameraBtn->setSizePolicy(sizePolicy);
        cameraBtn->setMinimumSize(QSize(15, 15));
        cameraBtn->setMaximumSize(QSize(15, 15));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        cameraBtn->setIcon(icon);
        cameraBtn->setIconSize(QSize(15, 15));

        gridLayout->addWidget(cameraBtn, 0, 6, 1, 1);

        btnClose = new QPushButton(VMTools);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        sizePolicy.setHeightForWidth(btnClose->sizePolicy().hasHeightForWidth());
        btnClose->setSizePolicy(sizePolicy);
        btnClose->setMinimumSize(QSize(15, 15));
        btnClose->setMaximumSize(QSize(15, 15));
        btnClose->setAutoFillBackground(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon1);
        btnClose->setIconSize(QSize(15, 15));

        gridLayout->addWidget(btnClose, 0, 7, 1, 1);

        recordBtn = new QPushButton(VMTools);
        recordBtn->setObjectName(QStringLiteral("recordBtn"));
        sizePolicy.setHeightForWidth(recordBtn->sizePolicy().hasHeightForWidth());
        recordBtn->setSizePolicy(sizePolicy);
        recordBtn->setMinimumSize(QSize(15, 15));
        recordBtn->setMaximumSize(QSize(15, 15));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/SoftIcon/VideoClose.png"), QSize(), QIcon::Normal, QIcon::Off);
        recordBtn->setIcon(icon2);
        recordBtn->setIconSize(QSize(15, 15));

        gridLayout->addWidget(recordBtn, 0, 5, 1, 1);

        talkBtn = new QPushButton(VMTools);
        talkBtn->setObjectName(QStringLiteral("talkBtn"));
        sizePolicy.setHeightForWidth(talkBtn->sizePolicy().hasHeightForWidth());
        talkBtn->setSizePolicy(sizePolicy);
        talkBtn->setMinimumSize(QSize(15, 15));
        talkBtn->setMaximumSize(QSize(15, 15));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/SoftIcon/talkClose.png"), QSize(), QIcon::Normal, QIcon::Off);
        talkBtn->setIcon(icon3);
        talkBtn->setIconSize(QSize(15, 15));

        gridLayout->addWidget(talkBtn, 0, 3, 1, 1);

        soundBtn = new QPushButton(VMTools);
        soundBtn->setObjectName(QStringLiteral("soundBtn"));
        sizePolicy.setHeightForWidth(soundBtn->sizePolicy().hasHeightForWidth());
        soundBtn->setSizePolicy(sizePolicy);
        soundBtn->setMinimumSize(QSize(15, 15));
        soundBtn->setMaximumSize(QSize(15, 15));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/SoftIcon/voiceClose.png"), QSize(), QIcon::Normal, QIcon::Off);
        soundBtn->setIcon(icon4);
        soundBtn->setIconSize(QSize(15, 15));

        gridLayout->addWidget(soundBtn, 0, 4, 1, 1);

        label_IP = new QLabel(VMTools);
        label_IP->setObjectName(QStringLiteral("label_IP"));
        label_IP->setMinimumSize(QSize(140, 0));
        label_IP->setScaledContents(true);

        gridLayout->addWidget(label_IP, 0, 1, 1, 1);

        label_Num = new QLabel(VMTools);
        label_Num->setObjectName(QStringLiteral("label_Num"));
        label_Num->setMinimumSize(QSize(30, 0));

        gridLayout->addWidget(label_Num, 0, 0, 1, 1);


        retranslateUi(VMTools);

        QMetaObject::connectSlotsByName(VMTools);
    } // setupUi

    void retranslateUi(QDialog *VMTools)
    {
        VMTools->setWindowTitle(QApplication::translate("VMTools", "VMTools", Q_NULLPTR));
        cameraBtn->setText(QString());
        btnClose->setText(QString());
        recordBtn->setText(QString());
        talkBtn->setText(QString());
        soundBtn->setText(QString());
        label_IP->setText(QString());
        label_Num->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VMTools: public Ui_VMTools {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VMTOOLS_H
