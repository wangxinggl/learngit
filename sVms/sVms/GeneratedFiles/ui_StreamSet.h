/********************************************************************************
** Form generated from reading UI file 'StreamSet.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMSET_H
#define UI_STREAMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StreamSet
{
public:
    QGroupBox *groupBox;
    QComboBox *comboBox_CodeFormat;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_BitControl;
    QLabel *label_4;
    QComboBox *comboBox_QuAlity;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_18;
    QComboBox *comboBox_ResoLution;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_GOP;
    QLabel *label_8;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit_FPS;
    QLabel *label_17;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_FramRate;
    QLabel *label_20;
    QGroupBox *groupBox_2;
    QComboBox *comboBox_Expand;
    QLabel *label_10;
    QComboBox *comboBox_Expand_ResoLution;
    QLabel *label_11;
    QLabel *label_12;
    QComboBox *comboBox_Expand_BitControl;
    QLabel *label_13;
    QComboBox *comboBox_Expand_QuaLity;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_Expand_FrameRate;
    QLabel *label_21;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_Expand_FPS;
    QLabel *label_19;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_Expand_GOP;
    QLabel *label_9;
    QPushButton *btnSave;
    QPushButton *btnUpGrade;
    QLabel *label;
    QPushButton *btnClose;
    QComboBox *comboBox_Channel;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_7;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_8;

    void setupUi(QDialog *StreamSet)
    {
        if (StreamSet->objectName().isEmpty())
            StreamSet->setObjectName(QStringLiteral("StreamSet"));
        StreamSet->resize(824, 624);
        groupBox = new QGroupBox(StreamSet);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 90, 391, 471));
        comboBox_CodeFormat = new QComboBox(groupBox);
        comboBox_CodeFormat->setObjectName(QStringLiteral("comboBox_CodeFormat"));
        comboBox_CodeFormat->setGeometry(QRect(120, 40, 145, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 40, 111, 20));
        label_2->setMaximumSize(QSize(120, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 240, 111, 20));
        label_3->setMaximumSize(QSize(120, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_BitControl = new QComboBox(groupBox);
        comboBox_BitControl->setObjectName(QStringLiteral("comboBox_BitControl"));
        comboBox_BitControl->setGeometry(QRect(120, 140, 145, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 140, 101, 20));
        label_4->setMaximumSize(QSize(120, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_QuAlity = new QComboBox(groupBox);
        comboBox_QuAlity->setObjectName(QStringLiteral("comboBox_QuAlity"));
        comboBox_QuAlity->setGeometry(QRect(120, 190, 145, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 190, 101, 20));
        label_5->setMaximumSize(QSize(120, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(1, 290, 111, 20));
        label_6->setMaximumSize(QSize(120, 16777215));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(0, 340, 111, 20));
        label_7->setMaximumSize(QSize(120, 16777215));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 90, 101, 20));
        label_18->setMaximumSize(QSize(120, 16777215));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_ResoLution = new QComboBox(groupBox);
        comboBox_ResoLution->setObjectName(QStringLiteral("comboBox_ResoLution"));
        comboBox_ResoLution->setGeometry(QRect(120, 90, 145, 22));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 340, 195, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEdit_GOP = new QLineEdit(layoutWidget);
        lineEdit_GOP->setObjectName(QStringLiteral("lineEdit_GOP"));
        lineEdit_GOP->setMinimumSize(QSize(145, 0));

        horizontalLayout_4->addWidget(lineEdit_GOP);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_4->addWidget(label_8);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 290, 189, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        lineEdit_FPS = new QLineEdit(layoutWidget1);
        lineEdit_FPS->setObjectName(QStringLiteral("lineEdit_FPS"));
        lineEdit_FPS->setMinimumSize(QSize(145, 0));

        horizontalLayout_5->addWidget(lineEdit_FPS);

        label_17 = new QLabel(layoutWidget1);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_5->addWidget(label_17);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(120, 240, 213, 22));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lineEdit_FramRate = new QLineEdit(layoutWidget2);
        lineEdit_FramRate->setObjectName(QStringLiteral("lineEdit_FramRate"));
        lineEdit_FramRate->setMinimumSize(QSize(145, 0));

        horizontalLayout_6->addWidget(lineEdit_FramRate);

        label_20 = new QLabel(layoutWidget2);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_6->addWidget(label_20);

        groupBox_2 = new QGroupBox(StreamSet);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(410, 90, 391, 471));
        comboBox_Expand = new QComboBox(groupBox_2);
        comboBox_Expand->setObjectName(QStringLiteral("comboBox_Expand"));
        comboBox_Expand->setGeometry(QRect(120, 40, 145, 20));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(40, 40, 71, 16));
        comboBox_Expand_ResoLution = new QComboBox(groupBox_2);
        comboBox_Expand_ResoLution->setObjectName(QStringLiteral("comboBox_Expand_ResoLution"));
        comboBox_Expand_ResoLution->setGeometry(QRect(120, 90, 145, 20));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(40, 90, 71, 16));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(40, 240, 71, 16));
        comboBox_Expand_BitControl = new QComboBox(groupBox_2);
        comboBox_Expand_BitControl->setObjectName(QStringLiteral("comboBox_Expand_BitControl"));
        comboBox_Expand_BitControl->setGeometry(QRect(120, 140, 145, 20));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(40, 140, 71, 16));
        comboBox_Expand_QuaLity = new QComboBox(groupBox_2);
        comboBox_Expand_QuaLity->setObjectName(QStringLiteral("comboBox_Expand_QuaLity"));
        comboBox_Expand_QuaLity->setGeometry(QRect(120, 190, 145, 20));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(40, 190, 71, 16));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(40, 290, 71, 20));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(40, 340, 71, 16));
        layoutWidget3 = new QWidget(groupBox_2);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(121, 240, 213, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_Expand_FrameRate = new QLineEdit(layoutWidget3);
        lineEdit_Expand_FrameRate->setObjectName(QStringLiteral("lineEdit_Expand_FrameRate"));
        lineEdit_Expand_FrameRate->setMinimumSize(QSize(145, 0));

        horizontalLayout->addWidget(lineEdit_Expand_FrameRate);

        label_21 = new QLabel(layoutWidget3);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout->addWidget(label_21);

        layoutWidget4 = new QWidget(groupBox_2);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(121, 290, 234, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_Expand_FPS = new QLineEdit(layoutWidget4);
        lineEdit_Expand_FPS->setObjectName(QStringLiteral("lineEdit_Expand_FPS"));
        lineEdit_Expand_FPS->setMinimumSize(QSize(145, 0));

        horizontalLayout_2->addWidget(lineEdit_Expand_FPS);

        label_19 = new QLabel(layoutWidget4);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_2->addWidget(label_19);

        layoutWidget5 = new QWidget(groupBox_2);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(121, 340, 195, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineEdit_Expand_GOP = new QLineEdit(layoutWidget5);
        lineEdit_Expand_GOP->setObjectName(QStringLiteral("lineEdit_Expand_GOP"));
        lineEdit_Expand_GOP->setMinimumSize(QSize(145, 0));

        horizontalLayout_3->addWidget(lineEdit_Expand_GOP);

        label_9 = new QLabel(layoutWidget5);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_3->addWidget(label_9);

        btnSave = new QPushButton(StreamSet);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(180, 580, 75, 23));
        btnUpGrade = new QPushButton(StreamSet);
        btnUpGrade->setObjectName(QStringLiteral("btnUpGrade"));
        btnUpGrade->setGeometry(QRect(550, 580, 75, 23));
        label = new QLabel(StreamSet);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 61, 16));
        label->setMinimumSize(QSize(10, 0));
        label->setMaximumSize(QSize(90, 16777215));
        btnClose = new QPushButton(StreamSet);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(790, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));
        comboBox_Channel = new QComboBox(StreamSet);
        comboBox_Channel->setObjectName(QStringLiteral("comboBox_Channel"));
        comboBox_Channel->setGeometry(QRect(130, 30, 141, 22));
        layoutWidget6 = new QWidget(StreamSet);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        layoutWidget7 = new QWidget(StreamSet);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);

        retranslateUi(StreamSet);

        QMetaObject::connectSlotsByName(StreamSet);
    } // setupUi

    void retranslateUi(QDialog *StreamSet)
    {
        StreamSet->setWindowTitle(QApplication::translate("StreamSet", "StreamSet", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("StreamSet", "\344\270\273\347\240\201\346\265\201", Q_NULLPTR));
        label_2->setText(QApplication::translate("StreamSet", "\347\274\226\347\240\201\346\250\241\345\274\217:", Q_NULLPTR));
        label_3->setText(QApplication::translate("StreamSet", "\345\270\247\347\216\207(FPS):", Q_NULLPTR));
        label_4->setText(QApplication::translate("StreamSet", "\347\240\201\346\265\201\346\216\247\345\210\266:", Q_NULLPTR));
        label_5->setText(QApplication::translate("StreamSet", "\347\224\273\350\264\250:", Q_NULLPTR));
        label_6->setText(QApplication::translate("StreamSet", "\347\240\201\347\216\207(Kb/S):", Q_NULLPTR));
        label_7->setText(QApplication::translate("StreamSet", "I\345\270\247\351\227\264\351\232\224(S):", Q_NULLPTR));
        label_18->setText(QApplication::translate("StreamSet", "\345\210\206\350\276\250\347\216\207:", Q_NULLPTR));
        label_8->setText(QApplication::translate("StreamSet", "(1~200)", Q_NULLPTR));
        label_17->setText(QApplication::translate("StreamSet", "(1~25)", Q_NULLPTR));
        label_20->setText(QApplication::translate("StreamSet", "(30~16384)", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("StreamSet", "\346\254\241\347\240\201\346\265\201", Q_NULLPTR));
        label_10->setText(QApplication::translate("StreamSet", "\347\274\226\347\240\201\346\250\241\345\274\217:", Q_NULLPTR));
        label_11->setText(QApplication::translate("StreamSet", "\345\210\206\350\276\250\347\216\207:", Q_NULLPTR));
        label_12->setText(QApplication::translate("StreamSet", "\345\270\247\347\216\207(FPS):", Q_NULLPTR));
        label_13->setText(QApplication::translate("StreamSet", "\347\240\201\346\265\201\346\216\247\345\210\266:", Q_NULLPTR));
        label_14->setText(QApplication::translate("StreamSet", "\347\224\273\350\264\250:", Q_NULLPTR));
        label_15->setText(QApplication::translate("StreamSet", "\347\240\201\347\216\207(Kb/S):", Q_NULLPTR));
        label_16->setText(QApplication::translate("StreamSet", "I\345\270\247\351\227\264\351\232\224(S):", Q_NULLPTR));
        label_21->setText(QApplication::translate("StreamSet", "(30~16384)", Q_NULLPTR));
        label_19->setText(QApplication::translate("StreamSet", "(1~25)", Q_NULLPTR));
        label_9->setText(QApplication::translate("StreamSet", "(1~200)", Q_NULLPTR));
        btnSave->setText(QApplication::translate("StreamSet", "\344\277\235\345\255\230\351\205\215\347\275\256", Q_NULLPTR));
        btnUpGrade->setText(QApplication::translate("StreamSet", "\346\233\264\346\226\260", Q_NULLPTR));
        label->setText(QApplication::translate("StreamSet", "\351\200\232\351\201\223\345\217\267\357\274\232", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StreamSet: public Ui_StreamSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMSET_H
