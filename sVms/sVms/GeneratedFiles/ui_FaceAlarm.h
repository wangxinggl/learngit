/********************************************************************************
** Form generated from reading UI file 'FaceAlarm.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEALARM_H
#define UI_FACEALARM_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceAlarm
{
public:
    QPushButton *btnUpgrade;
    QPushButton *btnSave;
    QPushButton *btnClose;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_ALARMENABLE;
    QCheckBox *checkBox_ALARM_WHITE;
    QCheckBox *checkBox_ENABLE_BLACK;
    QCheckBox *checkBox_IOENABLE;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_OUTPUTTIME;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *lineEdit_SIMILARITY;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *comboBox_OUTPUTTYPE;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QCheckBox *checkBox_TIME1_COMPARE;
    QTimeEdit *timeEdit_DATETIMEPICKER_START1_COMPARE;
    QLabel *label_7;
    QTimeEdit *timeEdit_DATETIMEPICKER_END1_COMPARE;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QCheckBox *checkBox_TIME2_COMPARE;
    QTimeEdit *timeEdit_DATETIMEPICKER_START2_COMPARE;
    QLabel *label_8;
    QTimeEdit *timeEdit_DATETIMEPICKER_END2_COMPARE;

    void setupUi(QDialog *FaceAlarm)
    {
        if (FaceAlarm->objectName().isEmpty())
            FaceAlarm->setObjectName(QStringLiteral("FaceAlarm"));
        FaceAlarm->resize(800, 562);
        btnUpgrade = new QPushButton(FaceAlarm);
        btnUpgrade->setObjectName(QStringLiteral("btnUpgrade"));
        btnUpgrade->setGeometry(QRect(440, 470, 75, 23));
        btnSave = new QPushButton(FaceAlarm);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(270, 470, 75, 23));
        btnClose = new QPushButton(FaceAlarm);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(760, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));
        layoutWidget = new QWidget(FaceAlarm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 60, 631, 18));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_ALARMENABLE = new QCheckBox(layoutWidget);
        checkBox_ALARMENABLE->setObjectName(QStringLiteral("checkBox_ALARMENABLE"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_ALARMENABLE->sizePolicy().hasHeightForWidth());
        checkBox_ALARMENABLE->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(checkBox_ALARMENABLE);

        checkBox_ALARM_WHITE = new QCheckBox(layoutWidget);
        checkBox_ALARM_WHITE->setObjectName(QStringLiteral("checkBox_ALARM_WHITE"));
        sizePolicy.setHeightForWidth(checkBox_ALARM_WHITE->sizePolicy().hasHeightForWidth());
        checkBox_ALARM_WHITE->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(checkBox_ALARM_WHITE);

        checkBox_ENABLE_BLACK = new QCheckBox(layoutWidget);
        checkBox_ENABLE_BLACK->setObjectName(QStringLiteral("checkBox_ENABLE_BLACK"));
        sizePolicy.setHeightForWidth(checkBox_ENABLE_BLACK->sizePolicy().hasHeightForWidth());
        checkBox_ENABLE_BLACK->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(checkBox_ENABLE_BLACK);

        checkBox_IOENABLE = new QCheckBox(layoutWidget);
        checkBox_IOENABLE->setObjectName(QStringLiteral("checkBox_IOENABLE"));
        sizePolicy.setHeightForWidth(checkBox_IOENABLE->sizePolicy().hasHeightForWidth());
        checkBox_IOENABLE->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(checkBox_IOENABLE);

        widget = new QWidget(FaceAlarm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(78, 121, 531, 301));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(80, 0));

        horizontalLayout_2->addWidget(label);

        lineEdit_OUTPUTTIME = new QLineEdit(widget);
        lineEdit_OUTPUTTIME->setObjectName(QStringLiteral("lineEdit_OUTPUTTIME"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_OUTPUTTIME->sizePolicy().hasHeightForWidth());
        lineEdit_OUTPUTTIME->setSizePolicy(sizePolicy1);
        lineEdit_OUTPUTTIME->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(lineEdit_OUTPUTTIME);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);

        lineEdit_SIMILARITY = new QLineEdit(widget);
        lineEdit_SIMILARITY->setObjectName(QStringLiteral("lineEdit_SIMILARITY"));
        sizePolicy1.setHeightForWidth(lineEdit_SIMILARITY->sizePolicy().hasHeightForWidth());
        lineEdit_SIMILARITY->setSizePolicy(sizePolicy1);
        lineEdit_SIMILARITY->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_6->addWidget(lineEdit_SIMILARITY);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));

        horizontalLayout_3->addWidget(label_4);

        comboBox_OUTPUTTYPE = new QComboBox(widget);
        comboBox_OUTPUTTYPE->setObjectName(QStringLiteral("comboBox_OUTPUTTYPE"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_OUTPUTTYPE->sizePolicy().hasHeightForWidth());
        comboBox_OUTPUTTYPE->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(comboBox_OUTPUTTYPE);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(label_5);

        checkBox_TIME1_COMPARE = new QCheckBox(widget);
        checkBox_TIME1_COMPARE->setObjectName(QStringLiteral("checkBox_TIME1_COMPARE"));
        sizePolicy1.setHeightForWidth(checkBox_TIME1_COMPARE->sizePolicy().hasHeightForWidth());
        checkBox_TIME1_COMPARE->setSizePolicy(sizePolicy1);
        checkBox_TIME1_COMPARE->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_4->addWidget(checkBox_TIME1_COMPARE);

        timeEdit_DATETIMEPICKER_START1_COMPARE = new QTimeEdit(widget);
        timeEdit_DATETIMEPICKER_START1_COMPARE->setObjectName(QStringLiteral("timeEdit_DATETIMEPICKER_START1_COMPARE"));
        sizePolicy1.setHeightForWidth(timeEdit_DATETIMEPICKER_START1_COMPARE->sizePolicy().hasHeightForWidth());
        timeEdit_DATETIMEPICKER_START1_COMPARE->setSizePolicy(sizePolicy1);
        timeEdit_DATETIMEPICKER_START1_COMPARE->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(timeEdit_DATETIMEPICKER_START1_COMPARE);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_4->addWidget(label_7);

        timeEdit_DATETIMEPICKER_END1_COMPARE = new QTimeEdit(widget);
        timeEdit_DATETIMEPICKER_END1_COMPARE->setObjectName(QStringLiteral("timeEdit_DATETIMEPICKER_END1_COMPARE"));
        sizePolicy1.setHeightForWidth(timeEdit_DATETIMEPICKER_END1_COMPARE->sizePolicy().hasHeightForWidth());
        timeEdit_DATETIMEPICKER_END1_COMPARE->setSizePolicy(sizePolicy1);
        timeEdit_DATETIMEPICKER_END1_COMPARE->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(timeEdit_DATETIMEPICKER_END1_COMPARE);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(label_6);

        checkBox_TIME2_COMPARE = new QCheckBox(widget);
        checkBox_TIME2_COMPARE->setObjectName(QStringLiteral("checkBox_TIME2_COMPARE"));
        sizePolicy1.setHeightForWidth(checkBox_TIME2_COMPARE->sizePolicy().hasHeightForWidth());
        checkBox_TIME2_COMPARE->setSizePolicy(sizePolicy1);
        checkBox_TIME2_COMPARE->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_5->addWidget(checkBox_TIME2_COMPARE);

        timeEdit_DATETIMEPICKER_START2_COMPARE = new QTimeEdit(widget);
        timeEdit_DATETIMEPICKER_START2_COMPARE->setObjectName(QStringLiteral("timeEdit_DATETIMEPICKER_START2_COMPARE"));
        sizePolicy1.setHeightForWidth(timeEdit_DATETIMEPICKER_START2_COMPARE->sizePolicy().hasHeightForWidth());
        timeEdit_DATETIMEPICKER_START2_COMPARE->setSizePolicy(sizePolicy1);
        timeEdit_DATETIMEPICKER_START2_COMPARE->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(timeEdit_DATETIMEPICKER_START2_COMPARE);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_5->addWidget(label_8);

        timeEdit_DATETIMEPICKER_END2_COMPARE = new QTimeEdit(widget);
        timeEdit_DATETIMEPICKER_END2_COMPARE->setObjectName(QStringLiteral("timeEdit_DATETIMEPICKER_END2_COMPARE"));
        sizePolicy1.setHeightForWidth(timeEdit_DATETIMEPICKER_END2_COMPARE->sizePolicy().hasHeightForWidth());
        timeEdit_DATETIMEPICKER_END2_COMPARE->setSizePolicy(sizePolicy1);
        timeEdit_DATETIMEPICKER_END2_COMPARE->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(timeEdit_DATETIMEPICKER_END2_COMPARE);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(FaceAlarm);

        QMetaObject::connectSlotsByName(FaceAlarm);
    } // setupUi

    void retranslateUi(QDialog *FaceAlarm)
    {
        FaceAlarm->setWindowTitle(QApplication::translate("FaceAlarm", "FaceAlarm", Q_NULLPTR));
        btnUpgrade->setText(QApplication::translate("FaceAlarm", "\346\233\264\346\226\260", Q_NULLPTR));
        btnSave->setText(QApplication::translate("FaceAlarm", "\344\277\235\345\255\230", Q_NULLPTR));
        btnClose->setText(QString());
        checkBox_ALARMENABLE->setText(QApplication::translate("FaceAlarm", "\346\212\245\350\255\246\345\274\200\345\205\263", Q_NULLPTR));
        checkBox_ALARM_WHITE->setText(QApplication::translate("FaceAlarm", "\346\211\223\345\274\200\347\231\275\345\220\215\345\215\225\346\212\245\350\255\246", Q_NULLPTR));
        checkBox_ENABLE_BLACK->setText(QApplication::translate("FaceAlarm", "\346\211\223\345\274\200\351\273\221\345\220\215\345\215\225\346\212\245\350\255\246", Q_NULLPTR));
        checkBox_IOENABLE->setText(QApplication::translate("FaceAlarm", "IO\350\276\223\345\207\272", Q_NULLPTR));
        label->setText(QApplication::translate("FaceAlarm", "   IO\350\276\223\345\207\272\346\227\266\351\227\264:", Q_NULLPTR));
        label_2->setText(QApplication::translate("FaceAlarm", "(\347\247\222)", Q_NULLPTR));
        label_3->setText(QApplication::translate("FaceAlarm", "\347\233\270\344\274\274\345\272\246", Q_NULLPTR));
        label_4->setText(QApplication::translate("FaceAlarm", "   IO\350\276\223\345\207\272\347\261\273\345\236\213:", Q_NULLPTR));
        comboBox_OUTPUTTYPE->clear();
        comboBox_OUTPUTTYPE->insertItems(0, QStringList()
         << QApplication::translate("FaceAlarm", "\346\214\201\347\273\255\350\276\223\345\207\272", Q_NULLPTR)
         << QApplication::translate("FaceAlarm", "\350\204\211\345\206\262\350\276\223\345\207\272", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("FaceAlarm", "\345\270\203\351\230\262\346\227\266\351\227\264\346\256\2651:", Q_NULLPTR));
        checkBox_TIME1_COMPARE->setText(QString());
        label_7->setText(QApplication::translate("FaceAlarm", "----", Q_NULLPTR));
        label_6->setText(QApplication::translate("FaceAlarm", "\345\270\203\351\230\262\346\227\266\351\227\264\346\256\2652:", Q_NULLPTR));
        checkBox_TIME2_COMPARE->setText(QString());
        label_8->setText(QApplication::translate("FaceAlarm", "----", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FaceAlarm: public Ui_FaceAlarm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEALARM_H
