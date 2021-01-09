/********************************************************************************
** Form generated from reading UI file 'changeskin.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGESKIN_H
#define UI_CHANGESKIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_changeSkin
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    ClickedLabel *hui_label;
    QLabel *label_8;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout_6;
    ClickedLabel *wathetgray_label;
    QLabel *label_10;
    QWidget *layoutWidget_12;
    QVBoxLayout *verticalLayout_13;
    ClickedLabel *darkblack_label;
    QLabel *label_17;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    ClickedLabel *mei_label;
    QLabel *label_6;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    ClickedLabel *sky_label;
    QLabel *label_7;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout1;
    ClickedLabel *black_label;
    QLabel *label_5;
    QWidget *layoutWidget_6;
    QVBoxLayout *verticalLayout_7;
    ClickedLabel *darkgray_label;
    QLabel *label_11;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    ClickedLabel *gray_label;
    QLabel *label_9;
    QWidget *layoutWidget_7;
    QVBoxLayout *verticalLayout_8;
    ClickedLabel *sliver_label;
    QLabel *label_12;
    QWidget *layoutWidget_8;
    QVBoxLayout *verticalLayout_9;
    ClickedLabel *flatblack_label;
    QLabel *label_13;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *btnClose;

    void setupUi(QWidget *changeSkin)
    {
        if (changeSkin->objectName().isEmpty())
            changeSkin->setObjectName(QStringLiteral("changeSkin"));
        changeSkin->resize(960, 641);
        gridLayout = new QGridLayout(changeSkin);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(changeSkin);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        layoutWidget_3 = new QWidget(groupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 240, 202, 170));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        hui_label = new ClickedLabel(layoutWidget_3);
        hui_label->setObjectName(QStringLiteral("hui_label"));
        hui_label->setMinimumSize(QSize(200, 150));
        hui_label->setMaximumSize(QSize(200, 150));
        hui_label->setStyleSheet(QStringLiteral(""));
        hui_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/darkblue.png")));

        verticalLayout_4->addWidget(hui_label);

        label_8 = new QLabel(layoutWidget_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_8);

        layoutWidget_5 = new QWidget(groupBox);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(470, 240, 202, 170));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        wathetgray_label = new ClickedLabel(layoutWidget_5);
        wathetgray_label->setObjectName(QStringLiteral("wathetgray_label"));
        wathetgray_label->setMinimumSize(QSize(200, 150));
        wathetgray_label->setMaximumSize(QSize(200, 150));
        wathetgray_label->setStyleSheet(QStringLiteral(""));
        wathetgray_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/wathetgray.png")));

        verticalLayout_6->addWidget(wathetgray_label);

        label_10 = new QLabel(layoutWidget_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_10);

        layoutWidget_12 = new QWidget(groupBox);
        layoutWidget_12->setObjectName(QStringLiteral("layoutWidget_12"));
        layoutWidget_12->setGeometry(QRect(700, 240, 202, 170));
        verticalLayout_13 = new QVBoxLayout(layoutWidget_12);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        darkblack_label = new ClickedLabel(layoutWidget_12);
        darkblack_label->setObjectName(QStringLiteral("darkblack_label"));
        darkblack_label->setMinimumSize(QSize(200, 150));
        darkblack_label->setMaximumSize(QSize(200, 150));
        darkblack_label->setStyleSheet(QStringLiteral(""));
        darkblack_label->setPixmap(QPixmap(QString::fromUtf8(":/res/qss/darkblack.png")));

        verticalLayout_13->addWidget(darkblack_label);

        label_17 = new QLabel(layoutWidget_12);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_17);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(240, 60, 202, 170));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        mei_label = new ClickedLabel(layoutWidget1);
        mei_label->setObjectName(QStringLiteral("mei_label"));
        mei_label->setMinimumSize(QSize(200, 150));
        mei_label->setMaximumSize(QSize(200, 150));
        mei_label->setStyleSheet(QStringLiteral(""));
        mei_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/blue.png")));
        mei_label->setScaledContents(true);

        verticalLayout_2->addWidget(mei_label);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_6);

        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(470, 60, 202, 170));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        sky_label = new ClickedLabel(layoutWidget_2);
        sky_label->setObjectName(QStringLiteral("sky_label"));
        sky_label->setMinimumSize(QSize(200, 150));
        sky_label->setMaximumSize(QSize(200, 150));
        sky_label->setStyleSheet(QLatin1String("background-color: rgb(31, 31, 31);\n"
"background-color: rgb(0, 78, 235);"));
        sky_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/wathetblue.png")));

        verticalLayout_3->addWidget(sky_label);

        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_7);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 60, 202, 171));
        verticalLayout1 = new QVBoxLayout(layoutWidget2);
        verticalLayout1->setSpacing(6);
        verticalLayout1->setContentsMargins(11, 11, 11, 11);
        verticalLayout1->setObjectName(QStringLiteral("verticalLayout1"));
        verticalLayout1->setContentsMargins(0, 0, 0, 0);
        black_label = new ClickedLabel(layoutWidget2);
        black_label->setObjectName(QStringLiteral("black_label"));
        black_label->setMinimumSize(QSize(200, 150));
        black_label->setMaximumSize(QSize(200, 150));
        black_label->setStyleSheet(QStringLiteral(""));
        black_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/black.png")));

        verticalLayout1->addWidget(black_label);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout1->addWidget(label_5);

        layoutWidget_6 = new QWidget(groupBox);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 420, 202, 170));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        darkgray_label = new ClickedLabel(layoutWidget_6);
        darkgray_label->setObjectName(QStringLiteral("darkgray_label"));
        darkgray_label->setMinimumSize(QSize(200, 150));
        darkgray_label->setMaximumSize(QSize(200, 150));
        darkgray_label->setStyleSheet(QStringLiteral(""));
        darkgray_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/darkgray.png")));

        verticalLayout_7->addWidget(darkgray_label);

        label_11 = new QLabel(layoutWidget_6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_11);

        layoutWidget_4 = new QWidget(groupBox);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(240, 240, 202, 170));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        gray_label = new ClickedLabel(layoutWidget_4);
        gray_label->setObjectName(QStringLiteral("gray_label"));
        gray_label->setMinimumSize(QSize(200, 150));
        gray_label->setMaximumSize(QSize(200, 150));
        gray_label->setStyleSheet(QLatin1String("background-color: rgb(31, 31, 31);\n"
"background-color: rgb(160, 160, 160);"));
        gray_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/gray.png")));

        verticalLayout_5->addWidget(gray_label);

        label_9 = new QLabel(layoutWidget_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_9);

        layoutWidget_7 = new QWidget(groupBox);
        layoutWidget_7->setObjectName(QStringLiteral("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(240, 420, 202, 170));
        verticalLayout_8 = new QVBoxLayout(layoutWidget_7);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        sliver_label = new ClickedLabel(layoutWidget_7);
        sliver_label->setObjectName(QStringLiteral("sliver_label"));
        sliver_label->setMinimumSize(QSize(200, 150));
        sliver_label->setMaximumSize(QSize(200, 150));
        sliver_label->setStyleSheet(QStringLiteral(""));
        sliver_label->setPixmap(QPixmap(QString::fromUtf8(":/Client/res/qss/sliver.png")));

        verticalLayout_8->addWidget(sliver_label);

        label_12 = new QLabel(layoutWidget_7);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_12);

        layoutWidget_8 = new QWidget(groupBox);
        layoutWidget_8->setObjectName(QStringLiteral("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(700, 60, 202, 171));
        verticalLayout_9 = new QVBoxLayout(layoutWidget_8);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        flatblack_label = new ClickedLabel(layoutWidget_8);
        flatblack_label->setObjectName(QStringLiteral("flatblack_label"));
        flatblack_label->setMinimumSize(QSize(200, 150));
        flatblack_label->setMaximumSize(QSize(200, 150));
        flatblack_label->setStyleSheet(QStringLiteral(""));
        flatblack_label->setPixmap(QPixmap(QString::fromUtf8(":/res/qss/flatblack.png")));

        verticalLayout_9->addWidget(flatblack_label);

        label_13 = new QLabel(layoutWidget_8);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_13);

        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 921, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        btnClose = new QPushButton(layoutWidget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnClose);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(changeSkin);

        QMetaObject::connectSlotsByName(changeSkin);
    } // setupUi

    void retranslateUi(QWidget *changeSkin)
    {
        changeSkin->setWindowTitle(QApplication::translate("changeSkin", "changeSkin", Q_NULLPTR));
        groupBox->setTitle(QString());
        hui_label->setText(QString());
        label_8->setText(QApplication::translate("changeSkin", "\346\267\261\350\223\235\350\211\262", Q_NULLPTR));
        wathetgray_label->setText(QString());
        label_10->setText(QApplication::translate("changeSkin", "\346\265\205\347\201\260\350\211\262", Q_NULLPTR));
        darkblack_label->setText(QString());
        label_17->setText(QApplication::translate("changeSkin", "\346\267\261\351\273\221\350\211\262", Q_NULLPTR));
        mei_label->setText(QString());
        label_6->setText(QApplication::translate("changeSkin", "\350\223\235\350\211\262", Q_NULLPTR));
        sky_label->setText(QString());
        label_7->setText(QApplication::translate("changeSkin", "\346\265\205\350\223\235\350\211\262", Q_NULLPTR));
        black_label->setText(QString());
        label_5->setText(QApplication::translate("changeSkin", "\351\273\221\350\211\262", Q_NULLPTR));
        darkgray_label->setText(QString());
        label_11->setText(QApplication::translate("changeSkin", "\346\267\261\347\201\260\350\211\262", Q_NULLPTR));
        gray_label->setText(QString());
        label_9->setText(QApplication::translate("changeSkin", "\347\201\260\350\211\262", Q_NULLPTR));
        sliver_label->setText(QString());
        label_12->setText(QApplication::translate("changeSkin", "\351\223\266\350\211\262", Q_NULLPTR));
        flatblack_label->setText(QString());
        label_13->setText(QApplication::translate("changeSkin", "\346\265\205\351\273\221\350\211\262", Q_NULLPTR));
        label->setText(QApplication::translate("changeSkin", "\345\210\207\346\215\242\347\232\256\350\202\244", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class changeSkin: public Ui_changeSkin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGESKIN_H
