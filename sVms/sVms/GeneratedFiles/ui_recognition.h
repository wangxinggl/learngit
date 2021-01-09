/********************************************************************************
** Form generated from reading UI file 'recognition.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECOGNITION_H
#define UI_RECOGNITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_Recognition
{
public:
    QGridLayout *gridLayout;
    ClickedLabel *label_pic;
    QSpacerItem *horizontalSpacer;
    QLabel *label_Lib;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *label_Name;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_16;
    QProgressBar *progressBar;
    QLabel *label_progress;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLabel *label_Number;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *label_Device;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLabel *label_Time;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLabel *label_Type;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLabel *label_temperature;

    void setupUi(QWidget *Recognition)
    {
        if (Recognition->objectName().isEmpty())
            Recognition->setObjectName(QStringLiteral("Recognition"));
        Recognition->resize(217, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Recognition->sizePolicy().hasHeightForWidth());
        Recognition->setSizePolicy(sizePolicy);
        Recognition->setMinimumSize(QSize(200, 300));
        Recognition->setMaximumSize(QSize(217, 300));
        Recognition->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(Recognition);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_pic = new ClickedLabel(Recognition);
        label_pic->setObjectName(QStringLiteral("label_pic"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(80);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(label_pic->sizePolicy().hasHeightForWidth());
        label_pic->setSizePolicy(sizePolicy1);
        label_pic->setMinimumSize(QSize(90, 100));
        label_pic->setMaximumSize(QSize(90, 100));
        label_pic->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_pic->setPixmap(QPixmap(QString::fromUtf8(":/res/SoftIcon/User.png")));
        label_pic->setScaledContents(true);

        gridLayout->addWidget(label_pic, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        label_Lib = new QLabel(Recognition);
        label_Lib->setObjectName(QStringLiteral("label_Lib"));
        label_Lib->setMinimumSize(QSize(90, 100));
        label_Lib->setMaximumSize(QSize(90, 100));
        label_Lib->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_Lib->setPixmap(QPixmap(QString::fromUtf8(":/res/SoftIcon/User.png")));
        label_Lib->setScaledContents(true);

        gridLayout->addWidget(label_Lib, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(Recognition);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(60, 0));
        label_4->setMaximumSize(QSize(55, 16777215));

        horizontalLayout->addWidget(label_4);

        label_Name = new QLabel(Recognition);
        label_Name->setObjectName(QStringLiteral("label_Name"));
        label_Name->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label_Name);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_16 = new QLabel(Recognition);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(60, 0));
        label_16->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_6->addWidget(label_16);

        progressBar = new QProgressBar(Recognition);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        progressBar->setFont(font);
        progressBar->setFocusPolicy(Qt::NoFocus);
        progressBar->setContextMenuPolicy(Qt::NoContextMenu);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        horizontalLayout_6->addWidget(progressBar);

        label_progress = new QLabel(Recognition);
        label_progress->setObjectName(QStringLiteral("label_progress"));
        label_progress->setMinimumSize(QSize(35, 0));

        horizontalLayout_6->addWidget(label_progress);


        gridLayout->addLayout(horizontalLayout_6, 7, 0, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(Recognition);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(60, 0));
        label_5->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_2->addWidget(label_5);

        label_Number = new QLabel(Recognition);
        label_Number->setObjectName(QStringLiteral("label_Number"));
        label_Number->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(label_Number);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_6 = new QLabel(Recognition);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(60, 0));
        label_6->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_3->addWidget(label_6);

        label_Device = new QLabel(Recognition);
        label_Device->setObjectName(QStringLiteral("label_Device"));
        label_Device->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(label_Device);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_8 = new QLabel(Recognition);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(60, 0));
        label_8->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_5->addWidget(label_8);

        label_Time = new QLabel(Recognition);
        label_Time->setObjectName(QStringLiteral("label_Time"));
        label_Time->setStyleSheet(QStringLiteral(""));

        horizontalLayout_5->addWidget(label_Time);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(Recognition);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(60, 0));
        label_7->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_4->addWidget(label_7);

        label_Type = new QLabel(Recognition);
        label_Type->setObjectName(QStringLiteral("label_Type"));
        label_Type->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(label_Type);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_9 = new QLabel(Recognition);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(60, 0));
        label_9->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_7->addWidget(label_9);

        label_temperature = new QLabel(Recognition);
        label_temperature->setObjectName(QStringLiteral("label_temperature"));
        label_temperature->setStyleSheet(QStringLiteral(""));

        horizontalLayout_7->addWidget(label_temperature);


        gridLayout->addLayout(horizontalLayout_7, 6, 0, 1, 3);


        retranslateUi(Recognition);

        QMetaObject::connectSlotsByName(Recognition);
    } // setupUi

    void retranslateUi(QWidget *Recognition)
    {
        Recognition->setWindowTitle(QApplication::translate("Recognition", "Recognition", Q_NULLPTR));
        label_pic->setText(QString());
        label_Lib->setText(QString());
        label_4->setText(QApplication::translate("Recognition", "    \345\247\223\345\220\215", Q_NULLPTR));
        label_Name->setText(QString());
        label_16->setText(QApplication::translate("Recognition", " \347\233\270\344\274\274\345\272\246", Q_NULLPTR));
        label_progress->setText(QString());
        label_5->setText(QApplication::translate("Recognition", "    \347\274\226\345\217\267", Q_NULLPTR));
        label_Number->setText(QString());
        label_6->setText(QApplication::translate("Recognition", "\350\256\276\345\244\207\345\220\215\347\247\260", Q_NULLPTR));
        label_Device->setText(QString());
        label_8->setText(QApplication::translate("Recognition", "\346\212\223\346\213\215\346\227\266\351\227\264", Q_NULLPTR));
        label_Time->setText(QString());
        label_7->setText(QApplication::translate("Recognition", "\345\220\215\345\215\225\347\261\273\345\236\213", Q_NULLPTR));
        label_Type->setText(QString());
        label_9->setText(QApplication::translate("Recognition", "\344\275\223\346\270\251", Q_NULLPTR));
        label_temperature->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Recognition: public Ui_Recognition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOGNITION_H
